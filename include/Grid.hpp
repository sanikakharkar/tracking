#ifndef GRID_HPP
#define GRID_HPP

#include <unordered_map>
#include <iostream>
#include "LidarScan.hpp"
#include "Point.hpp"

class Grid
{
public:
    ~Grid() = default;
    Grid(double const cellSize = GRID_CELL_SIZE, 
         double const width = GRID_WIDTH, 
         double const height = GRID_HEIGHT);

    void populateGrid(LidarScan const& scan);

    std::unordered_map<Point, int, PointHash> const& getGrid();

    void saveGridToImage();

protected:
    double const cellSize_;
    double const width_;
    double const height_;

    std::unordered_map<Point, int, PointHash> grid_;


};


#endif /* GRID_HPP */