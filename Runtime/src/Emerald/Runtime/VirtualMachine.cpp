#include "VirtualMachine.h"

#if 0
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
            OperandPush(DataUnit(OperandPop().AsInt + OperandPop().AsInt));
            break;
        }
        case ISUB:
        {
            long long b = OperandPop().AsInt;
            long long a = OperandPop().AsInt;
            OperandPush(DataUnit(a - b));
            break;
        }
        case IMUL:
        {
            OperandPush(DataUnit(OperandPop().AsInt * OperandPop().AsInt));
            break;
        }
        case IDIV:
        {
            OperandPush(DataUnit(OperandPop().AsInt / OperandPop().AsInt));
            break;
        }
        case INEG:
        {
            OperandPush(DataUnit(-OperandPop().AsInt));
            break;
        }
        case ICONST_M1:
        {
            OperandPush(DataUnit(-1LL));
            break;
        }
        case ICONST_0:
        {
            OperandPush(DataUnit(0LL));
            break;
        }
        case ICONST_1:
        {
            OperandPush(DataUnit(1LL));
            break;
        }
        case ICONST_2:
        {
            OperandPush(DataUnit(2LL));
            break;
        }
        case ICONST_3:
        {
            OperandPush(DataUnit(3LL));
            break;
        }
        case ICONST_4:
        {
            OperandPush(DataUnit(4LL));
            break;
        }
        case ICONST_5:
        {
            OperandPush(DataUnit(5LL));
            break;
        }
        case ILDC:
        {
            OperandPush(DataUnit(NextInt()));
            break;
        }
        case DUP:
        {
            OperandPush(OperandPeek());
            break;
        }
        case IFEQ:
        {
            DataUnit d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt == 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFGE:
        {
            DataUnit d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt >= 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFGT:
        {
            DataUnit d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt > 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFLE:
        {
            DataUnit d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt <= 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFLT:
        {
            DataUnit d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt < 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case IFNE:
        {
            DataUnit d = OperandPop();
            long long offset = NextInt();
            if (d.AsInt != 0 || d.AsFloat != 0)
            {
                m_PC = (unsigned char*)((unsigned long long)m_PC0 + offset);
            }
            break;
        }
        case PTR_ACCESS:
        {
            auto* ptr = (DataUnit*)OperandPop().AsPointer;
            OperandPush(*ptr);
            break;
        }
        case PTR_STORE:
        {
            DataUnit data = OperandPop();
            auto* ptr = (DataUnit*)OperandPop().AsPointer;
            *ptr = data;
            break;
        }
        case PTR_STACK:
        {
            OperandPush(DataUnit(m_OperandStackPtr));
            break;
        }
        case CALL:
        {
            int numArgs = NextByte();
            auto* address = (unsigned char*)((unsigned long long)m_PC0 + NextInt());
            std::stack<DataUnit> args;
            for (int i = 0; i < numArgs; i++)
            {
                args.push(OperandPop());
            }
            // push the original base pointer, then the return address onto the operand stack, then the args
            // TODO compressed pointers, instead of saving the data as a pointer, save it as a memory offset, so that
            // the total amount of addressable memory remains 4 GB.
            OperandPush(DataUnit((long long)m_OperandStackBasePtr));
            OperandPush(DataUnit((long long)m_PC));
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
            m_OperandStackBasePtr = reinterpret_cast<DataUnit*>(OperandPop().AsInt);
            break;
        }
        case DRETURN:
        {
            DataUnit ret = OperandPop();
            m_OperandStackPtr = m_OperandStackBasePtr - 1;
            m_PC = reinterpret_cast<unsigned char*>(OperandPop().AsInt);
            m_OperandStackBasePtr = reinterpret_cast<DataUnit*>(OperandPop().AsInt);
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
            OperandPush(DataUnit((double)OperandPop().AsInt));
            break;
        }
        case F2I:
        {
            OperandPush(DataUnit((long long)OperandPop().AsFloat));
            break;
        }
        case SWAP:
        {
            int index1 = NextByte();
            int index2 = NextByte();
            DataUnit temp = m_OperandStackBasePtr[index1];
            m_OperandStackBasePtr[index1] = m_OperandStackBasePtr[index2];
            m_OperandStackBasePtr[index2] = temp;
            break;
        }
        case POP:
        {
            OperandPop();
            break;
        }
        case POP2:
        {
            OperandPop();
            OperandPop();
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

    DataUnit VirtualMachine::OperandPeek()
    {
        return *m_OperandStackPtr;
    }

    void VirtualMachine::OperandPush(const DataUnit& du)
    {
        *(++m_OperandStackPtr) = du;
    }

    DataUnit VirtualMachine::OperandPop()
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

#endif