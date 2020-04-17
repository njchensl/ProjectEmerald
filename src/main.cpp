#include <iostream>
#include <fstream>
#include <vector>
#include "OperandStackData.h"
#include "VirtualMachine.h"

int main(int argc, char** argv)
{
    // flags
    bool execution = true;
    bool disassembly = false;

    std::string filepath;
    for (int i = 1; i < argc; ++i)
    {
        std::string param = argv[i];
        if (param == "-d")
        {
            // disassembly
            disassembly = true;
        }
        else
        {
            filepath = param;
            break;
        }
    }

    //std::cout << filepath << std::endl;
    std::ifstream input(filepath, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    //unsigned long long length = buffer.size();
    unsigned char* code = &buffer[0];

    VirtualMachine vm(code);

    for (;;)
    {
        vm.Execute();
    }

    return 1;
}
