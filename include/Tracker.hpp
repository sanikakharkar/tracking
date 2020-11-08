#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <vector>
#include "LidarScan.hpp"
#include "Grid.hpp"

class Tracker
{
public:
    ~Tracker() = default;

    void track(std::vector<LidarScan> const& lidarScans);
    
};

#endif /* TRACKER_HPP */



