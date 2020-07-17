#include "VirtualMachine.h"

#include "../Core.h"
#include "../Instructions.h"

namespace Emerald
{
    VirtualMachine::VirtualMachine(byte* p0)
    {
        m_Registers.rip = (ulong)p0;
        ulong codeOffset = NextULong();
        ulong dataOffset = NextULong();
        m_Registers.rip = codeOffset + (ulong)p0;
        m_Registers.rp0 = m_Registers.rip;
        m_Data0 = p0 + dataOffset;
        Running = true;
    }

    void VirtualMachine::Execute()
    {
        ushort instruction = NextUShort();
        switch (instruction)
        {
        default:
        {
            throw UnknownInstructionError();
        }
        }
    }

#define VM_NEXT_MEMBER_FUNCTION(type) type VirtualMachine::Next##type () { type value = ptr_copy_cast<type>(m_Registers.ripPtr, sizeof(type)); m_Registers.rip += sizeof(type); return value; }

    VM_NEXT_MEMBER_FUNCTION(Byte)
    VM_NEXT_MEMBER_FUNCTION(UShort)
    VM_NEXT_MEMBER_FUNCTION(Short)
    VM_NEXT_MEMBER_FUNCTION(Int)
    VM_NEXT_MEMBER_FUNCTION(UInt)
    VM_NEXT_MEMBER_FUNCTION(Long)
    VM_NEXT_MEMBER_FUNCTION(ULong)
    VM_NEXT_MEMBER_FUNCTION(Float)
    VM_NEXT_MEMBER_FUNCTION(Double)
    VM_NEXT_MEMBER_FUNCTION(Bool)
    VM_NEXT_MEMBER_FUNCTION(Char)

#undef VM_NEXT_MEMBER_FUNCTION

    VirtualMachine::~VirtualMachine() = default;
}
