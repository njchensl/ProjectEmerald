#include <iostream>
#include "VirtualMachine.h"
#include "Instructions.h"

VirtualMachine::VirtualMachine(unsigned char *pc) {
    this->PC = pc;
    this->PC0 = pc;
    this->operandStackPtr = operandStack;
}

void VirtualMachine::execute() {
    unsigned char instruction = nextByte();
    switch (instruction) {
        case HALT: {
            while (operandStackPtr > operandStack) {
                std::cout << operandPeek().asInt << "\t" << operandPop().asFloat << std::endl;
            }
            exit(0);
            break;
        }
        case CALL: {
            int numArgs = nextByte();
            auto *address = (unsigned char *) ((unsigned long long) PC0 + nextInt());
            
        }
        case GOTO: {
            int offset = nextInt();
            //std::cout << offset << std::endl;
            PC = (unsigned char *) ((unsigned long long) PC0 + offset);
            break;
        }
        case I2F: {
            operandPush(StackData((float) operandPop().asInt));
            break;
        }
        case F2I: {
            operandPush(StackData((int) operandPop().asFloat));
            break;
        }
        case IADD: {
            operandPush(StackData(operandPop().asInt + operandPop().asInt));
            break;
        }
        case ISUB: {
            operandPush(StackData(operandPop().asInt - operandPop().asInt));
            break;
        }
        case IMUL: {
            operandPush(StackData(operandPop().asInt * operandPop().asInt));
            break;
        }
        case IDIV: {
            operandPush(StackData(operandPop().asInt / operandPop().asInt));
            break;
        }
        case INEG: {
            operandPush(StackData(-operandPop().asInt));
            break;
        }
        case ICONST_M1: {
            operandPush(StackData(-1));
            break;
        }
        case ICONST_0: {
            operandPush(StackData(0));
            break;
        }
        case ICONST_1: {
            operandPush(StackData(1));
            break;
        }
        case ICONST_2: {
            operandPush(StackData(2));
            break;
        }
        case ICONST_3: {
            operandPush(StackData(3));
            break;
        }
        case ICONST_4: {
            operandPush(StackData(4));
            break;
        }
        case ICONST_5: {
            operandPush(StackData(5));
            break;
        }
        default: {
            break;
        }
    }
}

inline unsigned char VirtualMachine::nextByte() {
    return *(PC++);
}

StackData VirtualMachine::operandPeek() {
    return *operandStackPtr;
}

void VirtualMachine::operandPush(StackData sd) {
    *(++operandStackPtr) = sd;
}

StackData VirtualMachine::operandPop() {
    return *(operandStackPtr--);
}

int VirtualMachine::nextInt() {
    return int(nextByte() |
               nextByte() << 8 |
               nextByte() << 16 |
               nextByte() << 24);
}

VirtualMachine::~VirtualMachine() = default;
