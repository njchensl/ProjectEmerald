#pragma once

namespace Emerald
{
    struct StackData {
        explicit StackData();

        explicit StackData(long long);

        explicit StackData(double);

        union {
            long long AsInt;
            double AsFloat;
        };
    };
}

