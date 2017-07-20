#include <math.h>

#include "ray.hh"

long double Ray::dist_to(Node* n) const
{
  /* FIXME */
  return 0 && n;
}

void Ray::rotate_once(unsigned nb_cones)
{
  /* FIXME */
  angle += (2 * M_PI) / nb_cones;
  return;
}

bool belongs_to(Node* n, Ray left, Ray right)
{
  /* FIXME */
  return n && left.origin == right.origin;
}

Ray bisector(Ray r1, Ray r2)
{
  return Ray(r1.origin, (r2.angle + r1.angle) / 2);
}

  
