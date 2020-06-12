#include "VirtualMachine.h"

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
        m_Data0 = p0 + dataOffset;
    }

    void VirtualMachine::Execute()
    {
        ushort instruction = NextUShort();
        switch (instruction)
        {
            // arithmetic operations
#define ADD_OPERATION(name, type) case name: { type var0 = m_OperandStacks.GetActive().Pop##type##();  \
    type var1 = m_OperandStacks.GetActive().Pop##type##(); \
    m_OperandStacks.GetActive().Push##type##((type)(var0 + var1));\
    break; }

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
#define SUB_OPERATION(name, type) case name: {  type var1 = m_OperandStacks.GetActive().Pop##type##(); \
    type var0 = m_OperandStacks.GetActive().Pop##type##(); \
    m_OperandStacks.GetActive().Push##type##((type)(var0 - var1));\
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

#define MUL_OPERATION(name, type) case name: { type var0 = m_OperandStacks.GetActive().Pop##type##();  \
    type var1 = m_OperandStacks.GetActive().Pop##type##(); \
    m_OperandStacks.GetActive().Push##type##((type)(var0 * var1));\
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
#define DIV_OPERATION(name, type) case name: {  type var1 = m_OperandStacks.GetActive().Pop##type##(); \
    type var0 = m_OperandStacks.GetActive().Pop##type##(); \
    m_OperandStacks.GetActive().Push##type##((type)(var0 / var1));\
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
            // operand stack operations
#define OPERAND_STACK_PUSH_OPERATION(name, type) case name : { m_OperandStacks.GetActive().Push##type##(Next##type()); break; }
        OPERAND_STACK_PUSH_OPERATION(BPUSH, Byte)
        OPERAND_STACK_PUSH_OPERATION(SPUSH, Short)
        OPERAND_STACK_PUSH_OPERATION(IPUSH, Int)
        OPERAND_STACK_PUSH_OPERATION(JPUSH, Long)
        OPERAND_STACK_PUSH_OPERATION(FPUSH, Float)
        OPERAND_STACK_PUSH_OPERATION(DPUSH, Double)
        OPERAND_STACK_PUSH_OPERATION(ZPUSH, Bool)
        OPERAND_STACK_PUSH_OPERATION(CPUSH, Char)
#undef  OPERAND_STACK_PUSH_OPERATION

#define OPERAND_STACK_POP_OPERATION(name, type) case name : { m_OperandStacks.GetActive().Pop##type##(); break; }
        OPERAND_STACK_POP_OPERATION(BPOP, Byte)
        OPERAND_STACK_POP_OPERATION(SPOP, Short)
        OPERAND_STACK_POP_OPERATION(IPOP, Int)
        OPERAND_STACK_POP_OPERATION(JPOP, Long)
        OPERAND_STACK_POP_OPERATION(FPOP, Float)
        OPERAND_STACK_POP_OPERATION(DPOP, Double)
        OPERAND_STACK_POP_OPERATION(ZPOP, Bool)
        OPERAND_STACK_POP_OPERATION(CPOP, Char)
#undef  OPERAND_STACK_POP_OPERATION

            // load from address
#define OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION(name, type) case name : { auto* ptr = (type*)m_OperandStacks.GetActive().PopULong(); m_OperandStacks.GetActive().Push##type##(*ptr); break; }
        OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION(BLOAD, Byte)
        OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION(SLOAD, Short)
        OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION(ILOAD, Int)
        OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION(JLOAD, Long)
        OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION(FLOAD, Float)
        OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION(DLOAD, Double)
        OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION(ZLOAD, Bool)
        OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION(CLOAD, Char)
#undef  OPERAND_STACK_LOAD_FROM_ADDRESS_OPERATION

            // put into address
#define OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION(name, type) case name : { type data = m_OperandStacks.GetActive().Pop##type##(); auto* ptr = (type*)m_OperandStacks.GetActive().PopULong(); *ptr = data; break; }
        OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION(BPUT, Byte)
        OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION(SPUT, Short)
        OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION(IPUT, Int)
        OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION(JPUT, Long)
        OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION(FPUT, Float)
        OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION(DPUT, Double)
        OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION(ZPUT, Bool)
        OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION(CPUT, Char)
#undef  OPERAND_STACK_PUT_INTO_ADDRESS_OPERATION

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

#define VM_NEXT_MEMBER_FUNCTION(type) type VirtualMachine::Next##type##() { type value = *(type*)m_Registers.rip; m_Registers.rip += sizeof type; return value; }

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
