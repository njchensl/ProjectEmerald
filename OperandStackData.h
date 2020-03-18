#pragma once

struct StackData {
    explicit StackData();

    explicit StackData(int);

    explicit StackData(float);

    union {
        int asInt;
        float asFloat;
    };
};
