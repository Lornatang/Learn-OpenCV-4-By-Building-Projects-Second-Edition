cmake_minimum_required(VERSION 3.0)

project(Photo_Tool)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV 4.0.0 REQUIRED)
message("OpenCV version: ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

add_executable(sample1 sample1.cc)
target_link_libraries(sample1 ${OpenCV_LIBS})
add_executable(sample2 sample2.cc)
target_link_libraries(sample2 ${OpenCV_LIBS})
add_executable(sample3 sample3.cc)
target_link_libraries(sample3 ${OpenCV_LIBS})
add_executable(sample4 sample4.cc)
target_link_libraries(sample4 ${OpenCV_LIBS})
