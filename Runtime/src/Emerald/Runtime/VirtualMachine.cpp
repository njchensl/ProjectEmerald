#include "VirtualMachine.h"

#include "../Core.h"
#include "../Instructions.h"

namespace Emerald
{
    VirtualMachine::VirtualMachine(byte* p0) : m_LocalVariableStack(1 << 23, &m_Registers.rspPtr, &m_Registers.rbpPtr)
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
#define ADD_OPERATION(name, type) case name: { type var0 = m_OperandStack.Pop##type##();  \
    type var1 = m_OperandStack.Pop##type##(); \
    m_OperandStack.Push##type##((type)(var0 + var1));\
    break; }

        case BADD:
        {
            byte var0 = m_OperandStack.PopByte();
            byte var1 = m_OperandStack.PopByte();
            m_OperandStack.PushByte((byte)((uint)var0 + (uint)var1));
            break;
        }
        ADD_OPERATION(SADD, Short)
        ADD_OPERATION(IADD, Int)
        ADD_OPERATION(JADD, Long)
        ADD_OPERATION(FADD, Float)
        ADD_OPERATION(DADD, Double)

#undef ADD_OPERATION
#define SUB_OPERATION(name, type) case name: {  type var1 = m_OperandStack.Pop##type##(); \
    type var0 = m_OperandStack.Pop##type##(); \
    m_OperandStack.Push##type##((type)(var0 - var1));\
    break; }

        case BSUB:
        {
            Byte var1 = m_OperandStack.PopByte();
            Byte var0 = m_OperandStack.PopByte();
            m_OperandStack.PushByte((Byte)((Short)var0 - (Short)var1));
            break;
        }
        SUB_OPERATION(SSUB, Short)
        SUB_OPERATION(ISUB, Int)
        SUB_OPERATION(JSUB, Long)
        SUB_OPERATION(FSUB, Float)
        SUB_OPERATION(DSUB, Double)

#undef SUB_OPERATION

#define MUL_OPERATION(name, type) case name: { type var0 = m_OperandStack.Pop##type##();  \
    type var1 = m_OperandStack.Pop##type##(); \
    m_OperandStack.Push##type##((type)(var0 * var1));\
    break; }

        case BMUL:
        {
            Byte var0 = m_OperandStack.PopByte();
            Byte var1 = m_OperandStack.PopByte();
            m_OperandStack.PushByte((Byte)((Short)var0 * (Short)var1));
            break;
        }
        MUL_OPERATION(SMUL, Short)
        MUL_OPERATION(IMUL, Int)
        MUL_OPERATION(JMUL, Long)
        MUL_OPERATION(FMUL, Float)
        MUL_OPERATION(DMUL, Double)

#undef MUL_OPERATION
#define DIV_OPERATION(name, type) case name: {  type var1 = m_OperandStack.Pop##type##(); \
    type var0 = m_OperandStack.Pop##type##(); \
    m_OperandStack.Push##type##((type)(var0 / var1));\
    break; }
        case BDIV:
        {
            Byte var1 = m_OperandStack.PopByte();
            Byte var0 = m_OperandStack.PopByte();
            m_OperandStack.PushByte((Byte)((Short)var0 / (Short)var1));
            break;
        }
        DIV_OPERATION(SDIV, Short)
        DIV_OPERATION(IDIV, Int)
        DIV_OPERATION(JDIV, Long)
        DIV_OPERATION(FDIV, Float)
        DIV_OPERATION(DDIV, Double)
#undef DIV_OPERATION
        case ZAND:
        {
            Bool var0 = m_OperandStack.PopBool();
            Bool var1 = m_OperandStack.PopBool();
            m_OperandStack.PushBool(var0 && var1);
            break;
        }
        case ZOR:
        {
            Bool var0 = m_OperandStack.PopBool();
            Bool var1 = m_OperandStack.PopBool();
            m_OperandStack.PushBool(var0 || var1);
            break;
        }
        case ZNOT:
        {
            Bool var0 = m_OperandStack.PopBool();
            m_OperandStack.PushBool(!var0);
            break;
        }
        case ZNAND:
        {
            Bool var0 = m_OperandStack.PopBool();
            Bool var1 = m_OperandStack.PopBool();
            m_OperandStack.PushBool(!(var0 && var1));
            break;
        }
        case ZNOR:
        {
            Bool var0 = m_OperandStack.PopBool();
            Bool var1 = m_OperandStack.PopBool();
            m_OperandStack.PushBool(!(var0 || var1));
            break;
        }
        case ZXOR:
        {
            Bool var0 = m_OperandStack.PopBool();
            Bool var1 = m_OperandStack.PopBool();
            m_OperandStack.PushBool((bool)((byte)var0 ^ (byte)var1));
            break;
        }
        case ZXNOR:
        {
            Bool var0 = m_OperandStack.PopBool();
            Bool var1 = m_OperandStack.PopBool();
            m_OperandStack.PushBool(!(bool)((byte)var0 ^ (byte)var1));
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
        case ACCRIP:
        {
            break;
        }
        case ACCRSP:
        {
            break;
        }
        case ACCRBP:
        {
            break;
        }
        case PUTRSP:
        {
            break;
        }
        case PUTRBP:
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
