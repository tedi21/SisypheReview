#ifndef _PACK_SQL_HPP_
#define _PACK_SQL_HPP_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PACKSQL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PACKSQL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_PACKSQL_DLL
#    ifdef BUILD_PACKSQL_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKSQL_API __declspec(dllexport)
#               else
#            define PACKSQL_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKSQL_API __declspec(dllimport)
#               else
#            define PACKSQL_API
#               endif 
#    endif
#else
#    define PACKSQL_API 
#endif

#include "SimpleSQLGenerator.hpp"
#include "SimpleSQLParser.hpp"
#include "ProjectConverter.hpp"

using namespace fctr;
using namespace dsg::generator;
using namespace dsg::parser;

namespace dsg {
    // This class is exported from the PackSQL.dll
    struct SimpleSQLConverter
    : ProjectConverter<SimpleSQLConverter>
    {
        static const char * Format_Name;
        static const char * Family_Name;
        typedef SimpleSQLGenerator generator_t;
        typedef SimpleSQLParser    parser_t; 
    };

}

extern "C" PACKSQL_API void PlugInit(va_list vl, void** res);
extern "C" PACKSQL_API void PlugTerm(void** res);

#endif

