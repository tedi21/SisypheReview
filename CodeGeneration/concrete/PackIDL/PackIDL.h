#ifndef _PACK_IDL_HPP_
#define _PACK_IDL_HPP_

#include <stdio.h>

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PACKIDL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PACKIDL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_PACKIDL_DLL
#    ifdef BUILD_PACKIDL_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKIDL_API __declspec(dllexport)
#               else
#            define PACKIDL_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKIDL_API __declspec(dllimport)
#               else
#            define PACKIDL_API
#               endif 
#    endif
#else
#    define PACKIDL_API 
#endif

extern "C" PACKIDL_API void PlugInit(va_list vl, void** res);
extern "C" PACKIDL_API void PlugTerm(void** res);

#endif // _PACK_IDL_HPP_

