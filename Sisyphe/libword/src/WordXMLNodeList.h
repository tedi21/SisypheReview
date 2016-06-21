#ifndef _WORD_XML_NODELIST_H_
#define _WORD_XML_NODELIST_H_

#include "LibWordExport.h"
#include "config.hpp"
#include <xercesc/dom/DOMNodeList.hpp>
#include <xalanc/XPath/NodeRefList.hpp>
#include <boost/shared_ptr.hpp>

NAMESPACE_BEGIN(libword)

    class WordXMLDocument;
    class WordXMLNode;

    // Classe représentant une liste de noeuds
    class LIBWORD_API WordXMLNodeList
    {
    private:
        // Classe représentant une liste abstraite d'objet WordXMLNode
        class WordXMLNodePlaceHolderList
        {
        public:
            virtual ~WordXMLNodePlaceHolderList() {}
            virtual WordXMLNode item(size_t i) const = 0;
            virtual size_t length() const = 0;
        };

        // Implémentation du placeholder pour les listes xerces
        class WordXMLNodeXercesList
        : public WordXMLNodePlaceHolderList
        {
        private:
            WordXMLDocument*      m_document;
            xercesc::DOMNodeList* m_list;

        public:
            WordXMLNodeXercesList(WordXMLDocument* doc, xercesc::DOMNodeList* list);
            virtual WordXMLNode item(size_t i) const;
            virtual size_t length() const;
        };

        // Implémentation du placeholder pour les listes xalan
        class WordXMLNodeXalanList
        : public WordXMLNodePlaceHolderList
        {
        private:
            WordXMLDocument*    m_document;
            xalanc::NodeRefList m_list;

        public:
            WordXMLNodeXalanList(WordXMLDocument* doc, const xalanc::NodeRefList& list);
            virtual WordXMLNode item(size_t i) const;
            virtual size_t length() const;
        };

        // Implémentation du placeholder pour les vecteur stl
        class WordXMLNodeVector
        : public WordXMLNodePlaceHolderList
        {
        private:
            std::vector<WordXMLNode> m_list;

        public:
            WordXMLNodeVector(const std::vector<WordXMLNode>& list);
            virtual WordXMLNode item(size_t i) const;
            virtual size_t length() const;
        };

        // Attributs
        log4cpp::Category*    m_logger;
        boost::shared_ptr<WordXMLNodePlaceHolderList> m_list;

    public:
        WordXMLNodeList();

        WordXMLNodeList(WordXMLDocument* doc, const xalanc::NodeRefList& list);

        WordXMLNodeList(WordXMLDocument* doc, xercesc::DOMNodeList* list);

        WordXMLNodeList(const std::vector<WordXMLNode>& list);

        ~WordXMLNodeList();

        // Retourne le noeud à l'index i
        WordXMLNode item(size_t i) const;

        // Retourne la taille de la liste
        size_t length() const;
    };

NAMESPACE_END

#endif // _WORD_XML_NODELIST_H_
