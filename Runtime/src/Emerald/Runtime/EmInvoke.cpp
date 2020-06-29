#include "EmInvoke.h"

#include <iostream>
#include <thread>
#include <Windows.h>

#include "Utils.h"

namespace Emerald
{
#define BUF_SIZE 8192


    EmInvokeStatus EmInvoke::Init()
    {
        memset(&m_StartupInfo, 0, sizeof(m_StartupInfo));
        memset(&m_ProcessInfo, 0, sizeof(m_ProcessInfo));
        if (!CreateProcess(R"(EmeraldInvoke.exe)",
                           (LPSTR)"",
                           nullptr,
                           nullptr,
                           FALSE,
                           0,
                           nullptr,
                           nullptr,
                           &m_StartupInfo, &m_ProcessInfo))
        {
            fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
            return EmInvokeStatus::Failed;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        m_MapFile = OpenFileMapping(
            FILE_MAP_ALL_ACCESS,
            FALSE,
            "em-invoke");
        if (m_MapFile == nullptr)
        {
            fprintf(stderr, TEXT("Could not open file mapping object (%lu).\n"),
                    GetLastError());
            return EmInvokeStatus::Failed;
        }
        LPTSTR pBuf = (LPTSTR)MapViewOfFile(m_MapFile,
                                            FILE_MAP_ALL_ACCESS,
                                            0,
                                            0,
                                            BUF_SIZE);

        if (pBuf == nullptr)
        {
            fprintf(stderr, TEXT("Could not map view of file (%lu).\n"),
                    GetLastError());

            CloseHandle(m_MapFile);

            return EmInvokeStatus::Failed;
        }

        m_Buffer = (uint8_t*)pBuf;

        return EmInvokeStatus::Success;
    }

    EmInvokeStatus EmInvoke::Call(
        byte moduleNameLength, char* moduleName,
        byte functionNameLength, char* functionName,
        byte callingConvention,
        char returnFormat,
        byte numArgs, char* argFormat, byte* argsPacked)
    {
        byte* head = (byte*)(m_Buffer + 8);

        *head = moduleNameLength;
        head++;
        memcpy(head, moduleName, (size_t)moduleNameLength);
        head += (size_t)moduleNameLength;
        head = (byte*)RoundUp<ulong, 8>((ulong)head);

        *head = functionNameLength;
        head++;
        memcpy(head, functionName, (size_t)functionNameLength);
        head += (size_t)functionNameLength;
        head = (byte*)RoundUp<ulong, 8>((ulong)head);

        *head = callingConvention;
        head++;
        *(char*)head = returnFormat;
        head++;
        *head = numArgs;
        head++;
        memcpy(head, argFormat, (size_t)numArgs);
        head += (size_t)numArgs;
        head = (byte*)RoundUp<ulong, 8>((ulong)head);

        byte* argHead = argsPacked;
        for (int i = 0; i < (int)numArgs; i++)
        {
            switch (argFormat[i])
            {
#define ARG_TYPE_CASE(name, type) case name : { memcpy(head, argHead, sizeof(type)); argHead += sizeof(type); head += 8; break; }

            ARG_TYPE_CASE('c', Byte)
            case '2':
            ARG_TYPE_CASE('s', Short)
            case '4':
            case 'l':
            ARG_TYPE_CASE('i', Int)
            case '8':
            ARG_TYPE_CASE('e', Long)
            ARG_TYPE_CASE('f', Float)
            ARG_TYPE_CASE('d', Double)

#undef ARG_TYPE_CASE
            case 'p':
            {
                // pointer marshalling
                // uint size + data
                uint size = *(uint*)argHead;
                argHead += sizeof(uint);
                *(uint*)head = size;
                head += 8;

                memcpy(head, argHead, size);
                argHead += size;
                head += size;
                head = (byte*)RoundUp<ulong, 8>((ulong)head);
                break;
            }
            }
        }

        *(int*)m_Buffer = (int)MemStatus::ServerRead;
        while (*(MemStatus*)m_Buffer != MemStatus::ClientRead);
        // read execution result

        // return value

        // pointers


        return EmInvokeStatus::Success;
    }

    EmInvokeStatus EmInvoke::Close()
    {
        *(int*)m_Buffer = (int)MemStatus::Exit;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        UnmapViewOfFile(m_Buffer);
        CloseHandle(m_MapFile);
        CloseHandle(m_ProcessInfo.hProcess);
        CloseHandle(m_ProcessInfo.hThread);
        return EmInvokeStatus::Success;
    }
}
