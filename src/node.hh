#pragma once
#include <iostream>
#include <string>

class Node
{
  public :
    std::string name;
    long double x;
    long double y;

    Node (std::string name, long double x, long double y);
    Node ();
    friend std::ostream& operator<<(std::ostream& o, Node n);
};

#include "node.hxx"
