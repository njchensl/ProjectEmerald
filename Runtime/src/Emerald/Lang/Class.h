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
        Class(const std::string& name, const std::vector<Field>& fields) : m_Name(name)
        {
        }

        void SetFields(const std::vector<Field>& fields);

        void SetMethods(const std::vector<Method>& methods);

        std::string GetTypeName() const;
    private:
        std::string m_Name;
        std::vector<Field> m_Fields;
        std::vector<Method> m_Methods;
    };
}
