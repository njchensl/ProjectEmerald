#pragma once

namespace Emerald
{
    struct alignas(4) DataUnit
    {
        explicit DataUnit(int intValue)
        {
            AsInt = intValue;
        }

        explicit DataUnit(float floatValue)
        {
            AsFloat = floatValue;
        }

        union
        {
            int AsInt;
            float AsFloat;
            // TODO : reference type
            unsigned int AsUInt; // for internal use only
        };

        explicit operator int()
        {
            return AsInt;
        }

        explicit operator unsigned int()
        {
            return AsUInt;
        }

        explicit operator float()
        {
            return AsFloat;
        }

        static double GetDoubleValue(DataUnit lower, DataUnit higher)
        {
            unsigned long long value = (unsigned int)lower | (unsigned long long)(unsigned int)higher << 32;
            return *(double*)&value;
        }

        static long long GetLongValue(DataUnit lower, DataUnit higher)
        {
            unsigned long long value = (unsigned int)lower | (unsigned long long)(unsigned int)higher << 32;
            return *(long long*)&value;
        }
    };
}
