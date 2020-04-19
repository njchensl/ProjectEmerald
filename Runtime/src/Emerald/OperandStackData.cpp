#include "OperandStackData.h"

namespace Emerald
{
    DataUnit::DataUnit(long long i) {
        AsInt = i;
    }

    DataUnit::DataUnit(double f) {
        AsFloat = f;
    }

    DataUnit::DataUnit(void* ptr)
    {
        AsPointer = ptr;
    }

    DataUnit::DataUnit() {
        AsInt = 0;
    }

}
