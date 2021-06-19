#pragma once
#include "../Core.h"
#include "../Utils.h"


namespace Emerald
{
    class PermGenAllocator
    {
    public:
        PermGenAllocator() = delete;
        static void Init(size_t size);

        template <typename T, typename... Args>
        static T* New(Args&& ... args)
        {
            T* ptr = reinterpret_cast<T*>(m_Head);
            size_t size = sizeof(T);
            m_Head += size;
            m_Head = reinterpret_cast<Byte*>(RoundUp<ULong, 8>(reinterpret_cast<ULong>(m_Head)));
            if (m_Head >= m_Max)
            {
                return nullptr; // buffer overflow
            }

            return new(ptr) T(std::forward<Args>(args)...); // call ctor
        }

        static void Shutdown();
    private:
        inline static Byte* m_Block = nullptr;
        inline static Byte* m_Head = nullptr;
        inline static Byte* m_Max = nullptr;
    };
}
