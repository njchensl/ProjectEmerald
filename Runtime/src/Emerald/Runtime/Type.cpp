#include "Type.h"

namespace Emerald
{
    Type::Type() : m_Primitive(true), m_TypeCode('\0')
    {
    }

    Type::Type(Class* cls) : m_Primitive(false), m_Class(cls)
    {
    }

    Type::Type(char typecode) : m_Primitive(true), m_TypeCode(typecode)
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

    bool Type::IsValid() const
    {
        return !(m_Primitive && m_TypeCode == '\0' || !m_Primitive && m_Class == nullptr);
    }
}
