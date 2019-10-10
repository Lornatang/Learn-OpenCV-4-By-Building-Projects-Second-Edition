cmake_minimum_required(VERSION 3.0)

PROJECT(Chapter6)

set(CMAKE_CXX_STANDARD 17)

# Requires OpenCV
FIND_PACKAGE(OpenCV 4.0.0 REQUIRED)
MESSAGE("OpenCV version : ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE(earDetector earDetector.cc)
TARGET_LINK_LIBRARIES(earDetector ${OpenCV_LIBS})

ADD_EXECUTABLE(overlayFacemask overlayFacemask.cc)
TARGET_LINK_LIBRARIES(overlayFacemask ${OpenCV_LIBS})

ADD_EXECUTABLE(overlayMoustache overlayMoustache.cc)
TARGET_LINK_LIBRARIES(overlayMoustache ${OpenCV_LIBS})

ADD_EXECUTABLE(overlayNose overlayNose.cc)
TARGET_LINK_LIBRARIES(overlayNose ${OpenCV_LIBS})

ADD_EXECUTABLE(overlaySunglasses overlaySunglasses.cc)
TARGET_LINK_LIBRARIES(overlaySunglasses ${OpenCV_LIBS})