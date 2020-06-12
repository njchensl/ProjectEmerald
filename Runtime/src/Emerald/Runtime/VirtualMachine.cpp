#include "VirtualMachine.h"

#include "../Core.h"
#include "../Instructions.h"

namespace Emerald
{
    VirtualMachine::VirtualMachine(byte* p0)
    {
        m_Registers.rip = (ulong)p0;
        unsigned long long codeOffset = NextLong();
        unsigned long long dataOffset = NextLong();
        m_Registers.rip = codeOffset + (ulong)p0;
        m_Data0 = p0 + dataOffset;
    }

    void VirtualMachine::Execute()
    {
        ushort instruction = NextUShort();
        switch (instruction)
        {
        case BADD:
        {
            break;
        }
        case SADD:
        {
            break;
        }
        case IADD:
        {
            break;
        }
        case JADD:
        {
            break;
        }
        case FADD:
        {
            break;
        }
        case DADD:
        {
            break;
        }
        case BSUB:
        {
            break;
        }
        case SSUB:
        {
            break;
        }
        case ISUB:
        {
            break;
        }
        case JSUB:
        {
            break;
        }
        case FSUB:
        {
            break;
        }
        case DSUB:
        {
            break;
        }
        case BMUL:
        {
            break;
        }
        case SMUL:
        {
            break;
        }
        case IMUL:
        {
            break;
        }
        case JMUL:
        {
            break;
        }
        case FMUL:
        {
            break;
        }
        case DMUL:
        {
            break;
        }
        case BDIV:
        {
            break;
        }
        case SDIV:
        {
            break;
        }
        case IDIV:
        {
            break;
        }
        case JDIV:
        {
            break;
        }
        case FDIV:
        {
            break;
        }
        case DDIV:
        {
            break;
        }
        case ZAND:
        {
            break;
        }
        case ZOR:
        {
            break;
        }
        case ZNOT:
        {
            break;
        }
        case ZNAND:
        {
            break;
        }
        case ZNOR:
        {
            break;
        }
        case ZXOR:
        {
            break;
        }
        case ZXNOR:
        {
            break;
        }
        case JMP:
        {
            break;
        }
        case CALL:
        {
            break;
        }
        case CMP:
        {
            break;
        }
        case JE:
        {
            break;
        }
        case JNE:
        {
            break;
        }
        case JG:
        {
            break;
        }
        case JGE:
        {
            break;
        }
        case JL:
        {
            break;
        }
        case JLE:
        {
            break;
        }
        default:
        {
            throw UnknownInstructionError();
        }
        }
    }

    byte VirtualMachine::NextByte()
    {
        return *(byte*)(m_Registers.rip++);
    }

    ushort VirtualMachine::NextUShort()
    {
        ushort value = *(ushort*)m_Registers.rip;
        m_Registers.rip += 2;
        return value;
    }

    Int VirtualMachine::NextInt()
    {
        Int value = *(Int*)m_Registers.rip;
        m_Registers.rip += 4;
        return value;
    }

    Long VirtualMachine::NextLong()
    {
        Long value = *(Long*)m_Registers.rip;
        m_Registers.rip += 8;
        return value;
    }

    VirtualMachine::~VirtualMachine() = default;
}
