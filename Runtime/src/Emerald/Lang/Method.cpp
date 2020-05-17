#include "Method.h"

#include <sstream>

namespace Emerald
{
    std::string Method::GetSignature() const
    {
        std::stringstream ss;
        ss << VisibilityToString(m_Visibility) << " ";
        if (m_Static)
        {
            ss << "static ";
        }
        ss << m_ReturnType.ToString() << " " << m_Name << "(";
        // list of args
        bool first = true;
        for (const auto& arg : m_Args)
        {
            const auto& [type, name] = arg;
            if (!first)
            {
                ss << ", ";
            }
            ss << type.ToString() << " " << name;
            first = false;
        }
        ss << ");";

        return ss.str();
    }
}
