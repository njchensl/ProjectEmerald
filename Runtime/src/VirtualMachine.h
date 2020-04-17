#pragma once

#include <exception>
#include "OperandStackData.h"

class UnknownInstructionError : std::exception
{
};

class IVirtualMachine
{
public:
    IVirtualMachine() = default;

    virtual ~IVirtualMachine() = default;

    virtual void Execute() = 0;
};

class VirtualMachine final : public IVirtualMachine
{
private:
    unsigned char* m_PC;
    const unsigned char* m_PC0;
    const unsigned char* m_Data0;
    StackData* m_OperandStackBasePtr;
    StackData* m_OperandStackPtr;
    StackData m_OperandStack[1024];

    inline unsigned char NextByte();

    inline long long NextInt();

    inline StackData OperandPeek();

    inline void OperandPush(const StackData& sd);

    inline StackData OperandPop();

public:
    explicit VirtualMachine(unsigned char*);

    ~VirtualMachine() override;

    void Execute() override;
};

