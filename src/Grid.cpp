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
            ++grid_[Point<int>{x,y}];
            angle += LIDAR_ANGLE_INCREMENT;
        }
    }
    saveGridToImage();
}

void Grid::setObjects(std::set<Object, associateDetections> const& objects)
{
    centersAndInliers_.clear();
    for (auto object: objects)
    {
        // std::cout << static_cast<int>(object.center.x/ GRID_CELL_SIZE) << ", " << static_cast<int>(object.center.y/ GRID_CELL_SIZE) << std::endl;
        centersAndInliers_.insert(Point<int>{static_cast<int>(object.center.x/ GRID_CELL_SIZE), 
                                  static_cast<int>(object.center.y/ GRID_CELL_SIZE)});
        for (auto inlier: object.inliers)
        {
            centersAndInliers_.insert(Point<int>{static_cast<int>(inlier.x/ GRID_CELL_SIZE), 
                                  static_cast<int>(inlier.y/ GRID_CELL_SIZE)});
        }
    }
    // std::cout << centersAndInliers_.size() << std::endl;
}

void Grid::setTracks(std::vector<Track> const& tracks)
{
    for (auto track: tracks)
    {
        tracks_.insert(Point<int>{static_cast<int>(track.currentPosition.x/ GRID_CELL_SIZE), 
                                  static_cast<int>(track.currentPosition.y/ GRID_CELL_SIZE)});
        for (auto position: track.history)
        {
            tracks_.insert(Point<int>{static_cast<int>(position.x/ GRID_CELL_SIZE), 
                                  static_cast<int>(position.y/ GRID_CELL_SIZE)});
        }
    }
}

void Grid::saveGridToImage()
{
    int width = 1400, height = 800; 
    FILE* pgmimg; 
    pgmimg = fopen("pgmimg.pgm", "wb"); 
  
    fprintf(pgmimg, "P2\n");  
    fprintf(pgmimg, "%d %d\n", width, height);  
  
    fprintf(pgmimg, "255\n");   
    for (int i = height/2; i > -height/2; --i) 
    { 
        for (int j = width/2; j > -width/2; --j) 
        {   
            auto it1 = centersAndInliers_.find(Point<int>{j, i});
            auto it2 = tracks_.find(Point<int>{j, i});
            if (it1 != centersAndInliers_.end() || it2 != tracks_.end())
            {
                fprintf(pgmimg, "%d ", 255); 
                // std::cout << "Object position: ( " << i << ", " << j << " )" << std::endl;
            }
            else
            {
                auto it = grid_.find(Point<int>{j, i});
                if (it != grid_.end())
                {
                    fprintf(pgmimg, "%d ", 75); 
                }
                else
                {
                    fprintf(pgmimg, "%d ", 0); 
                }
            }
            
            
        } 
        fprintf(pgmimg, "\n"); 
    } 
    fclose(pgmimg); 
}

