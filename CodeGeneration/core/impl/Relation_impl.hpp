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
    DOMNode* Relation<EncodingT>::saveXML(DOMDocument* xml_doc) const
    {
        DOMElement* xml_relation = NULL;
        DOMNode*    xml_comment  = NULL;
        DOMText*    xml_text     = NULL;
        xml::string_t strMultiplicity;
        try 
        {
            xml_relation = xml_doc->createElement( AX("Relation") ); 
            xml_relation->setAttribute( AX("Name"),      CX(m_name) );
            if (hasAlias())
            {
                xml_relation->setAttribute(AX("Alias"),  CX(m_alias));
            }
            xml_relation->setAttribute( AX("Target"),    CX(m_target) );
            xml_relation->setAttribute( AX("TargetREF"), CX(m_targetRef) );
            xml_relation->setAttribute( AX("Source"),    CX(m_source) );
            xml_relation->setAttribute( AX("SourceREF"), CX(m_sourceRef) );
            switch (m_multiplicity)
            {
            case RELATION_ZERO_ONE : strMultiplicity = u"Zero-One";break;
            case RELATION_ONE      : strMultiplicity = u"One";     break;
            default                : strMultiplicity = u"Unknown"; break;
            }
            xml_relation->setAttribute( AX("Multiplicity"), strMultiplicity.c_str() );
            if (hasComment()) 
            {
                xml_comment = xml_doc->createElement( AX("Comments") );
                xml_relation->appendChild(xml_comment);
                xml_text = xml_doc->createTextNode( CX(m_comment) );
                xml_comment->appendChild(xml_text);
            }
            m_logger->debug("Relation::saveXML() : XML relation saved");
        } 
        catch ( const DOMException& e ) 
        {
            m_logger->fatalStream() << "Relation::saveXML() : XML relation save error: " << A(e.getMessage());
            //throw e;
        }
        return xml_relation;
    }

    template <class EncodingT>
    void Relation<EncodingT>::loadXML(DOMElement* xml_relation)
    {
        DOMText*     xml_text       = NULL;
        DOMNodeList* xml_list       = NULL;
        DOMElement*  xml_comment    = NULL;
        string       strMultiplicity;

        if (!xml_relation || string("Relation") != A(xml_relation->getTagName()))
        {
            m_logger->fatalStream() << "Relation::loadXML() : XML relation element expected";
        }
        else 
        {
            m_name      = C(xml_relation->getAttribute( AX("Name") ));
            m_alias     = C(xml_relation->getAttribute( AX("Alias") ));
            m_target    = C(xml_relation->getAttribute( AX("Target") ));
            m_targetRef = C(xml_relation->getAttribute( AX("TargetREF") ));
            m_source    = C(xml_relation->getAttribute( AX("Source") ));
            m_sourceRef = C(xml_relation->getAttribute( AX("SourceREF") ));
            strMultiplicity = A(xml_relation->getAttribute( AX("Multiplicity") ));
            if (strMultiplicity == "Zero-One") m_multiplicity = RELATION_ZERO_ONE;
            else if (strMultiplicity == "One") m_multiplicity = RELATION_ONE;
            else if (strMultiplicity != "")    m_logger->warnStream() << "Relation::loadXML() : unknown multiplicity : " << strMultiplicity;
            m_comment   = EncodingT::EMPTY;
            xml_list    = xml_relation->getElementsByTagName( AX("Comments") );
            if ( xml_list->getLength()>0 )
            {
                xml_comment = (DOMElement*) xml_list->item(0);
                if (!xml_comment || string("Comments") != A(xml_comment->getTagName()))
                {
                    m_logger->fatalStream() << "Relation::loadXML() : XML comments element expected";
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
                        m_logger->fatalStream() << "Relation::loadXML() : XML relation comments element error: " << A(e.getMessage());
                        //throw e;
                    }
                }
            }
            m_logger->debugStream() << "Relation::loadXML() : set relation : "
                                    << encode<EncodingT,ansi>(m_name) 
                                    << " Value " << encode<EncodingT,ansi>(m_target) 
                                    << " (" << encode<EncodingT,ansi>(m_targetRef) << ")"                                    
                                    << " is a reference of " << encode<EncodingT,ansi>(m_source) 
                                    << " (" << encode<EncodingT,ansi>(m_sourceRef) << "), "
                                    << encode<EncodingT,ansi>(m_comment);
            m_logger->debug("Relation::loadXML() : XML relation loaded");
        }
    }

    #undef CX
    #undef AX
    #undef C
    #undef A

}
