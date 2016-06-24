#ifndef LIBWORDPLG_H
#define LIBWORDPLG_H
#include <cstdarg>

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LIBWORDPLG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LIBWORDPLG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_LIBWORDPLG_DLL
#    ifdef BUILD_LIBWORDPLG_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBWORDPLG_API __declspec(dllexport)
#               else
#            define LIBWORDPLG_API
#               endif
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBWORDPLG_API __declspec(dllimport)
#               else
#            define LIBWORDPLG_API
#               endif
#    endif
#else
#    define LIBWORDPLG_API
#endif

extern "C" LIBWORDPLG_API void PlugInit(va_list vl, void** res);
extern "C" LIBWORDPLG_API void PlugTerm(void** res);

#endif // LIBWORDPLG_H
