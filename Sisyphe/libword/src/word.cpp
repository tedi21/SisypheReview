
#include "word.h"

namespace word
{
	Application* Word::m_application = NULL;

	bool Word::Initialize()
	{
		if (m_application == NULL)
		{
			CoInitialize(NULL);
			CLSID clsid;
			IDispatch* pApp = NULL;
			HRESULT hr = CLSIDFromProgID(L"Word.Application", &clsid);
			if(SUCCEEDED(hr))
			{
				hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&pApp);
				if(SUCCEEDED(hr)) m_application = new Application(pApp);
			}
		}
		return (m_application != NULL);
	}

	bool Word::UnInitialize()
	{
		if(m_application != NULL)
		{
			delete m_application;
			m_application = NULL;
			CoUninitialize();
		}
		return (m_application == NULL);
	}

	Application* Word::getApplication()
	{
		return m_application;
	}

}