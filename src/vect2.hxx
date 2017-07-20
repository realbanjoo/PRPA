
inline Vect2::Vect2(long double x, long double y)
  : x(x), y(y)
{}

inline long double Vect2::dot(const Vect2& v2)
{
  return x * v2.x + y * v2.y; 
}

inline long double Vect2::cross(const Vect2& v2)
{
  return x * v2.y - y * v2.x; 
}

inline long double Vect2::len_squared()
{
  return dot(*this); 
}

template<typename U>
Vect2 operator *(Vect2& v, U scalar)
{
  return Vect2(v.x * scalar, v.y * scalar);
}




