#ifndef _PACK_INTERPRETER_HPP_
#define _PACK_INTERPRETER_HPP_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PACKINTERPRETER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PACKINTERPRETER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_PACKINTERPRETER_DLL
#    ifdef BUILD_PACKINTERPRETER_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKINTERPRETER_API __declspec(dllexport)
#               else
#            define PACKINTERPRETER_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKINTERPRETER_API __declspec(dllimport)
#               else
#            define PACKINTERPRETER_API
#               endif 
#    endif
#else
#    define PACKINTERPRETER_API
#endif

#include "ProjectGenerator.hpp"
#include "FileGenerator.hpp"
#include "SimpleHPPInterpreterGenerator.hpp"
#include "SimpleCPPInterpreterGenerator.hpp"
#include "SimpleCPPDataInterpreterGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

    struct SimpleHPPInterpreterConv
    : ProjectGenerator<SimpleHPPInterpreterConv>
    {
        static const char* Format_Name;
        static const char* Family_Name;
        typedef SimpleHPPInterpreterGenerator    generator_t;
    };

    struct SimpleCPPInterpreterConv
    : ProjectGenerator<SimpleCPPInterpreterConv>
    {
        static const char* Format_Name;
        static const char* Family_Name;
        typedef SimpleCPPInterpreterGenerator    generator_t;
    };

    struct SimpleCPPDataInterpreterConv
    : FileGenerator<SimpleCPPDataInterpreterConv>
    {
        static const char* Format_Name;
        static const char* Family_Name;
        typedef SimpleCPPDataInterpreterGenerator    generator_t;
    };
}

extern "C" PACKINTERPRETER_API void PlugInit(va_list vl, void** res);
extern "C" PACKINTERPRETER_API void PlugTerm(void** res);

#endif //_PACK_INTERPRETER_HPP_
