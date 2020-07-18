cmake_minimum_required(VERSION 3.16)
project(ProjectEmerald)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(_AMD64_)

include_directories(Runtime/src/Emerald)
include_directories(Runtime/src/Emerald/Runtime)

add_executable(ProjectEmerald
        Runtime/src/Emerald/Runtime/OperandStack.h
        Runtime/src/Emerald/Runtime/OperandStackStack.cpp
        Runtime/src/Emerald/Runtime/OperandStackStack.h
        Runtime/src/Emerald/Runtime/Registers.cpp
        Runtime/src/Emerald/Runtime/Registers.h
        Runtime/src/Emerald/Runtime/VirtualMachine.cpp
        Runtime/src/Emerald/Runtime/VirtualMachine.h
        Runtime/src/Emerald/Core.h
        Runtime/src/Emerald/Disassembler.cpp
        Runtime/src/Emerald/Disassembler.h
        Runtime/src/Emerald/Instructions.h
        Runtime/src/Emerald/main.cpp
        "Runtime/src/Emerald/Utils.h" "Runtime/src/Emerald/Runtime/Type.h" "Runtime/src/Emerald/Runtime/Type.cpp" "Runtime/src/Emerald/Runtime/Class.h" "Runtime/src/Emerald/Runtime/Class.cpp" "Runtime/src/Emerald/Runtime/LocalVarArray.cpp" "Runtime/src/Emerald/Runtime/PermGenAllocator.cpp")

