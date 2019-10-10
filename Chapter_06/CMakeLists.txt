cmake_minimum_required (VERSION 3.0)

PROJECT(Chapter6)

set (CMAKE_CXX_STANDARD 17)

# Requires OpenCV
FIND_PACKAGE(OpenCV 4.0.0 REQUIRED)
MESSAGE("OpenCV version : ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE(${PROJECT_NAME} main.cc utils/multiple_image_window.cc)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS})
