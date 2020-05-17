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
            unsigned long long value = (unsigned int)lower | (unsigned int)higher << 4;
            return *(double*)&value;
        }
    };
}
