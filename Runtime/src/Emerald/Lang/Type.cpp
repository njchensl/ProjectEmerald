#include "Type.h"
#include "Class.h"

namespace Emerald
{
    std::string Type::ToString() const
    {
        if (Primitive)
        {
            return PrimitiveTypeToString(AsPrimitiveType);
        }
        return AsClassType->GetTypeName();
    }
}
