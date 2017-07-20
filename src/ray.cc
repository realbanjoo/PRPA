#include <cmath>
#include <iostream>

#include "ray.hh"

long double Ray::dist_to(Node* n) const
{
  /* FIXME */
  return 0 && n;
}

void Ray::rotate_once(unsigned nb_cones)
{
  double angle = (2 * M_PI) / nb_cones;
  auto cs = std::cos(angle);
  auto sn = std::sin(angle);
  double x = dir.x;
  double y = dir.y;
  std::cout << "angle=" << angle << std::endl
    << "cs="<< cs << std::endl
    << "sn=" << sn << std::endl
    << "x=" << x << std::endl
    << "y=" << y << std::endl;
  auto px = (x * cs) - (y * sn);
  auto py = (x * sn) + (y * cs);
  dir.x = px;
  dir.y = py;
  return;
}

bool belongs_to(Node* n, Ray left, Ray right)
{
  Node* ori = left.origin;
  Ray r(ori, n->x - ori->x, n->y - ori->y);

  return left.origin == n && right.origin == n 
    && left.dir.cross(r.dir) * left.dir.cross(right.dir) >= 0
    && right.dir.cross(r.dir) * right.dir.cross(left.dir) >= 0;
}

Ray bisector(Ray& r1, Ray& r2)
{
  return Ray(r1.origin, (r1.dir.x + r2.dir.x) / 2, (r1.dir.y + r2.dir.y) / 2);
}

  
