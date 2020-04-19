#include "Disassembler.h"

#include <cstdint>
#include <iostream>
#include <sstream>

#include "Instructions.h"

namespace Emerald
{
    Disassembler::Disassembler(unsigned char* code, unsigned long long size) : m_PC(code), m_PC0(code), m_Size(size)
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
        unsigned char instruction = NextByte();
        switch (instruction)
        {
        case IADD:
        {
            ss << "iadd";
            break;
        }
        case ISUB:
        {
            ss << "isub";
            break;
        }
        case IMUL:
        {
            ss << "imul";
            break;
        }
        case IDIV:
        {
            ss << "idiv";
            break;
        }
        case INEG:
        {
            ss << "ineg";
            break;
        }
        case ICONST_M1:
        {
            ss << "iconst_m1";
            break;
        }
        case ICONST_0:
        {
            ss << "iconst_0";
            break;
        }
        case ICONST_1:
        {
            ss << "iconst_1";
            break;
        }
        case ICONST_2:
        {
            ss << "iconst_2";
            break;
        }
        case ICONST_3:
        {
            ss << "iconst_3";
            break;
        }
        case ICONST_4:
        {
            ss << "iconst_4";
            break;
        }
        case ICONST_5:
        {
            ss << "iconst_5";
            break;
        }
        case ILDC:
        {
            ss << "ildc " << std::dec;
            auto data = NextInt();
            ss << data;
            break;
        }
        case DUP:
        {
            ss << "dup";
            break;
        }
        case IFEQ:
        {
            ss << "ifeq 0x" << std::hex;
            long long offset = NextInt();
            ss << offset;
            break;
        }
        case IFGE:
        {
            ss << "ifge 0x" << std::hex;
            long long offset = NextInt();
            ss << offset;
            break;
        }
        case IFGT:
        {
            ss << "ifgt 0x" << std::hex;
            long long offset = NextInt();
            ss << offset;
            break;
        }
        case IFLE:
        {
            ss << "ifle 0x" << std::hex;
            long long offset = NextInt();
            ss << offset;
            break;
        }
        case IFLT:
        {
            ss << "iflt 0x" << std::hex;
            long long offset = NextInt();
            ss << offset;
            break;
        }
        case IFNE:
        {
            ss << "ifne 0x" << std::hex;
            long long offset = NextInt();
            ss << offset;
            break;
        }
        case PTR_ACCESS:
        {
            ss << "ptr_access";
            break;
        }
        case PTR_STORE:
        {
            ss << "ptr_store";
            break;
        }
        case PTR_STACK:
        {
            ss << "ptr_stack";
            break;
        }
        case CALL:
        {
            int numArgs = NextByte();
            ss << "call (" << numArgs << ") 0x" << std::hex;
            auto offset = NextInt();
            ss << offset;
            break;
        }
        case RETURN:
        {
            ss << "return";
            break;
        }
        case DRETURN:
        {
            ss << "dreturn";
            break;
        }
        case GOTO:
        {
            ss << "goto 0x" << std::hex;
            long long offset = NextInt();
            ss << offset;
            break;
        }
        case I2F:
        {
            ss << "i2f";
            break;
        }
        case F2I:
        {
            ss << "f2i";
            break;
        }
        case SWAP:
        {
            ss << "swap ";
            int index1 = NextByte();
            ss << index1 << ", ";
            int index2 = NextByte();
            ss << index2;
            break;
        }
        case HALT:
        {
            ss << "halt";
            break;
        }
        default:
        {
            ss << "unknown";
            break;
        }
        }
        std::cout << ss.str() << std::endl;
    }

    unsigned char Disassembler::NextByte()
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
