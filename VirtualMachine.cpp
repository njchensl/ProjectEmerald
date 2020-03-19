#include <iostream>
#include <vector>
#include <stack>
#include "VirtualMachine.h"
#include "Instructions.h"

VirtualMachine::VirtualMachine(unsigned char *pc) {
    this->PC = pc;
    this->PC0 = pc;
    this->operandStackPtr = operandStack;
    this->operandStackBasePtr = operandStack + 1;
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
        case SWAP: {
            int index1 = nextByte();
            int index2 = nextByte();
            StackData temp = operandStackBasePtr[index1];
            operandStackBasePtr[index1] = operandStackBasePtr[index2];
            operandStackBasePtr[index2] = temp;
            break;
        }
        case DUP: {
            operandPush(operandPeek());
            break;
        }
        case GOTO: {
            long long offset = nextInt();
            //std::cout << offset << std::endl;
            PC = (unsigned char *) ((unsigned long long) PC0 + offset);
            break;
        }
        case IFEQ: {
            StackData d = operandPop();
            long long offset = nextInt();
            if (d.asInt == 0) {
                PC = (unsigned char *) ((unsigned long long) PC0 + offset);
            }
            break;
        }
        case IFGE: {
            StackData d = operandPop();
            long long offset = nextInt();
            if (d.asInt >= 0) {
                PC = (unsigned char *) ((unsigned long long) PC0 + offset);
            }
            break;
        }
        case IFGT: {
            StackData d = operandPop();
            long long offset = nextInt();
            if (d.asInt > 0) {
                PC = (unsigned char *) ((unsigned long long) PC0 + offset);
            }
            break;
        }
        case IFLE: {
            StackData d = operandPop();
            long long offset = nextInt();
            if (d.asInt <= 0) {
                PC = (unsigned char *) ((unsigned long long) PC0 + offset);
            }
            break;
        }
        case IFLT: {
            StackData d = operandPop();
            long long offset = nextInt();
            if (d.asInt < 0) {
                PC = (unsigned char *) ((unsigned long long) PC0 + offset);
            }
            break;
        }
        case IFNE: {
            StackData d = operandPop();
            long long offset = nextInt();
            if (d.asInt != 0 || d.asFloat != 0) {
                PC = (unsigned char *) ((unsigned long long) PC0 + offset);
            }
            break;
        }
        case CALL: {
            int numArgs = nextByte();
            auto *address = (unsigned char *) ((unsigned long long) PC0 + nextInt());
            std::stack<StackData> args;
            for (int i = 0; i < numArgs; i++) {
                args.push(operandPop());
            }
            // push the original base pointer, then the return address onto the operand stack, then the args
            // TODO compressed pointers, instead of saving the data as a pointer, save it as a memory offset, so that
            // the total amount of addressable memory remains 4 GB.
            operandPush(StackData((long long) operandStackBasePtr));
            operandPush(StackData((long long) PC));
            operandStackBasePtr = operandStackPtr + 1;

            for (int i = 0; i < numArgs; i++) {
                operandPush(args.top());
                args.pop();
            }
            PC = address;
            break;
        }
        case RETURN: {
            operandStackPtr = operandStackBasePtr - 1;
            PC = reinterpret_cast<unsigned char *>(operandPop().asInt);
            operandStackBasePtr = reinterpret_cast<StackData *>(operandPop().asInt);
            break;
        }
        case DRETURN: {
            StackData ret = operandPop();
            operandStackPtr = operandStackBasePtr - 1;
            PC = reinterpret_cast<unsigned char *>(operandPop().asInt);
            operandStackBasePtr = reinterpret_cast<StackData *>(operandPop().asInt);
            operandPush(ret);
            break;
        }
        case I2F: {
            operandPush(StackData((double) operandPop().asInt));
            break;
        }
        case F2I: {
            operandPush(StackData((long long) operandPop().asFloat));
            break;
        }
        case IADD: {
            operandPush(StackData(operandPop().asInt + operandPop().asInt));
            break;
        }
        case ISUB: {
            operandPush(StackData(-operandPop().asInt + operandPop().asInt));
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
        case ILDC: {
            operandPush(StackData(nextInt()));
            break;
        }
        case ICONST_M1: {
            operandPush(StackData(-1LL));
            break;
        }
        case ICONST_0: {
            operandPush(StackData(0LL));
            break;
        }
        case ICONST_1: {
            operandPush(StackData(1LL));
            break;
        }
        case ICONST_2: {
            operandPush(StackData(2LL));
            break;
        }
        case ICONST_3: {
            operandPush(StackData(3LL));
            break;
        }
        case ICONST_4: {
            operandPush(StackData(4LL));
            break;
        }
        case ICONST_5: {
            operandPush(StackData(5LL));
            break;
        }
        default: {
            throw UnknownInstructionError();
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

void VirtualMachine::operandPush(const StackData &sd) {
    *(++operandStackPtr) = sd;
}

StackData VirtualMachine::operandPop() {
    return *(operandStackPtr--);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

long long VirtualMachine::nextInt() {
    return int64_t((long long) nextByte() |
                   (long long) nextByte() << 8 |
                   (long long) nextByte() << 16 |
                   (long long) nextByte() << 24 |
                   (long long) nextByte() << 32 |
                   (long long) nextByte() << 40 |
                   (long long) nextByte() << 48 |
                   (long long) nextByte() << 56);
}

#pragma clang diagnostic pop

VirtualMachine::~VirtualMachine() = default;
