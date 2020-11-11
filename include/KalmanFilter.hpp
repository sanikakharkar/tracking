#ifndef KALMANFILTER_HPP
#define KALMANFILTER_HPP

#include <iostream>
#include <iomanip>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "constants.hpp"
#include "Point.hpp"

struct State
{
    double time;
    Point<double> position;
    Point<double> velocity;
};

struct Observation
{
    Point<double> position;
    int confidence;
};

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