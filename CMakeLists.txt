cmake_minimum_required(VERSION 3.16)
project(Interpreter)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Ofast -march=native")

add_executable(Interpreter main.cpp VirtualMachine.cpp OperandStackData.cpp)