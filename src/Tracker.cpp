#include "../include/Tracker.hpp"

void Tracker::track(std::vector<LidarScan> const& lidarScans)
{
    ArcDetector detector;
    Grid grid;

    for (size_t i = 0; i < lidarScans.size(); ++i)
    {
        std::cout << i << std::endl;
        for (size_t id = 0; id < tracks_.size(); ++id)
        {
            tracks_[id].history.push_back(tracks_[id].currentPosition);
            filters_[id].predict(lidarScans[i].timestamp);
        }
        auto objects = detector.detect(lidarScans[i]);
        for (auto object : objects)
        {
            // std::cout << "Object: (" << static_cast<int>(object.center.x/GRID_CELL_SIZE) << ", " 
            // << static_cast<int>(object.center.y/GRID_CELL_SIZE) << ") | Count:" << object.numInliers << std::endl;

            if (tracks_.empty())
            {
                addNewTrack(object);
            }
            else
            {
                auto id = associateObjectToTrack(object);
                if (object.center.distance(tracks_[id].currentPosition) < ASSOCIATION_DISTANCE_TRACKING)
                {
                    updateTrack(id, object);
                }
                else
                {
                    addNewTrack(object);
                }
            }  
        }
        
        for (size_t id = 0; id < tracks_.size(); ++id)
        {
            auto state = filters_[id].getCurrentState();
            tracks_[id].currentPosition = state.position;
            tracks_[id].currentVelocity = sqrt( pow(state.velocity.x, 2) + pow(state.velocity.y, 2) );
            if (tracks_[id].currentVelocity > 0.1) 
            {
                tracks_[id].isMoving = true;
            }
            else
            {
                tracks_[id].isMoving = false;
            }
            
            if (id == getMostConfidentTrack())
            {
                std::cout << "Track#" << tracks_[id].ID 
                << ": ( " << static_cast<int>(tracks_[id].currentPosition.x/ GRID_CELL_SIZE) 
                << ", " << static_cast<int>(tracks_[id].currentPosition.y/ GRID_CELL_SIZE) 
                << " ) | Velocity: " << tracks_[id].currentVelocity 
                << " | Confidence: " << tracks_[id].confidence << std::endl;
                // std::cout  << tracks_[id].currentPosition.x
                // << ", " << tracks_[id].currentPosition.y
                // << ", " << tracks_[id].currentVelocity << std::endl;
            }
        }

        std::cout << std::endl << std::endl;

        if (i == lidarScans.size()-1)
        {
            grid.populateGrid(lidarScans[i]);
            grid.setObjects(objects);
            grid.setTracks(tracks_);
            grid.saveGridToImage();
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

void Tracker::updateTrack(size_t id, Object const& object)
{
    // std::cout << "Associated Track#" << tracks_[id].ID 
    // << ": ( " << static_cast<int>(tracks_[id].currentPosition.x/ GRID_CELL_SIZE) 
    // << ", " << static_cast<int>(tracks_[id].currentPosition.y/ GRID_CELL_SIZE) 
    // << " ) | Confidence: " << tracks_[id].confidence << std::endl;

    Observation observation{object.center, object.numInliers};
    filters_[id].update(observation);
    tracks_[id].confidence += object.numInliers;

    // std::cout << "Updated Track#" << tracks_[id].ID
    // << ": ( " << static_cast<int>(tracks_[id].currentPosition.x/ GRID_CELL_SIZE) 
    // << ", " << static_cast<int>(tracks_[id].currentPosition.y/ GRID_CELL_SIZE) 
    // << " ) | Confidence: " << tracks_[id].confidence << std::endl;
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