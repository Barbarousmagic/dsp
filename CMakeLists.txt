cmake_minimum_required(VERSION 4.2)
set(CMAKE_CXX_COMPILER_WORKS 1)
project(linuxtest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-stdlib=libstdc++)
add_link_options(-stdlib=libstdc++)

list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/.cudaq")
find_package(CUDAQ REQUIRED)

include_directories(include)

# ==========================================
# ==========================================
add_executable(dsp_app src/main.cpp include/QuantumCircuit.h)
target_compile_options(dsp_app PRIVATE -fopenmp)
target_link_options(dsp_app PRIVATE -fopenmp)

add_executable(tensor_test src/tensor_test.cpp include/QuantumCircuit.h)
add_executable(csd_2d_filter src/csd_2d_filter.cpp include/QuantumCircuit.h)
add_executable(qrng src/qrng.cpp include/QuantumCircuit.h)


add_executable(unit_tests src/unit_tests.cpp include/QuantumCircuit.h)

set_target_properties(unit_tests PROPERTIES BUILD_RPATH "$ENV{HOME}/.cudaq/lib")

target_link_libraries(unit_tests PRIVATE cudaq::cudaq)