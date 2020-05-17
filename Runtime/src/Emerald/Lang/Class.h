#pragma once

#include <string>
#include <vector>

#include "Field.h"
#include "Method.h"

namespace Emerald
{
    class Class
    {
    public:
        Class(const std::string& name) : m_Name(name)
        {
        }

        void SetFields(const std::vector<Field>& fields);

        void SetMethods(const std::vector<Method>& methods);

        Type GetType() const;

        Field* GetFieldBySignature(const std::string& signature) const;

        Method* GetMethodBySignature(const std::string& signature) const;

        std::string GetTypeName() const;
    private:
        std::string m_Name;
        std::vector<Field> m_Fields;
        std::vector<Method> m_Methods;
        std::map<std::string, Field*> m_FieldSignatureMap;
        std::map<std::string, Method*> m_MethodSignatureMap;
    };
}
