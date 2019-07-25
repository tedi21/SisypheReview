#include "xstring.hpp"

using namespace log4cpp;
using namespace xercesc;
using namespace std;
using namespace enc;

namespace dsg {

    #define CX(str) encode<EncodingT,xml>(str).c_str()
    #define C(str)  encode<xml,EncodingT>(str).c_str()
    #define AX(str) encode<ansi,xml>(str).c_str()
    #define A(str)  encode<xml,ansi>(str).c_str()

    template <class EncodingT>
    DOMNode* Entity<EncodingT>::saveXML(DOMDocument* xml_doc) const
    {
        DOMElement* xml_entity  = NULL;
        DOMNode*    xml_comment = NULL;
        DOMText*    xml_text    = NULL;
        xml::string_t strClass;
        try 
        {
            xml_entity = xml_doc->createElement( AX("Entity") ); 
            xml_entity->setAttribute( AX("Name"), CX(m_name) );
            if (hasFunctionName())
            {
                xml_entity->setAttribute( AX("FunctionName"), CX(m_functionName) );
            }
            if (hasAlias())
            {
                xml_entity->setAttribute( AX("Alias"), CX(m_alias) );
            }
            switch (m_class)
            {
            case ENTITY_DATA        : strClass = u"Data";       break;
            case ENTITY_FUNCTION    : strClass = u"Function";   break;
            case ENTITY_ENUMERATION : strClass = u"Enumeration";break;
            case ENTITY_PACKAGE     : strClass = u"Package";    break;
            default                 : strClass = u"Unknown";    break;
            }
            xml_entity->setAttribute( AX("Class"), strClass.c_str() );
            if (hasComment()) 
            {
                xml_comment = xml_doc->createElement( AX("Comments") );
                xml_entity->appendChild(xml_comment);
                xml_text = xml_doc->createTextNode( CX(m_comment) );
                xml_comment->appendChild(xml_text);
            }
            for (const_attr_iterator ite = beginAttributes(); ite != endAttributes(); ++ite)
            {
                xml_entity->appendChild(ite->saveXML(xml_doc));
            }
            m_logger->debug("Entity::saveXML() : XML entity saved");
        } 
        catch ( const DOMException& e ) 
        {
            m_logger->fatalStream() << "Entity::saveXML() : XML entity save error: " 
                                    << A(e.getMessage());
            //throw e;
        }
        return xml_entity;
    }

    template <class EncodingT>
    void Entity<EncodingT>::loadXML(DOMElement* xml_entity)
    {
        DOMElement*  xml_attribute = NULL;
        DOMText*     xml_text     = NULL;
        DOMNodeList* xml_list     = NULL;
        string       strClass;

        if (!xml_entity || string("Entity") != A(xml_entity->getTagName()))
        {
            m_logger->fatalStream() << "Entity::loadXML() : XML entity element expected";
            //throw BadXmlFormatException("XML entity element expected");
        }
        else 
        {
            m_name = C(xml_entity->getAttribute( AX("Name") ));
            m_functionName = C(xml_entity->getAttribute( AX("FunctionName") ));
            m_alias = C(xml_entity->getAttribute( AX("Alias") ));
            strClass = A(xml_entity->getAttribute( AX("Class") ));
            if (strClass == "Data")             m_class = ENTITY_DATA;
            else if (strClass == "Function")    m_class = ENTITY_FUNCTION;
            else if (strClass == "Enumeration") m_class = ENTITY_ENUMERATION;
            else if (strClass == "Package")     m_class = ENTITY_PACKAGE;
            else m_logger->warnStream() << "Entity::loadXML() : unknown class : " << strClass;
            m_comment = EncodingT::EMPTY;
            m_attributes.clear();
            if (xml_entity->hasChildNodes()) 
            {
                 xml_list =    xml_entity->getChildNodes();
                 for (unsigned int i=0; i<xml_list->getLength(); ++i)
                 {
                     xml_attribute = (DOMElement*) xml_list->item(i);
                     if (xml_attribute && string("Attribute") == A(xml_attribute->getTagName()))  
                     {
                         Attribute<EncodingT> attr;
                         attr.loadXML(xml_attribute);
                         m_attributes.push_back(attr);
                     }

                     if (xml_attribute && string("Comments") == A(xml_attribute->getTagName())) 
                     {
                        try 
                        {
                            xml_text = (DOMText*) xml_attribute->getFirstChild();
                            if (xml_text) 
                            {
                                m_comment = C(xml_text->getData());
                            }
                        } 
                        catch(DOMException & e) 
                        {
                            m_logger->fatalStream() << "Entity::loadXML() : XML entity comments element error: " 
													<< A(e.getMessage());
                            //throw e;
                        }
                     }
                 }
            }
            m_logger->debugStream() << "Entity::loadXML() : set entity : " 
                                    << encode<EncodingT,ansi>(m_name) << ", "
                                    << encode<EncodingT,ansi>(m_comment);
            m_logger->debug("Entity::loadXML() : XML entity loaded");
        }
    }

    #undef CX
    #undef AX
    #undef C
    #undef A

}
