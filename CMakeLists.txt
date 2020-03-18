cmake_minimum_required(VERSION 3.16)
project(Interpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(Interpreter main.cpp VirtualMachine.cpp VirtualMachine.h OperandStackData.h OperandStackData.cpp Instructions.h)