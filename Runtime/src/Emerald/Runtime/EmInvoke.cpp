#include "EmInvoke.h"

#include <iostream>
#include <thread>
#include <Windows.h>

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

    EmInvokeStatus EmInvoke::Close()
    {
        UnmapViewOfFile(m_Buffer);

        CloseHandle(m_MapFile);
        *(int*)m_Buffer = (int)MemStatus::Exit;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        CloseHandle(m_ProcessInfo.hProcess);
        CloseHandle(m_ProcessInfo.hThread);
        return EmInvokeStatus::Success;
    }
}
