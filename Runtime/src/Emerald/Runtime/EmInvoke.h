#pragma once

#include <cstdint>
#include <processthreadsapi.h>

namespace Emerald
{
    enum class MemStatus : int
    {
        Exit = -1,
        Idle = 0,
        ServerRead = 1,
        ClientRead = 2
    };

    enum class EmInvokeStatus : int
    {
        Success = 0,
        Failed = 1
    };

    class EmInvoke
    {
    public:
        static EmInvokeStatus Init();
        static EmInvokeStatus Close();
    private:
        inline static STARTUPINFO m_StartupInfo;
        inline static PROCESS_INFORMATION m_ProcessInfo;
        inline static uint8_t* m_Buffer;
        inline static HANDLE m_MapFile;
    };
}
