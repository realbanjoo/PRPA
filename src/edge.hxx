#include <tgmath.h>

inline Edge::Edge(Node* from, Node* to)
  : from(from), to(to), weight(0)
{
  long double x_dis = to->x - from->x;
  long double y_dis = to->y - from->y;
  weight = sqrtl((x_dis * x_dis) + (y_dis * y_dis));
}

inline bool Edge::operator < (const Edge& e) const
{
  return weight < e.weight;
}

inline bool Edge::operator == (const Edge& e) const
{
  return from == e.from && to == e.to;
}

inline std::ostream& operator<<(std::ostream& o, Edge e)
{
  return o << "E{" << *e.from << ", " << *e.to << ", " << e.weight << "}";
}



