#include "PermGenAllocator.h"

namespace Emerald
{
    void PermGenAllocator::Init(size_t size)
    {
        m_Block = new Byte[size];
        m_Head = m_Block;
        m_Max = m_Block + size;
    }

    void PermGenAllocator::Shutdown()
    {
        delete[] m_Block;
    }
}
