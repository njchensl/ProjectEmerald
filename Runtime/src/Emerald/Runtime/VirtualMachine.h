#pragma once

#include <exception>


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

        virtual ~IVirtualMachine() noexcept = default;

        virtual void Execute() = 0;
    };

    class VirtualMachine final : public IVirtualMachine {
    private:
        Registers m_Registers;
        byte* m_Data0;
        OperandStackStack m_OperandStacks;

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

        ~VirtualMachine() noexcept override;

        void Execute() override;
    };
}

