#include <math.h>

static constexpr double LIDAR_SCAN_MIN_ANGLE = -2*M_PI/3;
static constexpr double LIDAR_SCAN_MAX_ANGLE = 2*M_PI/3;
static constexpr int LIDAR_SCAN_NUM_RANGES = 961U;