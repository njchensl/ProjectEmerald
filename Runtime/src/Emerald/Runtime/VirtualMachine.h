#pragma once

#include <exception>
#include "../DataUnit.h"

#if 0
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
        unsigned char* m_PC;
        const unsigned char* m_PC0;
        const unsigned char* m_Data0;
        DataUnit* m_OperandStackBasePtr;
        DataUnit* m_OperandStackPtr;
        DataUnit m_OperandStack[1024];

        inline unsigned char NextByte();

        inline long long NextInt();

        inline DataUnit OperandPeek();

        inline void OperandPush(const DataUnit& du);

        inline DataUnit OperandPop();

    public:
        explicit VirtualMachine(unsigned char*);

        ~VirtualMachine() override;

        void Execute() override;
    };
}


#endif