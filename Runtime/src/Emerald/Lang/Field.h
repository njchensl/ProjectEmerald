#pragma once
#include <sstream>

#include "Modifiers.h"
#include "Type.h"

namespace Emerald
{
    class Class;

    // these classes will only be instantiated once and will only act as a blueprint for concrete data
    class Field
    {
    public:
        Field(Class* class_, Visibility visibility, bool static_, const Type& type,
            const std::string& name) : m_Class(class_),
                                       m_Visibility(visibility),
                                       m_Static(static_),
                                       m_Type(type),
                                       m_Name(name)
        {
        }

        Class* GetClass() const
        {
            return m_Class;
        }

        void SetClass(Class* cls)
        {
            m_Class = cls;
        }

        std::string GetSignature() const;
    private:
        // will never be modified once created
        Class* m_Class;
        Visibility m_Visibility;
        bool m_Static;
        Type m_Type;
        std::string m_Name;
    };
}
