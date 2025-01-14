cmake_minimum_required(VERSION 3.25)
project(sensor-reader)

find_library(wiringPi REQUIRED NAMES wiringPi)
find_library(i2c_loc REQUIRED NAMES libi2c.a)

message(STATUS ${i2c_loc})
message(STATUS ${wiringPi})

add_library(i2c STATIC IMPORTED)
set_target_properties(i2c PROPERTIES IMPORTED_LOCATION ${i2c_loc})

#find_package(WiringPi)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC wiringPi i2c)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "/opt/${PROJECT_NAME}"
)
