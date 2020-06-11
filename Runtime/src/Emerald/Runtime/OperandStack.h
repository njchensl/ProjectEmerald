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
        void PushByte(byte b)
        {
            *(m_StackPtr++) = b;
        }

        OperandStack& operator<<(byte b)
        {
            PushByte(b);
            return *this;
        }

        void PushUShort(ushort s)
        {
            *(ushort*)m_StackPtr = s;
            m_StackPtr += 2;
        }

        void PushUInt(uint i)
        {
            *(uint*)m_StackPtr = i;
            m_StackPtr += 4;
        }

        void PushULong(ulong l)
        {
            *(ulong*)m_StackPtr = l;
            m_StackPtr += 8;
        }

        void PushSByte(sbyte b)
        {
            *(sbyte*)(m_StackPtr++) = b;
        }

        OperandStack& operator<<(sbyte b)
        {
            PushByte(b);
            return *this;
        }

        void PushShort(Short s)
        {
            *(Short*)m_StackPtr = s;
            m_StackPtr += 2;
        }

        void PushInt(Int i)
        {
            *(Int*)m_StackPtr = i;
            m_StackPtr += 4;
        }

        void PushLong(Long l)
        {
            *(Long*)m_StackPtr = l;
            m_StackPtr += 8;
        }

        void PushFloat(float f)
        {
            *(float*)m_StackPtr = f;
            m_StackPtr += 4;
        }

        OperandStack& operator<<(float f)
        {
            PushFloat(f);
            return *this;
        }

        void PushDouble(double d)
        {
            *(double*)m_StackPtr = d;
            m_StackPtr += 8;
        }

        OperandStack& operator<<(double d)
        {
            PushDouble(d);
            return *this;
        }

        // pop
        byte PopByte()
        {
            m_StackPtr--;
            return *m_StackPtr;
        }

        OperandStack& operator>>(byte& b)
        {
            b = PopByte();
            return *this;
        }

        ushort PopUShort()
        {
            m_StackPtr -= 2;
            return *(ushort*)m_StackPtr;
        }

        OperandStack& operator>>(ushort& s)
        {
            s = PopUShort();
            return *this;
        }

        uint PopUInt()
        {
            m_StackPtr -= 4;
            return *(uint*)m_StackPtr;
        }

        OperandStack& operator>>(uint& i)
        {
            i = PopUInt();
            return *this;
        }

        ulong PopULong()
        {
            m_StackPtr -= 8;
            return *(ulong*)m_StackPtr;
        }

        OperandStack& operator>>(ulong& l)
        {
            l = PopULong();
            return *this;
        }

        sbyte PopSByte()
        {
            m_StackPtr--;
            return *(sbyte*)m_StackPtr;
        }

        OperandStack& operator>>(sbyte& b)
        {
            b = PopSByte();
            return *this;
        }

        Short PopShort()
        {
            m_StackPtr -= 2;
            return *(Short*)m_StackPtr;
        }

        OperandStack& operator>>(Short& s)
        {
            s = PopShort();
            return *this;
        }

        Int PopInt()
        {
            m_StackPtr -= 4;
            return *(Int*)m_StackPtr;
        }

        OperandStack& operator>>(Int& i)
        {
            i = PopInt();
            return *this;
        }

        Long PopLong()
        {
            m_StackPtr -= 8;
            return *(Long*)m_StackPtr;
        }

        OperandStack& operator>>(Long& l)
        {
            l = PopLong();
            return *this;
        }

        float PopFloat()
        {
            m_StackPtr -= 4;
            return *(float*)m_StackPtr;
        }

        OperandStack& operator>>(float& f)
        {
            f = PopFloat();
            return *this;
        }

        double PopDouble()
        {
            m_StackPtr -= 8;
            return *(double*)m_StackPtr;
        }

        OperandStack& operator>>(double& l)
        {
            l = PopDouble();
            return *this;
        }


    private:
        byte m_StackData[Size];
        const byte* m_StackBase;
        const byte* m_StackTop;
        // this pointer always points at the next available byte, i.e. the byte that it points at is always empty, or assumed to be empty
        byte* m_StackPtr;
    };
}
