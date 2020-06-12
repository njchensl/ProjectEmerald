#pragma once
#include "Core.h"

namespace Emerald
{
    class Disassembler {
    public:
        Disassembler(byte* code, size_t size);
        void Execute();

    private:
        byte NextByte();
        long long NextInt();

        byte* m_PC;
        byte* const m_PC0;
        byte* m_Data0;
        size_t m_Size;
    };

}
