cmake_minimum_required(VERSION 3.16)
project(ompl_edu)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Release")

cmake_policy(SET CMP0072 OLD)
#
#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
#if(OPENGL_FOUNG)
#    message(STATUS "OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")
#    message(STATUS "OPENGL_LIBRARIES: ${OPENGL_LIBRARIES}")
#endif()

# find_package(Boost)
# find_package(ompl)

### OPENCV
find_package(OpenCV REQUIRED)
message(STATUS "Found OpenCV version is ${OpenCV_VERSION}")
message(STATUS "Found OpenCV include is ${OpenCV_INCLUDE_DIRS}")
message(STATUS "Found OpenCV libraries is ${OpenCV_LIBS}")
# include_directories(${OpenCV_INCLUDE_DIRS})
###

# include_directories(${OMPL_INCLUDE_DIRS} "/usr/include")
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("./include")
set(LIBS ${OpenCV_LIBS})

add_executable(ompl_edu main.cpp src/rrt.cpp src/Map.cpp)
target_link_libraries(ompl_edu PUBLIC ${LIBS})

