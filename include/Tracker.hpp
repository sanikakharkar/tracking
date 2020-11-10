#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <vector>
#include <map>
#include "Track.hpp"
#include "LidarScan.hpp"
#include "Grid.hpp"
#include "ArcDetector.hpp"

class Tracker
{
public:
    ~Tracker() = default;

    void track(std::vector<LidarScan> const& lidarScans);

protected:
    std::vector<Track> tracks_;

    void addNewTrack(Object const& object);

    size_t findClosestTrackToObject(Object const& object);

    void updateTrack(size_t id, Object const& object);
    
};

#endif /* TRACKER_HPP */



