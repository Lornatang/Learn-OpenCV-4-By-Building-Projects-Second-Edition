cmake_minimum_required(VERSION 3.0)

project(Photo_Tool)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV 4.0.0 REQUIRED)
message("OpenCV version: ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

add_executable(main main.cc)
target_link_libraries(main ${OpenCV_LIBS})
