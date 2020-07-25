#include "Class.h"
#include "Utils.h"

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

    ClassData ClassFileToClassData(void* file)
    {
        const auto HeadRoundUp = [](Byte*& head) -> void
        {
            head = reinterpret_cast<Byte*>(RoundUp<ULong, 8>(reinterpret_cast<ULong>(head)));
        };


        Byte* head = static_cast<Byte*>(file);

        ClassData classData;

        //////////////////////////
        // CLASS HEADER //////////
        //////////////////////////
        const auto length = ptr_copy_cast<Byte>(head, sizeof(Byte));
        head++;
        classData.Name = reinterpret_cast<const char*>(head);
        head += static_cast<ULong>(length) + 1ULL;
        classData.Type = ptr_copy_cast<ClassType>(head, sizeof(ClassType));
        head++;
        HeadRoundUp(head);
        uint numSuperclasses = static_cast<uint>(ptr_copy_cast<Byte>(head, sizeof(Byte)));
        head++;

        for (uint i = 0; i < numSuperclasses; i++)
        {
            const auto lengthSuperclassName = static_cast<size_t>(*head);
            head++;
            classData.NameSuperClasses.emplace_back(reinterpret_cast<const char*>(head));
            head += lengthSuperclassName + 1ULL;
        }

        HeadRoundUp(head);
        // constant pool
        const auto numConstants = ptr_copy_cast<Int>(head, sizeof(Int));
        HeadRoundUp(head);
        // constant pool entries
        for (Int i = 0; i < numConstants; i++)
        {
            AChar type = *reinterpret_cast<AChar*>(head);
            head++;
            std::any data;
            switch (type)
            {
            case 'A': case 's':
            {
                size_t stringLength = static_cast<size_t>(*head);
                head++;
                String stringConstant = reinterpret_cast<const char*>(head);
                data = stringConstant;
                head += stringLength + 1;
                break;
            }
            case 'B':
            {
                data = ptr_copy_cast<Byte>(head, sizeof(Byte));
                head++;
                break;
            }
            case 'S':
            {
                data = ptr_copy_cast<Short>(head, sizeof(Short));
                head += sizeof(Short);
                break;
            }
            case 'I':
            {
                data = ptr_copy_cast<Int>(head, sizeof(Int));
                head += sizeof(Int);
                break;
            }
            case 'J':
            {
                data = ptr_copy_cast<Long>(head, sizeof(Long));
                head += sizeof(Long);
                break;
            }
            case 'F':
            {
                data = ptr_copy_cast<Float>(head, sizeof(Float));
                head += sizeof(Float);
                break;
            }
            case 'D':
            {
                data = ptr_copy_cast<Double>(head, sizeof(Double));
                head += sizeof(Double);
                break;
            }
            case 'C':
            {
                data = ptr_copy_cast<Char>(head, sizeof(Char));
                head += sizeof(Char);
                break;
            }
            case 'Z':
            {
                data = ptr_copy_cast<Boolean>(head, sizeof(Boolean));
                head += sizeof(Boolean);
                break;
            }
            }
            classData.ConstantPool.emplace_back(type, data);
            HeadRoundUp(head);
        }

        //////////////////////////////////
        // CLASS DATA ////////////////////
        //////////////////////////////////
        return classData;
    }
}
