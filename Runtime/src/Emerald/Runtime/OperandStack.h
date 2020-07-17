#pragma once

#include <cstring>



#include "Type.h"
#include "Utils.h"
#include "../Core.h"

namespace Emerald
{
    template <size_t Count>
    class alignas(8) OperandStack
    {
    public:
        OperandStack() : m_Index(0)
        {
        }

        void PushByte(Byte val)
        {
            m_StackData[m_Index] = static_cast<int>(val);
            m_IsPrimitive[m_Index] = true;
            m_Index++;
        }

        void PushShort(Short val)
        {
            m_StackData[m_Index] = val;
            m_IsPrimitive[m_Index] = true;
            m_Index++;
        }

        void PushInt(Int val)
        {
            m_StackData[m_Index] = val;
            m_IsPrimitive[m_Index] = true;
            m_Index++;
        }

        void PushLong(Long val)
        {
            memcpy(&m_StackData[m_Index], &val, 8);
            m_IsPrimitive[m_Index++] = true;
            m_IsPrimitive[m_Index++] = true;
        }

        void PushFloat(Float val)
        {
            memcpy(&m_StackData[m_Index], &val, 4);
            m_IsPrimitive[m_Index++] = true;
        }

        void PushDouble(Double val)
        {
            memcpy(&m_StackData[m_Index], &val, 8);
            m_IsPrimitive[m_Index++] = true;
            m_IsPrimitive[m_Index++] = true;
        }

        void PushChar(Char val)
        {
            m_StackData[m_Index] = val;
            m_IsPrimitive[m_Index++] = true;
        }

        void PushBoolean(Boolean val)
        {
            m_StackData[m_Index] = val;
            m_IsPrimitive[m_Index++] = true;
        }

        Byte PopByte()
        {
            m_Index--;
            return static_cast<Byte>(m_StackData[m_Index]);
        }

        Short PopShort()
        {
            m_Index--;
            return static_cast<Short>(m_StackData[m_Index]);
        }

        Int PopInt()
        {
            m_Index--;
            return m_StackData[m_Index];
        }

        Long PopLong()
        {
            m_Index -= 2;
            return ptr_copy_cast<Long>(&m_StackData[m_Index], 8);
        }

        Float PopFloat()
        {
            m_Index--;
            return ptr_copy_cast<Float>(&m_StackData[m_Index], 4);
        }

        Double PopDouble()
        {
            m_Index -= 2;
            return ptr_copy_cast<Double>(&m_StackData[m_Index], 8);
        }

        Char PopChar()
        {
            m_Index--;
            return static_cast<Char>(m_StackData[m_Index]);
        }

        Boolean PopBoolean()
        {
            m_Index--;
            return static_cast<Boolean>(m_StackData[m_Index]);
        }

        void Reset()
        {
            m_Index = 0;
        }

    private:
        int m_StackData[Count];
        bool m_IsPrimitive[Count];
        // this index always points at the next available byte, i.e. the byte that it points at is always empty, or assumed to be empty
        size_t m_Index;
    };
}
