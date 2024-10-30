cmake_minimum_required(VERSION 3.5.0)
project(raytracing VERSION 0.1.0 LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(raytracing main.cpp)

target_include_directories(raytracing PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src/raymath"
                           "${PROJECT_SOURCE_DIR}/src/rayimage"
                           "${PROJECT_SOURCE_DIR}/src/lodepng"
                           "${PROJECT_SOURCE_DIR}/src/objects"
                           "${PROJECT_SOURCE_DIR}/src/utils"
                           )

add_subdirectory(./src/raymath)
add_subdirectory(./src/rayimage)
add_subdirectory(./src/lodepng)
add_subdirectory(./src/objects)
add_subdirectory(./src/utils)

target_link_libraries(raytracing PUBLIC raymath)
target_link_libraries(raytracing PUBLIC rayimage)
target_link_libraries(raytracing PUBLIC lodepng)
target_link_libraries(raytracing PUBLIC objects)
target_link_libraries(raytracing PUBLIC utils)