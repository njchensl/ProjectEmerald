#pragma once
#include "Core.h"

namespace Emerald
{
    // round up util func
    template <typename T, T multiple>
    static T RoundUp(T numToRound) {
        if (multiple == 0) {
            return numToRound;
        }

        int remainder = numToRound % multiple;
        if (remainder == 0) {
            return numToRound;
        }

        return numToRound + multiple - remainder;
    }

    template <size_t Size>
    class MemBlockAllocator {
    public:
        MemBlockAllocator() : m_Head(m_Data) {}

        void* Allocate(size_t size) {
            void* ptr = m_Head;
            m_Head += size;
            m_Head = (Byte*)RoundUp<ulong, 8>((ulong)m_Head);
            return ptr;
        }

    private:
        Byte m_Data[Size];
        Byte* m_Head;
    };

    template <typename R, typename T>
    R copy_cast(T& t) {
        R r;
        memcpy(&r, &t, sizeof(T));
        return r;
    }

    template <typename R>
    R ptr_copy_cast(void* ptr, size_t size)
    {
        R r;
        memcpy(&r, ptr, size);
        return r;
    }
}
