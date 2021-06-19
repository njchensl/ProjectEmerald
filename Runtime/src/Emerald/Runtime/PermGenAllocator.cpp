#include "PermGenAllocator.h"

#include <cassert>

namespace Emerald
{
    void PermGenAllocator::Init(size_t size)
    {
        assert(size % 8 == 0);
        m_Block = new Byte[size];
        assert(reinterpret_cast<ULong>(m_Block) % 8 == 0);
        m_Head = m_Block;
        m_Max = m_Block + size;
    }

    void PermGenAllocator::Shutdown()
    {
        delete[] m_Block;
    }
}
