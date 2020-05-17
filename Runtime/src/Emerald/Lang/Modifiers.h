#pragma once
#include <map>
#include <string>

#include "../Core.h"

namespace Emerald
{
    enum class Visibility : unsigned char
    {
        Public = 0,
        Protected = 1,
        Private = 2
    };

    inline std::string VisibilityToString(Visibility visibility)
    {
        switch (visibility)
        {
        case Visibility::Public:
        {
            return "public";
        }
        case Visibility::Protected:
        {
            return "protected";
        }
        case Visibility::Private:
        {
            return "Private";
        }
        }
        EM_CORE_ASSERT(false, "Unsupported visibility modifier!");
        // should never reach here
        return "";
    }
}
