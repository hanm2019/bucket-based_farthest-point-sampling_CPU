cmake_minimum_required(VERSION 3.19)
project(FPS_CPU)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

file(GLOB SOURCE src/Interval.cpp
        src/KDNode.cpp
        src/KDTreeBase.cpp
        src/Point.cpp)

add_executable(baseline ${SOURCE} src/baseline_main.cpp)

add_executable(kdline ${SOURCE} src/kdtree_main.cpp src/KDLineTree.cpp src/KDLineTree.h)
target_compile_definitions(kdline PUBLIC -DLINE)

add_executable(kdtree ${SOURCE} src/kdtree_main.cpp src/KDTree.cpp src/KDTree.h)