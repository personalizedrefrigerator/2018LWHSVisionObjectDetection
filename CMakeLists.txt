#Execute with: cmake ../ -DCMAKE_BUILD_TYPE=Release

# Set the minimum CMake version that can compile this.
cmake_minimum_required(VERSION 3.1) #CMAKE_CXX_STANDARD

# Try to force this to be compiled as release.
set(CMAKE_CONFIGURATION_TYPES Release CACHE STRING "" FORCE)

# Note the project name.
project(Vision)

# Set the minimum version of c++ to be used while compiling.
set(CMAKE_CXX_STANDARD 11)

# Set whether WPILib should be used.
option(USE_WPILIB "Use the WPILib library?" OFF)

# Tell OpenCV which file to use to store information about the program.
configure_file("robotVision/Headers/CMakeConfigurationInformation.h.in"
	"CMakeGeneratedHeaders/CMakeConfigurationInformation.h")




# Find OpenCV.
find_package(OpenCV REQUIRED)



# Include OpenCV headers.
include_directories(${OPENCV_INCLUDE_DIRS})

# Note that the directory, "Headers" should be a location
#to search for header files.
include_directories(robotVision/Headers)

# Do this with the pre-generated header files in the build directory.
include_directories(build/CMakeGeneratedHeaders)

# Create variables to store the source files stored in the root directory.
set(SOURCE_NAMES "CameraNormalizer.cpp;CameraFilter.cpp;PlaneDetector.cpp;Point2D.cpp;Point3D.cpp;Line.cpp;Color.cpp;CameraOptionsTrackbarManager.cpp;Shape.cpp;CornerDetector.cpp;VisitedList.cpp;ShapeDetector.cpp;ApplicationController.cpp;NetworkCommunicator.cpp;ShapeList.cpp;VisionApplication.cpp;Serialize.cpp;ShapeLoader.cpp;NetworkVisionOutput.cpp;GenericVisionOutput.cpp;Vector3D.cpp;ListHelper.cpp;ObjectSortingContainer.cpp;Box.cpp;PowerCube.cpp;LightedLine.cpp;MathHelper.cpp;Detector.cpp")

# For all sources, add them to a list, with this as the starting directory.
set(SOURCE_DIR "robotVision/Source")

set(SOURCES, "robotVision/main.cpp")

foreach(CURRENT ${SOURCE_NAMES})
 set(SOURCES "${SOURCES};${SOURCE_DIR}/${CURRENT}")
endforeach()

# So long as there were sources,
if(NOT "${SOURCES}" EQUAL "")
 add_executable(Vision robotVision/main.cpp ${SOURCES}) # Compile the executable with them.
else()
 add_executable(Vision robotVision/main.cpp) # Otherwise, just compile the main file.
endif()

# If using WPILib,
if(USE_WPILIB)
	# Set options relating to wpilib and ntcore (FIRST FRC libraries).
	set(LIB_PATH /home/ubuntu/VisionObjectDetection/ntcore/)
	set(OTHER_LIBS "wpiutil pthread")
	set(NT_INCLUDE_PATH ntcore/include)
	set(WPI_INCLUDE_PATH ntcore/wpiutil/include)

	# Include NTCore and WPILib headers.
	include_directories(${NT_INCLUDE_PATH})
	include_directories(${WPI_INCLUDE_PATH})

	link_directories(./ntcore)

	find_library(NTCORE ntcore ./ntcore)
	find_library(WPIUTIL wpiutil ./ntcore)

	target_link_libraries(Vision stdc++)
	target_link_libraries(Vision ntcore wpiutil)
	target_link_libraries(Vision pthread)
endif()

target_link_libraries(Vision ${OpenCV_LIBS})
