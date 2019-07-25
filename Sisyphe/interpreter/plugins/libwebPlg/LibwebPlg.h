#ifndef LIBWEBPLG_H
#define LIBWEBPLG_H
#include <cstdarg>

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIBWEBPLG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIBWEBPLG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_LIBWEBPLG_DLL
#    ifdef BUILD_LIBWEBPLG_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBWEBPLG_API __declspec(dllexport)
#               else
#            define LIBWEBPLG_API
#               endif
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBWEBPLG_API __declspec(dllimport)
#               else
#            define LIBWEBPLG_API
#               endif
#    endif
#else
#    define LIBWEBPLG_API
#endif

extern "C" LIBWEBPLG_API void PlugInit(va_list vl, void** res);
extern "C" LIBWEBPLG_API void PlugTerm(void** res);

#endif // LIBWEBPLG_H
