#include "../include/Grid.hpp"

Grid::Grid(double const cellSize, double const width, double const height)
:cellSize_{cellSize},
width_{width},
height_{height}
{}

void Grid::populateGrid(LidarScan const& scan)
{
    grid_.clear();
    auto angle = LIDAR_MIN_ANGLE;
    for (auto const& r : scan.ranges)
    {
        if (r < LIDAR_MAX_RANGE)
        {
            auto x = static_cast<int>(r*cos(angle)/cellSize_);
            auto y = static_cast<int>(r*sin(angle)/cellSize_);
            ++grid_[Point{x,y}];
            angle += LIDAR_ANGLE_INCREMENT;
        }
    }
    saveGridToImage();
}

std::unordered_map<Point, int, PointHash> const& Grid::getGrid()
{
    return grid_;
}

void Grid::saveGridToImage()
{
    int width = 1000, height = 800; 
    FILE* pgmimg; 
    pgmimg = fopen("pgmimg.pgm", "wb"); 
  
    fprintf(pgmimg, "P2\n");  
    fprintf(pgmimg, "%d %d\n", width, height);  
  
    fprintf(pgmimg, "255\n");   
    for (int i = 0; i < height; i++) 
    { 
        for (int j = 0; j < width; j++) 
        {   
            auto it = grid_.find(Point{i-10, j-10});
            if (it != grid_.end())
            {
                fprintf(pgmimg, "%d ", 255); 
            }
            else
            {
                fprintf(pgmimg, "%d ", 0); 
            }
        } 
        fprintf(pgmimg, "\n"); 
    } 
    fclose(pgmimg); 
}

