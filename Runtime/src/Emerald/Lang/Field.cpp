#include "Field.h"

namespace Emerald
{
    std::string Field::GetSignature() const
    {
        std::stringstream ss;
        ss << VisibilityToString(m_Visibility) << " ";
        if (m_Static)
        {
            ss << "static ";
        }
        ss << m_Type.ToString() << " " << m_Name << ';';

        return ss.str();
    }
}
