#include "Registers.h"

#include <cstring>

namespace Emerald
{
    Registers::Registers()
    {
        memset(this, 0, sizeof Registers);
    }
}
