add_library(objects 
  ${CMAKE_CURRENT_SOURCE_DIR}/Sphere.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Light.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Plan.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Cube.cpp
)
target_link_libraries(objects PUBLIC raymath)