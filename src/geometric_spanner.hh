#pragma once

#include <map>
#include <vector>

#include "node.hh"
#include "edge.hh"


class Geometric_Spanner
{
  private :
    bool S_t_path_exist(const std::vector<Edge> span_edges, Edge e,
        const long double t);
    bool P_t_path_exist(const std::vector<Edge> span_edges, Edge e,
        const long double t);
  public :
    std::vector<Node*> points;
    std::vector<Edge> span;

    Geometric_Spanner (std::vector<Node*> points);
    Geometric_Spanner (std::string file, unsigned length);
    ~Geometric_Spanner();
    void S_greedy_Spanner (const long double t);
    void P_greedy_Spanner (const long double t);
    void export_As_Dot(std::string file);
    void export_As_Dot();
    void clear();
};


