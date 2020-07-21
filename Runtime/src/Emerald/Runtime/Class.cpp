#include "Class.h"

namespace Emerald
{
    ConstantPoolEntry::ConstantPoolEntry(AChar type, std::any data) : Type(type)
    {
        switch (type)
        {
        case 'A':
        {
            ClassName = std::any_cast<String>(data);
            break;
        }
        case 's':
        {
            StringConstant = std::any_cast<String>(data);
            break;
        }
        case 'B':
        {
            PrimitiveValue.ByteValue = std::any_cast<Byte>(data);
            break;
        }
        case 'S':
        {
            PrimitiveValue.ShortValue = std::any_cast<Short>(data);
            break;
        }
        case 'I':
        {
            PrimitiveValue.IntValue = std::any_cast<Int>(data);
            break;
        }
        case 'J':
        {
            PrimitiveValue.LongValue = std::any_cast<Long>(data);
            break;
        }
        case 'F':
        {
            PrimitiveValue.FloatValue = std::any_cast<Float>(data);
            break;
        }
        case 'D':
        {
            PrimitiveValue.DoubleValue = std::any_cast<Double>(data);
            break;
        }
        case 'C':
        {
            PrimitiveValue.CharValue = std::any_cast<Char>(data);
            break;
        }
        case 'Z':
        {
            PrimitiveValue.BooleanValue = std::any_cast<Boolean>(data);
            break;
        }
        }
    }
}
