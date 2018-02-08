#Execute with: cmake ../ -DCMAKE_BUILD_TYPE=Release

cmake_minimum_required(VERSION 3.1) #CMAKE_CXX_STANDARD

set(CMAKE_CONFIGURATION_TYPES Release CACHE STRING "" FORCE)
project(Vision)

set(CMAKE_CXX_STANDARD 11)

#set(wpilib_DIR ../ntcore2)
set(LIB_PATH ../ntcore2)
set(NT_INCLUDE_PATH ../ntcore2/include)
set(WPI_INCLUDE_PATH ../ntcore2/wpiutil/include)

#find_package(wpilib REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${NT_INCLUDE_PATH})
include_directories(${WPI_INCLUDE_PATH})

include_directories(${OPENCV_INCLUDE_DIRS})

# Note that the directory, "Headers" should be a location
#to search for header files.
include_directories(robotVision/Headers)

# Create variables to store the source files stored in the root directory.
set(SOURCE_NAMES "CameraNormalizer.cpp;CameraFilter.cpp;PlaneDetector.cpp;Point2D.cpp;Point3D.cpp;Line.cpp;Color.cpp;CameraOptionsTrackbarManager.cpp;Shape.cpp;CornerDetector.cpp;VisitedList.cpp;ShapeDetector.cpp;ApplicationController.cpp;NetworkCommunicator.cpp")

set(SOURCE_DIR "robotVision/Source")

set(SOURCES, "robotVision/main.cpp")

foreach(CURRENT ${SOURCE_NAMES})
 set(SOURCES "${SOURCES};${SOURCE_DIR}/${CURRENT}")
endforeach()

if(NOT "${SOURCES}" EQUAL "")
 add_executable(Vision robotVision/main.cpp ${SOURCES})
else()
 add_executable(Vision robotVision/main.cpp)
endif()

target_link_libraries(Vision ${LIB_PATH})
target_link_libraries(Vision ${OpenCV_LIBS})
