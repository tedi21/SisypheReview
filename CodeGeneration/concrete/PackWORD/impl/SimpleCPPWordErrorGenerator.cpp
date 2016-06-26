#include "SimpleCPPWordErrorGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleCPPWordErrorGenerator::SimpleCPPWordErrorGenerator()
		{
			SourceCPP = 
				CreateFile;

			CreateFile =
				                CreateInclude
				<< line_g(1) << CreateNamespace(str_g("word"))
                << CreateWordFunction      
				<< line_g(1) << CreateEndNamespace;            

			CreateInclude =
                   line_g(1) << STR_G(#include "word_error.h")
                << line_g(1) << STR_G(#include <stdio.h>);

			CreateWordFunction =
                   line_g(1) << htab_g(1) << "void ErrHandler(HRESULT hr, EXCEPINFO excep)"
				<< line_g(1) << htab_g(1) << "{"
				<< line_g(1) << htab_g(2) << "if(hr==DISP_E_EXCEPTION)"
				<< line_g(1) << htab_g(2) << "{"
				<< line_g(1) << htab_g(3) << "TCHAR errMsg[512];"
				<< line_g(1) << htab_g(3) << "_stprintf_s(errMsg, TEXT(\"Run-time error %d:\\n\\n %s\"),"
				<< line_g(1) << htab_g(5) << "excep.scode & 0x0000FFFF,  //Lower 16-bits of SCODE"
				<< line_g(1) << htab_g(5) << "excep.bstrDescription);    //Text error description"
				<< line_g(1) << htab_g(3) << "::MessageBox(NULL, errMsg, TEXT(\"Server Error\"), MB_SETFOREGROUND |"
				<< line_g(1) << htab_g(6) << " MB_OK);"
				<< line_g(1) << htab_g(2) << "}"
				<< line_g(1) << htab_g(2) << "else"
				<< line_g(1) << htab_g(2) << "{"
				<< line_g(1) << htab_g(3) << "LPVOID lpMsgBuf;"
				<< line_g(1) << htab_g(3) << "::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |"
				<< line_g(1) << htab_g(7) << "FORMAT_MESSAGE_FROM_SYSTEM |"
				<< line_g(1) << htab_g(7) << "FORMAT_MESSAGE_IGNORE_INSERTS, NULL, hr,"
				<< line_g(1) << htab_g(7) << "MAKELANGID(LANG_NEUTRAL,"
				<< line_g(1) << htab_g(7) << "SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,"
				<< line_g(1) << htab_g(7) << "0, NULL);"
				<< line_g(1) << htab_g(3) << "::MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT(\"COM Error\"),"
				<< line_g(1) << htab_g(6) << " MB_OK | MB_SETFOREGROUND);"
				<< line_g(1) << htab_g(3) << "::LocalFree( lpMsgBuf );"
				<< line_g(1) << htab_g(2) << "}"
				<< line_g(1) << htab_g(1) << "}";

		}
    }
}
