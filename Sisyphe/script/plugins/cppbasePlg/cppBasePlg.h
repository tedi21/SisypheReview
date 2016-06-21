#ifndef CPPBASEPLG_H
#define CPPBASEPLG_H
#include <cstdarg>

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the PACKCPP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// PACKCPP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_CPPBASEPLG_DLL
#    ifdef BUILD_CPPBASEPLG_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define CPPBASEPLG_API __declspec(dllexport)
#               else
#            define CPPBASEPLG_API
#               endif
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define CPPBASEPLG_API __declspec(dllimport)
#               else
#            define CPPBASEPLG_API
#               endif
#    endif
#else
#    define CPPBASEPLG_API
#endif

extern "C" CPPBASEPLG_API void PlugInit(va_list vl, void** res);
extern "C" CPPBASEPLG_API void PlugTerm(void** res);

#endif // CPPBASEPLG_H
