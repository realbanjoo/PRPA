#include <cmath>

#include "ray.hh"

long double Ray::dist_to(Node* n)
{
  Vect2 pt((n->x - origin->x), (n->y - origin->y));
  auto v2_ls = dir.len_squared();
  Vect2 proj = dir * (pt.dot(dir) / v2_ls);
  return sqrt(pow(2, proj.x) + pow(2, proj.y));
  
}

void Ray::rotate_once(unsigned nb_cones)
{
  double angle = (2 * M_PI) / nb_cones;
  auto cs = std::cos(angle);
  auto sn = std::sin(angle);
  double x = dir.x;
  double y = dir.y;
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

  return left.origin == right.origin 
    && left.dir.cross(r.dir) * left.dir.cross(right.dir) >= 0
    && right.dir.cross(r.dir) * right.dir.cross(left.dir) >= 0;
}

Ray bisector(Ray& r1, Ray& r2)
{
  return Ray(r1.origin, (r1.dir.x + r2.dir.x) / 2, (r1.dir.y + r2.dir.y) / 2);
}

  
