#ifndef ARCDETECTOR_HPP
#define ARCDETECTOR_HPP

#include "ObjectDetector.hpp"

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