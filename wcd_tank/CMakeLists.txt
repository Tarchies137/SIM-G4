cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(Estanque)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(wcd wcd.cc ${sources} ${headers})
target_link_libraries(wcd ${Geant4_LIBRARIES})

add_custom_target(Estanque DEPENDS wcd)