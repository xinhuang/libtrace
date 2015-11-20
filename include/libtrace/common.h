#pragma once

#ifdef _MSC_VER
  #ifdef LIBTRACE_EXPORTS
    #define PERFLIB_API __declspec(dllexport)
  #else // LIBTRACE_EXPORTS
    #define PERFLIB_API __declspec(dllimport)
  #endif // LIBTRACE_EXPORTS
#else
  #define PERFLIB_API
#endif // _MSC_VER
