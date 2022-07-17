# 注意事項

cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_BUILD_TYPE Release)

set (CMAKE_CXX_FLAGS "--std=c++14")

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR "/usr/share/OpenCV")
set(OpenCV_DIR "/usr/local/lib/cmake/opencv4/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# readRAWfromGMTSAR2を作る
add_executable(readRAWfromGMTSAR readRAWfromGMTSAR.cpp)
target_link_libraries(readRAWfromGMTSAR ${OpenCV_LIBS})
