cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(python_from_cpp)
add_subdirectory(pybind11)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

 
add_executable(demo_1 src/demo_1.cpp)
target_link_libraries(demo_1 PRIVATE pybind11::embed)
add_executable(demo_2 src/demo_2.cpp)
target_link_libraries(demo_2 PRIVATE pybind11::embed ${OpenCV_LIBS})

