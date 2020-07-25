#pragma once
#include <iostream>
#include <vector>
#include <any>

#include "Core.h"

namespace Emerald
{
#define ALIGN8 alignas(8)

    enum class ClassType : unsigned char
    {
        Class = 0,
        Interface = 1
    };

    static_assert(sizeof(ClassType) == 1);

    union ALIGN8 PrimitiveData
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

    static_assert(sizeof(PrimitiveData) == 8);

    struct ALIGN8 ConstantPoolEntry
    {
        ConstantPoolEntry(AChar type, std::any data);

        ConstantPoolEntry(const ConstantPoolEntry& other) : Type(other.Type)
        {
            switch (other.Type)
            {
            case 'A':
            {
                ClassName = other.ClassName;
                break;
            }
            case 's':
            {
                StringConstant = other.StringConstant;
                break;
            }
            default:
            {
                memcpy(&PrimitiveValue, &other.PrimitiveValue, sizeof(PrimitiveData));
                break;
            }
            }
        }

        ConstantPoolEntry(ConstantPoolEntry&& other) noexcept : Type(other.Type)
        {
            switch (other.Type)
            {
            case 'A':
            {
                ClassName = std::move(other.ClassName);
                break;
            }
            case 's':
            {
                StringConstant = std::move(other.StringConstant);
                break;
            }
            default:
            {
                memcpy(&PrimitiveValue, &other.PrimitiveValue, sizeof(PrimitiveData));
                break;
            }
            }
        }

        ConstantPoolEntry& operator=(const ConstantPoolEntry& other)
        {
            if (this == &other)
            {
                return *this;
            }
            switch (other.Type) {
            case 'A':
            {
                ClassName = other.ClassName;
                break;
            }
            case 's':
            {
                StringConstant = other.StringConstant;
                break;
            }
            default:
            {
                memcpy(&PrimitiveValue, &other.PrimitiveValue, sizeof(PrimitiveData));
                break;
            }
            }
            return *this;
        }

        ConstantPoolEntry& operator=(ConstantPoolEntry&& other)
        {
            if (this == &other)
            {
                return *this;
            }
            switch (other.Type) {
            case 'A':
            {
                ClassName = std::move(other.ClassName);
                break;
            }
            case 's':
            {
                StringConstant = std::move(other.StringConstant);
                break;
            }
            default:
            {
                memcpy(&PrimitiveValue, &other.PrimitiveValue, sizeof(PrimitiveData));
                break;
            }
            }
            return *this;
        }

        ~ConstantPoolEntry() noexcept
        {
            switch (Type)
            {
            case 'A':
            {
                ClassName.~String();
                break;
            }
            case 'S':
            {
                StringConstant.~String();
                break;
            }
            }
        }

        AChar Type; // char code for primitives, ‘A’ for classes, ‘s’ for strings
        union ALIGN8
        {
            String ClassName; // 'A'
            String StringConstant; // 's'
            // primitive values
            PrimitiveData PrimitiveValue;
        };
    };

    struct ALIGN8 TypeInfoData
    {
        AChar Type;
        Int ConstantPoolIndex; // -1 if primitive
    };

    // unlinked classes and code
    struct ALIGN8 FieldData
    {
        TypeInfoData TypeInfo;
        String Name;
    };

    struct ALIGN8 MethodData
    {
        TypeInfoData ReturnType; // 'V' for void
        String Name;
        std::vector<std::pair<TypeInfoData, String>> Parameters;
        Bool Static;
    };

    struct ALIGN8 ClassData
    {
        String Name;
        ClassType Type;
        std::vector<String> NameSuperClasses;
        std::vector<ConstantPoolEntry> ConstantPool;
    };

    // linked classes and code
    // the data fields in each of the following classes are for linking purposes. (unlinked classes might have,
    // e.g. nullptr values, and the data field is needed to properly link them
    class Field
    {
        FieldData m_FieldData;
    };

    class Method
    {
        MethodData m_MethodData;
    };

    // class data can be copied, but class data can't
    class Class
    {
        ClassData m_ClassData;
    };

    ClassData ClassFileToClassData(void* file);
#undef ALIGN8
}
