#include "../include/Tracker.hpp"

void Tracker::track(std::vector<LidarScan> const& lidarScans)
{
    ArcDetector detector;
    Grid grid;

    for (size_t i = 0; i < lidarScans.size(); ++i)
    {
        std::cout << i << std::endl;
        auto objects = detector.detect(lidarScans[i]);
        for (auto object : objects)
        {
            std::cout << "Object: (" << static_cast<int>(object.center.x/GRID_CELL_SIZE) << ", " 
            << static_cast<int>(object.center.y/GRID_CELL_SIZE) << ") | Count:" << object.numInliers << std::endl;

            if (tracks_.empty())
            {
                addNewTrack(object);
            }
            else
            {
                auto id = findClosestTrackToObject(object);
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

        std::cout << std::endl << std::endl;

        if (i == 250)
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
    Track track{tracks_.size(), object.numInliers, object.center, std::vector<Point<double>>{}};
    tracks_.push_back(track);
    std::cout << "New Track#" << track.ID 
    << ": ( " << static_cast<int>(track.currentPosition.x/ GRID_CELL_SIZE) 
    << ", " << static_cast<int>(track.currentPosition.y/ GRID_CELL_SIZE) 
    << " ) | Confidence: " << track.confidence << std::endl;
}

size_t Tracker::findClosestTrackToObject(Object const& object)
{
    double minimumDistance = 1000.0;
    size_t trackID = 1000;
    for (size_t id = 0; id < tracks_.size(); ++id)
    {
        auto distance = object.center.distance(tracks_[id].currentPosition);
        if (distance < minimumDistance)
        {
            minimumDistance = distance;
            trackID = id;
        }
    }
    std::cout << "Closest Track# " << trackID << ": " << minimumDistance << std::endl;
    return trackID;  
}

void Tracker::updateTrack(size_t id, Object const& object)
{
    std::cout << "Associated Track#" << tracks_[id].ID 
    << ": ( " << static_cast<int>(tracks_[id].currentPosition.x/ GRID_CELL_SIZE) 
    << ", " << static_cast<int>(tracks_[id].currentPosition.y/ GRID_CELL_SIZE) 
    << " ) | Confidence: " << tracks_[id].confidence << std::endl;

    tracks_[id].history.push_back(tracks_[id].currentPosition);
    tracks_[id].currentPosition = object.center;
    tracks_[id].confidence = object.numInliers;

    std::cout << "Updated Track#" << tracks_[id].ID
    << ": ( " << static_cast<int>(tracks_[id].currentPosition.x/ GRID_CELL_SIZE) 
    << ", " << static_cast<int>(tracks_[id].currentPosition.y/ GRID_CELL_SIZE) 
    << " ) | Confidence: " << tracks_[id].confidence << std::endl;
}