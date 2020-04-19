#pragma once

namespace Emerald
{
    struct DataUnit {
        explicit DataUnit();

        explicit DataUnit(long long);

        explicit DataUnit(double);

        explicit DataUnit(void* ptr);

        union {
            long long AsInt;
            unsigned long long AsUnsignedInt;
            double AsFloat;
            void* AsPointer;
        };
    };
}

