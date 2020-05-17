#pragma once

#include "Modifiers.h"

namespace Emerald
{
    class Class;

    enum class PrimitiveType : unsigned char
    {
        Void = 0,
        Byte = 1,
        Short = 2,
        Int = 3,
        Long = 4,
        Float = 5,
        Double = 6,
        Char = 7,
        Bool = 8
    };

    inline static std::map<PrimitiveType, char> s_PrimitiveTypeToCharLookup = {
        {PrimitiveType::Void, 'V'},
        {PrimitiveType::Byte, 'B'},
        {PrimitiveType::Short, 'S'},
        {PrimitiveType::Int, 'I'},
        {PrimitiveType::Long, 'J'},
        {PrimitiveType::Float, 'F'},
        {PrimitiveType::Double, 'D'},
        {PrimitiveType::Char, 'C'},
        {PrimitiveType::Bool, 'Z'}
    };

    inline static std::map<PrimitiveType, std::string> s_PrimitiveTypeToStringLookup = {
        {PrimitiveType::Void, "void"},
        {PrimitiveType::Byte, "byte"},
        {PrimitiveType::Short, "short"},
        {PrimitiveType::Int, "int"},
        {PrimitiveType::Long, "long"},
        {PrimitiveType::Float, "float"},
        {PrimitiveType::Double, "double"},
        {PrimitiveType::Char, "char"},
        {PrimitiveType::Bool, "boolean"}
    };

    inline std::string PrimitiveTypeToString(PrimitiveType type)
    {
        return s_PrimitiveTypeToStringLookup[type];
    }

    inline char PrimitiveTypeToChar(PrimitiveType type)
    {
        return s_PrimitiveTypeToCharLookup[type];
    }

    // acts as data struct only
    struct Type
    {
        Type(PrimitiveType type) : AsPrimitiveType(type)
        {
            Primitive = true;
        }

        Type(Class* type) : AsClassType(type)
        {
            Primitive = false;
        }

        std::string ToString() const;

        bool Primitive;

        union
        {
            PrimitiveType AsPrimitiveType;
            Class* AsClassType;
        };


        Type(const Type& other) : Primitive(other.Primitive)
        {
        }

        friend bool operator==(const Type& lhs, const Type& rhs)
        {
            if (lhs.Primitive != rhs.Primitive)
            {
                return false;
            }
            if (lhs.Primitive)
            {
                return lhs.AsPrimitiveType == rhs.AsPrimitiveType;
            }
            return lhs.AsClassType == rhs.AsClassType;
        }

        friend bool operator!=(const Type& lhs, const Type& rhs)
        {
            return !(lhs == rhs);
        }
    };
}
