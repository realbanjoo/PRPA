#pragma once

#include <map>
#include <utility>
#include <vector>

#include "edge.hh"
#include "node.hh"
#include "ray.hh"


class Geometric_Spanner
{
  private :
    bool S_t_path_exist(const std::vector<Edge> span_edges, Edge e,
        const long double t);
    bool P_t_path_exist(const std::vector<Edge> span_edges, Edge e,
        const long double t);

    std::vector<Node*> compute_cone(unsigned nb_cones, Ray init);
    std::vector<std::vector<Node*>> compute_cones_for(unsigned nb_cones,
        Ray init);
  public :
    std::vector<Node*> points;
    std::vector<Edge> span;

    Geometric_Spanner (std::vector<Node*> points);
    Geometric_Spanner (std::string file, unsigned length);
    ~Geometric_Spanner();

    void S_greedy_Spanner (const long double t);
    void P_greedy_Spanner (const long double t);


    static bool compare(std::pair<Node*, long double> i,
        std::pair<Node*, long double> j);
    void S_theta_graph(unsigned nb_cones);


    void export_As_Dot(std::string file);
    void export_As_Dot();
    void clear();
};


