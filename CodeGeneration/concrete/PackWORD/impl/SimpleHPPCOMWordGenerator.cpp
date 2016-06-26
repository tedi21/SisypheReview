#include "SimpleHPPCOMWordGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHPPCOMWordGenerator::SimpleHPPCOMWordGenerator()
		{
			SourceHPP = 
				CreateFile;

			CreateFile =
				                CreateHeader(str_g("word.h"))
				<< line_g(1) << CreateHPPDefine(str_g("_word_h_"))
				<< CreateInclude
				<< line_g(1) << CreateNamespace(str_g("word"))
                << CreateWordClass      
				<< line_g(1) << CreateEndNamespace
				<< line_g(1) << CreateHPPEndDefine;            

			CreateInclude =
				   line_g(1) << STR_G(#include <windows.h>)
                << (line_g(1) << STR_G(#include "Application.h"))[If_IsProject]
                << (line_g(1) << "#include \"" << ProjectName << ".h\"")[!If_IsProject];

			CreateWordClass =
                   line_g(1) << htab_g(1) << "class Word"
                << line_g(1) << htab_g(1) << "{"
                << line_g(2) << htab_g(1) << "private:"
                << line_g(1) << htab_g(2) << "static Application* m_application;"
                << line_g(2) << htab_g(1) << "public:"
                << line_g(1) << htab_g(2) << "static bool Initialize();"
                << line_g(1) << htab_g(2) << "static bool UnInitialize();"
                << line_g(1) << htab_g(2) << "static Application* getApplication();"
                << line_g(1) << htab_g(1) << "};";

		}
    }
}