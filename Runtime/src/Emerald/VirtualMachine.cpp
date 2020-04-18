#include <iostream>
#include <vector>
#include <stack>
#include "VirtualMachine.h"
#include "Instructions.h"

namespace Emerald
{
    VirtualMachine::VirtualMachine(unsigned char* p0) : m_PC(p0), m_PC0(p0)
    {
        unsigned long long codeOffset = NextInt();
        unsigned long long dataOffset = NextInt();
        m_PC = codeOffset + p0;
        m_Data0 = p0 + dataOffset;
        m_OperandStackPtr = m_OperandStack;
        m_OperandStackBasePtr = m_OperandStack + 1;
    }

    void VirtualMachine::Execute()
    {
        unsigned char instruction = NextByte();
        switch (instruction)
        {
        case IADD:
        {
            OperandPush(StackData(OperandPop().AsInt + OperandPop().AsInt));
            break;
        }
        case ISUB:
        {
            long long b = OperandPop().AsInt;
            long long a = OperandPop().AsInt;
            OperandPush(StackData(a - b));
            break;
        }
        case IMUL:
        {
            OperandPush(StackData(OperandPop().AsInt * OperandPop().AsInt));
            break;
        }
        case IDIV:
        {
            OperandPush(StackData(OperandPop().AsInt / OperandPop().AsInt));
            break;
        }
        case INEG:
        {
            OperandPush(StackData(-OperandPop().AsInt));
            break;
        }
        case ICONST_M1:
        {
            OperandPush(StackData(-1LL));
            break;
        }
        case ICONST_0:
        {
            OperandPush(StackData(0LL));
            break;
        }
        case ICONST_1:
        {
            OperandPush(StackData(1LL));
            break;
        }
        case ICONST_2:
        {
            OperandPush(StackData(2LL));
            break;
        }
        case ICONST_3:
        {
            OperandPush(StackData(3LL));
            break;
        }
        case ICONST_4:
        {
            OperandPush(StackData(4LL));
            break;
        }
        case ICONST_5:
        {
            OperandPush(StackData(5LL));
            break;
        }
        case ILDC:
        {
            OperandPush(StackData(NextInt()));
            break;
        }
        case DUP:
        {
            OperandPush(OperandPeek());
            break;
        }
        case IFEQ:
        {
            StackData d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt == 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFGE:
        {
            StackData d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt >= 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFGT:
        {
            StackData d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt > 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFLE:
        {
            StackData d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt <= 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFLT:
        {
            StackData d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt < 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFNE:
        {
            StackData d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt != 0 || d.AsFloat != 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case CALL:
        {
            int numArgs = NextByte();
            auto* address = (unsigned char*)((unsigned long long)m_PC0 + NextInt());
            std::stack<StackData> args;
            for (int i = 0; i < numArgs; i++)
            {
                args.push(OperandPop());
            }
            // push the original base pointer, then the return address onto the operand stack, then the args
            // TODO compressed pointers, instead of saving the data as a pointer, save it as a memory offset, so that
            // the total amount of addressable memory remains 4 GB.
            OperandPush(StackData((long long)m_OperandStackBasePtr));
            OperandPush(StackData((long long)m_PC));
            m_OperandStackBasePtr = m_OperandStackPtr + 1;

            for (int i = 0; i < numArgs; i++)
            {
                OperandPush(args.top());
                args.pop();
            }
            m_PC = address;
            break;
        }
        case RETURN:
        {
            m_OperandStackPtr = m_OperandStackBasePtr - 1;
            m_PC = reinterpret_cast<unsigned char*>(OperandPop().AsInt);
            m_OperandStackBasePtr = reinterpret_cast<StackData*>(OperandPop().AsInt);
            break;
        }
        case DRETURN:
        {
            StackData ret = OperandPop();
            m_OperandStackPtr = m_OperandStackBasePtr - 1;
            m_PC = reinterpret_cast<unsigned char*>(OperandPop().AsInt);
            m_OperandStackBasePtr = reinterpret_cast<StackData*>(OperandPop().AsInt);
            OperandPush(ret);
            break;
        }
        case GOTO:
        {
            long long offset = NextInt();
            //std::cout << offset << std::endl;
            m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            break;
        }
        case I2F:
        {
            OperandPush(StackData((double)OperandPop().AsInt));
            break;
        }
        case F2I:
        {
            OperandPush(StackData((long long)OperandPop().AsFloat));
            break;
        }
        case SWAP:
        {
            int index1 = NextByte();
            int index2 = NextByte();
            StackData temp = m_OperandStackBasePtr[index1];
            m_OperandStackBasePtr[index1] = m_OperandStackBasePtr[index2];
            m_OperandStackBasePtr[index2] = temp;
            break;
        }
        case HALT:
        {
            while (m_OperandStackPtr > m_OperandStack)
            {
                std::cout << OperandPeek().AsInt << "\t" << OperandPop().AsFloat << std::endl;
            }
            exit(0);
            break;
        }
        default:
        {
            throw UnknownInstructionError();
            break;
        }
        }
    }

    inline unsigned char VirtualMachine::NextByte()
    {
        return *(m_PC++);
    }

    StackData VirtualMachine::OperandPeek()
    {
        return *m_OperandStackPtr;
    }

    void VirtualMachine::OperandPush(const StackData& sd)
    {
        *(++m_OperandStackPtr) = sd;
    }

    StackData VirtualMachine::OperandPop()
    {
        return *(m_OperandStackPtr--);
    }

    long long VirtualMachine::NextInt()
    {
        return int64_t((long long)NextByte() |
            (long long)NextByte() << 8 |
            (long long)NextByte() << 16 |
            (long long)NextByte() << 24 |
            (long long)NextByte() << 32 |
            (long long)NextByte() << 40 |
            (long long)NextByte() << 48 |
            (long long)NextByte() << 56);
    }

    VirtualMachine::~VirtualMachine() = default;
}
