cmake_minimum_required(VERSION 3.1) #CMAKE_CXX_STANDARD

set(CMAKE_CONFIGURATION_TYPES Release CACHE STRING "" FORCE)
project(Vision)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
//find_package(wpilib REQUIRED)

include_directories(${OPENCV_INCLUDE_DIRS})

# Note that the directory, "Headers" should be a location
#to search for header files.
include_directories(Headers)

# Create variables to store the source files stored in the root directory.
set(SOURCE_NAMES "CameraNormalizer.cpp;CameraFilter.cpp;PlaneDetector.cpp;Point2D.cpp;Point3D.cpp;Line.cpp;Color.cpp;CameraOptionsTrackbarManager.cpp;Shape.cpp;CornerDetector.cpp")

set(SOURCE_DIR "Source")

set(SOURCES, "main.cpp")

foreach(CURRENT ${SOURCE_NAMES})
 set(SOURCES "${SOURCES};${SOURCE_DIR}/${CURRENT}")
endforeach()

if(NOT "${SOURCES}" EQUAL "")
 add_executable(Vision main.cpp ${SOURCES})
else()
 add_executable(Vision main.cpp)
endif()

target_link_libraries(Vision ${OpenCV_LIBS})
