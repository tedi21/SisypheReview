#ifndef _WORD_XML_DOCUMENT_H_
#define _WORD_XML_DOCUMENT_H_

#include "LibWordExport.h"
#include "config.hpp"
#include "encoding.hpp"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xalanc/XercesParserLiaison/XercesDOMSupport.hpp>
#include <xalanc/XercesParserLiaison/XercesParserLiaison.hpp>
#include <xalanc/XPath/XPathEvaluator.hpp>
#include <xalanc/XalanDOM/XalanDocument.hpp>
#include <xalanc/XercesParserLiaison/XercesDocumentWrapper.hpp>

NAMESPACE_BEGIN(libword)

    class WordXMLNode;

    // Classe représantant un document Word XML
    class LIBWORD_API WordXMLDocument
    {
    private:
        log4cpp::Category* m_logger;
        enc::ucs::string_t m_documentName;
        friend class WordXMLNode;
        friend class WordXMLNodeList;
        xercesc::XercesDOMParser*    m_parser;

        xalanc::XercesParserLiaison* m_liaison;
        xalanc::XPathEvaluator*      m_evaluator;
        xalanc::XercesDOMSupport*    m_domsupport;
        xercesc::DOMDocument*        m_xmldocument;
        xalanc::XalanDocument*       m_xlstdocument;
        xalanc::XercesDocumentWrapper* m_wrapper;
        
        // Pas de recopie
        WordXMLDocument(const WordXMLDocument&);
        WordXMLDocument& operator=(const WordXMLDocument&);

    public:
        WordXMLDocument();

        ~WordXMLDocument();

        // Ouvre un fichier Word XML
        void parse(const enc::ucs::string_t& doc);

        // Retourne le noeud racine du document
        WordXMLNode getDocumentNode();

        // Crée un nouveau noeud
        WordXMLNode createNode(const enc::ucs::char_t* tagName);

        // Crée un noeud texte
        WordXMLNode createTextNode(const enc::ucs::char_t* str);

        // Enregistre le document
        void save() const ;

        // Initialise le parser XML
        static void initialize();

        // Libère le parser XML
        static void terminate();
    };

NAMESPACE_END

#endif // _WORD_XML_DOCUMENT_H_
