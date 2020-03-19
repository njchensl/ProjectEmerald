#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#include "OperandStackData.h"

StackData::StackData(long long i) {
    asInt = i;
}

StackData::StackData(double f) {
    asFloat = f;
}

StackData::StackData() {
    asInt = 0;
}

#pragma clang diagnostic pop