cmake_minimum_required(VERSION 3.10)
project(MyGeant4Project)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

add_executable(MyGeant4Executable main.cpp)
target_link_libraries(MyGeant4Executable ${Geant4_LIBRARIES})

