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
            byte var0 = m_OperandStack.PopByte();
            byte var1 = m_OperandStack.PopByte();
            m_OperandStack.PushByte((byte)((uint)var0 + (uint)var1));
            break;
        }
        case SADD:
        {
            Short var0 = m_OperandStack.PopShort();
            Short var1 = m_OperandStack.PopShort();
            m_OperandStack.PushShort((Short)(var0 + var1));
            break;
        }
        case IADD:
        {
            Int var0 = m_OperandStack.PopInt();
            Int var1 = m_OperandStack.PopInt();
            m_OperandStack.PushInt((Int)(var0 + var1));
            break;
        }
        case JADD:
        {
            Long var0 = m_OperandStack.PopLong();
            Long var1 = m_OperandStack.PopLong();
            m_OperandStack.PushLong((Long)(var0 + var1));
            break;
        }
        case FADD:
        {
            float var0 = m_OperandStack.PopFloat();
            float var1 = m_OperandStack.PopFloat();
            m_OperandStack.PushFloat(var0 + var1);
            break;
        }
        case DADD:
        {
            double var0 = m_OperandStack.PopDouble();
            double var1 = m_OperandStack.PopDouble();
            m_OperandStack.PushDouble(var0 + var1);
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
        case BPUSH:
        {
            break;
        }
        case SPUSH:
        {
            break;
        }
        case IPUSH:
        {
            break;
        }
        case JPUSH:
        {
            break;
        }
        case FPUSH:
        {
            break;
        }
        case DPUSH:
        {
            break;
        }
        case ZPUSH:
        {
            break;
        }
        case CPUSH:
        {
            break;
        }
        case BPOP:
        {
            break;
        }
        case SPOP:
        {
            break;
        }
        case IPOP:
        {
            break;
        }
        case JPOP:
        {
            break;
        }
        case FPOP:
        {
            break;
        }
        case DPOP:
        {
            break;
        }
        case ZPOP:
        {
            break;
        }
        case CPOP:
        {
            break;
        }
        case BLOAD:
        {
            break;
        }
        case SLOAD:
        {
            break;
        }
        case ILOAD:
        {
            break;
        }
        case JLOAD:
        {
            break;
        }
        case FLOAD:
        {
            break;
        }
        case DLOAD:
        {
            break;
        }
        case ZLOAD:
        {
            break;
        }
        case CLOAD:
        {
            break;
        }
        case BPUT:
        {
            break;
        }
        case SPUT:
        {
            break;
        }
        case IPUT:
        {
            break;
        }
        case JPUT:
        {
            break;
        }
        case FPUT:
        {
            break;
        }
        case DPUT:
        {
            break;
        }
        case ZPUT:
        {
            break;
        }
        case CPUT:
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
