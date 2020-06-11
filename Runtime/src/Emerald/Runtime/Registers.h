#pragma once
#include <cstdint>

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

        REGISTER_A_TO_D(a)

        REGISTER_A_TO_D(b)

        REGISTER_A_TO_D(c)

        REGISTER_A_TO_D(d)

        REGISTER_SPECIAL(si)

        REGISTER_SPECIAL(di)

        REGISTER_SPECIAL(sp)

        REGISTER_SPECIAL(bp)

        REGISTER_8_TO_15(8)

        REGISTER_8_TO_15(9)

        REGISTER_8_TO_15(10)

        REGISTER_8_TO_15(11)

        REGISTER_8_TO_15(12)

        REGISTER_8_TO_15(13)

        REGISTER_8_TO_15(14)

        REGISTER_8_TO_15(15)
    };

#undef REGISTER_A_TO_D
#undef REGISTER_SPECIAL
#undef REGISTER_8_TO_15

}
