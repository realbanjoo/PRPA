#pragma once


class Vect2
{

  public:
    long double x;
    long double y;

    Vect2(long double x, long double y);

    long double dot(const Vect2& v2);
    long double cross(const Vect2& v2);
    long double len_squared();


};

template<typename U>
Vect2 operator *(Vect2& v, U scalar);

#include "vect2.hxx"
