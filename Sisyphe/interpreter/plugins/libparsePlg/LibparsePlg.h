#ifndef LIBPARSEPLG_H
#define LIBPARSEPLG_H
#include <cstdarg>

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIBPARSEPLG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIBPARSEPLG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_LIBPARSEPLG_DLL
#    ifdef BUILD_LIBPARSEPLG_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBPARSEPLG_API __declspec(dllexport)
#               else
#            define LIBPARSEPLG_API
#               endif
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBPARSEPLG_API __declspec(dllimport)
#               else
#            define LIBPARSEPLG_API
#               endif
#    endif
#else
#    define LIBPARSEPLG_API
#endif

extern "C" LIBPARSEPLG_API void PlugInit(va_list vl, void** res);
extern "C" LIBPARSEPLG_API void PlugTerm(void** res);

#endif // LIBPARSEPLG_H
