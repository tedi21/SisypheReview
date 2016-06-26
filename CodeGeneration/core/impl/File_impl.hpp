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
    DOMNode* File<EncodingT>::saveXML(DOMDocument* xml_doc) const
    {
        DOMElement* xml_file    = NULL;
        DOMNode*    xml_comment = NULL;
        DOMText*    xml_text    = NULL;
        try 
        {
            xml_file = xml_doc->createElement( AX("File") ); 
            xml_file->setAttribute( AX("Name"), CX(m_name) );
            if (hasAlias())
            {
                xml_file->setAttribute( AX("Alias"), CX(m_alias) );
            }
            if (hasComment()) 
            {
                xml_comment = xml_doc->createElement( AX("Comments") );
                xml_file->appendChild(xml_comment);
                xml_text = xml_doc->createTextNode( CX(m_comment) );
                xml_comment->appendChild(xml_text);
            }
            for (const_ent_iterator e = m_entities.begin(); e != m_entities.end(); ++e)
            {
                xml_file->appendChild(e->saveXML(xml_doc));
            }
            for (const_rel_iterator r = m_relations.begin(); r != m_relations.end(); ++r)
            {
                xml_file->appendChild(r->saveXML(xml_doc));
            }
            for (const_cnt_iterator c = m_contents.begin(); c != m_contents.end(); ++c)
            {
                xml_file->appendChild(c->saveXML(xml_doc));
            }
            m_logger->debug("File::saveXML() : XML file saved");
        } 
        catch ( const DOMException& e ) 
        {
            m_logger->fatalStream() << "File::saveXML() : XML file save error: " 
									<< A(e.getMessage());
            //throw e;
        }
        return xml_file;
    }

    template <class EncodingT>
    void File<EncodingT>::loadXML(DOMElement* xml_file)
    {
        DOMElement*  xml_entity     = NULL;
        DOMText*     xml_text       = NULL;
        DOMNodeList* xml_list       = NULL;

        if (!xml_file || string("File") != A(xml_file->getTagName()))
        {
            m_logger->fatalStream() << "File::loadXML() : XML file element expected";
            //throw BadXmlFormatException("XML entity element expected");
        }
        else 
        {
            m_name = C(xml_file->getAttribute( AX("Name") ));
            m_alias = C(xml_file->getAttribute( AX("Alias") ));
            m_comment = EncodingT::EMPTY;
            m_entities.clear();
            m_relations.clear();
            m_contents.clear();
            if (xml_file->hasChildNodes()) 
            {
                 xml_list =    xml_file->getChildNodes();
                 for (unsigned int i=0; i<xml_list->getLength(); ++i)
                 {
                     xml_entity = (DOMElement*) xml_list->item(i);
                     if (xml_entity && string("Entity") == A(xml_entity->getTagName()))  
                     {
                         Entity<EncodingT> ent;
                         ent.loadXML(xml_entity);
                         m_entities.push_back(ent);
                     }
                     if (xml_entity && string("Relation") == A(xml_entity->getTagName()))  
                     {
                         Relation<EncodingT> rel;
                         rel.loadXML(xml_entity);
                         m_relations.push_back(rel);
                     }
                     if (xml_entity && string("Content") == A(xml_entity->getTagName()))  
                     {
                         Content<EncodingT> cnt;
                         cnt.loadXML(xml_entity);
                         m_contents.push_back(cnt);
                     }
                     if (xml_entity && string("Comments") == A(xml_entity->getTagName())) 
                     {
                        try 
                        {
                            xml_text = (DOMText*) xml_entity->getFirstChild();
                            if (xml_text)
                            {
                                m_comment = C(xml_text->getData());
                            }
                        } 
                        catch(DOMException & e) 
                        {
                            m_logger->fatalStream() << "File::loadXML() : XML file comments element error: " 
                                                    << A(e.getMessage());
                            //throw e;
                        }
                     }
                 }
            }
            m_logger->debugStream() << "File::loadXML() : set file : " 
                                    << encode<EncodingT,ansi>(m_name) << ", "
                                    << encode<EncodingT,ansi>(m_comment);
            m_logger->debug("File::loadXML() : XML file loaded");
        }
    }

    #undef CX
    #undef AX
    #undef C
    #undef A

}
