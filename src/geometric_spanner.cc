#include <algorithm>
#include <fstream>
#include <map>
#include <vector>


/* Parallel */
#include <functional>
#include <iterator>
#include <mutex>
#include <tbb/tbb.h>

#include "geometric_spanner.hh"
#include "ray.hh"

Geometric_Spanner::Geometric_Spanner (std::vector<Node*> points) 
  : points(points)
{}

Geometric_Spanner::Geometric_Spanner (std::string file, unsigned length) 
{
  std::ifstream i_f(file);
  if (i_f.is_open())
  {
    std::string line;
    std::getline(i_f,  line);
    for (unsigned i = 0; i < length && i_f; i++)
    {
      std::getline(i_f,  line);
      Node* n = new Node();
      std::stringstream str(line);
      std::string val;
      std::getline(str, val, ',');
      std::replace(val.begin(), val.end(), ' ', '_');
      n->name = val;
      std::getline(str, val, ',');
      try
      {
        n->x = std::stold(val);
      }
      catch (std::exception& e) {}
      std::getline(str, val, ',');
      try
      {
        n->y = std::stold(val);
      }
      catch (std::exception& e) {}
      points.push_back(n);
    }
    i_f.close();
  }
}

Geometric_Spanner::~Geometric_Spanner()
{
  for (auto i : points)
    delete(i);
}

void Geometric_Spanner::clear()
{
  span.clear();
}


/* GREEDY SPANNER */
/* SERIAL */

bool Geometric_Spanner::S_t_path_exist(const std::vector<Edge> span_edges, Edge e,
    const long double t)
{
  // Use Dijkstra algorithm
  std::vector<Node*> p;
  std::map<Node*, long double> dist;
  dist[e.from] = 0;
  p.push_back(e.from);
  while (!p.empty())
  {
    Node* n = p.back();
    p.pop_back();
    /* Optimisation: Stops if the shortest distance is already too big */
    if (dist[n] > t * e.weight)
      continue;
    /* Destination reached */
    if (n == e.to)
      return true;
    /* Neighbours discovery */
    for (Edge ed : span_edges)
    {
      if (ed.from == n)
      {
        if (dist.find(ed.to) == dist.end()
            || dist[ed.to] > ed.weight + dist[n])
        {
          dist[ed.to] = dist[n] + ed.weight;
          p.push_back(ed.to);
        }
      }
      if (ed.to == n)
      {
        if (dist.find(ed.from) == dist.end()
            || dist[ed.from] > ed.weight + dist[n])
        {
          dist[ed.from] = dist[n] + ed.weight;
          p.push_back(ed.from);
        }
      }
    }
    /* Sort to keep the priority of short distances */
    std::sort(p.begin(), p.end(),
      [&](Node* i, Node* j){ return dist[i] > dist[j]; });
  }
  return false;
}

void Geometric_Spanner::S_greedy_Spanner (const long double t)
{
  std::vector<Edge> all_edges;
  span.clear();
  // Computes all possible edges of the complete graph
  for (auto i = points.begin(); i < points.end(); i++)
  {
    for (auto j = i + 1; j < points.end(); j++)
    {
      all_edges.emplace_back(*i, *j);
    }
  }
  // Sort them by shortest distance
  std::sort(all_edges.begin(), all_edges.end());
  // Add edge e iff no t-path exist between the two nodes of e
  // unsigned max = all_edges.size();
  for (Edge& e : all_edges)
  {
    if (!S_t_path_exist(span, e, t))
    {
      span.push_back(e);
    } 
  }
  // Debug Print
  /*
     std::cout << "all edges:" << std::endl;
     for (Edge e : all_edges)
     std::cout << e << std::endl;
     std::cout << "Span:" << std::endl;
     for (Edge e : span)
     std::cout << e << std::endl;
     */
  return;
}

/* PARALLEL */

bool Geometric_Spanner::P_t_path_exist(const std::vector<Edge> span_edges, Edge e,
    const long double t)
{
  // Use Dijkstra algorithm
  std::vector<Node*> p;
  std::mutex p_mutex;
  tbb::concurrent_unordered_map<Node*, long double> dist;
  dist[e.from] = 0;
  p.push_back(e.from);

  while (!p.empty())
  {
    Node* n = p.back();
    p.pop_back();
    /* Optimisation: Stops if the shortest distance is already too big */
    if (dist[n] > t * e.weight)
      continue;
    /* Destination reached */
    if (n == e.to)
      return true;
    /* Neighbours discovery */

    /* WORKS ONLY IF NO DOUBLE EDGES EXIST (if there are, two different
     * discoveries could modify the dist value, and nothing guarantes that the
     * last one will be the smaller).  */
    auto work = [&] (const Edge &ed) {
      if (ed.from == n)
      {
        if (dist.find(ed.to) == dist.end()
            || dist[ed.to] > ed.weight + dist[n])
        {
          dist[ed.to] = dist[n] + ed.weight;
          std::lock_guard<std::mutex> guard(p_mutex);
          p.push_back(ed.to);
        }
      }
      else if (ed.to == n)
      {
        if (dist.find(ed.from) == dist.end()
            || dist[ed.from] > ed.weight + dist[n])
        {
          dist[ed.from] = dist[n] + ed.weight;
          std::lock_guard<std::mutex> guard(p_mutex);
          p.push_back(ed.from);
        }
      }
      return;
    };

    tbb::parallel_for_each(span_edges.begin(), span_edges.end(), work);

    /* Sort to keep the priority of short distances */
    std::sort(p.begin(), p.end(),
      [&](Node* i, Node* j){ return dist[i] > dist[j]; });
  }
  return false;
}

void Geometric_Spanner::P_greedy_Spanner (const long double t)
{
  tbb::concurrent_vector<Edge> p_all_edges;
  span.clear();
  
  // Computes all possible edges of the complete graph
  const auto i_terator = [&] (tbb::blocked_range<std::vector<Node*>::iterator> &r) {
    for (auto i = r.begin(); i < r.end(); i++)
    {
      const auto j_terator = [&] (Node* &j) {
        p_all_edges.emplace_back(*i, j);
      };
      tbb::parallel_for_each(std::next(i, 1), points.end(), j_terator);
    }
  };

  tbb::parallel_for(
      tbb::blocked_range<std::vector<Node*>::iterator>
      (points.begin(), points.end()), i_terator);

  // Sort them by shortest distance
  std::sort(p_all_edges.begin(), p_all_edges.end());
  
  // Add edge e iff no t-path exist between the two nodes of e
  // unsigned max = all_edges.size();
  
  for (Edge& e : p_all_edges)
  {
    if (!P_t_path_exist(span, e, t))
    {
      span.push_back(e);
    } 
  }
  
  // Debug Print
  /*
     std::cout << "all edges:" << std::endl;
     for (Edge e : all_edges)
     std::cout << e << std::endl;
     std::cout << "Span:" << std::endl;
     for (Edge e : span)
     std::cout << e << std::endl;
     */
  return;
}


/* THEATA GRAPH */
/* SERIAL */


std::vector<Node*> Geometric_Spanner::compute_cone(unsigned nb_cones, Ray init)
{
  Ray right = init;
  right.rotate_once(nb_cones);
  std::vector<Node*> nodes;
  for (auto p : points)
    if (belongs_to(p, init, right))
      nodes.push_back(p);
  return nodes;
}

std::vector<std::vector<Node*>> Geometric_Spanner::compute_cones_for(unsigned nb_cones,
    Ray init)
{
  std::vector<std::vector<Node*>> res;
  for (unsigned i = 0; i < nb_cones; i++)
  {
    res.push_back(compute_cone(nb_cones, init));
    init.rotate_once(nb_cones);
  }
  return res;
}




void Geometric_Spanner::export_As_Dot(std::string file)
{
  std::ofstream of(file);
  if (of.is_open())
  {
    of << "graph geometric_spanner_greedy_spanner {" << std::endl;;
    of << "outputorder=edgesfirst;" << std::endl;
    of << "node[fontsize=8, style=filled, margin=\"0.05,0.03\"];" << std::endl;
    for (auto n : points)
      of << n->name << " [pos=\"" << n->x * 5 << "," << n->y * 5 << "!\"];" << std::endl;
    for (auto e : span)
      of << e.from->name << " -- " << e.to->name << std::endl;
    of << "}" << std::endl;
  }
  of.close();
  return;
}

void Geometric_Spanner::export_As_Dot()
{
  return export_As_Dot("output.dot");
}



