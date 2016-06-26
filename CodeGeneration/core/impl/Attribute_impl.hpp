#include "xstring.hpp"
#include "Convert.hpp"

using namespace log4cpp;
using namespace xercesc;
using namespace std;
using namespace enc;
using namespace fctr;

namespace dsg {

    #define CX(str) encode<EncodingT,xml>(str).c_str()
    #define C(str)  encode<xml,EncodingT>(str).c_str()
    #define AX(str) encode<ansi,xml>(str).c_str()
    #define A(str)  encode<xml,ansi>(str).c_str()

    template <class EncodingT>
    DOMNode* Attribute<EncodingT>::saveXML(DOMDocument* xml_doc) const
    {
        DOMElement* xml_attribute = NULL;
        DOMNode*    xml_comment   = NULL;
        DOMText*    xml_text      = NULL;
        xml::string_t strType, strModifier;
        try 
        {
            xml_attribute = xml_doc->createElement(AX("Attribute"));
            xml_attribute->setAttribute(AX("Name"), CX(m_name));
            if (hasAlias())
            {
                xml_attribute->setAttribute(AX("Alias"), CX(m_alias));
            }
            switch (m_type)
            {
            case ATTR_BOOLEAN     : strType = L"Boolean";     break;
            case ATTR_SBYTE       : strType = L"SByte";       break;
            case ATTR_BYTE        : strType = L"Byte";        break;
            case ATTR_ANSICHAR    : strType = L"AnsiChar";        break;
            case ATTR_WIDECHAR    : strType = L"WideChar";        break;
            case ATTR_CHAR        : strType = L"Char";        break;
            case ATTR_INT16       : strType = L"Int16";       break;
            case ATTR_UINT16      : strType = L"UInt16";      break;
            case ATTR_INT32       : strType = L"Int32";       break;
            case ATTR_UINT32      : strType = L"UInt32";      break;
            case ATTR_INT64       : strType = L"Int64";       break;
            case ATTR_UINT64      : strType = L"UInt64";      break;
            case ATTR_INT         : strType = L"Int";         break;
            case ATTR_UINT        : strType = L"UInt";        break;
            case ATTR_SINGLE      : strType = L"Single";      break;
            case ATTR_DOUBLE      : strType = L"Double";      break;
            case ATTR_ANSISTRING  : strType = L"AnsiString";  break;
            case ATTR_WIDESTRING  : strType = L"WideString";  break;
            case ATTR_STRING      : strType = L"String";      break;
            case ATTR_TEXT        : strType = L"Text";        break;
            case ATTR_TIME        : strType = L"Time";        break;
            case ATTR_DATE        : strType = L"Date";        break;
            case ATTR_ANY         : strType = L"Any";         break;
            case ATTR_BINARY      : strType = L"Binary";      break;
            default               : strType = L"Unknown";     break;
            }
            xml_attribute->setAttribute(AX("Type"), strType.c_str());
            if (isId()) 
            {
                strModifier += L"Id ";
            }
            if (isRef()) 
            {
                strModifier += L"Ref ";
            }
            if (isAuto()) 
            {
                strModifier += L"Auto ";
            }
            if (isConst()) 
            {
                strModifier += L"Const ";
            }
            if (isContextual()) 
            {
                strModifier += L"Contextual ";
            }
            if (isBase()) 
            {
                strModifier += L"Base ";
            }
            if (isVirtual()) 
            {
                strModifier += L"Virtual ";
            }
            if (isStatic()) 
            {
                strModifier += L"Static ";
            }
            if (isArray())
            {
                strModifier += L"Array ";
            }
            if (!strModifier.empty())
            {
                xml_attribute->setAttribute(AX("Modifier"), strModifier.c_str());
            }
            if (hasDefault())
            {
                xml_attribute->setAttribute(AX("Default"), CX(m_default));
            }
            if (hasComment()) 
            {
                xml_comment = xml_doc->createElement(AX("Comments"));
                xml_attribute->appendChild(xml_comment);
                xml_text = xml_doc->createTextNode(CX(m_comment));
                xml_comment->appendChild(xml_text);
            }
            m_logger->debug("Attribute::saveXML() : XML attribute saved");
        } 
        catch ( const DOMException& e ) 
        {
            m_logger->fatalStream() << "Attribute::saveXML() : XML attribute save error: " 
									<< A(e.getMessage());
            //throw e;
        }
        return xml_attribute;
    }

    template <class EncodingT>
    void Attribute<EncodingT>::loadXML(DOMElement* xml_attribute)
    {
        DOMElement*  xml_comment = NULL;
        DOMText*     xml_text    = NULL;
        DOMNodeList* xml_list    = NULL;
        string       strType, strModifier;

        if (!xml_attribute || string("Attribute") != A(xml_attribute->getTagName()))
        {
            m_logger->fatalStream() << "Attribute::loadXML() : XML attribute element expected";
            //throw BadXmlFormatException("XML attribute element expected");
        }
        else
        {
            m_name = C(xml_attribute->getAttribute(AX("Name")));
            m_alias = C(xml_attribute->getAttribute( AX("Alias") ));
            strType = A(xml_attribute->getAttribute(AX("Type")));
            if (strType == "Boolean")           m_type = ATTR_BOOLEAN;
            else if (strType == "SByte")        m_type = ATTR_SBYTE;
            else if (strType == "Byte")         m_type = ATTR_BYTE;
            else if (strType == "AnsiChar")     m_type = ATTR_ANSICHAR;
            else if (strType == "WideChar")     m_type = ATTR_WIDECHAR;
            else if (strType == "Char")         m_type = ATTR_CHAR;
            else if (strType == "Int16")        m_type = ATTR_INT16;
            else if (strType == "UInt16")       m_type = ATTR_UINT16;
            else if (strType == "Int32")        m_type = ATTR_INT32;
            else if (strType == "UInt32")       m_type = ATTR_UINT32;
            else if (strType == "Int64")        m_type = ATTR_INT64;
            else if (strType == "UInt64")       m_type = ATTR_UINT64;
            else if (strType == "Int")          m_type = ATTR_INT;
            else if (strType == "UInt")         m_type = ATTR_UINT;
            else if (strType == "Single")       m_type = ATTR_SINGLE;
            else if (strType == "Double")       m_type = ATTR_DOUBLE;
            else if (strType == "AnsiString")   m_type = ATTR_ANSISTRING;
            else if (strType == "WideString")   m_type = ATTR_WIDESTRING;
            else if (strType == "String")       m_type = ATTR_STRING;
            else if (strType == "Text")         m_type = ATTR_TEXT;
            else if (strType == "Time")         m_type = ATTR_TIME;
            else if (strType == "Date")         m_type = ATTR_DATE;
            else if (strType == "Any")          m_type = ATTR_ANY;
            else if (strType == "Binary")       m_type = ATTR_BINARY;
            else m_logger->warnStream() << "Attribute::loadXML() : unknown type : " << strType;

            if (xml_attribute->hasAttribute( AX("Modifier") ))
            {
                istringstream iss(A(xml_attribute->getAttribute(AX("Modifier"))));
                while (!(iss >> strModifier).eof())
                {
                    if (strModifier == "Id")           		setModifier(ATTR_ID);
                    else if (strModifier == "Ref")     		setModifier(ATTR_REF);
                    else if (strModifier == "Auto")    		setModifier(ATTR_AUTO);
                    else if (strModifier == "Const")   		setModifier(ATTR_CONST);
                    else if (strModifier == "Contextual")	setModifier(ATTR_CONTEXTUAL);
                    else if (strModifier == "Base")    		setModifier(ATTR_BASE);
                    else if (strModifier == "Virtual") 		setModifier(ATTR_VIRTUAL);
                    else if (strModifier == "Static")  		setModifier(ATTR_STATIC);
                    else if (strModifier == "Array")  		setModifier(ATTR_ARRAY);
                    else m_logger->warnStream() << "Attribute::loadXML() : unknown modifier : " << strModifier;
                }
            }
            if (xml_attribute->hasAttribute( AX("Default") ))
            {
                m_default = C(xml_attribute->getAttribute(AX("Default")));
            }
            m_comment = EncodingT::EMPTY;
            xml_list = xml_attribute->getElementsByTagName( AX("Comments") );
            if ( xml_list->getLength()>0 )
            {
                xml_comment = (DOMElement*) xml_list->item(0);
                if (!xml_comment || string("Comments") != A(xml_comment->getTagName()))
                {
                    m_logger->fatalStream() << "Attribute::loadXML() : XML comments element expected";
                    //throw BadXmlFormatException("XML comments element expected");
                }
                else
                {
                    try 
                    {
                        xml_text = (DOMText*) xml_comment->getFirstChild();
                        if (xml_text)
                        {
                            m_comment = C(xml_text->getData());
                        }
                    } 
					catch(DOMException & e) 
                    {
                        m_logger->fatalStream() << "Attribute::loadXML() : XML attr comments element error: " 
												<< A(e.getMessage());
                        //throw e;
                    }
                }
            }
            m_logger->debugStream() << "Attribute::loadXML() : set attribute : "
                                    << encode<EncodingT,ansi>(m_name) << ", "
                                    << encode<EncodingT,ansi>(m_comment);
            m_logger->debug("Attribute::loadXML() : XML attribute loaded");
        }
    }

    #undef CX
    #undef AX
    #undef C
    #undef A

}
