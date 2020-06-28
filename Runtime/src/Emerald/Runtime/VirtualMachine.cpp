#include "VirtualMachine.h"

#include <cmath>
#include "../Core.h"
#include "../Instructions.h"

namespace Emerald
{
    VirtualMachine::VirtualMachine(byte* p0) : m_LocalVariableStack(1 << 23, &m_Registers.rspPtr, &m_Registers.rbpPtr)
    {
        m_Registers.rip = (ulong)p0;
        ulong codeOffset = NextULong();
        ulong dataOffset = NextULong();
        m_Registers.rip = codeOffset + (ulong)p0;
        m_Registers.rp0 = m_Registers.rip;
        m_Data0 = p0 + dataOffset;
        Running = true;
    }

    void VirtualMachine::Execute()
    {
        ushort instruction = NextUShort();
        switch (instruction)
        {
            // arithmetic operations
#define ADD_OPERATION(name, type) case name: { type var0 = m_OperandStacks.GetActive().Pop##type ();  \
    type var1 = m_OperandStacks.GetActive().Pop##type (); \
    m_OperandStacks.GetActive().Push##type ((type)(var0 + var1));\
    break; }
        case NOP:
        {
            // nop / padding
            break;
        }
        case BADD:
        {
            byte var0 = m_OperandStacks.GetActive().PopByte();
            byte var1 = m_OperandStacks.GetActive().PopByte();
            m_OperandStacks.GetActive().PushByte((byte)((uint)var0 + (uint)var1));
            break;
        }
        ADD_OPERATION(SADD, Short)
        ADD_OPERATION(IADD, Int)
        ADD_OPERATION(JADD, Long)
        ADD_OPERATION(FADD, Float)
        ADD_OPERATION(DADD, Double)

#undef ADD_OPERATION
#define SUB_OPERATION(name, type) case name: {  type var1 = m_OperandStacks.GetActive().Pop##type (); \
    type var0 = m_OperandStacks.GetActive().Pop##type (); \
    m_OperandStacks.GetActive().Push##type ((type)(var0 - var1));\
    break; }

        case BSUB:
        {
            Byte var1 = m_OperandStacks.GetActive().PopByte();
            Byte var0 = m_OperandStacks.GetActive().PopByte();
            m_OperandStacks.GetActive().PushByte((Byte)((Short)var0 - (Short)var1));
            break;
        }
        SUB_OPERATION(SSUB, Short)
        SUB_OPERATION(ISUB, Int)
        SUB_OPERATION(JSUB, Long)
        SUB_OPERATION(FSUB, Float)
        SUB_OPERATION(DSUB, Double)

#undef SUB_OPERATION

#define MUL_OPERATION(name, type) case name: { type var0 = m_OperandStacks.GetActive().Pop##type ();  \
    type var1 = m_OperandStacks.GetActive().Pop##type (); \
    m_OperandStacks.GetActive().Push##type ((type)(var0 * var1));\
    break; }

        case BMUL:
        {
            Byte var0 = m_OperandStacks.GetActive().PopByte();
            Byte var1 = m_OperandStacks.GetActive().PopByte();
            m_OperandStacks.GetActive().PushByte((Byte)((Short)var0 * (Short)var1));
            break;
        }
        MUL_OPERATION(SMUL, Short)
        MUL_OPERATION(IMUL, Int)
        MUL_OPERATION(JMUL, Long)
        MUL_OPERATION(FMUL, Float)
        MUL_OPERATION(DMUL, Double)

#undef MUL_OPERATION
#define DIV_OPERATION(name, type) case name: {  type var1 = m_OperandStacks.GetActive().Pop##type (); \
    type var0 = m_OperandStacks.GetActive().Pop##type (); \
    m_OperandStacks.GetActive().Push##type ((type)(var0 / var1));\
    break; }
        case BDIV:
        {
            Byte var1 = m_OperandStacks.GetActive().PopByte();
            Byte var0 = m_OperandStacks.GetActive().PopByte();
            m_OperandStacks.GetActive().PushByte((Byte)((Short)var0 / (Short)var1));
            break;
        }
        DIV_OPERATION(SDIV, Short)
        DIV_OPERATION(IDIV, Int)
        DIV_OPERATION(JDIV, Long)
        DIV_OPERATION(FDIV, Float)
        DIV_OPERATION(DDIV, Double)
#undef DIV_OPERATION
            // logical
        case ZAND:
        {
            Bool var0 = m_OperandStacks.GetActive().PopBool();
            Bool var1 = m_OperandStacks.GetActive().PopBool();
            m_OperandStacks.GetActive().PushBool(var0 && var1);
            break;
        }
        case ZOR:
        {
            Bool var0 = m_OperandStacks.GetActive().PopBool();
            Bool var1 = m_OperandStacks.GetActive().PopBool();
            m_OperandStacks.GetActive().PushBool(var0 || var1);
            break;
        }
        case ZNOT:
        {
            Bool var0 = m_OperandStacks.GetActive().PopBool();
            m_OperandStacks.GetActive().PushBool(!var0);
            break;
        }
        case ZNAND:
        {
            Bool var0 = m_OperandStacks.GetActive().PopBool();
            Bool var1 = m_OperandStacks.GetActive().PopBool();
            m_OperandStacks.GetActive().PushBool(!(var0 && var1));
            break;
        }
        case ZNOR:
        {
            Bool var0 = m_OperandStacks.GetActive().PopBool();
            Bool var1 = m_OperandStacks.GetActive().PopBool();
            m_OperandStacks.GetActive().PushBool(!(var0 || var1));
            break;
        }
        case ZXOR:
        {
            Bool var0 = m_OperandStacks.GetActive().PopBool();
            Bool var1 = m_OperandStacks.GetActive().PopBool();
            m_OperandStacks.GetActive().PushBool((bool)((byte)var0 ^ (byte)var1));
            break;
        }
        case ZXNOR:
        {
            Bool var0 = m_OperandStacks.GetActive().PopBool();
            Bool var1 = m_OperandStacks.GetActive().PopBool();
            m_OperandStacks.GetActive().PushBool(!(bool)((byte)var0 ^ (byte)var1));
            break;
        }
            // control flow and functions
        case JMP:
        {
            m_Registers.ripPtr = (byte*)m_OperandStacks.GetActive().PopULong();
            break;
        }
        case CALL:
        {
            m_LocalVariableStack.Push(m_Registers.rip);
            byte* func = (byte*)m_OperandStacks.GetActive().PopULong();
            m_Registers.ripPtr = func;
            m_OperandStacks.Push();
            break;
        }
        case RET:
        {
            m_OperandStacks.Pop();
            m_Registers.ripPtr = m_LocalVariableStack.Pop<byte*>();
            break;
        }
#define COMP_OPERATION_FLOAT(name, type) case name : { \
    \
    type var1 = m_OperandStacks.GetActive().Pop##type (); \
    type var0 = m_OperandStacks.GetActive().Pop##type (); \
    type result = var0 - var1; \
    m_Registers.SetZF(var0 == var1); \
    m_Registers.SetSF(std::signbit(result));\
    break; }
#define COMP_OPERATION_INT(name, type) case name : { \
    \
    type var1 = m_OperandStacks.GetActive().Pop##type (); \
    type var0 = m_OperandStacks.GetActive().Pop##type (); \
    type result = var0 - var1; \
    m_Registers.SetZF(var0 == var1); \
    m_Registers.SetSF(result < 0);\
    break; }
        case BCMP:
        {
            Short var1 = (Short)m_OperandStacks.GetActive().PopByte();
            Short var0 = (Short)m_OperandStacks.GetActive().PopByte();
            Short result = var0 - var1;
            m_Registers.SetZF(var0 == var1);
            m_Registers.SetSF(result < 0);
            break;
        }
        COMP_OPERATION_INT(SCMP, Short)
        COMP_OPERATION_INT(ICMP, Int)
        COMP_OPERATION_INT(JCMP, Long)
        COMP_OPERATION_FLOAT(FCMP, Float)
        COMP_OPERATION_FLOAT(DCMP, Double)

#undef COMP_OPERATION_INT
#undef COMP_OPERATION_FLOAT

        case JE:
        {
            if (m_Registers.GetZF())
            {
                m_Registers.rip = m_OperandStacks.GetActive().PopULong();
            }
            break;
        }
        case JNE:
        {
            if (!m_Registers.GetZF())
            {
                m_Registers.rip = m_OperandStacks.GetActive().PopULong();
            }
            break;
        }
        case JG:
        {
            if (!m_Registers.GetZF() && !m_Registers.GetSF())
            {
                m_Registers.rip = m_OperandStacks.GetActive().PopULong();
            }
            break;
        }
        case JGE:
        {
            if (m_Registers.GetZF() || !m_Registers.GetSF())
            {
                m_Registers.rip = m_OperandStacks.GetActive().PopULong();
            }
            break;
        }
        case JL:
        {
            if (!m_Registers.GetZF() && m_Registers.GetSF())
            {
                m_Registers.rip = m_OperandStacks.GetActive().PopULong();
            }
            break;
        }
        case JLE:
        {
            if (m_Registers.GetZF() || m_Registers.GetSF())
            {
                m_Registers.rip = m_OperandStacks.GetActive().PopULong();
            }
            break;
        }
            // operand stack operations
#define OPERAND_STACK_PUSH_OPERATION(name, type) case name : { m_OperandStacks.GetActive().Push##type (Next##type()); break; }
        OPERAND_STACK_PUSH_OPERATION(BPUSH, Byte)
        OPERAND_STACK_PUSH_OPERATION(SPUSH, Short)
        OPERAND_STACK_PUSH_OPERATION(IPUSH, Int)
        OPERAND_STACK_PUSH_OPERATION(JPUSH, Long)
        OPERAND_STACK_PUSH_OPERATION(FPUSH, Float)
        OPERAND_STACK_PUSH_OPERATION(DPUSH, Double)
        OPERAND_STACK_PUSH_OPERATION(ZPUSH, Bool)
        OPERAND_STACK_PUSH_OPERATION(CPUSH, Char)
#undef  OPERAND_STACK_PUSH_OPERATION

#define OPERAND_STACK_POP_OPERATION(name, type) case name : { m_OperandStacks.GetActive().Pop##type (); break; }
        OPERAND_STACK_POP_OPERATION(BPOP, Byte)
        OPERAND_STACK_POP_OPERATION(SPOP, Short)
        OPERAND_STACK_POP_OPERATION(IPOP, Int)
        OPERAND_STACK_POP_OPERATION(JPOP, Long)
        OPERAND_STACK_POP_OPERATION(FPOP, Float)
        OPERAND_STACK_POP_OPERATION(DPOP, Double)
        OPERAND_STACK_POP_OPERATION(ZPOP, Bool)
        OPERAND_STACK_POP_OPERATION(CPOP, Char)
#undef  OPERAND_STACK_POP_OPERATION

            // get from address
#define GET_FROM_ADDRESS_OPERATION(name, type) case name : { auto* ptr = (type*)m_OperandStacks.GetActive().PopULong(); m_OperandStacks.GetActive().Push##type (*ptr); break; }
        GET_FROM_ADDRESS_OPERATION(BGET, Byte)
        GET_FROM_ADDRESS_OPERATION(SGET, Short)
        GET_FROM_ADDRESS_OPERATION(IGET, Int)
        GET_FROM_ADDRESS_OPERATION(JGET, Long)
        GET_FROM_ADDRESS_OPERATION(FGET, Float)
        GET_FROM_ADDRESS_OPERATION(DGET, Double)
        GET_FROM_ADDRESS_OPERATION(ZGET, Bool)
        GET_FROM_ADDRESS_OPERATION(CGET, Char)
#undef  GET_FROM_ADDRESS_OPERATION

            // put into address
#define PUT_INTO_ADDRESS_OPERATION(name, type) case name : { type data = m_OperandStacks.GetActive().Pop##type (); auto* ptr = (type*)m_OperandStacks.GetActive().PopULong(); *ptr = data; break; }
        PUT_INTO_ADDRESS_OPERATION(BPUT, Byte)
        PUT_INTO_ADDRESS_OPERATION(SPUT, Short)
        PUT_INTO_ADDRESS_OPERATION(IPUT, Int)
        PUT_INTO_ADDRESS_OPERATION(JPUT, Long)
        PUT_INTO_ADDRESS_OPERATION(FPUT, Float)
        PUT_INTO_ADDRESS_OPERATION(DPUT, Double)
        PUT_INTO_ADDRESS_OPERATION(ZPUT, Bool)
        PUT_INTO_ADDRESS_OPERATION(CPUT, Char)
#undef  PUT_INTO_ADDRESS_OPERATION
            // load from offset
        case LDO:
        {
            // 0xLDO       - aa                      - bb                   - cccccccc - dd
            // instruction - offset from (register)  - arithmetic operation - offset   - size
            //      00: 0
            //      01: 
            // calculatedOffset = aa +/- cccccccc
            //                       bb
            byte fromRegister = NextByte();
            ulong offsetFrom = m_Registers.SpecialRegisters[(uint8_t)fromRegister];
            byte op = NextByte();
            ulong offset = NextULong();
            byte size = NextByte();
            ulong result = 0;
            if ((uint8_t)op == 0)
            {
                // +
                result = offsetFrom + offset;
            }
            else if ((uint8_t)op == 1)
            {
                // -
                result = offsetFrom - offset;
            }
            m_OperandStacks.GetActive().Push((size_t)size, (void*)result);
            break;
        }
            // load effective address
        case LEA:
        {
            byte fromRegister = NextByte();
            ulong offsetFrom = m_Registers.SpecialRegisters[(uint8_t)fromRegister];
            byte op = NextByte();
            ulong offset = NextULong();
            ulong result = 0;
            if ((uint8_t)op == 0)
            {
                // +
                result = offsetFrom + offset;
            }
            else if ((uint8_t)op == 1)
            {
                // -
                result = offsetFrom - offset;
            }
            m_OperandStacks.GetActive().Push((void*)result);
            break;
        }

            // registers
        case ACCRIP:
        {
            m_OperandStacks.GetActive().PushULong(m_Registers.rip);
            break;
        }
        case ACCRSP:
        {
            m_OperandStacks.GetActive().PushULong(m_Registers.rsp);
            break;
        }
        case ACCRBP:
        {
            m_OperandStacks.GetActive().PushULong(m_Registers.rbp);
            break;
        }
        case PUTRSP:
        {
            m_Registers.rsp = m_OperandStacks.GetActive().PopULong();
            break;
        }
        case PUTRBP:
        {
            m_Registers.rbp = m_OperandStacks.GetActive().PopULong();
            break;
        }
        default:
        {
            throw UnknownInstructionError();
        }
        }
    }

#define VM_NEXT_MEMBER_FUNCTION(type) type VirtualMachine::Next##type () { type value = *(type*)m_Registers.rip; m_Registers.rip += sizeof(type); return value; }

    VM_NEXT_MEMBER_FUNCTION(Byte)
    VM_NEXT_MEMBER_FUNCTION(UShort)
    VM_NEXT_MEMBER_FUNCTION(Short)
    VM_NEXT_MEMBER_FUNCTION(Int)
    VM_NEXT_MEMBER_FUNCTION(Long)
    VM_NEXT_MEMBER_FUNCTION(ULong)
    VM_NEXT_MEMBER_FUNCTION(Float)
    VM_NEXT_MEMBER_FUNCTION(Double)
    VM_NEXT_MEMBER_FUNCTION(Bool)
    VM_NEXT_MEMBER_FUNCTION(Char)

#undef VM_NEXT_MEMBER_FUNCTION

    VirtualMachine::~VirtualMachine() = default;
}
