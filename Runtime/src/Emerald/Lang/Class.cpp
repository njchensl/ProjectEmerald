#include "Class.h"

#include <sstream>

namespace Emerald
{
    void Class::SetFields(const std::vector<Field>& fields)
    {
        m_Fields = fields;
        m_FieldSignatureMap.clear();
        for (auto& field : m_Fields)
        {
            field.SetClass(this);
            m_FieldSignatureMap[field.GetSignature()] = &field;
        }
    }

    void Class::SetMethods(const std::vector<Method>& methods)
    {
        m_Methods = methods;
        m_MethodSignatureMap.clear();
        for (auto& method : m_Methods)
        {
            method.SetClass(this);
            m_MethodSignatureMap[method.GetSignature()] = &method;
        }
    }

    Type Class::GetType() const
    {
        return Type(const_cast<Class*>(this));
    }

    Field* Class::GetFieldBySignature(const std::string& signature) const
    {
        return m_FieldSignatureMap.at(signature);
    }

    Method* Class::GetMethodBySignature(const std::string& signature) const
    {
        return m_MethodSignatureMap.at(signature);
    }

    std::string Class::GetTypeName() const
    {
        std::stringstream ss;
        ss << 'L' << m_Name << ';';
        return ss.str();
    }
}
