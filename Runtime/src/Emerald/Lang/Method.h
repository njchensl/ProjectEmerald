#pragma once

#include <string>
#include <vector>


#include "Modifiers.h"
#include "Type.h"

namespace Emerald
{
    class Class;

    class Method
    {
    public:

        Method(Class* class_, Visibility visibility, bool static_, const Type& returnType, const std::string& name,
               const std::vector<std::pair<Type, std::string>>& args, unsigned char* code) : m_Class(class_),
                                                                                             m_Visibility(visibility),
                                                                                             m_Static(static_),
                                                                                             m_ReturnType(returnType),
                                                                                             m_Name(name),
                                                                                             m_Args(args),
                                                                                             m_Code(code)
        {
        }

        unsigned char* GetCode() const
        {
            return m_Code;
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
        Type m_ReturnType;
        std::string m_Name;
        std::vector<std::pair<Type, std::string>> m_Args;
        unsigned char* m_Code;
    };
}
