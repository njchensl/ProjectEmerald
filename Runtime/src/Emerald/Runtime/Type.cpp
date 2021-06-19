#include "Type.h"

namespace Emerald
{
    Type::Type() : m_Primitive(true), m_Class(nullptr)
    {
    }

    Type::Type(Class* cls) : m_Primitive(false), m_Class(cls)
    {
    }

    Type::Type(char typecode) : m_Primitive(true), m_Class(nullptr)
    {
    }

    bool Type::IsPrimitive() const
    {
        return m_Primitive;
    }

    bool Type::IsClass() const
    {
        return !m_Primitive;
    }

    bool Type::IsGenericReference() const
    {
        return IsClass() && m_Class == nullptr;
    }

    bool Type::IsValid() const
    {
        return m_Primitive && m_TypeCode == '\0';
    }
}
