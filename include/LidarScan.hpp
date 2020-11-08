#ifndef LIDARSCAN_HPP
#define LIDARSCAN_HPP

#include <vector>
#include "constants.hpp"

struct LidarScan
{
    double timestamp;
    std::vector<double> ranges;
};

#endif /* LIDARSCAN_HPP */
