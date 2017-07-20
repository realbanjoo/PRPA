#pragma once

#include "node.hh"

class Ray
{
  public:
    Node* origin;
    double angle;

    Ray(Node* ori, double angle);

    long double dist_to(Node* n) const;

    void rotate_once(unsigned nb_cones);
};

bool belongs_to(Node* n, Ray left, Ray right);

Ray bisector(Ray r1, Ray r2);

#include "ray.hxx"



