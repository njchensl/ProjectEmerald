#include "Disassembler.h"

#include <cstdint>
#include <iostream>
#include <sstream>

#include "Instructions.h"

namespace Emerald
{
    Disassembler::Disassembler(byte* code, ulong size) : m_PC(code), m_PC0(code), m_Size(size)
    {
        // read code segment and data segment offsets
        unsigned long long codeOffset = NextInt();
        unsigned long long dataOffset = NextInt();
        m_PC = codeOffset + code;
        m_Data0 = code + dataOffset;

        std::cout << "Code offset: 0x" << std::hex << codeOffset << std::endl;
        std::cout << "Data offset: 0x" << std::hex << dataOffset << std::endl;
    }

    void Disassembler::Execute()
    {
        if (m_PC >= m_PC0 + m_Size)
        {
            exit(0);
        }

        std::stringstream ss;
        ss << "0x" << std::hex << m_PC - m_PC0 << "\t";
        //unsigned char instruction = NextByte();
        //switch (instruction)
        //{
        //{
        //    ss << "unknown";
        //    break;
        //}
        //}
        std::cout << ss.str() << std::endl;
    }

    byte Disassembler::NextByte()
    {
        return *(m_PC++);
    }

    long long Disassembler::NextInt()
    {
        return int64_t((long long)NextByte() |
            (long long)NextByte() << 8 |
            (long long)NextByte() << 16 |
            (long long)NextByte() << 24 |
            (long long)NextByte() << 32 |
            (long long)NextByte() << 40 |
            (long long)NextByte() << 48 |
            (long long)NextByte() << 56);
    }
}
