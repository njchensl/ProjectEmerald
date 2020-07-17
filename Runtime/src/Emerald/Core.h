#pragma once
#include <cstdint>
#include <cstddef>
#include <string>
#include <Windows.h>

namespace Emerald
{
    typedef std::byte Byte;
    typedef std::byte byte;
    typedef int8_t SByte;
    typedef int8_t sbyte;

    typedef uint16_t UShort;
    typedef uint16_t ushort;
    typedef int16_t Short;

    typedef uint32_t UInt;
    typedef uint32_t uint;
    typedef int32_t Int;

    typedef uint64_t ULong;
    typedef uint64_t ulong;
    typedef int64_t Long;

    typedef wchar_t Char;
    typedef wchar_t Character;

    typedef float Float;
    typedef double Double;

    typedef bool Bool;
    typedef bool Boolean;
    typedef std::string String;

    typedef UINT OBJHANDLE;
    static_assert(sizeof(OBJHANDLE) == 4);
    
}

