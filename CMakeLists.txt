cmake_minimum_required(VERSION 4.2)
project(linuxtest)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)

add_executable(linuxtest main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(linuxtest PUBLIC OpenMP::OpenMP_CXX)
endif()