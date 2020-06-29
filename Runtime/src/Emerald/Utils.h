#pragma once

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
            m_Head = (byte*)RoundUp<ulong, 8>((ulong)m_Head);
            return ptr;
        }

    private:
        byte m_Data[Size];
        byte* m_Head;
    };
}
