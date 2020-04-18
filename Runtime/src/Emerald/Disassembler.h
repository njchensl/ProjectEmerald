#pragma once

namespace Emerald
{
    class Disassembler {
    public:
        Disassembler(unsigned char* code, unsigned long long size);
        void Execute();

    private:
        unsigned char NextByte();
        long long NextInt();

        unsigned char* m_PC;
        const unsigned char* m_PC0;
        const unsigned char* m_Data0;
        unsigned long long m_Size;
    };

}
