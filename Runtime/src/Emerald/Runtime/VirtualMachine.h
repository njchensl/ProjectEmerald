#pragma once

#include <exception>



#include "LocalVariableStack.h"
#include "OperandStack.h"
#include "OperandStackStack.h"
#include "Registers.h"
#include "../Core.h"

namespace Emerald
{
    class UnknownInstructionError : std::exception {};

    class IVirtualMachine {
    public:
        IVirtualMachine() = default;

        virtual ~IVirtualMachine() = default;

        virtual void Execute() = 0;
    };

    class VirtualMachine final : public IVirtualMachine {
    private:
        Registers m_Registers;
        byte* m_Data0;
        OperandStackStack m_OperandStacks;
        LocalVariableStack m_LocalVariableStack;

        inline Byte NextByte();
        inline UShort NextUShort();
        inline Short NextShort();
        inline Int NextInt();
        inline UInt NextUInt();
        inline Long NextLong();
        inline ULong NextULong();
        inline Float NextFloat();
        inline Double NextDouble();
        inline Bool NextBool();
        inline Char NextChar();

    public:
        explicit VirtualMachine(byte*);

        bool Running;

        ~VirtualMachine() override;

        void Execute() override;
    };
}

