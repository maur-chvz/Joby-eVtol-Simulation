cmake_minimum_required(VERSION 3.20)
project(eVTOL LANGUAGES CXX)

set(SOURCES
    src/eVTOL.cpp
    src/Vehicle.cpp
    src/VehicleMetric.cpp
)

set(HEADERS
    src/Vehicle.h
    src/VehicleMetric.h
)

add_executable(eVTOL ${SOURCES} ${HEADERS})

target_include_directories(eVTOL PRIVATE src)

target_compile_features(eVTOL PRIVATE cxx_std_20)

set_target_properties(eVTOL PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
