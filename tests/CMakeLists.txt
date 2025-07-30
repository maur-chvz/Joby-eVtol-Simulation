cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Prevent GoogleTest from building tests for itself
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(eVTOL_TEST
    test_vehicle.cpp
    test_vehicle_metrics.cpp
    ../src/Vehicle.cpp
    ../src/VehicleMetric.cpp
    ../src/Battery.cpp
    ../src/Simulator.cpp
)

target_link_libraries(eVTOL_TEST
    gtest_main
)

target_include_directories(eVTOL_TEST PRIVATE ../src)
target_compile_features(eVTOL_TEST PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(eVTOL_TEST)
