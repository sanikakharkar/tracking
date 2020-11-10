#ifndef OBJECTDETECTOR_HPP
#define OBJECTDETECTOR_HPP

#include <iostream>
#include <algorithm>
#include <set>
#include "constants.hpp"
#include "LidarScan.hpp"
#include "Object.hpp"

class ObjectDetector
{
public:
    virtual ~ObjectDetector() = default;

    virtual std::set<Object, associateDetections>& detect(LidarScan const& scan) = 0;

};


#endif /* OBJECTDETECTOR_HPP */