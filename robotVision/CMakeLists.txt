cmake_minimum_required(VERSION 3.0)
project(Vision)

find_package(OpenCV REQUIRED)

include_directories(${OPENCV_INCLUDE_DIRS})

# Note that the directory, "Headers" should be a location
#to search for header files.
include_directories(Headers)

# Create variables to store the source files stored in the root directory.
set(SOURCE_NAMES "")

set(SOURCE_DIR "Source")

set(SOURCES, "main.cpp")

foreach(CURRENT ${SOURCE_NAMES})
 set(SOURCES "${SOURCES};${SOURCE_DIR}/${CURRENT}")
endforeach()

if(NOT ${SOURCES} EQUAL "")
 add_executable(Vision ${SOURCES})
else()
 add_executable(Vision main.cpp)
endif()

target_link_libraries(Vision ${OpenCV_LIBS})
