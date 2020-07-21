#pragma once
#include "OperandStack.h"

namespace Emerald
{
    static constexpr size_t Size = 1 << 10;

    class OperandStackStack
    {
    public:
        OperandStackStack();

        OperandStackStack(const OperandStackStack& other) = delete;

        OperandStackStack(OperandStackStack&& other) noexcept = delete;

        OperandStackStack& operator=(const OperandStackStack& other) = delete;

        OperandStackStack& operator=(OperandStackStack&& other) noexcept = delete;

        OperandStack<Size>& GetActive()
        {
            return m_OperandStacks[m_Index];
        }

        typedef OperandStack<Size>* iterator;
        typedef const OperandStack<Size>* const_iterator;

        iterator begin()
        {
            return &m_OperandStacks[0];
        }

        const_iterator begin() const
        {
            return &m_OperandStacks[0];
        }

        iterator end()
        {
            return &m_OperandStacks[m_Index];
        }

        const_iterator end() const
        {
            return &m_OperandStacks[m_Index];
        }


        void Push();
        void Pop();

        // enumerator
    private:
        OperandStack<Size> m_OperandStacks[1000];
        int m_Index = 0;
    };
}
