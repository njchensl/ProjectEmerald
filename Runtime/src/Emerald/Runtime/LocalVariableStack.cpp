#include "LocalVariableStack.h"

namespace Emerald
{
    LocalVariableStack::~LocalVariableStack()
    {
        free(m_BaseAddress);
    }
}
