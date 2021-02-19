cmake_minimum_required(VERSION 3.17)
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

find_package(Boost)
find_package(ompl)

include_directories(${OMPL_INCLUDE_DIRS} "/usr/include")


add_executable(ompl_edu main.cpp)
target_link_libraries(ompl_edu PUBLIC
        ${OMPL_LIBRARIES})

