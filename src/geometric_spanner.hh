#pragma once

#include <map>
#include <vector>

#include "node.hh"
#include "edge.hh"


class Geometric_Spanner
{
  private :
    bool t_path_exist(std::vector<Edge> span_edges, Edge e,
        const long double t);
    bool OPT_t_path_exist(std::vector<Edge> span_edges, Edge e,
        const long double t);
  public :
    std::vector<Node*> points;
    std::vector<Edge> span;

    Geometric_Spanner (std::vector<Node*> points);
    Geometric_Spanner (std::string file, unsigned length);
    ~Geometric_Spanner();
    void greedy_Spanner (const long double t);
    void OPT_greedy_Spanner (const long double t);
    void export_As_Dot(std::string file);
    void export_As_Dot();
    void clear();
};


