#ifndef LIBDIFFPLG_H
#define LIBDIFFPLG_H
#include <cstdarg>

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIBDIFFPLG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIBDIFFPLG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_LIBDIFFPLG_DLL
#    ifdef BUILD_LIBDIFFPLG_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBDIFFPLG_API __declspec(dllexport)
#               else
#            define LIBDIFFPLG_API
#               endif
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBDIFFPLG_API __declspec(dllimport)
#               else
#            define LIBDIFFPLG_API
#               endif
#    endif
#else
#    define LIBDIFFPLG_API
#endif

extern "C" LIBDIFFPLG_API void PlugInit(va_list vl, void** res);
extern "C" LIBDIFFPLG_API void PlugTerm(void** res);

#endif // LIBDIFFPLG_H
