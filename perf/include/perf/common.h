#pragma once

#ifdef _MSC_VER
  #ifdef PERFLIB_EXPORTS
    #define PERFLIB_API __declspec(dllexport)
  #else // PERFLIB_EXPORTS
    #define PERFLIB_API __declspec(dllimport)
  #endif // PERFLIB_EXPORTS
#else
  #define PERFLIB_API
#endif // _MSC_VER
