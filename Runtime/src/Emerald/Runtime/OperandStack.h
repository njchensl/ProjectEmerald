#pragma once

#include "../Core.h"

namespace Emerald
{
    template <int Size>
    class OperandStack
    {
    public:
        OperandStack() : m_StackBase(m_StackData), m_StackTop(m_StackData + Size), m_StackPtr(m_StackData)
        {
        }

        // push
#define OPERAND_STACK_PUSH(type) void Push##type##(type val) { *(type*)m_StackPtr = val; m_StackPtr += sizeof type; } \
    OperandStack& operator<<(type val) { Push##type##(val); return *this; }
        OPERAND_STACK_PUSH(Byte)
        OPERAND_STACK_PUSH(UShort)
        OPERAND_STACK_PUSH(UInt)
        OPERAND_STACK_PUSH(ULong)
        OPERAND_STACK_PUSH(SByte)
        OPERAND_STACK_PUSH(Short)
        OPERAND_STACK_PUSH(Int)
        OPERAND_STACK_PUSH(Long)
        OPERAND_STACK_PUSH(Float)
        OPERAND_STACK_PUSH(Double)
        OPERAND_STACK_PUSH(Char)
        OPERAND_STACK_PUSH(Bool)
#undef  OPERAND_STACK_PUSH

        // pop
#define OPERAND_STACK_POP(type) type Pop##type##() { m_StackPtr -= sizeof(type); return *(type*)m_StackPtr; } \
    OperandStack& operator>>(##type##& val) { val = Pop##type##(); return *this; }

        OPERAND_STACK_POP(Byte)
        OPERAND_STACK_POP(UShort)
        OPERAND_STACK_POP(UInt)
        OPERAND_STACK_POP(ULong)
        OPERAND_STACK_POP(SByte)
        OPERAND_STACK_POP(Short)
        OPERAND_STACK_POP(Int)
        OPERAND_STACK_POP(Long)
        OPERAND_STACK_POP(Float)
        OPERAND_STACK_POP(Double)
        OPERAND_STACK_POP(Char)
        OPERAND_STACK_POP(Bool)

#undef  OPERAND_STACK_POP

        void Reset()
        {
            m_StackPtr = m_StackBase;
        }

    private:
        byte m_StackData[Size];
        byte* const m_StackBase;
        byte* const m_StackTop;
        // this pointer always points at the next available byte, i.e. the byte that it points at is always empty, or assumed to be empty
        byte* m_StackPtr;
    };
}
