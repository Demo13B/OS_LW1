cmake_minimum_required(VERSION 3.10)
project(Child_processes_with_pipes)

set (CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)
add_executable(calculator calculator.cpp)