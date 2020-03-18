#pragma once

#include <exception>
#include "OperandStackData.h"

class UnknownInstructionError : std::exception {
};

class IVirtualMachine {
public:
    IVirtualMachine() = default;

    virtual ~IVirtualMachine() = default;

    virtual void execute() = 0;
};

class VirtualMachine final : public IVirtualMachine {
private:
    unsigned char *PC;
    const unsigned char *PC0;
    StackData *operandStackBasePtr;
    StackData *operandStackPtr;
    StackData operandStack[1024];

    inline unsigned char nextByte();

    inline int nextInt();

    inline StackData operandPeek();

    inline void operandPush(StackData sd);

    inline StackData operandPop();

public:
    explicit VirtualMachine(unsigned char *);

    ~VirtualMachine() override;

    void execute() override;
};

