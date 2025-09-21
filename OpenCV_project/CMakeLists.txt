cmake_minimum_required(VERSION 3.10.0)
project(cpp VERSION 0.1.0 LANGUAGES C CXX)


add_executable(armor src/armor_detector_v2.cpp)

find_package(OpenCV REQUIRED)
include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(armor 
    ${OpenCV_LIBS}
)