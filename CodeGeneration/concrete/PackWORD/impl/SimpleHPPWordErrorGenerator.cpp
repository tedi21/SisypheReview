#include "SimpleHPPWordErrorGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHPPWordErrorGenerator::SimpleHPPWordErrorGenerator()
		{
			SourceHPP = 
				CreateFile;

			CreateFile =
				                CreateHeader(str_g("word_error.h"))
				<< line_g(1) << CreateHPPDefine(str_g("_word_error_h_"))
				<< CreateInclude
				<< line_g(1) << CreateNamespace(str_g("word"))
                << CreateWordFunction     
				<< line_g(1) << CreateEndNamespace
				<< line_g(1) << CreateHPPEndDefine;            

			CreateInclude =
				   line_g(1) << STR_G(#include <windows.h>)
                << line_g(1) << STR_G(#include <TCHAR.H>);

			CreateWordFunction =
                   line_g(1) << htab_g(1) << STR_G(void ErrHandler(HRESULT hr, EXCEPINFO excep););

		}
    }
}