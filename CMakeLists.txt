cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_FLAGS "-Wconversion -Wall -Werror -Wextra -pedantic")

project(tracking)

include_directories(include)

#include_directories(circleFit)
 
file(GLOB SOURCES src/*.cpp)
 
add_executable(tracking tracking.cpp ${SOURCES})

find_package(Eigen3 3.3 REQUIRED NO_MODULE)  
target_link_libraries(tracking Eigen3::Eigen)