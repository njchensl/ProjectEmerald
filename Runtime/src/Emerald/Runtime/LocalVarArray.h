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

        ~LocalVarArray();

        template <typename T>
        T Load(size_t index)
        {
            throw UnsupportedTypeException();
        }

        template <>
        Byte Load<Byte>(size_t index)
        {
            if (m_Types[index].IsClass())
            {
                throw UnsupportedTypeException();
            }
            return static_cast<Byte>(m_Data[index]);
        }

        template <>
        Short Load<Short>(size_t index)
        {
            if (m_Types[index].IsClass())
            {
                throw UnsupportedTypeException();
            }
            return static_cast<Short>(m_Data[index]);
        }

        template <>
        Int Load<Int>(size_t index)
        {
            if (m_Types[index].IsClass())
            {
                throw UnsupportedTypeException();
            }
            return static_cast<Int>(m_Data[index]);
        }

        template <>
        Long Load<Long>(size_t index)
        {
            if (m_Types[index].IsClass())
            {
                throw UnsupportedTypeException();
            }
            return ptr_copy_cast<Long>(&m_Data[index], sizeof(Long));
        }

        template <>
        Float Load<Float>(size_t index)
        {
            if (m_Types[index].IsClass())
            {
                throw UnsupportedTypeException();
            }
            return ptr_copy_cast<Float>(&m_Data[index], sizeof(Float));
        }

        template <>
        Double Load<Double>(size_t index)
        {
            if (m_Types[index].IsClass())
            {
                throw UnsupportedTypeException();
            }
            return ptr_copy_cast<Double>(&m_Data[index], sizeof(Double));
        }

        template <>
        Char Load<Char>(size_t index)
        {
            if (m_Types[index].IsClass())
            {
                throw UnsupportedTypeException();
            }
            return static_cast<Char>(m_Data[index]);
        }

        template <>
        Boolean Load<Boolean>(size_t index)
        {
            if (m_Types[index].IsClass())
            {
                throw UnsupportedTypeException();
            }
            return static_cast<Boolean>(m_Data[index]);
        }

        template <>
        OBJHANDLE Load<OBJHANDLE>(size_t index)
        {
            if (!m_Types[index].IsClass())
            {
                throw UnsupportedTypeException();
            }
            return ptr_copy_cast<OBJHANDLE>(&m_Data[index], sizeof(OBJHANDLE));
        }

    private:
        int* m_Data;
        Type* m_Types;
    };
}
