#include "OperandStackStack.h"

namespace Emerald
{
    OperandStackStack::OperandStackStack() = default;

    void OperandStackStack::Push()
    {
        m_Index++;
        m_OperandStacks[m_Index].Reset();
    }

    void OperandStackStack::Pop()
    {
        m_Index--;
    }
}
