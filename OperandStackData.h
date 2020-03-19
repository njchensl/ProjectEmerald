#pragma once

struct StackData {
    explicit StackData();

    explicit StackData(long long);

    explicit StackData(double);

    union {
        long long asInt;
        double asFloat;
    };
};
