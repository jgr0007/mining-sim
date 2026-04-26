cmake_minimum_required(VERSION 3.10)

project(MiningSim LANGUAGES CXX)

add_executable(mining_sim "")

target_include_directories(mining_sim PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_sources(mining_sim PRIVATE src/main.cpp
    include/SimManager.h
    include/Station.h
    include/Truck.h
    src/SimManager.cpp
    src/Station.cpp
    src/Truck.cpp
)