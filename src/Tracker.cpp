#include "../include/Tracker.hpp"

void Tracker::track(std::vector<LidarScan> const& lidarScans)
{
    for (size_t i = 0; i < lidarScans.size(); ++i)
    {
        for (size_t id = 0; id < tracks_.size(); ++id)
        {
            tracks_[id].history.push_back(tracks_[id].currentPosition);
            filters_[id].predict(lidarScans[i].timestamp);
        }
        auto objects = detector_.detect(lidarScans[i]);
        for (auto object : objects)
        {
            if (tracks_.empty())
            {
                addNewTrack(object);
            }
            else
            {
                auto id = associateObjectToTrack(object);
                if (object.center.distance(tracks_[id].currentPosition) < ASSOCIATION_DISTANCE_TRACKING)
                {
                    Observation observation{object.center, object.numInliers};
                    filters_[id].update(observation);
                    tracks_[id].confidence += object.numInliers;
                }
                else
                {
                    addNewTrack(object);
                }
            }  
        }

        updateTracks();
        
        // Save the last scan, objects and tracks to an image
        if (i == lidarScans.size()-1)
        {
            grid_.populateGrid(lidarScans[i]);
            grid_.setObjects(objects);
            grid_.setTracks(tracks_);
            grid_.saveGridToImage();
        }
    }
}

void Tracker::addNewTrack(Object const& object)
{
    Track track{tracks_.size(), object.numInliers, object.center, 0.0, false, std::vector<Point<double>>{}};
    KalmanFilter filter;
    filter.initialize({object.timestamp, {object.center.x, object.center.y}, {0.0, 0.0}});
    tracks_.push_back(track);
    filters_.push_back(filter);
}

size_t Tracker::associateObjectToTrack(Object const& object)
{
    double minimumDistance = std::numeric_limits<double>::max();
    size_t trackID = std::numeric_limits<size_t>::max();
    for (size_t id = 0; id < tracks_.size(); ++id)
    {
        auto distance = object.center.distance(tracks_[id].currentPosition);
        if (distance < minimumDistance)
        {
            minimumDistance = distance;
            trackID = id;
        }
    }
    return trackID;  
}

void Tracker::updateTracks()
{
    for (size_t id = 0; id < tracks_.size(); ++id)
    {
        auto state = filters_[id].getCurrentState();
        tracks_[id].currentPosition = state.position;
        tracks_[id].currentVelocity = sqrt( pow(state.velocity.x, 2) + pow(state.velocity.y, 2) );
        
        if (id == getMostConfidentTrack())
        {
            std::cout << std::setprecision(17) << "Time: " << state.time
            <<  std::setprecision(3) << " | Position: ( " << tracks_[id].currentPosition.x 
            << ", " << tracks_[id].currentPosition.y
            << " ) | Velocity: " << tracks_[id].currentVelocity 
            << " | Confidence: " << tracks_[id].confidence << std::endl;
        }
    }
}

size_t Tracker::getMostConfidentTrack()
{
    int maxConfidence = 0;
    size_t trackID = std::numeric_limits<size_t>::max();

    for (size_t id = 0; id < tracks_.size(); ++id)
    {
        if (tracks_[id].confidence > maxConfidence)
        {
            maxConfidence = tracks_[id].confidence;
            trackID = id;
        }
    }
    return trackID;
}