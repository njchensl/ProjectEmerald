#include "OperandStackData.h"

namespace Emerald
{
    StackData::StackData(long long i) {
        AsInt = i;
    }

    StackData::StackData(double f) {
        AsFloat = f;
    }

    StackData::StackData() {
        AsInt = 0;
    }

}
