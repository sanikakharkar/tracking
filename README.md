
PROBLEM
-------------------------------------------------------------------------------------------------------------------------------------

Detection and tracking of a circular object using sensor data from a single layer LIDAR.
LIDAR sensor provides scans with ranges, which are the distances to the first detection. 
Infinite measurements return 65.5339965 as a maximum value.

Data format:
timestamp    minimum_angle    maximum_angle     measurement1     measurement2     ...

Angle values are in radians from -2pi/3 to 2pi/3. Measurement values are in meters.


CODE
-------------------------------------------------------------------------------------------------------------------------------------

To build:

mkdir build
cd build
cmake ..
make

To run:

1.  STRAIGHT PATH
    ./tracking -c ../data/car_driving_straight.csv 

2.  TURNING PATH 
    ./tracking -c ../data/turning.csv 


RESULTS
-------------------------------------------------------------------------------------------------------------------------------------

Results can be found in the results directory. The following is included:
1. CSV files with <x, y, velocity> output for both datasets
3. MATLAB plots generated from the above CSV files for <x, y> position and velocity over time
   (MATLAB file for plotting is included)
2. Gray scale visualization of the scan, object and track for both data sets 
   (brighter points indicate the track and detected objects, dimmer points indicate the LIDAR scan end points)
