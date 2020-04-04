# minimum requirement
cmake_minimum_required(VERSION 3.6)

# solution
project(customKernel)

SET(TARGET_NAME sincosTest)
# find OpenCV
find_package(OpenCV REQUIRED)

# set include directory
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${TARGET_NAME} main.cpp)

# set the link
target_link_libraries(${TARGET_NAME} ${OpenCV_LIBS})
