#include <iostream>
#include <fstream>
#include <vector>

#include "Core.h"
#include "Disassembler.h"
#include "Runtime/Registers.h"
#include "Runtime/VirtualMachine.h"

enum class ExecutionMode
{
    None = 0,
    Interpret = 1,
    Disassembly = 2
};

int main(int argc, char** argv)
{
    using namespace Emerald;
#ifndef _DEBUG
    if (argc == 1) {
        std::cout << "No parameters" << std::endl;
        return 0x101;
    }
    if (argc < 1) {
        std::cout << "No parameters" << std::endl;
        return 0x102;
    }

    ExecutionMode mode = ExecutionMode::Interpret;

    std::string filepath;
    for (int i = 1; i < argc; ++i) {
        std::string param = argv[i];
        if (param == "-d") {
            // disassembly mode
            mode = ExecutionMode::Disassembly;
        }
        else {
            filepath = param;
            break;
        }
    }
#else
    ExecutionMode mode = ExecutionMode::Interpret;
    std::string filepath = "C:\\Users\\njche\\Desktop\\test.exec";
#endif


    //std::cout << filepath << std::endl;
    std::ifstream input(filepath, std::ios::binary);
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(input), {});
    //unsigned long long length = buffer.size();
    Byte* code = (Byte*)buffer.data();

    switch (mode)
    {
    case ExecutionMode::Interpret:
    {
        VirtualMachine* vm = new VirtualMachine(code);
        while (vm->Running)
        {
            vm->Execute();
        }

        delete vm;
        return 0;
    }
    case ExecutionMode::Disassembly:
    {
        Disassembler disassembler(code, buffer.size());
        for (;;)
        {
            disassembler.Execute();
        }
        return 0;
    }
    case ExecutionMode::None:
    {
    }
    }
}
