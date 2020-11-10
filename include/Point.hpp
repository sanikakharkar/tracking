#ifndef POINT_HPP
#define POINT_HPP

#include <functional>
#include <math.h>

template<typename T>
struct Point
{
    T x;
    T y;

    Point() : x(0), y(0) {}

	Point(T x, T y)
    :x{x}, y{y} 
    {}

	bool operator==(Point<T> const& p) const
	{
		return ((x == p.x) && (y == p.y));
	}

    bool operator<(Point<T> const& p) const 
    {
        return ((x < p.x) || ((x == p.x) && (y < p.y)));
    }

    T distance(Point<T> const& p) const
    {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
};

template<typename T>
struct PointHash
{
    std::size_t operator()(Point<T> const& p) const noexcept
    {
        std::size_t h1 = std::hash<T>{}(p.x);
        std::size_t h2 = std::hash<T>{}(p.y);
        return h1 ^ (h2 << 1);
    }
};

#endif /* POINT_HPP */
