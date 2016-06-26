#ifndef _PACK_MD_HPP_
#define _PACK_MD_HPP_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PACKMD_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PACKMD_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_PACKMD_DLL
#    ifdef BUILD_PACKMD_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKMD_API __declspec(dllexport)
#               else
#            define PACKMD_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKMD_API __declspec(dllimport)
#               else
#            define PACKMD_API
#               endif 
#    endif
#else
#    define PACKMD_API
#endif

#include "ProjectGenerator.hpp"
#include "FileGenerator.hpp"
#include "SimpleMDGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleMDConv
    : ProjectGenerator<SimpleMDConv>
    {
        static const char* Format_Name;
        static const char* Family_Name;
        typedef SimpleMDGenerator    generator_t;
    };

}

extern "C" PACKMD_API void PlugInit(va_list vl, void** res);
extern "C" PACKMD_API void PlugTerm(void** res);

#endif //_PACK_MD_HPP_
