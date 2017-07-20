#include "node.hh"
#include "vect2.hh"

inline Ray::Ray(Node* ori, Vect2 dir)
: origin(ori), dir(dir){}

inline Ray::Ray(Node* ori, long double x, long double y)
: origin(ori), dir(Vect2(x, y)){}

