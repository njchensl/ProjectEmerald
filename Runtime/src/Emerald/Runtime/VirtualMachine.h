#pragma once

#include <exception>



#include "OperandStack.h"
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
        OperandStack<1024> m_OperandStack;

        inline byte NextByte();
        inline ushort NextUShort();
        inline Int NextInt();
        inline Long NextLong();

    public:
        explicit VirtualMachine(byte*);

        ~VirtualMachine() override;

        void Execute() override;
    };
}

