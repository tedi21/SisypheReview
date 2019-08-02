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
    DOMNode* Content<EncodingT>::saveXML(DOMDocument* xml_doc) const
    {
        DOMElement* xml_content    = NULL;
        DOMText*    xml_data       = NULL;
        try 
        {
            xml_content = xml_doc->createElement( XML("Content") ); 
            xml_content->setAttribute( XML("Type"), CX(m_type) );
            if (!m_target.empty())
            {
                xml_content->setAttribute( XML("Target"), CX(m_target) );
            }
            if (!m_targetREF.empty())
            {
                xml_content->setAttribute( XML("TargetREF"), CX(m_targetREF) );
            }
            xml_data = xml_doc->createTextNode( CX(m_data) );
            xml_content->appendChild(xml_data);
            m_logger->debug("Content::saveXML() : XML content saved");
        } 
        catch ( const DOMException& e ) 
        {
            m_logger->fatalStream() << "Content::saveXML() : XML content save error: " 
									<< A(e.getMessage());
            //throw e;
        }
        return xml_content;
    }

    template <class EncodingT>
    void Content<EncodingT>::loadXML(DOMElement* xml_content)
    {
        DOMText*     xml_data       = NULL;

        if (!xml_content || string("Content") != A(xml_content->getTagName()))
        {
            m_logger->fatalStream() << "Content::loadXML() : XML content element expected";
            //throw BadXmlFormatException("XML entity element expected");
        }
        else 
        {
            m_type = C(xml_content->getAttribute( XML("Type") ));
            m_target = C(xml_content->getAttribute( XML("Target") ));
            m_targetREF = C(xml_content->getAttribute( XML("TargetREF") ));
            m_data = EncodingT::EMPTY;
            if (xml_content->hasChildNodes()) 
            {
                try 
                {
                    xml_data = (DOMText*) xml_content->getFirstChild();
                    if (xml_data)
                    {
                        m_data = C(xml_data->getData());
                    }
                } 
                catch(DOMException & e) 
                {
                    m_logger->fatalStream() << "Content::loadXML() : XML content data element error: " 
                                            << A(e.getMessage());
                    //throw e;
                }
            }
            m_logger->debugStream() << "Content::loadXML() : set content : " 
                                    << encode<EncodingT,ansi>(m_type);
            m_logger->debug("Content::loadXML() : XML content loaded");
        }
    }

    #undef CX
    #undef AX
    #undef C
    #undef A

}
