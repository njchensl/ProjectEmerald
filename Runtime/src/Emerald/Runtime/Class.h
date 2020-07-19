#pragma once
#include "Core.h"

namespace Emerald
{
#define ALIGN8 alignas(8)

    struct ALIGN8 ConstantPoolEntry
    {
        AChar Type; // char code for primitives, ‘A’ for classes, ‘S’ for strings
        union ALIGN8
        {
            String ClassName; // 'A'
            String StringConstant; // 'S'
            // primitive values
            union
            {
                Byte ByteValue;
                Short ShortValue;
                Int IntValue;
                Long LongValue;
                Float FloatValue;
                Double DoubleValue;
                Char CharValue;
                Boolean BooleanValue;
            };
        };
    };

    // unlinked classes and code
    struct ALIGN8 FieldData
    {
        AChar Type;
        String Name;
        Int ConstantPoolIndex; // -1 if primitive
    };

    struct ALIGN8 MethodData
    {
        Bool Static;
        
    };

    struct ALIGN8 ClassData
    {
        String Name;
        AChar Type;
        Int NumberOfConstants;
    };

    // linked classes and code
    class Field
    {
    };

    class Method
    {
    };

    class Class
    {
    };
}
