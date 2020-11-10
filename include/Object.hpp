#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include "constants.hpp"
#include "Point.hpp"

struct Object
{
    Point<double> center;
    int numInliers;
    std::vector<Point<double>> inliers;

    bool operator==(Object const& ob) const
    {
        return (center.distance(ob.center) < ASSOCIATION_DISTANCE_DETECTION);
    }
};

struct associateDetections
{
    bool operator()(const Object& o1, const Object& o2)
    {
        if ( o1.center.distance(o2.center) < ASSOCIATION_DISTANCE_DETECTION )
        {
            return false;
        }
        else
        {
            return (o1.center.x < o2.center.x) || 
            ((o1.center.x == o2.center.x) && (o1.center.y < o2.center.y));
        }
        
    }
};


#endif /* OBJECT_HPP */