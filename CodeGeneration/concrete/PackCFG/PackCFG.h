#ifndef _PACK_CFG_HPP_
#define _PACK_CFG_HPP_

#include <stdio.h>

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PACKCFG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PACKCFG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_PACKCFG_DLL
#    ifdef BUILD_PACKCFG_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKCFG_API __declspec(dllexport)
#               else
#            define PACKCFG_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKCFG_API __declspec(dllimport)
#               else
#            define PACKCFG_API
#               endif 
#    endif
#else
#    define PACKCFG_API
#endif

extern "C" PACKCFG_API void PlugInit(va_list vl, void** res);
extern "C" PACKCFG_API void PlugTerm(void** res);

#endif // _PACK_CFG_HPP_

