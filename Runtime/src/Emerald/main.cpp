#include <iostream>
#include <fstream>
#include <vector>

#include "Core.h"
#include "Disassembler.h"
#include "EmInvoke.h"
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
    byte* code = (byte*)buffer.data();

    switch (mode)
    {
    case ExecutionMode::Interpret:
    {
        VirtualMachine* vm = new VirtualMachine(code);
        // init emerald invoke
        auto status = EmInvoke::Init();
        if (status != EmInvokeStatus::Success)
        {
            std::cerr << "Failed to initialize EmInvoke" << std::endl;
            return 1;
        }

        while (vm->Running)
        {
            vm->Execute();
        }

        delete vm;
        EmInvoke::Close();
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
