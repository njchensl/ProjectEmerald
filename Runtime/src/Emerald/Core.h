#pragma once

#ifdef EM_DEBUG
#define EM_ENABLE_ASSERTS
#endif

#ifdef EM_ENABLE_ASSERTS
#define EM_CORE_ASSERT(x, msg) { if(!(x)) { printf("Assertion Failed: %s\n", msg); __debugbreak(); } }
#else
#define EM_CORE_ASSERT(x, msg)
#endif
