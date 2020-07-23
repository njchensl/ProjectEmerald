#pragma once
#include "Core.h"

namespace Emerald
{
    // round up util func
    template <typename T, T multiple>
    __forceinline constexpr static T RoundUp(T numToRound)
    {
        if (multiple == 0)
        {
            return numToRound;
        }

        int remainder = numToRound % multiple;
        if (remainder == 0)
        {
            return numToRound;
        }

        return numToRound + multiple - remainder;
    }

    template <size_t Size>
    class MemBlockAllocator
    {
    public:
        MemBlockAllocator() : m_Head(m_Data)
        {
        }

        void* Allocate(size_t size)
        {
            void* ptr = m_Head;
            m_Head += size;
            m_Head = (Byte*)RoundUp<ulong, 8>((ulong)m_Head);
            return ptr;
        }

        template <typename T, typename... Args>
        T* NewPtr(Args&&... args)
        {
            T* ptr = static_cast<T*>(Allocate(sizeof(T)));
            return new(ptr) T(std::forward<Args>(args)...);
        }

        template <typename T, typename... Args>
        T& NewRef(Args&&... args)
        {
            return *NewPtr<T>(std::forward<Args>(args)...);
        }

    private:
        Byte m_Data[Size];
        Byte* m_Head;
    };

    template <typename R, typename T>
    __forceinline R copy_cast(const T& t)
    {
        R r;
        memcpy(&r, &t, sizeof(T));
        return r;
    }

    template <typename R>
    __forceinline R ptr_copy_cast(const void* src, size_t size)
    {
        R r;
        memcpy(&r, src, size);
        return r;
    }
}
