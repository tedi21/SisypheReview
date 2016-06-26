#include "SimpleCPPCOMWordGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleCPPCOMWordGenerator::SimpleCPPCOMWordGenerator()
		{
			SourceCPP = 
				CreateFile;

			CreateFile =
				                CreateInclude
				<< line_g(1) << CreateNamespace(str_g("word"))
                << CreateWordClass      
				<< line_g(1) << CreateEndNamespace;            

			CreateInclude =
				   line_g(1) << STR_G(#include "word.h");

			CreateWordClass =
                   line_g(1) << htab_g(1) << "Application* Word::m_application = NULL;"
                << line_g(2) << htab_g(1) << "bool Word::Initialize()"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "if (m_application == NULL)"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "CoInitialize(NULL);"
                << line_g(1) << htab_g(3) << "CLSID clsid;"
                << line_g(1) << htab_g(3) << "IDispatch* pApp = NULL;"
                << line_g(1) << htab_g(3) << "HRESULT hr = CLSIDFromProgID(L\"Word.Application\", &clsid);"
                << line_g(1) << htab_g(3) << "if(SUCCEEDED(hr))"
                << line_g(1) << htab_g(3) << "{"
                << line_g(1) << htab_g(4) << "hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&pApp);"
                << line_g(1) << htab_g(4) << "if(SUCCEEDED(hr)) m_application = new Application(pApp);"
                << line_g(1) << htab_g(3) << "}"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(2) << "return (m_application != NULL);"
                << line_g(1) << htab_g(1) << "}"
                << line_g(2) << htab_g(1) << "bool Word::UnInitialize()"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "if(m_application != NULL)"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "delete m_application;"
                << line_g(1) << htab_g(3) << "m_application = NULL;"
                << line_g(1) << htab_g(3) << "CoUninitialize();"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(2) << "return (m_application == NULL);"
                << line_g(1) << htab_g(1) << "}"
                << line_g(2) << htab_g(1) << "Application* Word::getApplication()"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "return m_application;"
                << line_g(1) << htab_g(1) << "}";

		}
    }
}