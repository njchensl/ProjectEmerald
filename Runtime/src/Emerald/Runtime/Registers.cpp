#include "Registers.h"

#include <cstring>

namespace Emerald
{
    Registers::Registers()
    {
        memset(this, 0, sizeof(Registers));
    }

    void Registers::ClearFlags()
    {
        m_Flags.reset();
    }

    Bool Registers::GetZF() const
    {
        return m_Flags.test(ZF);
    }

    Bool Registers::GetSF() const
    {
        return m_Flags.test(SF);
    }

    void Registers::SetZF(Bool val)
    {
        m_Flags.set(ZF, val);
    }

    void Registers::SetSF(Bool val)
    {
        m_Flags.set(SF, val);
    }
}
