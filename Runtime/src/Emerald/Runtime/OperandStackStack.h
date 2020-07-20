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

        void Push();
        void Pop();
    private:
        OperandStack<Size> m_OperandStacks[1000];
        int m_Index = 0;
    };
}
