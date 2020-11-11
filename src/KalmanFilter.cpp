#include "../include/KalmanFilter.hpp"

KalmanFilter::KalmanFilter()
:previousState{0, Point<double>{0, 0}, Point<double>{0, 0}},
currentState{0, Point<double>{0, 0}, Point<double>{0, 0}},
previousCovariance{Eigen::MatrixXd::Identity(STATE_SIZE, STATE_SIZE)},
currentCovariance{Eigen::MatrixXd::Identity(STATE_SIZE, STATE_SIZE)}
{
    motionNoise.resize(STATE_SIZE, STATE_SIZE);
    motionNoise <<  0.001, 0, 0, 0,
                    0, 0, 0.001, 0,
                    0, 0, 0.0001, 0,
                    0, 0, 0, 0.0001;

    measurementNoise.resize(OBSERVATION_SIZE, OBSERVATION_SIZE);
    measurementNoise << 0.0001, 0,
                        0, 0.0001;
}

void KalmanFilter::initialize(State state)
{
    previousState = state;
    currentState = state;
}
    
void KalmanFilter::predict(double currentTime)
{ 
    Eigen::MatrixXd A(STATE_SIZE, STATE_SIZE);
    double dt = currentTime - previousState.time;
    A << 1, 0, dt, 0,
         0, 1, 0, dt,
         0, 0, 1, 0,
         0, 0, 0, 1;

    Eigen::Vector4d previous{previousState.position.x, 
                             previousState.position.y, 
                             previousState.velocity.x, 
                             previousState.velocity.y};

    Eigen::Vector4d current = A*previous;
    currentCovariance = A*previousCovariance*A.transpose() + motionNoise;
    currentState = {currentTime, {current[0],current[1]}, {current[2],current[3]}};

    previousState = currentState;
    previousCovariance = currentCovariance;
}
    
void KalmanFilter::update(Observation const& observation)
{
    Eigen::MatrixXd C(OBSERVATION_SIZE, STATE_SIZE);
    C << 1, 0, 0, 0,
         0, 1, 0, 0;
    Eigen::Vector4d current{currentState.position.x, 
                            currentState.position.y, 
                            currentState.velocity.x, 
                            currentState.velocity.y};
    Eigen::Vector2d measurement{observation.position.x,
                                observation.position.y};

    auto K = currentCovariance*C.transpose()*((C*currentCovariance*C.transpose() + (measurementNoise/observation.confidence)).inverse());
    current = current + K*(measurement - C*current);
    currentCovariance = (Eigen::MatrixXd::Identity(STATE_SIZE,STATE_SIZE) - K*C)*currentCovariance;
    currentState.position = {current[0],current[1]};
    currentState.velocity = {current[2],current[3]};

    previousState = currentState;
    previousCovariance = currentCovariance;
}

State KalmanFilter::getCurrentState()
{
    return currentState;
}