#pragma once

namespace Emerald
{
    class Class;

    // types are only loaded after all classes are loaded
    class Type
    {
    public:
        Type();
        Type(Class* cls);
        Type(char typecode);

        bool IsPrimitive() const;
        bool IsClass() const;
        bool IsValid() const;
    private:
        bool m_Primitive;
        union
        {
            Class* m_Class;
            char m_TypeCode;
        };
    };
}
