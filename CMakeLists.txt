cmake_minimum_required(VERSION 4.2)
project(linuxtest)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenMP REQUIRED)

include_directories(include)

add_executable(dsp_app src/main.cpp
        include/QuantumCircuit.h)
if(OpenMP_CXX_FOUND)
    target_link_libraries(dsp_app PUBLIC OpenMP::OpenMP_CXX)
endif()
add_executable(tensor_test src/tensor_test.cpp
        include/QuantumCircuit.h)

add_executable(csd_2d_filter src/csd_2d_filter.cpp
        include/QuantumCircuit.h)

add_executable(qrng src/qrng.cpp
        include/QuantumCircuit.h)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(unit_tests src/unit_tests.cpp
        include/QuantumCircuit.h)
target_link_libraries(unit_tests PRIVATE gtest gtest_main)
include(GoogleTest)
gtest_discover_tests(unit_tests)