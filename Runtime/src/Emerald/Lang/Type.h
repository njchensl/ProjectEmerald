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
        Type(PrimitiveType type)
        {
            Primitive = true;
            AsPrimitiveType = type;
        }

        Type(Class* type)
        {
            Primitive = false;
            AsClassType = type;
        }

        std::string ToString() const;

        bool Primitive;

        union
        {
            PrimitiveType AsPrimitiveType;
            Class* AsClassType;
        };
    };
}
