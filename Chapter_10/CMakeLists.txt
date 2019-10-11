cmake_minimum_required(VERSION 3.0)

PROJECT(Segment_text_ch10)

set(CMAKE_CXX_STANDARD 17)

# Requires OpenCV
FIND_PACKAGE(OpenCV 4.0.0 REQUIRED)
MESSAGE("OpenCV version : ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

# load system include
include_directories(/usr/local/include)
# load opencv include
#include_directories(/usr/local/include/opencv4)
# load leptonica include
include_directories(/usr/local/include/leptonica)
# load tesseract include
include_directories(/usr/local/include/tesseract)

# load system library
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
  link_directories(/usr/local/lib)
  link_directories(/usr/local/lib64)
else ()
  link_directories(/usr/local/lib)
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")

ADD_EXECUTABLE(segment segment.cpp)
TARGET_LINK_LIBRARIES(segment
    ${OPENCV_LIBS}
    leptonica
    tesseract)

ADD_EXECUTABLE(segmentOcr segmentOcr.cpp)
TARGET_LINK_LIBRARIES(segmentOcr
    ${OPENCV_LIBS}
    leptonica
    tesseract)

ADD_EXECUTABLE(segmentOcrHigh segmentOcrHigh.cpp)
TARGET_LINK_LIBRARIES(segmentOcrHigh
    ${OPENCV_LIBS}
    leptonica
    tesseract)

