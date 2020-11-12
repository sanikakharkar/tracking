
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

This folder contains the code and the results for the toy car tracking problem.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CODE

To build:

mkdir build
cd build
cmake ..
make

To run:

1.  STRAIGHT PATH
    ./toyTrouble -c ../data/car_driving_straight.csv 

2.  TURNING PATH 
    ./toyTrouble -c ../data/turning.csv 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RESULTS

Results can be found in the results directory. The following is included:
1. CSV files with <x, y, velocity> output for both datasets
3. MATLAB plots generated from the above CSV files for <x, y> position and velocity over time
   (MATLAB file for plotting is included)
2. Gray scale visualization of the scan, object and track for both data sets 
   (brighter points indicate the track and detected objects, dimmer points indicate the LIDAR scan end points)