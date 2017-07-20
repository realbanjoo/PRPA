#pragma once

#include <iostream>

#include "node.hh"

class Edge
{
  public :
    Node* from;
    Node* to;
    long double weight;

    Edge(Node* from, Node* to);
    bool operator < (const Edge& e) const;
    bool operator ==(const Edge& e) const;
    friend std::ostream& operator<<(std::ostream& o, Edge e);
};

#include "edge.hxx"
