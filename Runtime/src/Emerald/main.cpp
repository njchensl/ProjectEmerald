#include <iostream>
#include <fstream>
#include <vector>

#include "Core.h"
#include "Disassembler.h"
#include "Lang/Field.h"
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


    Method method(
        nullptr,
        Visibility::Public,
        true,
        PrimitiveType::Void,
        "main",
        {
            {PrimitiveType::Int, "argc"},
            {PrimitiveType::Char, "argv"}
        },
        nullptr
    );
    std::cout << method.GetSignature();

#if 0


    EM_CORE_ASSERT(argc >= 2, "Argument count must be greater than or equal to 2!");
    if (argc == 1)
    {
        std::cout << "No parameters" << std::endl;
        return 0x101;
    }
    if (argc < 1)
    {
        std::cout << "No parameters" << std::endl;
        return 0x102;
    }

    ExecutionMode mode = ExecutionMode::Interpret;

    std::string filepath;
    for (int i = 1; i < argc; ++i)
    {
        std::string param = argv[i];
        if (param == "-d")
        {
            // disassembly mode
            mode = ExecutionMode::Disassembly;
        }
        else
        {
            filepath = param;
            break;
        }
    }

    EM_CORE_ASSERT(mode != ExecutionMode::None, "Invalid execution mode!");

    //std::cout << filepath << std::endl;
    std::ifstream input(filepath, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    //unsigned long long length = buffer.size();
    unsigned char* code = &buffer[0];

    switch (mode)
    {
    case ExecutionMode::Interpret:
    {
        VirtualMachine vm(code);

        for (;;)
        {
            vm.Execute();
        }

        return 1;
    }
    case ExecutionMode::Disassembly:
    {
        Disassembler disassembler(code, buffer.size());
        for (;;)
        {
            disassembler.Execute();
        }
        return 1;
    }
    case ExecutionMode::None:
    {
        EM_CORE_ASSERT(false, "Invalid execution path!");
    }
    }
#endif
}
