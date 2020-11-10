#include "../include/ArcDetector.hpp"

ArcDetector::ArcDetector(double const radius)
:radius_{radius}
{}

std::set<Object, associateDetections>& ArcDetector::detect(LidarScan const& scan)
{
    objects_.clear();
    for (size_t i = 0; i < scan.ranges.size() - POINT_FIT_OFFSET; ++i)
    {
        auto angle1 = LIDAR_MIN_ANGLE + i*LIDAR_ANGLE_INCREMENT;
        Point<double> p1{ scan.ranges[i]*cos(angle1), 
                          scan.ranges[i]*sin(angle1)};
        auto angle2 = LIDAR_MIN_ANGLE + (i + POINT_FIT_OFFSET)*LIDAR_ANGLE_INCREMENT;
        Point<double> p2{ scan.ranges[i + POINT_FIT_OFFSET]*cos(angle2),
                          scan.ranges[i + POINT_FIT_OFFSET]*sin(angle2)};

        if (p1.distance(p2) < 2*radius_)
        {
            auto center = findArcCenterGivenRadius(p1, p2);
            auto inliers = getInliersForCircle(i ,scan, center);

            if (inliers.size() > MINIMUM_INLIERS)
            {
                // std::cout << "Center: (" << center.x << ", " << center.y << ") | Count:" << numPoints << std::endl;
                // std::cout << "Center: (" << static_cast<int>(center.x/GRID_CELL_SIZE) << ", " 
                // << static_cast<int>(center.y/GRID_CELL_SIZE) << ") | Count:" << inliers.size() << std::endl;

                Object object{center, (int)inliers.size(), inliers};
                auto it = objects_.find(object);
                
                if (it != objects_.end())
                {
                    if (object.numInliers > it->numInliers)
                    {
                        objects_.erase(it);
                        objects_.insert(object);
                        // std::cout << "Center: (" << static_cast<int>(center.x/GRID_CELL_SIZE) << ", " 
                        // << static_cast<int>(center.y/GRID_CELL_SIZE) << ") | Count:" << inliers.size() << std::endl;
                    }
                }
                else
                {
                    objects_.insert(object);
                    // std::cout << "Center: (" << static_cast<int>(center.x/GRID_CELL_SIZE) << ", " 
                    // << static_cast<int>(center.y/GRID_CELL_SIZE) << ") | Count:" << inliers.size() << std::endl;
                }
            }
            
        }
    }
    
    // for (auto object: objects_)
    // {
    //     std::cout << "Center: (" << static_cast<int>(object.center.x/GRID_CELL_SIZE) << ", " 
    //                 << static_cast<int>(object.center.y/GRID_CELL_SIZE) << ") | Count:" << object.numInliers << std::endl;
    // }
    return objects_;
}

Point<double> ArcDetector::findArcCenterGivenRadius(Point<double> const& p1, Point<double> const& p2)
{
    auto q = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    Point<double> p3 = Point<double>{(p1.x + p2.x)/2, (p1.y + p2.y)/2};

    auto dx = sqrt(pow(radius_, 2) - pow(q/2, 2))*(p1.y - p2.y)/ q; 
    auto dy = sqrt(pow(radius_, 2) - pow(q/2, 2))*(p2.x - p1.x)/ q; 

    Point<double> c1{p3.x + dx, p3.y + dy};
    Point<double> c2{p3.x - dx, p3.y - dy};

    if (pow(c1.x, 2) + pow(c1.y, 2) > pow(c2.x, 2) + pow(c2.y, 2))
    {
        return c1;
    }
    else
    {
        return c2;
    }

}
 
std::vector<Point<double>> ArcDetector::getInliersForCircle(size_t const index,
                                                            LidarScan const& scan, 
                                                            Point<double> const& center)
{
    std::vector<Point<double>> inliers;
    for (size_t j = POINT_FIT_OFFSET/2 + 1; j < scan.ranges.size() - index; ++j)
    {
        auto angle = LIDAR_MIN_ANGLE + (index + j)*LIDAR_ANGLE_INCREMENT;
        Point<double> p{ scan.ranges[index + j]*cos(angle),
                            scan.ranges[index + j]*sin(angle)};

        if (fabs(center.distance(p) - radius_) < OBJECT_RADIUS_SIGMA)
        {
            inliers.push_back(p);
        }
        else if (fabs(center.distance(p) - radius_) > OBJECT_RADIUS)
        {
            break;
        }   
    }
    for (int j = -POINT_FIT_OFFSET/2; j <= (int)index; ++j)
    {
        auto angle = LIDAR_MIN_ANGLE + (index - j)*LIDAR_ANGLE_INCREMENT;
        Point<double> p{ scan.ranges[index - j]*cos(angle),
                            scan.ranges[index - j]*sin(angle)};

        if (fabs(center.distance(p) - radius_) < OBJECT_RADIUS_SIGMA)
        {
            inliers.push_back(p);
        }
        else if (fabs(center.distance(p) - radius_) > OBJECT_RADIUS)
        {
            break;
        }   
    }
    return inliers;

}
