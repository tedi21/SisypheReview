#ifndef LIBDEBUGPLG_H
#define LIBDEBUGPLG_H
#include <cstdarg>

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIBDEBUGPLG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIBDEBUGPLG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_LIBDEBUGPLG_DLL
#    ifdef BUILD_LIBDEBUGPLG_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBDEBUGPLG_API __declspec(dllexport)
#               else
#            define LIBDEBUGPLG_API
#               endif
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBDEBUGPLG_API __declspec(dllimport)
#               else
#            define LIBDEBUGPLG_API
#               endif
#    endif
#else
#    define LIBDEBUGPLG_API
#endif

extern "C" LIBDEBUGPLG_API void PlugInit(va_list vl, void** res);
extern "C" LIBDEBUGPLG_API void PlugTerm(void** res);

#endif // LIBDEBUGPLG_H
