#pragma once
#include <cstdlib>

#include "../Core.h"

namespace Emerald
{
    class LocalVariableStack
    {
    public:
        LocalVariableStack(size_t size, byte** rsp, byte** rbp) : m_Rsp(*rsp), m_Rbp(*rbp)
        {
            m_BaseAddress = (byte*)malloc(size);
            m_Rbp = m_BaseAddress;
            m_Rsp = m_Rbp;
        }

        ~LocalVariableStack();

        LocalVariableStack(const LocalVariableStack& other) = delete;

        LocalVariableStack(LocalVariableStack&& other) = delete;

        LocalVariableStack& operator=(const LocalVariableStack& other) = delete;

        LocalVariableStack& operator=(LocalVariableStack&& other) = delete;

        template<typename T>
        void Push(T val)
        {
            *(T*)m_Rsp = val;
            m_Rsp += sizeof(T);
        }

        template<typename T>
        T Pop()
        {
            m_Rsp -= sizeof(T);
            return *(T*)m_Rsp;
        }

    private:
        byte* m_BaseAddress;
        byte*& m_Rsp;
        byte*& m_Rbp;
    };
}
