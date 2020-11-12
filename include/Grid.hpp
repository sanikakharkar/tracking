#ifndef GRID_HPP
#define GRID_HPP

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <set>
#include "LidarScan.hpp"
#include "Point.hpp"
#include "Object.hpp"
#include "Track.hpp"

// A primitive tool for visualizing the data and output
// Projects LIDAR scans, object detections and tracks to a grid and saves
// the grid as a PGM image
class Grid
{
public:
    ~Grid() = default;
    Grid(double const cellSize = GRID_CELL_SIZE, 
         int const width = GRID_WIDTH, 
         int const height = GRID_HEIGHT);

    void populateGrid(LidarScan const& scan);

    void setObjects(std::set<Object, associateDetections> const& objects);

    void setTracks(std::vector<Track> const& tracks);

    void saveGridToImage();

protected:
    double const cellSize_;
    int const width_;
    int const height_;

    std::unordered_map<Point<int>, int, PointHash<int>> grid_;

    std::set<Point<int>> centersAndInliers_;
    std::set<Point<int>> tracks_;

};


#endif /* GRID_HPP */