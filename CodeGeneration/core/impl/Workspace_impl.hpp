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
    DOMNode* Workspace<EncodingT>::saveXML(DOMDocument* xml_doc) const
    {
        DOMElement* xml_wrks    = NULL;
        DOMNode*    xml_comment = NULL;
        DOMText*    xml_text    = NULL;
        try 
        {
            xml_wrks = xml_doc->createElement( AX("Workspace") );
            xml_wrks->setAttribute( AX("Name"), CX(m_name) );
            xml_wrks->setAttribute( AX("Author"), CX(m_author) );
            xml_wrks->setAttribute( AX("Brief"), CX(m_brief) );
            xml_wrks->setAttribute( AX("Version"), CX(m_version) );
            xml_wrks->setAttribute( AX("Type"), (m_type==WRK_FILE)?AX("File"):AX("Project") );
            xml_wrks->setAttribute( AX("Option"), AX(ToString::parse(m_option)));
            if (hasComment()) 
            {
                xml_comment = xml_doc->createElement( AX("Comments") );
                xml_wrks->appendChild(xml_comment);
                xml_text = xml_doc->createTextNode( CX(m_comment) );
                xml_comment->appendChild(xml_text);
            }
            for (const_file_iterator ite = beginFiles(); ite != endFiles(); ++ite)
            {
                xml_wrks->appendChild(ite->saveXML(xml_doc));
            }
            m_logger->debug("Workspace::saveXML() : XML workspace saved");
        } 
        catch ( const DOMException& e ) 
        {
            m_logger->fatalStream() << "Workspace::saveXML() : XML workspace save error: " 
                                    << A(e.getMessage());
            //throw e;
        }
        return xml_wrks;
    }

    template <class EncodingT>
    void Workspace<EncodingT>::loadXML(DOMElement* xml_wrks)
    {
        DOMElement*  xml_file       = NULL;
        DOMText*     xml_text       = NULL;
        DOMNodeList* xml_list       = NULL;

        if (!xml_wrks || string("Workspace") != A(xml_wrks->getTagName()))
        {
            m_logger->fatalStream() << "Workspace::loadXML() : XML workspace element expected";
            //throw BadXmlFormatException("XML entity element expected");
        }
        else {
            m_name = C(xml_wrks->getAttribute( AX("Name") ));
            m_author = C(xml_wrks->getAttribute( AX("Author") ));
            m_brief = C(xml_wrks->getAttribute( AX("Brief") ));
            m_version = C(xml_wrks->getAttribute( AX("Version") ));
            m_type = (A(xml_wrks->getAttribute( AX("Type") ))==string("File"))?WRK_FILE:WRK_PROJECT;
            m_option = ToInt::parse(A(xml_wrks->getAttribute( AX("Option") )));
            m_comment = EncodingT::EMPTY;
            m_files.clear();
            if (xml_wrks->hasChildNodes())
            {
                 xml_list = xml_wrks->getChildNodes();
                 for (unsigned int i=0; i<xml_list->getLength(); ++i)
                 {
                     xml_file = (DOMElement*) xml_list->item(i);
                     if (xml_file && string("File") == A(xml_file->getTagName()))
                     {
                         File<EncodingT> fi;
                         fi.loadXML(xml_file);
                         m_files.push_back(fi);
                     }

                     if (xml_file && string("Comments") == A(xml_file->getTagName()))
                     {
                        try 
                        {
                            xml_text = (DOMText*) xml_file->getFirstChild();
                            if (xml_text)
                            {
                                m_comment = C(xml_text->getData());
                            }
                        } 
                        catch(DOMException & e) 
                        {
                            m_logger->fatalStream() << "Workspace::loadXML() : XML wrk comments element error: " 
                                                    << A(e.getMessage());
                            //throw e;
                        }
                     }
                 }
            }
            // Add wokspace file if it is not defined.
            if (m_type==WRK_FILE && 
                (m_files.empty()  || 
                 sizeFiles() != 1 || 
                 beginFiles()->getName() != getName()))
            {
                openFile(getName(), true);
            }
            m_logger->debugStream() << "set workspace : "
                                    << encode<EncodingT,ansi>(m_name) << ", "
                                    << encode<EncodingT,ansi>(m_comment);
            m_logger->debug("Workspace::loadXML() : XML workspace loaded");
        }
    }

    #undef CX
    #undef AX
    #undef C
    #undef A

}
