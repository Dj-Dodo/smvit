cmake_minimum_required(VERSION 3.25)
project(dht11_reader_cpp)

find_library(wiringPi REQUIRED NAMES wiringPi)

message(STATUS ${wiringPi_LOCATION})

#find_package(WiringPi)
set(CMAKE_CXX_STANDARD 20)

add_executable(dht11_reader_cpp main.cpp)
target_link_libraries(dht11_reader_cpp PUBLIC wiringPi)
