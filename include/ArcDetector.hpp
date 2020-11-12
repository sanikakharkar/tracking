#ifndef ARCDETECTOR_HPP
#define ARCDETECTOR_HPP

#include "ObjectDetector.hpp"

// A detector that looks for arcs of a fixed radius in a given LIDAR scan
// It calculates the center of a circle of the fixed radius that passes through
// two points in the scan that are a few points away from each other.
// It then checks for inliers that fit the circle from the points around the two 
// selected points. 
// If the number of inliers is greater than a threshold then an object is detected.
// It uses a small association distance to not detect the same object multiple times.

class ArcDetector : public ObjectDetector
{
public:
    ~ArcDetector() override {};

    ArcDetector(double const radius = OBJECT_RADIUS);

    std::set<Object, associateDetections>& detect(LidarScan const& scan) override;

protected:
    double const radius_;
    std::set<Object, associateDetections> objects_;

    Point<double> findArcCenterGivenRadius(Point<double> const& p1, Point<double> const& p2);

    std::vector<Point<double>> getInliersForCircle( size_t const index, 
                                                    LidarScan const& scan, 
                                                    Point<double> const& center);
   
};




#endif /* ARCDETECTOR_HPP */