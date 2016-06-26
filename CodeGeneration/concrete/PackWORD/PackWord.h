#ifndef _PACK_WORD_HPP_
#define _PACK_WORD_HPP_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PACKWORD_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PACKWORD_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HAS_PACKWORD_DLL
#    ifdef BUILD_PACKWORD_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKWORD_API __declspec(dllexport)
#               else
#            define PACKWORD_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACKWORD_API __declspec(dllimport)
#               else
#            define PACKWORD_API
#               endif 
#    endif
#else
#    define PACKWORD_API 
#endif

#include "ProjectGenerator.hpp"
#include "FileGenerator.hpp"
#include "SimpleHPPWordErrorGenerator.hpp"
#include "SimpleCPPWordErrorGenerator.hpp"
#include "SimpleHPPCOMWordGenerator.hpp"
#include "SimpleCPPCOMWordGenerator.hpp"
#include "SimpleHPPWordGenerator.hpp"
#include "SimpleCPPWordGenerator.hpp"

using namespace fctr;
using namespace dsg::generator;

namespace dsg {

	struct SimpleHPPWordConv
	: ProjectGenerator<SimpleHPPWordConv>
	{
		static const char * Format_Name;
		static const char * Family_Name;
		typedef SimpleHPPWordGenerator    generator_t;
	};

	struct SimpleCPPWordConv
	: ProjectGenerator<SimpleCPPWordConv>
	{
		static const char * Format_Name;
		static const char * Family_Name;
		typedef SimpleCPPWordGenerator    generator_t;
	};

	struct SimpleHPPCOMWordConv
	: FileGenerator<SimpleHPPCOMWordConv>
	{
		static const char * Format_Name;
		static const char * Family_Name;
		typedef SimpleHPPCOMWordGenerator    generator_t;
	};

	struct SimpleCPPCOMWordConv
	: FileGenerator<SimpleCPPCOMWordConv>
	{
		static const char * Format_Name;
		static const char * Family_Name;
		typedef SimpleCPPCOMWordGenerator    generator_t;
	};

	struct SimpleHPPWordErrorConv
	: FileGenerator<SimpleHPPWordErrorConv>
	{
		static const char * Format_Name;
		static const char * Family_Name;
		typedef SimpleHPPWordErrorGenerator    generator_t;
	};

	struct SimpleCPPWordErrorConv
	: FileGenerator<SimpleCPPWordErrorConv>
	{
		static const char * Format_Name;
		static const char * Family_Name;
		typedef SimpleCPPWordErrorGenerator    generator_t;
	};

}

extern "C" PACKWORD_API void PlugInit(va_list vl, void** res);
extern "C" PACKWORD_API void PlugTerm(void** res);

#endif //_PACK_WORD_HPP_