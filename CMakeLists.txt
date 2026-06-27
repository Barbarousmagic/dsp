cmake_minimum_required(VERSION 4.2)
project(linuxtest)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenMP REQUIRED)

add_executable(dsp_app main.cpp)
if(OpenMP_CXX_FOUND)
    target_link_libraries(dsp_app PUBLIC OpenMP::OpenMP_CXX)
endif()
add_executable(tensor_test tensor_test.cpp)