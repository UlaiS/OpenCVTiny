cmake_minimum_required(VERSION 3.6)

set(target detection_based_tracker)

file(GLOB srcs *.cpp *.c)
file(GLOB hdrs *.hpp *.h)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("${CMAKE_CURRENT_LIST_DIR}")

add_library(${target} SHARED ${srcs} ${hdrs})
target_link_libraries (${target} jnigraphics)
target_link_libraries(${target} ${ANDROID_OPENCV_COMPONENTS} ${OpenCV_LIBS})
