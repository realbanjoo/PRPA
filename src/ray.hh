#pragma once

#include "node.hh"
#include "vect2.hh"

class Ray
{
  public:
    Node* origin;
    Vect2 dir;

    Ray(Node* ori, Vect2 dir);
    Ray(Node* ori, long double x, long double y);

    long double dist_to(Node* n);

    void rotate_once(unsigned nb_cones);
};

bool belongs_to(Node* n, Ray left, Ray right);

Ray bisector(Ray& r1, Ray& r2);

#include "ray.hxx"



