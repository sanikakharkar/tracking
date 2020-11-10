#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <math.h>

static constexpr double LIDAR_MIN_ANGLE = -2*M_PI/3;

static constexpr double LIDAR_MAX_ANGLE = 2*M_PI/3;

static constexpr double LIDAR_MAX_RANGE = 65.5339965;

static constexpr int LIDAR_NUM_RANGES = 961;

static constexpr double LIDAR_ANGLE_INCREMENT = 
                        ( LIDAR_MAX_ANGLE - LIDAR_MIN_ANGLE )/ double(LIDAR_NUM_RANGES - 1);

static constexpr double GRID_CELL_SIZE = 0.014;

static constexpr double GRID_WIDTH = 10.0;

static constexpr double GRID_HEIGHT = 10.0;

static constexpr double OBJECT_RADIUS = 0.14;

static constexpr double OBJECT_RADIUS_SIGMA = 0.01*OBJECT_RADIUS;

static constexpr int POINT_FIT_OFFSET = 10; //Even number

static constexpr int MINIMUM_INLIERS = 5;

static constexpr double ASSOCIATION_DISTANCE_DETECTION = 0.75*OBJECT_RADIUS;

static constexpr double ASSOCIATION_DISTANCE_TRACKING = 2*OBJECT_RADIUS;

#endif /* CONSTANTS_HPP */