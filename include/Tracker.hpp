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

// The main tracking algorithm is implemented in this class.
// For each scan, it does the following:
//      1. Run the filter's prediction step for existing tracks
//      2. Detect objects from scan
//      3. Associate objects with tracks
//      4. Add new tracks for unassociated objects
//      5. Run the filter's update step for associated tracks
//      6. Save all tracks

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



