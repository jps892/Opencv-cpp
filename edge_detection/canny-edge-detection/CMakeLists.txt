cmake_minimum_required(VERSION 2.8)

project(canny-edge-detection)
add_executable(${PROJECT_NAME} "main.cpp" "threshold.hpp" "gray.hpp" "filter.hpp" "nonmaxsupp.hpp"
    "threshold.cpp" "gray.cpp" "filter.cpp" "nonmaxsupp.cpp")

set(OpenCV_DIR "/home/jps/libs/opencv_3_4_3/opencv-3.4.3/build/install/share/OpenCV")
set(POCO_ROOT "/home/jps/libs/poco-poco-1.9.0-release/build_n_install/dist")

find_package(OpenCV)

message(STATUS "OpenCV version : ${OpenCV_VERSION}")
message(STATUS "OpenCV includes : ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libs : ${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${POCO_ROOT}/include)
link_directories(${POCO_ROOT}/lib)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
