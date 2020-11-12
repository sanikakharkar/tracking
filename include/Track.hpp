#ifndef TRACK_HPP
#define TRACK_HPP

#include <vector>
#include "Point.hpp"

// A holder for tracks.
struct Track
{
    size_t ID;
    int confidence;
    Point<double> currentPosition;
    double currentVelocity;
    std::vector<Point<double>> history;
};

#endif /* TRACK_HPP */