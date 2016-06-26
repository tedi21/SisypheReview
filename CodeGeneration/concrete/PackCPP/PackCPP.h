#ifndef _PACK_CPP_HPP_
#define _PACK_CPP_HPP_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PACKCPP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PACKCPP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_PACKCPP_DLL
#    ifdef BUILD_PACKCPP_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKCPP_API __declspec(dllexport)
#               else
#            define PACKCPP_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKCPP_API __declspec(dllimport)
#               else
#            define PACKCPP_API
#               endif 
#    endif
#else
#    define PACKCPP_API 
#endif

#include "ProjectGenerator.hpp"
#include "FileGenerator.hpp"
#include "SimpleHPPLogGenerator.hpp"
#include "SimpleHPPExportGenerator.hpp"
#include "SimpleHPPEntityGenerator.hpp"
#include "SimpleHPPAccessGenerator.hpp"
#include "SimpleCPPAccessGenerator.hpp"
#include "SimpleHDataGenerator.hpp"
#include "SimpleHPPPredicateGenerator.hpp"
#include "SimpleHPPInterpreterGenerator.hpp"
#include "SimpleCPPInterpreterGenerator.hpp"
#include "SimpleHPPInterpreterAccessGenerator.hpp"
#include "SimpleCPPInterpreterAccessGenerator.hpp"
#include "SimpleCPPInterpreterDataGenerator.hpp"
#include "SimpleCPPDataGenerator.hpp"
#include "SimpleMDGenerator.hpp"
#include "SimpleMDAccessGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

	struct SimpleHPPEntityConv
	: ProjectGenerator<SimpleHPPEntityConv>
	{
		static const char* Format_Name;
		static const char* Family_Name;
		typedef SimpleHPPEntityGenerator    generator_t;
	};

	struct SimpleHPPAccessConv
	: ProjectGenerator<SimpleHPPAccessConv>
	{
		static const char* Format_Name;
		static const char* Family_Name;
		typedef SimpleHPPAccessGenerator    generator_t;
	};

	struct SimpleCPPAccessConv
	: ProjectGenerator<SimpleCPPAccessConv>
	{
		static const char* Format_Name;
		static const char* Family_Name;
		typedef SimpleCPPAccessGenerator    generator_t;
	};

	struct SimpleHPPPredicateConv
	: ProjectGenerator<SimpleHPPPredicateConv>
	{
		static const char* Format_Name;
		static const char* Family_Name;
		typedef SimpleHPPPredicateGenerator    generator_t;
	};

	struct SimpleHPPLogConv
	: FileGenerator<SimpleHPPLogConv>
	{
		static const char* Format_Name;
		static const char* Family_Name;
		typedef SimpleHPPLogGenerator    generator_t;
	};

    struct SimpleHPPExportConv
    : FileGenerator<SimpleHPPExportConv>
    {
        static const char* Format_Name;
        static const char* Family_Name;
        typedef SimpleHPPExportGenerator    generator_t;
    };

	struct SimpleHDataConv
	: FileGenerator<SimpleHDataConv>
	{
		static const char* Format_Name;
		static const char* Family_Name;
		typedef SimpleHDataGenerator    generator_t;
	};

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

	struct SimpleHPPInterpreterAccessConv
	: ProjectGenerator<SimpleHPPInterpreterAccessConv>
	{
		static const char* Format_Name;
		static const char* Family_Name;
		typedef SimpleHPPInterpreterAccessGenerator    generator_t;
	};

	struct SimpleCPPInterpreterAccessConv
	: ProjectGenerator<SimpleCPPInterpreterAccessConv>
	{
		static const char* Format_Name;
		static const char* Family_Name;
		typedef SimpleCPPInterpreterAccessGenerator    generator_t;
	};

	struct SimpleCPPInterpreterDataConv
	: FileGenerator<SimpleCPPInterpreterDataConv>
	{
		static const char* Format_Name;
		static const char* Family_Name;
		typedef SimpleCPPInterpreterDataGenerator    generator_t;
	};

    struct SimpleCPPDataConv
    : FileGenerator<SimpleCPPDataConv>
    {
        static const char* Format_Name;
        static const char* Family_Name;
        typedef SimpleCPPDataGenerator    generator_t;
    };


    struct SimpleMDConv
    : ProjectGenerator<SimpleMDConv>
    {
        static const char* Format_Name;
        static const char* Family_Name;
        typedef SimpleMDGenerator    generator_t;
    };

    struct SimpleMDAccessConv
    : ProjectGenerator<SimpleMDAccessConv>
    {
        static const char* Format_Name;
        static const char* Family_Name;
        typedef SimpleMDAccessGenerator    generator_t;
    };
}

extern "C" PACKCPP_API void PlugInit(va_list vl, void** res);
extern "C" PACKCPP_API void PlugTerm(void** res);

#endif //_PACK_CPP_HPP_
