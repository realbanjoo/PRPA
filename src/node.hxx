
inline Node::Node (std::string name, long double x, long double y)
  : name(name), x(x), y(y)
{}

inline Node::Node ()
  : name(""), x(0), y(0)
{}

inline std::ostream& operator<<(std::ostream& o, Node n)
{
  return o << "N{" << n.x << ", " << n.y << "}";
}


