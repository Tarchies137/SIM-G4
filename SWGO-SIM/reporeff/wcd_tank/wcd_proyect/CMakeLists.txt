cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(Estanque_Lago)

find_package(Geant4n REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB source $(PROJECT_SOURCE_DIR)/*.cc)
file(GLOB headers $(PROJECT_SOURCE_DIR)/*.hh)

add_ executable(wcd wcd.cc ${sources} ${headers})
target_link_libraries(wcd ${Geant4_LIBRARIES}

add_custom_target{Estanque_Lago)DEPENDS wcd}