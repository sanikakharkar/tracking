#ifndef TRACK_HPP
#define TRACK_HPP

#include <vector>
#include "Point.hpp"

struct Track
{
    size_t ID;
    int confidence;
    Point<double> currentPosition;
    double currentVelocity;
    bool isMoving;
    std::vector<Point<double>> history;
};

#endif /* TRACK_HPP */