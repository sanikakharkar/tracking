#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <iomanip>
#include <vector>
#include <map>
#include "Track.hpp"
#include "LidarScan.hpp"
#include "Grid.hpp"
#include "ArcDetector.hpp"
#include "KalmanFilter.hpp"

class Tracker
{
public:
    ~Tracker() = default;

    void track(std::vector<LidarScan> const& lidarScans);

protected:
    ArcDetector detector_;
    Grid grid_;
    std::vector<Track> tracks_;
    std::vector<KalmanFilter> filters_;

    void addNewTrack(Object const& object);

    size_t associateObjectToTrack(Object const& object);

    void updateTracks();

    size_t getMostConfidentTrack();
    
};

#endif /* TRACKER_HPP */



