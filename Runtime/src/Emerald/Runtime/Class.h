#pragma once
#include "Core.h"

namespace Emerald
{
    class Class
    {
    public:
        Class(const Class&) = delete;
        Class& operator=(const Class&) = delete;

        Class(Class&&)
        {
        }

        Class& operator=(Class&&)
        {
        }

    private:
        String m_Name;
    };
}
