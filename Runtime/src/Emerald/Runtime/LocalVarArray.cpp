#include "LocalVarArray.h"

#include "Type.h"

namespace Emerald
{
    LocalVarArray::LocalVarArray(size_t count) : m_Data(new Int[count]), m_Types(new Type[count])
    {
    }

    LocalVarArray::~LocalVarArray()
    {
        delete[] m_Data;
        delete[] m_Types;
    }
}
