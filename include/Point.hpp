#ifndef POINT_HPP
#define POINT_HPP

#include <functional>

struct Point
{
    int x;
    int y;

	Point(int x, int y)
    :x{x}, y{y} 
    {}

	bool operator==(Point const& p) const
	{
		return ((x == p.x) && (y == p.y));
	}
};

struct PointHash
{
    std::size_t operator()(Point const& p) const noexcept
    {
        std::size_t h1 = std::hash<int>{}(p.x);
        std::size_t h2 = std::hash<int>{}(p.y);
        return h1 ^ (h2 << 1);
    }
};

#endif /* POINT_HPP */
