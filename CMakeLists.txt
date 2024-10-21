cmake_minimum_required(VERSION 3.10)

project(Hypatia)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(includes)

set(SRCS main.cpp src/Args.cpp src/Tokeniser.cpp)

add_executable(hypatia ${SRCS})