cmake_minimum_required(VERSION 2.8)

project(clock)
add_executable(clock clock.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(clock ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
