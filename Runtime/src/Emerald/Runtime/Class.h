#pragma once
#include "Core.h"

namespace Emerald
{
    class Class
    {
    public:
        Class(const Class&) = delete;
        Class& operator=(const Class&) = delete;
        Class(Class&&) = delete;
        Class& operator=(Class&&) = delete;
    private:
        String m_Name;
    };
}
