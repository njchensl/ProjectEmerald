#pragma once
#include <cstdint>
#include <bitset>
#include "../Core.h"

namespace Emerald
{
#define REGISTER_A_TO_D(letter)  union { \
    struct {\
        uint8_t letter##l;\
        uint8_t letter##h;\
    };\
    uint16_t letter##x;\
    uint32_t e##letter##x;\
    uint64_t r##letter##x;\
    };

#define REGISTER_SPECIAL(letters)  union { \
    uint8_t letters##l;\
    uint16_t letters;\
    uint32_t e##letters;\
    uint64_t r##letters;\
    };

#define REGISTER_8_TO_15(number) union { \
    uint8_t r##number##b;\
    uint16_t r##number##w;\
    uint32_t r##number##d;\
    uint64_t r##number;\
    };

    struct Registers
    {
        Registers();

        //REGISTER_A_TO_D(a)
        //REGISTER_A_TO_D(b)
        //REGISTER_A_TO_D(c)
        //REGISTER_A_TO_D(d)
        //REGISTER_SPECIAL(si)
        //REGISTER_SPECIAL(di)
        union
        {
            struct
            {
                union
                {
                    const uint e0;

                    union {
                        const ulong r0;
                        byte* const r0Ptr;
                    };
                };

                union
                {
                    uint ep0;

                    union
                    {
                        ulong rp0;
                        byte* rp0Ptr;
                    };
                };

                union
                {
                    byte spl;
                    ushort sp;
                    uint esp;

                    union
                    {
                        ulong rsp;
                        byte* rspPtr;
                    };
                };

                union
                {
                    byte bpl;
                    ushort bp;
                    uint ebp;

                    union
                    {
                        ulong rbp;
                        byte* rbpPtr;
                    };
                };

                union
                {
                    byte ipl;
                    ushort ip;
                    uint eip;

                    union
                    {
                        ulong rip;
                        byte* ripPtr;
                    };
                };
            };

            ulong SpecialRegisters[5];
        };

        void ClearFlags();

        Bool GetZF() const;

        Bool GetSF() const;

        void SetZF(Bool val);

        void SetSF(Bool val);

    private:
        std::bitset<sizeof(ulong)> m_Flags;

        static constexpr size_t ZF = 0;
        static constexpr size_t SF = 1;
        static constexpr size_t OF = 2; // future ues

        //REGISTER_8_TO_15(8)
        //REGISTER_8_TO_15(9)
        //REGISTER_8_TO_15(10)
        //REGISTER_8_TO_15(11)
        //REGISTER_8_TO_15(12)
        //REGISTER_8_TO_15(13)
        //REGISTER_8_TO_15(14)
        //REGISTER_8_TO_15(15)
    };

#undef REGISTER_A_TO_D
#undef REGISTER_SPECIAL
#undef REGISTER_8_TO_15
}
