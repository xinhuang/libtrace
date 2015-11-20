#pragma once

#ifdef _MSC_VER
  #ifdef LIBTRACE_EXPORTS
    #define LIBTRACE_API __declspec(dllexport)
  #else // LIBTRACE_EXPORTS
    #define LIBTRACE_API __declspec(dllimport)
  #endif // LIBTRACE_EXPORTS
#else
  #define LIBTRACE_API
#endif // _MSC_VER
