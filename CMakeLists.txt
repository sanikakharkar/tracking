cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wconversion -Wall -Werror -Wextra -pedantic")

project(toyTrouble)

include_directories(include)
 
file(GLOB SOURCES src/*.cpp)
 
# add the executable
add_executable(toyTrouble toyTrouble.cpp ${SOURCES})