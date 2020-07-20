#pragma once
#include <exception>

#include "Core.h"
#include "Type.h"
#include "Utils.h"

namespace Emerald
{
    class UnsupportedTypeException : std::exception
    {
    };

    class LocalVarArray
    {
    public:
        LocalVarArray(size_t count);

        LocalVarArray(const LocalVarArray& other) = delete;

        LocalVarArray(LocalVarArray&& other) noexcept : m_Data(other.m_Data), m_Types(other.m_Types)
        {
            other.m_Data = nullptr;
            other.m_Types = nullptr;
        }

        LocalVarArray& operator=(const LocalVarArray& other) = delete;

        LocalVarArray& operator=(LocalVarArray&& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }
            delete[] m_Data;
            delete[] m_Types;
            m_Data = other.m_Data;
            m_Types = other.m_Types;
            other.m_Data = nullptr;
            other.m_Types = nullptr;
            return *this;
        }

        ~LocalVarArray() noexcept;

        template <typename T>
        T Load(size_t index)
        {
            throw UnsupportedTypeException();
        }

        template <typename T>
        void Store(size_t index, T val)
        {
            throw UnsupportedTypeException();
        }

    private:
        Int* m_Data;
        Type* m_Types;
    };

    template <>
    inline void LocalVarArray::Store<Byte>(size_t index, Byte val)
    {
        m_Types[index] = Type('B');
        m_Data[index] = static_cast<Int>(val);
    }

    template <>
    inline void LocalVarArray::Store<Short>(size_t index, Short val)
    {
        m_Types[index] = Type('S');
        m_Data[index] = static_cast<Int>(val);
    }

    template <>
    inline void LocalVarArray::Store<Int>(size_t index, Int val)
    {
        m_Types[index] = Type('I');
        m_Data[index] = static_cast<Int>(val);
    }

    template <>
    inline void LocalVarArray::Store<Long>(size_t index, Long val)
    {
        m_Types[index] = Type('J');
        m_Types[index + 1] = Type('J');
        memcpy(&m_Data[index], &val, sizeof(Long));
    }

    template <>
    inline void LocalVarArray::Store<Float>(size_t index, Float val)
    {
        m_Types[index] = Type('F');
        m_Data[index] = copy_cast<Int>(val);
    }

    template <>
    inline void LocalVarArray::Store<Double>(size_t index, Double val)
    {
        m_Types[index] = Type('D');
        m_Types[index + 1] = Type('D');
        memcpy(&m_Data[index], &val, sizeof(Double));
    }

    template <>
    inline void LocalVarArray::Store<Char>(size_t index, Char val)
    {
        m_Types[index] = Type('C');
        m_Data[index] = static_cast<Int>(val);
    }

    template <>
    inline void LocalVarArray::Store<Boolean>(size_t index, Boolean val)
    {
        m_Types[index] = Type('Z');
        m_Data[index] = static_cast<Int>(val);
    }

    template <>
    inline void LocalVarArray::Store<OBJHANDLE>(size_t index, OBJHANDLE val)
    {
        m_Types[index] = Type(nullptr);
        m_Data[index] = static_cast<Int>(val);
    }

    template <>
    inline Byte LocalVarArray::Load<Byte>(size_t index)
    {
        if (m_Types[index].IsClass())
        {
            throw UnsupportedTypeException();
        }
        return static_cast<Byte>(m_Data[index]);
    }

    template <>
    inline Short LocalVarArray::Load<Short>(size_t index)
    {
        if (m_Types[index].IsClass())
        {
            throw UnsupportedTypeException();
        }
        return static_cast<Short>(m_Data[index]);
    }

    template <>
    inline Int LocalVarArray::Load<Int>(size_t index)
    {
        if (m_Types[index].IsClass())
        {
            throw UnsupportedTypeException();
        }
        return static_cast<Int>(m_Data[index]);
    }

    template <>
    inline Long LocalVarArray::Load<Long>(size_t index)
    {
        if (m_Types[index].IsClass())
        {
            throw UnsupportedTypeException();
        }
        return ptr_copy_cast<Long>(&m_Data[index], sizeof(Long));
    }

    template <>
    inline Float LocalVarArray::Load<Float>(size_t index)
    {
        if (m_Types[index].IsClass())
        {
            throw UnsupportedTypeException();
        }
        return ptr_copy_cast<Float>(&m_Data[index], sizeof(Float));
    }

    template <>
    inline Double LocalVarArray::Load<Double>(size_t index)
    {
        if (m_Types[index].IsClass())
        {
            throw UnsupportedTypeException();
        }
        return ptr_copy_cast<Double>(&m_Data[index], sizeof(Double));
    }

    template <>
    inline Char LocalVarArray::Load<Char>(size_t index)
    {
        if (m_Types[index].IsClass())
        {
            throw UnsupportedTypeException();
        }
        return static_cast<Char>(m_Data[index]);
    }


    template <>
    inline Boolean LocalVarArray::Load<Boolean>(size_t index)
    {
        if (m_Types[index].IsClass())
        {
            throw UnsupportedTypeException();
        }
        return static_cast<Boolean>(m_Data[index]);
    }

    template <>
    inline OBJHANDLE LocalVarArray::Load<OBJHANDLE>(size_t index)
    {
        if (!m_Types[index].IsClass())
        {
            throw UnsupportedTypeException();
        }
        return ptr_copy_cast<OBJHANDLE>(&m_Data[index], sizeof(OBJHANDLE));
    }
}
