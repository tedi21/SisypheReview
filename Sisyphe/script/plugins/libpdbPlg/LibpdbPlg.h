#ifndef LIBPDBPLG_H
#define LIBPDBPLG_H
#include <cstdarg>

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIBPDBPLG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIBPDBPLG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_LIBPDBPLG_DLL
#    ifdef BUILD_LIBPDBPLG_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBPDBPLG_API __declspec(dllexport)
#               else
#            define LIBPDBPLG_API
#               endif
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBPDBPLG_API __declspec(dllimport)
#               else
#            define LIBPDBPLG_API
#               endif
#    endif
#else
#    define LIBPDBPLG_API
#endif

extern "C" LIBPDBPLG_API void PlugInit(va_list vl, void** res);
extern "C" LIBPDBPLG_API void PlugTerm(void** res);

#endif // LIBPDBPLG_H
