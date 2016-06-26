#include "SimpleCPPWordGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleCPPWordGenerator::SimpleCPPWordGenerator()
		{
			SourceCPP = 
				CreateFile;

			CreateFile =
				                CreateInclude
				<< line_g(1) << CreateNamespace(str_g("word"))
                << ListClass
                   (
                        CreateWordClass
                     << line_g(1)
                   )
				<< line_g(1) << CreateEndNamespace;            

			CreateInclude =
                   line_g(1) << str_g("#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << str_g(".h\"")
                << line_g(1) << str_g("#include \"word_error.h\"");

			CreateWordClass =
                   line_g(1) << htab_g(1) << ClassName << "::" << ClassName << "()"
                <<(line_g(1) << htab_g(1) << ": m_pObject(NULL)") [!Has_Base]
                << line_g(1) << htab_g(1) << "{}"
                << line_g(2) << htab_g(1) << ClassName << "::" << ClassName << "(IDispatch* p" << ClassName << ", bool pAddRef)"
                <<(line_g(1) << htab_g(1) << ": m_pObject(p" << ClassName << ")")                     [!Has_Base]
                <<(line_g(1) << htab_g(1) << ": " << BaseName << "(p" << ClassName << ", pAddRef)")   [Has_Base]
                << line_g(1) << htab_g(1) << "{"
                <<(line_g(1) << htab_g(2) << "if (pAddRef && m_pObject != NULL) m_pObject->AddRef();")[!Has_Base]
                << line_g(1) << htab_g(1) << "}"
                <<(line_g(2) << htab_g(1) << ClassName << "::" << ClassName << "(const " << ClassName << "& copy)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "m_pObject = copy.m_pObject;"
                << line_g(1) << htab_g(2) << "if (m_pObject != NULL) m_pObject->AddRef();"
                << line_g(1) << htab_g(1) << "}"
                << line_g(2) << htab_g(1) << ClassName << "::" << "~" << ClassName << "()"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "if (m_pObject != NULL) m_pObject->Release();"
                << line_g(1) << htab_g(1) << "}"
                << line_g(2) << htab_g(1) << "const " << ClassName << "& " << ClassName << "::operator=(const " << ClassName << "& copy)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "if (m_pObject != NULL) m_pObject->Release();"                
                << line_g(1) << htab_g(2) << "m_pObject = copy.m_pObject;"
                << line_g(1) << htab_g(2) << "if (m_pObject != NULL) m_pObject->AddRef();"
                << line_g(1) << htab_g(2) << "return *this;"
                << line_g(1) << htab_g(1) << "}"
                << line_g(2) << htab_g(1) << ClassName << "::operator IDispatch*() const"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "return m_pObject;"
                << line_g(1) << htab_g(1) << "}") [!Has_Base]
                << line_g(1) << htab_g(1) << ListAttribute
                                             (
                                                  CreateWordAttribute
                                             )
                 << line_g(1) << htab_g(2) << ListArray
                                             (
                                                  CreateWordArray
                                             )
                << line_g(1) << htab_g(1) << ListMethod
                                             (
                                                  CreateWordMethod
                                             )
                << line_g(1) << htab_g(1) << ListConstant
                                             (
                                                  CreateWordConstant
                                             );
            
            CreateWordAttribute =
                   line_g(2) << htab_g(1) << AttributeType << " " << ClassName << "::get" << AttributeName << "() const"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "OLECHAR* szMember = " << str_g("OLESTR(\"") << attr_g(getAttributeNameHandler(KIND_NAME)) << str_g("\");")
                << line_g(1) << htab_g(2) << "VARIANT vResult;"
                << line_g(1) << htab_g(2) << "memset(&vResult, 0, sizeof(VARIANT));"
                << line_g(1) << htab_g(2) << "DISPID dispID;"
                << line_g(1) << htab_g(2) << "DISPPARAMS dp = { NULL, NULL, 0, 0 };"
                << line_g(1) << htab_g(2) << "if (m_pObject != NULL)"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);"
                << line_g(1) << htab_g(3) << "if (SUCCEEDED(hr))"
                << line_g(1) << htab_g(3) << "{"
                << line_g(1) << htab_g(4) << "EXCEPINFO excep;"
                << line_g(1) << htab_g(4) << "hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);"
                << line_g(1) << htab_g(4) << "if (FAILED(hr))"
                << line_g(1) << htab_g(4) << "{"
                << line_g(1) << htab_g(5) << "ErrHandler(hr, excep);"
                << line_g(1) << htab_g(4) << "}" 
                << line_g(1) << htab_g(3) << "}"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(2) << "return " << AttributeVTReturn("vResult." << VariantVal) << ";"
                << line_g(1) << htab_g(1) << "}"
                << (line_g(2) << htab_g(1) << "void " << ClassName << "::set" << AttributeName << "(" << AttributeTypeParam << " " << AttributeParamName << ")"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "OLECHAR* szMember = " << str_g("OLESTR(\"") << attr_g(getAttributeNameHandler(KIND_NAME)) << str_g("\");")
                << line_g(1) << htab_g(2) << "VARIANT pArgs[1];"
                << line_g(1) << htab_g(2) << "pArgs[0].vt = " << AttributeVTType << ";"
                << line_g(1) << htab_g(2) << "pArgs[0]." << VariantVal << " = " << AttributeVTVal(AttributeParamName) << ";"
                << line_g(1) << htab_g(2) << "DISPID dispID;"
                << line_g(1) << htab_g(2) << "DISPPARAMS dp = { NULL, NULL, 0, 0 };"
                << line_g(1) << htab_g(2) << "DISPID dispidNamed = DISPID_PROPERTYPUT;"
                << line_g(1) << htab_g(2) << "dp.cNamedArgs = 1;"
                << line_g(1) << htab_g(2) << "dp.rgdispidNamedArgs = &dispidNamed;"
                << line_g(1) << htab_g(2) << "dp.cArgs = 1;"
                << line_g(1) << htab_g(2) << "dp.rgvarg = pArgs;"
                << line_g(1) << htab_g(2) << "if (m_pObject != NULL)"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);"
                << line_g(1) << htab_g(3) << "if (SUCCEEDED(hr))"
                << line_g(1) << htab_g(3) << "{"
                << line_g(1) << htab_g(4) << "EXCEPINFO excep;"
                << line_g(1) << htab_g(4) << "hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);"
                << line_g(1) << htab_g(4) << "if (FAILED(hr))"
                << line_g(1) << htab_g(4) << "{"
                << line_g(1) << htab_g(5) << "ErrHandler(hr, excep);"
                << line_g(1) << htab_g(4) << "}"                 
                << line_g(1) << htab_g(3) << "}"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}")
                   [!If_IsReadOnly]; 

            CreateWordMethod =
                   line_g(2) << htab_g(1) << ReturnType << " " << MethodClassName << "::" << MethodName << "(" << CreateParameters << ")"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "OLECHAR* szMember = " << str_g("OLESTR(\"") << ent_g(getEntityFunctionNameHandler(KIND_NAME)) << str_g("\");")
                << (line_g(1) << htab_g(2) << "VARIANT pArgs[" << ParameterSize << "];")[Has_Parameter]
                << line_g(1) << htab_g(2) << "VARIANT vResult;"
                << line_g(1) << htab_g(2) << "memset(&vResult, 0, sizeof(VARIANT));"
                << ListParameter
                   (
                        line_g(1) << htab_g(2) << "pArgs[" << ParameterIndex << "].vt = " << AttributeVTType << ";"
                     << line_g(1) << htab_g(2) << "pArgs[" << ParameterIndex << "]." << VariantVal << " = " << AttributeVTVal(ParameterName) << ";"
                   )
                << line_g(1) << htab_g(2) << "DISPID dispID;"
                << line_g(1) << htab_g(2) << "DISPPARAMS dp = { NULL, NULL, 0, 0 };"
                << (line_g(1) << htab_g(2) << "dp.cArgs = " << ParameterSize << ";"
                <<  line_g(1) << htab_g(2) << "dp.rgvarg = pArgs;")[Has_Parameter]
                << line_g(1) << htab_g(2) << "if (m_pObject != NULL)"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);"
                << line_g(1) << htab_g(3) << "if (SUCCEEDED(hr))"
                << line_g(1) << htab_g(3) << "{"
                << line_g(1) << htab_g(4) << "EXCEPINFO excep;"
                << line_g(1) << htab_g(4) << "hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dp, &vResult, &excep, NULL);"
                << line_g(1) << htab_g(4) << "if (FAILED(hr))"
                << line_g(1) << htab_g(4) << "{"
                << line_g(1) << htab_g(5) << "ErrHandler(hr, excep);"
                << line_g(1) << htab_g(4) << "}"
                << line_g(1) << htab_g(3) << "}"                 
                << line_g(1) << htab_g(2) << "}"
                << ListParameter
                   (
                        (line_g(1) << htab_g(2) << AttributeVTRelease("pArgs[" << ParameterIndex << "]." << VariantVal) << ";")[If_IsAttributeVTAlloc]
                   )
                << (line_g(1) << htab_g(2) << "return " << GotoReturn(AttributeVTReturn("vResult." << VariantVal)) << ";")[Has_Return]
                << line_g(1) << htab_g(1) << "}";

            CreateParameters =
                   ListParameter
                   (
                        ParameterType << " " << ParameterName << ~-str_g(", ")
                   );

            CreateWordArray =
                   GotoElementArray
                   (
                       line_g(2) << htab_g(1) << AttributeType << " " << ArrayClassName << "::get" << AttributeName << "(" 
                    << GotoIndexArray
                       (
                           ParameterType << " " << ParameterName
                       )
                    << ") const"
                    << line_g(1) << htab_g(1) << "{"
                    << line_g(1) << htab_g(2) << "OLECHAR* szMember = " << str_g("OLESTR(\"") << attr_g(getAttributeNameHandler(KIND_NAME)) << str_g("\");")
                    << line_g(1) << htab_g(2) << "VARIANT vResult;"
                    << line_g(1) << htab_g(2) << "memset(&vResult, 0, sizeof(VARIANT));"
                    << line_g(1) << htab_g(2) << "VARIANT pArgs[1];"
                    << GotoIndexArray
                       (
                           line_g(1) << htab_g(2) << "pArgs[0].vt = " << AttributeVTType << ";"
                        << line_g(1) << htab_g(2) << "pArgs[0]." << VariantVal << " = " << AttributeVTVal(ParameterName) << ";"
                       )
                    << line_g(1) << htab_g(2) << "DISPID dispID;"
                    << line_g(1) << htab_g(2) << "DISPPARAMS dp = { NULL, NULL, 0, 0 };"
                    << line_g(1) << htab_g(2) << "dp.cArgs = 1;"
                    << line_g(1) << htab_g(2) << "dp.rgvarg = pArgs;"
                    << line_g(1) << htab_g(2) << "if (m_pObject != NULL)"
                    << line_g(1) << htab_g(2) << "{"
                    << line_g(1) << htab_g(3) << "HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);"
                    << line_g(1) << htab_g(3) << "if (SUCCEEDED(hr))"
                    << line_g(1) << htab_g(3) << "{"
                    << line_g(1) << htab_g(4) << "EXCEPINFO excep;"
                    << line_g(1) << htab_g(4) << "hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dp, &vResult, &excep, NULL);"
                    << line_g(1) << htab_g(4) << "if (FAILED(hr))"
                    << line_g(1) << htab_g(4) << "{"
                    << line_g(1) << htab_g(5) << "ErrHandler(hr, excep);"
                    << line_g(1) << htab_g(4) << "}"                     
                    << line_g(1) << htab_g(3) << "}"
                    << line_g(1) << htab_g(2) << "}"
                    << line_g(1) << htab_g(2) << "return " << AttributeVTReturn("vResult." << VariantVal) << ";"
                    << line_g(1) << htab_g(1) << "}"
                   )
                << GotoElementArray
                   (
                      (line_g(2) << htab_g(1) << "void " << ArrayClassName << "::set" << AttributeName << "("
                    << GotoIndexArray
                       (
                           ParameterType << " " << ParameterName
                       )
                    << ", "
                    << AttributeTypeParam << " " << AttributeParamName
                    << ")"
                    << line_g(1) << htab_g(1) << "{"
                    << line_g(1) << htab_g(2) << "OLECHAR* szMember = " << str_g("OLESTR(\"") << attr_g(getAttributeNameHandler(KIND_NAME)) << str_g("\");")
                    << line_g(1) << htab_g(2) << "VARIANT pArgs[2];"
                    << GotoIndexArray
                       (
                           line_g(1) << htab_g(2) << "pArgs[0].vt = " << AttributeVTType << ";"
                        << line_g(1) << htab_g(2) << "pArgs[0]." << VariantVal << " = " << AttributeVTVal(ParameterName) << ";"
                       )
                    << line_g(1) << htab_g(2) << "pArgs[1].vt = " << AttributeVTType << ";"
                    << line_g(1) << htab_g(2) << "pArgs[1]." << VariantVal << " = " << AttributeVTVal(AttributeParamName) << ";"
                    << line_g(1) << htab_g(2) << "DISPID dispID;"
                    << line_g(1) << htab_g(2) << "DISPPARAMS dp = { NULL, NULL, 0, 0 };"
                    << line_g(1) << htab_g(2) << "DISPID dispidNamed = DISPID_PROPERTYPUT;"
                    << line_g(1) << htab_g(2) << "dp.cNamedArgs = 1;"
                    << line_g(1) << htab_g(2) << "dp.rgdispidNamedArgs = &dispidNamed;"
                    << line_g(1) << htab_g(2) << "dp.cArgs = 2;"
                    << line_g(1) << htab_g(2) << "dp.rgvarg = pArgs;"
                    << line_g(1) << htab_g(2) << "if (m_pObject != NULL)"
                    << line_g(1) << htab_g(2) << "{"
                    << line_g(1) << htab_g(3) << "HRESULT hr = m_pObject->GetIDsOfNames(IID_NULL, &szMember, 1, LOCALE_SYSTEM_DEFAULT, &dispID);"
                    << line_g(1) << htab_g(3) << "if (SUCCEEDED(hr))"
                    << line_g(1) << htab_g(3) << "{"
                    << line_g(1) << htab_g(4) << "EXCEPINFO excep;"
                    << line_g(1) << htab_g(4) << "hr = m_pObject->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYPUT, &dp, NULL, &excep, NULL);"
                    << line_g(1) << htab_g(4) << "if (FAILED(hr))"
                    << line_g(1) << htab_g(4) << "{"
                    << line_g(1) << htab_g(5) << "ErrHandler(hr, excep);"
                    << line_g(1) << htab_g(4) << "}"                     
                    << line_g(1) << htab_g(3) << "}"
                    << line_g(1) << htab_g(2) << "}"
                    << line_g(1) << htab_g(1) << "}")[!If_IsReadOnly]
                   ); 

            CreateWordConstant =
                   line_g(2) << htab_g(1) << "const " << ConstantType << " " << ClassName << "::" << ConstantName << " = " << ConstantValue << ";"; 
		}
    }
}
