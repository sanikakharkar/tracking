#ifndef KALMANFILTER_HPP
#define KALMANFILTER_HPP

#include <iostream>
#include <iomanip>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "constants.hpp"
#include "Point.hpp"

// The state to be extimated.
// Contains the timestamp, the <x, y> coordinates of the object 
// and the velocity in the <x, y> directions.
struct State
{
    double time;
    Point<double> position;
    Point<double> velocity;
};

// The measurement used for updating the filter.
// Contains the position and confidence of the detection.
struct Observation
{
    Point<double> position;
    int confidence;
};

// A KalmanFilter for estimating the state of the tracked targets.
// Uses a constant velocity model for prediction.
// Uses location of the detection weighted by confidence for update.
class KalmanFilter
{
public:
EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    ~KalmanFilter() = default;

    KalmanFilter();

    void initialize(State state);

    void predict(double currentTime);

    void update(Observation const& observation);

    State getCurrentState();

protected:
    State previousState;
    State currentState;

    Eigen::MatrixXd previousCovariance;
    Eigen::MatrixXd currentCovariance;

    Eigen::MatrixXd motionNoise;
    Eigen::MatrixXd measurementNoise;

};

#endif /* KALMANFILTER_HPP */