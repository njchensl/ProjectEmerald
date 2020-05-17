#include "Class.h"

#include <sstream>

namespace Emerald
{
    void Class::SetFields(const std::vector<Field>& fields)
    {
        m_Fields = fields;
        for (auto& field : m_Fields)
        {
            field.SetClass(this);
        }
    }

    void Class::SetMethods(const std::vector<Method>& methods)
    {
        m_Methods = methods;
        for (auto& method : m_Methods)
        {
            method.SetClass(this);
        }
    }

    std::string Class::GetTypeName() const
    {
        std::stringstream ss;
        ss << 'L' << m_Name << ';';
        return ss.str();
    }
}
