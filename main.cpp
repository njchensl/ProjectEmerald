#include <iostream>
#include <fstream>
#include <vector>
#include "OperandStackData.h"
#include "VirtualMachine.h"


int main(int argc, char **argv) {
    std::string fIn = argv[1];
    //std::cout << fIn << std::endl;
    std::ifstream input(fIn, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    //unsigned long long length = buffer.size();
    unsigned char *code = &buffer[0];

    VirtualMachine vm(code);
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    for (;;) {
        vm.execute();
    }
#pragma clang diagnostic pop
    return 0;
}
