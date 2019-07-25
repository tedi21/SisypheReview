
#include "word_wrapper.h"
#include "word_error.h"

namespace word
{
	Application::Application()
	: m_pObject(NULL)
	{}

	Application::Application(IDispatch* pApplication, bool pAddRef)
	: m_pObject(pApplication)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Application::Application(const Application& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Application::~Application()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Application& Application::operator=(const Application& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Application::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	Document Application::getActiveDocument() const
	{
		OLECHAR* szMember = OLESTR("ActiveDocument");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Document(vResult.pdispVal);
	}

	Documents Application::getDocuments() const
	{
		OLECHAR* szMember = OLESTR("Documents");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Documents(vResult.pdispVal);
	}

	bool Application::getVisible() const
	{
		OLECHAR* szMember = OLESTR("Visible");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void Application::setVisible(bool visible)
	{
		OLECHAR* szMember = OLESTR("Visible");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (visible?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	bool Application::getScreenUpdating() const
	{
		OLECHAR* szMember = OLESTR("ScreenUpdating");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void Application::setScreenUpdating(bool screenupdating)
	{
		OLECHAR* szMember = OLESTR("ScreenUpdating");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (screenupdating?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	Selection Application::getSelection() const
	{
		OLECHAR* szMember = OLESTR("Selection");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Selection(vResult.pdispVal);
	}

	Options Application::getOptions() const
	{
		OLECHAR* szMember = OLESTR("Options");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Options(vResult.pdispVal);
	}

	IDispatch* Application::getCustomizationContext() const
	{
		OLECHAR* szMember = OLESTR("CustomizationContext");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.pdispVal;
	}

	void Application::setCustomizationContext(IDispatch* customizationcontext)
	{
		OLECHAR* szMember = OLESTR("CustomizationContext");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_UNKNOWN;
		pArgs[0].pdispVal = customizationcontext;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	Template Application::getNormalTemplate() const
	{
		OLECHAR* szMember = OLESTR("NormalTemplate");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Template(vResult.pdispVal);
	}

	CommandBars Application::getCommandBars() const
	{
		OLECHAR* szMember = OLESTR("CommandBars");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::CommandBars(vResult.pdispVal);
	}
		
	

	void Application::Quit()
	{
		OLECHAR* szMember = OLESTR("Quit");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
	

	Documents::Documents()
	: m_pObject(NULL)
	{}

	Documents::Documents(IDispatch* pDocuments, bool pAddRef)
	: m_pObject(pDocuments)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Documents::Documents(const Documents& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Documents::~Documents()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Documents& Documents::operator=(const Documents& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Documents::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Documents::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		
	

	Document Documents::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Document(vResult.pdispVal);
	}

	Document Documents::Open(const std::basic_string<TCHAR>& filename, bool confirmconversions, bool readonly, bool addtorecentfiles)
	{
		OLECHAR* szMember = OLESTR("Open");
		VARIANT pArgs[4];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[3].vt = VT_BSTR;
		pArgs[3].bstrVal = SysAllocString(filename.c_str());
		pArgs[2].vt = VT_BOOL;
		pArgs[2].boolVal = (confirmconversions?VARIANT_TRUE:VARIANT_FALSE);
		pArgs[1].vt = VT_BOOL;
		pArgs[1].boolVal = (readonly?VARIANT_TRUE:VARIANT_FALSE);
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (addtorecentfiles?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 4;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		SysFreeString(pArgs[3].bstrVal);
		return word::Document(vResult.pdispVal);
	}

	void Documents::Close(WdSaveOptions savechanges, WdOriginalFormat originalformat, bool routedocument)
	{
		OLECHAR* szMember = OLESTR("Close");
		VARIANT pArgs[3];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[2].vt = VT_I4;
		pArgs[2].lVal = savechanges;
		pArgs[1].vt = VT_I4;
		pArgs[1].lVal = originalformat;
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (routedocument?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 3;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	void Documents::Save()
	{
		OLECHAR* szMember = OLESTR("Save");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
	

	Document::Document()
	: m_pObject(NULL)
	{}

	Document::Document(IDispatch* pDocument, bool pAddRef)
	: m_pObject(pDocument)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Document::Document(const Document& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Document::~Document()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Document& Document::operator=(const Document& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Document::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	std::basic_string<TCHAR> Document::getFullName() const
	{
		OLECHAR* szMember = OLESTR("FullName");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return std::basic_string<TCHAR>(vResult.bstrVal ? vResult.bstrVal : _T(""));
	}

	Paragraphs Document::getParagraphs() const
	{
		OLECHAR* szMember = OLESTR("Paragraphs");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Paragraphs(vResult.pdispVal);
	}

	TablesOfContents Document::getTablesOfContents() const
	{
		OLECHAR* szMember = OLESTR("TablesOfContents");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::TablesOfContents(vResult.pdispVal);
	}

	Fields Document::getFields() const
	{
		OLECHAR* szMember = OLESTR("Fields");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Fields(vResult.pdispVal);
	}

	Tables Document::getTables() const
	{
		OLECHAR* szMember = OLESTR("Tables");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Tables(vResult.pdispVal);
	}

	Window Document::getActiveWindow() const
	{
		OLECHAR* szMember = OLESTR("ActiveWindow");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Window(vResult.pdispVal);
	}

	Range Document::getContent() const
	{
		OLECHAR* szMember = OLESTR("Content");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	bool Document::getSaved() const
	{
		OLECHAR* szMember = OLESTR("Saved");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void Document::setSaved(bool saved)
	{
		OLECHAR* szMember = OLESTR("Saved");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (saved?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
		
	

	void Document::Save()
	{
		OLECHAR* szMember = OLESTR("Save");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	void Document::AcceptAllRevisions()
	{
		OLECHAR* szMember = OLESTR("AcceptAllRevisions");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	Range Document::GoTo(WdGoToItem what, WdGoToDirection which, int count)
	{
		OLECHAR* szMember = OLESTR("GoTo");
		VARIANT pArgs[3];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[2].vt = VT_I4;
		pArgs[2].lVal = what;
		pArgs[1].vt = VT_I4;
		pArgs[1].lVal = which;
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = count;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 3;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	void Document::Close(WdSaveOptions savechanges, WdOriginalFormat originalformat, bool routedocument)
	{
		OLECHAR* szMember = OLESTR("Close");
		VARIANT pArgs[3];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[2].vt = VT_I4;
		pArgs[2].lVal = savechanges;
		pArgs[1].vt = VT_I4;
		pArgs[1].lVal = originalformat;
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (routedocument?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 3;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	void Document::Compare(const std::basic_string<TCHAR>& name, const std::basic_string<TCHAR>& authorname, WdCompareTarget comparetarget, bool detectformatchanges, bool ignoreallcomparisonwarnings, bool addtorecentfiles, bool removepersonalinformation, bool removedateandtime)
	{
		OLECHAR* szMember = OLESTR("Compare");
		VARIANT pArgs[8];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[7].vt = VT_BSTR;
		pArgs[7].bstrVal = SysAllocString(name.c_str());
		pArgs[6].vt = VT_BSTR;
		pArgs[6].bstrVal = SysAllocString(authorname.c_str());
		pArgs[5].vt = VT_I4;
		pArgs[5].lVal = comparetarget;
		pArgs[4].vt = VT_BOOL;
		pArgs[4].boolVal = (detectformatchanges?VARIANT_TRUE:VARIANT_FALSE);
		pArgs[3].vt = VT_BOOL;
		pArgs[3].boolVal = (ignoreallcomparisonwarnings?VARIANT_TRUE:VARIANT_FALSE);
		pArgs[2].vt = VT_BOOL;
		pArgs[2].boolVal = (addtorecentfiles?VARIANT_TRUE:VARIANT_FALSE);
		pArgs[1].vt = VT_BOOL;
		pArgs[1].boolVal = (removepersonalinformation?VARIANT_TRUE:VARIANT_FALSE);
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (removedateandtime?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 8;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		SysFreeString(pArgs[7].bstrVal);
		SysFreeString(pArgs[6].bstrVal);
	}

	void Document::Merge(const std::basic_string<TCHAR>& filename, WdMergeTarget mergetarget, bool detectformatchanges, WdUseFormattingFrom useformattingfrom, bool addtorecentfiles)
	{
		OLECHAR* szMember = OLESTR("Merge");
		VARIANT pArgs[5];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[4].vt = VT_BSTR;
		pArgs[4].bstrVal = SysAllocString(filename.c_str());
		pArgs[3].vt = VT_I4;
		pArgs[3].lVal = mergetarget;
		pArgs[2].vt = VT_BOOL;
		pArgs[2].boolVal = (detectformatchanges?VARIANT_TRUE:VARIANT_FALSE);
		pArgs[1].vt = VT_I4;
		pArgs[1].lVal = useformattingfrom;
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (addtorecentfiles?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 5;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		SysFreeString(pArgs[4].bstrVal);
	}

	void Document::SaveAs(const std::basic_string<TCHAR>& filename, WdSaveFormat fileformat)
	{
		OLECHAR* szMember = OLESTR("SaveAs");
		VARIANT pArgs[2];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[1].vt = VT_BSTR;
		pArgs[1].bstrVal = SysAllocString(filename.c_str());
		pArgs[0].vt = VT_I4;
		pArgs[0].lVal = fileformat;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 2;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		SysFreeString(pArgs[1].bstrVal);
	}
	

	Paragraphs::Paragraphs()
	: m_pObject(NULL)
	{}

	Paragraphs::Paragraphs(IDispatch* pParagraphs, bool pAddRef)
	: m_pObject(pParagraphs)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Paragraphs::Paragraphs(const Paragraphs& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Paragraphs::~Paragraphs()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Paragraphs& Paragraphs::operator=(const Paragraphs& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Paragraphs::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Paragraphs::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		
	

	Paragraph Paragraphs::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Paragraph(vResult.pdispVal);
	}
	

	Paragraph::Paragraph()
	: m_pObject(NULL)
	{}

	Paragraph::Paragraph(IDispatch* pParagraph, bool pAddRef)
	: m_pObject(pParagraph)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Paragraph::Paragraph(const Paragraph& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Paragraph::~Paragraph()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Paragraph& Paragraph::operator=(const Paragraph& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Paragraph::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	Range Paragraph::getRange() const
	{
		OLECHAR* szMember = OLESTR("Range");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	int Paragraph::getStyle() const
	{
		OLECHAR* szMember = OLESTR("Style");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	void Paragraph::setStyle(int style)
	{
		OLECHAR* szMember = OLESTR("Style");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = style;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
		
	

	Paragraph Paragraph::Next(int count)
	{
		OLECHAR* szMember = OLESTR("Next");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = count;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Paragraph(vResult.pdispVal);
	}
	

	TablesOfContents::TablesOfContents()
	: m_pObject(NULL)
	{}

	TablesOfContents::TablesOfContents(IDispatch* pTablesOfContents, bool pAddRef)
	: m_pObject(pTablesOfContents)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	TablesOfContents::TablesOfContents(const TablesOfContents& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	TablesOfContents::~TablesOfContents()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	TablesOfContents& TablesOfContents::operator=(const TablesOfContents& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	TablesOfContents::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int TablesOfContents::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		
	

	TableOfContents TablesOfContents::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::TableOfContents(vResult.pdispVal);
	}
	

	TableOfContents::TableOfContents()
	: m_pObject(NULL)
	{}

	TableOfContents::TableOfContents(IDispatch* pTableOfContents, bool pAddRef)
	: m_pObject(pTableOfContents)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	TableOfContents::TableOfContents(const TableOfContents& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	TableOfContents::~TableOfContents()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	TableOfContents& TableOfContents::operator=(const TableOfContents& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	TableOfContents::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	Range TableOfContents::getRange() const
	{
		OLECHAR* szMember = OLESTR("Range");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	bool TableOfContents::getUseFields() const
	{
		OLECHAR* szMember = OLESTR("UseFields");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void TableOfContents::setUseFields(bool usefields)
	{
		OLECHAR* szMember = OLESTR("UseFields");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (usefields?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	bool TableOfContents::getUseHeadingStyles() const
	{
		OLECHAR* szMember = OLESTR("UseHeadingStyles");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void TableOfContents::setUseHeadingStyles(bool useheadingstyles)
	{
		OLECHAR* szMember = OLESTR("UseHeadingStyles");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (useheadingstyles?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	HeadingStyles TableOfContents::getHeadingStyles() const
	{
		OLECHAR* szMember = OLESTR("HeadingStyles");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::HeadingStyles(vResult.pdispVal);
	}
		
	

	void TableOfContents::Update()
	{
		OLECHAR* szMember = OLESTR("Update");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
	

	Range::Range()
	: m_pObject(NULL)
	{}

	Range::Range(IDispatch* pRange, bool pAddRef)
	: m_pObject(pRange)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Range::Range(const Range& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Range::~Range()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Range& Range::operator=(const Range& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Range::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	std::basic_string<TCHAR> Range::getText() const
	{
		OLECHAR* szMember = OLESTR("Text");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return std::basic_string<TCHAR>(vResult.bstrVal ? vResult.bstrVal : _T(""));
	}

	void Range::setText(const std::basic_string<TCHAR>& text)
	{
		OLECHAR* szMember = OLESTR("Text");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BSTR;
		pArgs[0].bstrVal = SysAllocString(text.c_str());
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	Tables Range::getTables() const
	{
		OLECHAR* szMember = OLESTR("Tables");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Tables(vResult.pdispVal);
	}

	std::basic_string<TCHAR> Range::getXML() const
	{
		OLECHAR* szMember = OLESTR("XML");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return std::basic_string<TCHAR>(vResult.bstrVal ? vResult.bstrVal : _T(""));
	}
		
	

	Range Range::GoTo(WdGoToItem what, WdGoToDirection which, int count)
	{
		OLECHAR* szMember = OLESTR("GoTo");
		VARIANT pArgs[3];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[2].vt = VT_I4;
		pArgs[2].lVal = what;
		pArgs[1].vt = VT_I4;
		pArgs[1].lVal = which;
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = count;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 3;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Range Range::GoToNext(WdGoToItem what)
	{
		OLECHAR* szMember = OLESTR("GoToNext");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_I4;
		pArgs[0].lVal = what;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Range Range::GoToPrevious(WdGoToItem what)
	{
		OLECHAR* szMember = OLESTR("GoToPrevious");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_I4;
		pArgs[0].lVal = what;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	bool Range::InRange(Range const& other)
	{
		OLECHAR* szMember = OLESTR("InRange");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_DISPATCH;
		pArgs[0].pdispVal = (IDispatch*) other;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	Range Range::Next(int unit, int count)
	{
		OLECHAR* szMember = OLESTR("Next");
		VARIANT pArgs[2];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[1].vt = VT_INT;
		pArgs[1].intVal = unit;
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = count;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 2;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}
	

	Cell::Cell()
	: m_pObject(NULL)
	{}

	Cell::Cell(IDispatch* pCell, bool pAddRef)
	: m_pObject(pCell)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Cell::Cell(const Cell& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Cell::~Cell()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Cell& Cell::operator=(const Cell& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Cell::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	Range Cell::getRange() const
	{
		OLECHAR* szMember = OLESTR("Range");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}
		
	
	

	Tables::Tables()
	: m_pObject(NULL)
	{}

	Tables::Tables(IDispatch* pTables, bool pAddRef)
	: m_pObject(pTables)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Tables::Tables(const Tables& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Tables::~Tables()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Tables& Tables::operator=(const Tables& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Tables::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Tables::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		
	

	Table Tables::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Table(vResult.pdispVal);
	}
	

	Table::Table()
	: m_pObject(NULL)
	{}

	Table::Table(IDispatch* pTable, bool pAddRef)
	: m_pObject(pTable)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Table::Table(const Table& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Table::~Table()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Table& Table::operator=(const Table& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Table::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	Range Table::getRange() const
	{
		OLECHAR* szMember = OLESTR("Range");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Rows Table::getRows() const
	{
		OLECHAR* szMember = OLESTR("Rows");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Rows(vResult.pdispVal);
	}

	Columns Table::getColumns() const
	{
		OLECHAR* szMember = OLESTR("Columns");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Columns(vResult.pdispVal);
	}
		
	

	Cell Table::GetCell(int column, int row)
	{
		OLECHAR* szMember = OLESTR("Cell");
		VARIANT pArgs[2];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[1].vt = VT_INT;
		pArgs[1].intVal = column;
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = row;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 2;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Cell(vResult.pdispVal);
	}

	void Table::AutoFitBehavior(WdAutoFitBehavior behavior)
	{
		OLECHAR* szMember = OLESTR("AutoFitBehavior");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_I4;
		pArgs[0].lVal = behavior;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
	

	Rows::Rows()
	: m_pObject(NULL)
	{}

	Rows::Rows(IDispatch* pRows, bool pAddRef)
	: m_pObject(pRows)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Rows::Rows(const Rows& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Rows::~Rows()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Rows& Rows::operator=(const Rows& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Rows::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Rows::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	Row Rows::getFirst() const
	{
		OLECHAR* szMember = OLESTR("First");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Row(vResult.pdispVal);
	}

	Row Rows::getLast() const
	{
		OLECHAR* szMember = OLESTR("Last");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Row(vResult.pdispVal);
	}
		
	

	Row Rows::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Row(vResult.pdispVal);
	}
	

	Row::Row()
	: m_pObject(NULL)
	{}

	Row::Row(IDispatch* pRow, bool pAddRef)
	: m_pObject(pRow)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Row::Row(const Row& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Row::~Row()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Row& Row::operator=(const Row& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Row::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	Range Row::getRange() const
	{
		OLECHAR* szMember = OLESTR("Range");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Cells Row::getCells() const
	{
		OLECHAR* szMember = OLESTR("Cells");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Cells(vResult.pdispVal);
	}

	int Row::getIndex() const
	{
		OLECHAR* szMember = OLESTR("Index");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		
	
	

	Cells::Cells()
	: m_pObject(NULL)
	{}

	Cells::Cells(IDispatch* pCells, bool pAddRef)
	: m_pObject(pCells)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Cells::Cells(const Cells& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Cells::~Cells()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Cells& Cells::operator=(const Cells& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Cells::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Cells::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		
	

	Cell Cells::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Cell(vResult.pdispVal);
	}
	

	Fields::Fields()
	: m_pObject(NULL)
	{}

	Fields::Fields(IDispatch* pFields, bool pAddRef)
	: m_pObject(pFields)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Fields::Fields(const Fields& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Fields::~Fields()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Fields& Fields::operator=(const Fields& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Fields::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Fields::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		
	

	Field Fields::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Field(vResult.pdispVal);
	}
	

	Field::Field()
	: m_pObject(NULL)
	{}

	Field::Field(IDispatch* pField, bool pAddRef)
	: m_pObject(pField)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Field::Field(const Field& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Field::~Field()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Field& Field::operator=(const Field& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Field::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Field::getType() const
	{
		OLECHAR* szMember = OLESTR("Type");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	std::basic_string<TCHAR> Field::getData() const
	{
		OLECHAR* szMember = OLESTR("Data");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return std::basic_string<TCHAR>(vResult.bstrVal ? vResult.bstrVal : _T(""));
	}

	void Field::setData(const std::basic_string<TCHAR>& data)
	{
		OLECHAR* szMember = OLESTR("Data");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BSTR;
		pArgs[0].bstrVal = SysAllocString(data.c_str());
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
		
	

	bool Field::Update()
	{
		OLECHAR* szMember = OLESTR("Update");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void Field::DoClick()
	{
		OLECHAR* szMember = OLESTR("DoClick");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
	

	HeadingStyles::HeadingStyles()
	: m_pObject(NULL)
	{}

	HeadingStyles::HeadingStyles(IDispatch* pHeadingStyles, bool pAddRef)
	: m_pObject(pHeadingStyles)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	HeadingStyles::HeadingStyles(const HeadingStyles& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	HeadingStyles::~HeadingStyles()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	HeadingStyles& HeadingStyles::operator=(const HeadingStyles& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	HeadingStyles::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int HeadingStyles::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		
	

	HeadingStyle HeadingStyles::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::HeadingStyle(vResult.pdispVal);
	}
	

	HeadingStyle::HeadingStyle()
	: m_pObject(NULL)
	{}

	HeadingStyle::HeadingStyle(IDispatch* pHeadingStyle, bool pAddRef)
	: m_pObject(pHeadingStyle)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	HeadingStyle::HeadingStyle(const HeadingStyle& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	HeadingStyle::~HeadingStyle()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	HeadingStyle& HeadingStyle::operator=(const HeadingStyle& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	HeadingStyle::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	short HeadingStyle::getLevel() const
	{
		OLECHAR* szMember = OLESTR("Level");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.iVal;
	}

	void HeadingStyle::setLevel(short level)
	{
		OLECHAR* szMember = OLESTR("Level");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_I2;
		pArgs[0].iVal = level;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	int HeadingStyle::getStyle() const
	{
		OLECHAR* szMember = OLESTR("Style");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	void HeadingStyle::setStyle(int style)
	{
		OLECHAR* szMember = OLESTR("Style");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = style;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
		
	
	

	Selection::Selection()
	: m_pObject(NULL)
	{}

	Selection::Selection(IDispatch* pSelection, bool pAddRef)
	: m_pObject(pSelection)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Selection::Selection(const Selection& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Selection::~Selection()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Selection& Selection::operator=(const Selection& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Selection::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	Range Selection::getRange() const
	{
		OLECHAR* szMember = OLESTR("Range");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Paragraphs Selection::getParagraphs() const
	{
		OLECHAR* szMember = OLESTR("Paragraphs");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Paragraphs(vResult.pdispVal);
	}

	int Selection::getStart() const
	{
		OLECHAR* szMember = OLESTR("Start");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	void Selection::setStart(int start)
	{
		OLECHAR* szMember = OLESTR("Start");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = start;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	int Selection::getEnd() const
	{
		OLECHAR* szMember = OLESTR("End");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	void Selection::setEnd(int end)
	{
		OLECHAR* szMember = OLESTR("End");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = end;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	Tables Selection::getTables() const
	{
		OLECHAR* szMember = OLESTR("Tables");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Tables(vResult.pdispVal);
	}

	int Selection::getType() const
	{
		OLECHAR* szMember = OLESTR("Type");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	std::basic_string<TCHAR> Selection::getText() const
	{
		OLECHAR* szMember = OLESTR("Text");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return std::basic_string<TCHAR>(vResult.bstrVal ? vResult.bstrVal : _T(""));
	}

	void Selection::setText(const std::basic_string<TCHAR>& text)
	{
		OLECHAR* szMember = OLESTR("Text");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BSTR;
		pArgs[0].bstrVal = SysAllocString(text.c_str());
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	int Selection::getStyle() const
	{
		OLECHAR* szMember = OLESTR("Style");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	void Selection::setStyle(int style)
	{
		OLECHAR* szMember = OLESTR("Style");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = style;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	Characters Selection::getCharacters() const
	{
		OLECHAR* szMember = OLESTR("Characters");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Characters(vResult.pdispVal);
	}

	Find Selection::getFind() const
	{
		OLECHAR* szMember = OLESTR("Find");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Find(vResult.pdispVal);
	}

	Sentences Selection::getSentences() const
	{
		OLECHAR* szMember = OLESTR("Sentences");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Sentences(vResult.pdispVal);
	}

	Words Selection::getWords() const
	{
		OLECHAR* szMember = OLESTR("Words");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Words(vResult.pdispVal);
	}
		
	

	Range Selection::GoTo(WdGoToItem what, WdGoToDirection which, int count)
	{
		OLECHAR* szMember = OLESTR("GoTo");
		VARIANT pArgs[3];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[2].vt = VT_I4;
		pArgs[2].lVal = what;
		pArgs[1].vt = VT_I4;
		pArgs[1].lVal = which;
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = count;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 3;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Range Selection::GoToNext(WdGoToItem what)
	{
		OLECHAR* szMember = OLESTR("GoToNext");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_I4;
		pArgs[0].lVal = what;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Range Selection::GoToPrevious(WdGoToItem what)
	{
		OLECHAR* szMember = OLESTR("GoToPrevious");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_I4;
		pArgs[0].lVal = what;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	int Selection::MoveStart(int unit, int count)
	{
		OLECHAR* szMember = OLESTR("MoveStart");
		VARIANT pArgs[2];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[1].vt = VT_INT;
		pArgs[1].intVal = unit;
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = count;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 2;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	int Selection::MoveEnd(int unit, int count)
	{
		OLECHAR* szMember = OLESTR("MoveEnd");
		VARIANT pArgs[2];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[1].vt = VT_INT;
		pArgs[1].intVal = unit;
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = count;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 2;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	void Selection::Collapse(WdCollapseDirection direction)
	{
		OLECHAR* szMember = OLESTR("Collapse");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_I4;
		pArgs[0].lVal = direction;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
	

	Characters::Characters()
	: m_pObject(NULL)
	{}

	Characters::Characters(IDispatch* pCharacters, bool pAddRef)
	: m_pObject(pCharacters)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Characters::Characters(const Characters& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Characters::~Characters()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Characters& Characters::operator=(const Characters& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Characters::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Characters::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	Range Characters::getFirst() const
	{
		OLECHAR* szMember = OLESTR("First");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Range Characters::getLast() const
	{
		OLECHAR* szMember = OLESTR("Last");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}
		
	

	Range Characters::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}
	

	Find::Find()
	: m_pObject(NULL)
	{}

	Find::Find(IDispatch* pFind, bool pAddRef)
	: m_pObject(pFind)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Find::Find(const Find& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Find::~Find()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Find& Find::operator=(const Find& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Find::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Find::getStyle() const
	{
		OLECHAR* szMember = OLESTR("Style");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	void Find::setStyle(int style)
	{
		OLECHAR* szMember = OLESTR("Style");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = style;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	std::basic_string<TCHAR> Find::getText() const
	{
		OLECHAR* szMember = OLESTR("Text");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return std::basic_string<TCHAR>(vResult.bstrVal ? vResult.bstrVal : _T(""));
	}

	void Find::setText(const std::basic_string<TCHAR>& text)
	{
		OLECHAR* szMember = OLESTR("Text");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BSTR;
		pArgs[0].bstrVal = SysAllocString(text.c_str());
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	bool Find::getMatchWildcards() const
	{
		OLECHAR* szMember = OLESTR("MatchWildcards");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void Find::setMatchWildcards(bool matchwildcards)
	{
		OLECHAR* szMember = OLESTR("MatchWildcards");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (matchwildcards?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	bool Find::getForward() const
	{
		OLECHAR* szMember = OLESTR("Forward");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void Find::setForward(bool forward)
	{
		OLECHAR* szMember = OLESTR("Forward");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (forward?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	bool Find::getFound() const
	{
		OLECHAR* szMember = OLESTR("Found");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	bool Find::getMatchCase() const
	{
		OLECHAR* szMember = OLESTR("MatchCase");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void Find::setMatchCase(bool matchcase)
	{
		OLECHAR* szMember = OLESTR("MatchCase");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (matchcase?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
		
	

	void Find::ClearFormatting()
	{
		OLECHAR* szMember = OLESTR("ClearFormatting");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	bool Find::Execute()
	{
		OLECHAR* szMember = OLESTR("Execute");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}
	

	Words::Words()
	: m_pObject(NULL)
	{}

	Words::Words(IDispatch* pWords, bool pAddRef)
	: m_pObject(pWords)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Words::Words(const Words& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Words::~Words()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Words& Words::operator=(const Words& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Words::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Words::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	Range Words::getFirst() const
	{
		OLECHAR* szMember = OLESTR("First");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Range Words::getLast() const
	{
		OLECHAR* szMember = OLESTR("Last");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}
		
	

	Range Words::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}
	

	Sentences::Sentences()
	: m_pObject(NULL)
	{}

	Sentences::Sentences(IDispatch* pSentences, bool pAddRef)
	: m_pObject(pSentences)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Sentences::Sentences(const Sentences& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Sentences::~Sentences()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Sentences& Sentences::operator=(const Sentences& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Sentences::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Sentences::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	Range Sentences::getFirst() const
	{
		OLECHAR* szMember = OLESTR("First");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}

	Range Sentences::getLast() const
	{
		OLECHAR* szMember = OLESTR("Last");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}
		
	

	Range Sentences::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Range(vResult.pdispVal);
	}
	

	Columns::Columns()
	: m_pObject(NULL)
	{}

	Columns::Columns(IDispatch* pColumns, bool pAddRef)
	: m_pObject(pColumns)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Columns::Columns(const Columns& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Columns::~Columns()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Columns& Columns::operator=(const Columns& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Columns::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int Columns::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	Column Columns::getFirst() const
	{
		OLECHAR* szMember = OLESTR("First");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Column(vResult.pdispVal);
	}

	Column Columns::getLast() const
	{
		OLECHAR* szMember = OLESTR("Last");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Column(vResult.pdispVal);
	}
		
	

	Column Columns::Item(int index)
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT pArgs[1];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = index;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Column(vResult.pdispVal);
	}
	

	Column::Column()
	: m_pObject(NULL)
	{}

	Column::Column(IDispatch* pColumn, bool pAddRef)
	: m_pObject(pColumn)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Column::Column(const Column& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Column::~Column()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Column& Column::operator=(const Column& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Column::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	Cells Column::getCells() const
	{
		OLECHAR* szMember = OLESTR("Cells");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::Cells(vResult.pdispVal);
	}

	int Column::getIndex() const
	{
		OLECHAR* szMember = OLESTR("Index");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		
	
	

	Options::Options()
	: m_pObject(NULL)
	{}

	Options::Options(IDispatch* pOptions, bool pAddRef)
	: m_pObject(pOptions)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Options::Options(const Options& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Options::~Options()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Options& Options::operator=(const Options& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Options::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	bool Options::getPagination() const
	{
		OLECHAR* szMember = OLESTR("Pagination");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void Options::setPagination(bool pagination)
	{
		OLECHAR* szMember = OLESTR("Pagination");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (pagination?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
		
	
	

	Window::Window()
	: m_pObject(NULL)
	{}

	Window::Window(IDispatch* pWindow, bool pAddRef)
	: m_pObject(pWindow)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Window::Window(const Window& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Window::~Window()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Window& Window::operator=(const Window& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Window::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	View Window::getView() const
	{
		OLECHAR* szMember = OLESTR("View");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::View(vResult.pdispVal);
	}

	bool Window::getVisible() const
	{
		OLECHAR* szMember = OLESTR("Visible");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return (vResult.boolVal!=VARIANT_FALSE);
	}

	void Window::setVisible(bool visible)
	{
		OLECHAR* szMember = OLESTR("Visible");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (visible?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
		
	
	

	View::View()
	: m_pObject(NULL)
	{}

	View::View(IDispatch* pView, bool pAddRef)
	: m_pObject(pView)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	View::View(const View& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	View::~View()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	View& View::operator=(const View& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	View::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int View::getType() const
	{
		OLECHAR* szMember = OLESTR("Type");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}

	void View::setType(int type)
	{
		OLECHAR* szMember = OLESTR("Type");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = type;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
		
	
	

	Template::Template()
	: m_pObject(NULL)
	{}

	Template::Template(IDispatch* pTemplate, bool pAddRef)
	: m_pObject(pTemplate)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	Template::Template(const Template& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	Template::~Template()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	Template& Template::operator=(const Template& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	Template::operator IDispatch*() const
	{
		return m_pObject;
	}
	
		
	
	

	CommandBars::CommandBars()
	: m_pObject(NULL)
	{}

	CommandBars::CommandBars(IDispatch* pCommandBars, bool pAddRef)
	: m_pObject(pCommandBars)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	CommandBars::CommandBars(const CommandBars& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	CommandBars::~CommandBars()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	CommandBars& CommandBars::operator=(const CommandBars& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	CommandBars::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int CommandBars::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		

	CommandBar CommandBars::getItem(const std::basic_string<TCHAR>& id) const
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BSTR;
		pArgs[0].bstrVal = SysAllocString(id.c_str());
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::CommandBar(vResult.pdispVal);
	}
	
	

	CommandBar::CommandBar()
	: m_pObject(NULL)
	{}

	CommandBar::CommandBar(IDispatch* pCommandBar, bool pAddRef)
	: m_pObject(pCommandBar)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	CommandBar::CommandBar(const CommandBar& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	CommandBar::~CommandBar()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	CommandBar& CommandBar::operator=(const CommandBar& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	CommandBar::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	CommandBarControls CommandBar::getControls() const
	{
		OLECHAR* szMember = OLESTR("Controls");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::CommandBarControls(vResult.pdispVal);
	}
		
	
	

	CommandBarControls::CommandBarControls()
	: m_pObject(NULL)
	{}

	CommandBarControls::CommandBarControls(IDispatch* pCommandBarControls, bool pAddRef)
	: m_pObject(pCommandBarControls)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	CommandBarControls::CommandBarControls(const CommandBarControls& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	CommandBarControls::~CommandBarControls()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	CommandBarControls& CommandBarControls::operator=(const CommandBarControls& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	CommandBarControls::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	int CommandBarControls::getCount() const
	{
		OLECHAR* szMember = OLESTR("Count");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return vResult.intVal;
	}
		

	CommandBarControl CommandBarControls::getItem(int id) const
	{
		OLECHAR* szMember = OLESTR("Item");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		VARIANT pArgs[1];
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = id;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::CommandBarControl(vResult.pdispVal);
	}
	

	CommandBarControl CommandBarControls::Add(MsoControlType type, int controlid)
	{
		OLECHAR* szMember = OLESTR("Add");
		VARIANT pArgs[2];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[1].vt = VT_I4;
		pArgs[1].lVal = type;
		pArgs[0].vt = VT_INT;
		pArgs[0].intVal = controlid;
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 2;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::CommandBarControl(vResult.pdispVal);
	}
	

	CommandBarControl::CommandBarControl()
	: m_pObject(NULL)
	{}

	CommandBarControl::CommandBarControl(IDispatch* pCommandBarControl, bool pAddRef)
	: m_pObject(pCommandBarControl)
	{
		if (pAddRef && m_pObject != NULL) m_pObject->AddRef();
	}

	CommandBarControl::CommandBarControl(const CommandBarControl& copy)
	{
		m_pObject = copy.m_pObject;
		if (m_pObject != NULL) m_pObject->AddRef();
	}

	CommandBarControl::~CommandBarControl()
	{
		if (m_pObject != NULL) m_pObject->Release();
	}

	CommandBarControl& CommandBarControl::operator=(const CommandBarControl& copy)
	{
		if (this != &copy)
		{
			if (m_pObject != NULL) m_pObject->Release();
			m_pObject = copy.m_pObject;
			if (m_pObject != NULL) m_pObject->AddRef();
		}
		return *this;
	}

	CommandBarControl::operator IDispatch*() const
	{
		return m_pObject;
	}
	

	std::basic_string<TCHAR> CommandBarControl::getCaption() const
	{
		OLECHAR* szMember = OLESTR("Caption");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return std::basic_string<TCHAR>(vResult.bstrVal ? vResult.bstrVal : _T(""));
	}

	void CommandBarControl::setCaption(const std::basic_string<TCHAR>& caption)
	{
		OLECHAR* szMember = OLESTR("Caption");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BSTR;
		pArgs[0].bstrVal = SysAllocString(caption.c_str());
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}

	std::basic_string<TCHAR> CommandBarControl::getOnAction() const
	{
		OLECHAR* szMember = OLESTR("OnAction");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return std::basic_string<TCHAR>(vResult.bstrVal ? vResult.bstrVal : _T(""));
	}

	void CommandBarControl::setOnAction(const std::basic_string<TCHAR>& onaction)
	{
		OLECHAR* szMember = OLESTR("OnAction");
		VARIANT pArgs[1];
		pArgs[0].vt = VT_BSTR;
		pArgs[0].bstrVal = SysAllocString(onaction.c_str());
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		DISPID dispidNamed = DISPID_PROPERTYPUT;
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
		dp.cArgs = 1;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
		
	
	

	CommandBarPopup::CommandBarPopup()
	{}

	CommandBarPopup::CommandBarPopup(IDispatch* pCommandBarPopup, bool pAddRef)
	: CommandBarControl(pCommandBarPopup, pAddRef)
	{
	}
	

	CommandBarControls CommandBarPopup::getControls() const
	{
		OLECHAR* szMember = OLESTR("Controls");
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
		return word::CommandBarControls(vResult.pdispVal);
	}
		
	
	

	CommandBarButton::CommandBarButton()
	{}

	CommandBarButton::CommandBarButton(IDispatch* pCommandBarButton, bool pAddRef)
	: CommandBarControl(pCommandBarButton, pAddRef)
	{
	}
	
		
	

	void CommandBarButton::Click(CommandBarButton const& ctrl, bool& canceldefault)
	{
		OLECHAR* szMember = OLESTR("Click");
		VARIANT pArgs[2];
		VARIANT vResult;
		memset(&vResult, 0, sizeof(VARIANT));
		pArgs[1].vt = VT_DISPATCH;
		pArgs[1].pdispVal = (IDispatch*) ctrl;
		pArgs[0].vt = VT_BOOL;
		pArgs[0].boolVal = (canceldefault?VARIANT_TRUE:VARIANT_FALSE);
		DISPID dispID;
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		dp.cArgs = 2;
		dp.rgvarg = pArgs;
		if (m_pObject != NULL)
		{
			HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
			if (SUCCEEDED(hr))
			{
				EXCEPINFO excep;
				hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);
				if (FAILED(hr))
				{
					ErrHandler(hr, excep);
				}
			}
		}
	}
	

	const GUID CommandBarButton::IID_CommandBarButtonEvents = {0x000c0351,0x0000,0x0000,{0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};


}