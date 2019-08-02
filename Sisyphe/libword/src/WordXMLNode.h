#ifndef _WORD_XML_NODE_H_
#define _WORD_XML_NODE_H_

#include "LibWordExport.h"
#include "config.hpp"
#include "encoding.hpp"
#include <xercesc/dom/DOMNode.hpp>
#include <list>

NAMESPACE_BEGIN(libword)

    class WordXMLDocument;
    class WordXMLNodeList;

    // Classe représentant un noeud XML du document Word
    class LIBWORD_API WordXMLNode
    {
    private:
        log4cpp::Category* m_logger;
        WordXMLDocument*   m_document;
        xercesc::DOMNode*  m_node;

    public:
        static const enc::ucs::char_t* DOCUMENT_TAG;
        static const enc::ucs::char_t* BODY_TAG;
        static const enc::ucs::char_t* SECTION_TAG;
        static const enc::ucs::char_t* SUBSECTION_TAG;
        static const enc::ucs::char_t* TABLE_TAG;
        static const enc::ucs::char_t* ROW_TAG;
        static const enc::ucs::char_t* CELL_TAG;
        static const enc::ucs::char_t* PARAGRAPH_TAG;
        static const enc::ucs::char_t* REVISION_TAG;
        static const enc::ucs::char_t* RUN_TAG;

        static const size_t NO_LENGTH = static_cast<size_t>(-1);

        WordXMLNode();

        WordXMLNode(WordXMLDocument* doc, xercesc::DOMNode* node);

        // Retourne le nom du noeud
        enc::ucs::string_t getTagName() const;

        // Execute une requête XPath
        WordXMLNodeList evaluate(const enc::ucs::char_t* xpath) const;

        // Retourne les noeuds fils
        WordXMLNodeList getNodes() const;

        // Retourne les noeuds fils avec le nom tagName
        WordXMLNodeList getNodes(const enc::ucs::char_t* tagName) const;

        // Retourne le noeud suivant
        WordXMLNode getNextNode() const;

        // Retourne le noeud suivant
        WordXMLNode getNextNode(const enc::ucs::char_t* tagName) const;

        // Retourne le noeud précèdent
        WordXMLNode getPreviousNode() const;

        // Retourne le noeud précèdent
        WordXMLNode getPreviousNode(const enc::ucs::char_t* tagName) const;

        // Retourne le noeud parent
        WordXMLNode getParent() const;

        // Retourne le noeud parent avec le nom tagName
        WordXMLNode getParent(const enc::ucs::char_t* tagName) const;

        // Retourne le contenu d'un noeud
        enc::ucs::string_t getContent() const;

        // Indique si le noeud à un attribut attrName
        bool hasAttribute(const enc::ucs::char_t* attrName) const;

        // Retourne la valeur de l'attribut attrName
        enc::ucs::string_t getAttribute(const enc::ucs::char_t* attrName) const;

        // retourne les noms des attributs du noeud
        std::list<enc::ucs::string_t> getAttributesNames() const;

        // Retourne le texte brut du noeud
        enc::ucs::string_t getString() const;

        // Retourne le noeud Propriétés correspondant au noeud conteneur en cours
        WordXMLNode getPropertiesNode() const;

        // Retourne le document
        WordXMLDocument* getDocument() const;

        // Indique si le noeud est valide
        bool isValid() const;

        // Définit le contenu
        void setContent(const enc::ucs::char_t* content);

        // Définit un attribut
        void setAttribute(const enc::ucs::char_t* attrName, const enc::ucs::char_t* attrValue);

        // Supprime un attribut
        void eraseAttribute(const enc::ucs::char_t* attrName);

        // Retourne le noeud Propriétés correspondant au noeud conteneur en cours
        // ou crée le noeud si celui-ci n'existe pas
        WordXMLNode createPropertiesNode();

        // Définit le noeud Propriétés
        void setPropertiesNode(WordXMLNode node);

        // Supprime le noeud Propriétés
        void erasePropertiesNode();

        // Ajoute un nouveau noeud
        void append(WordXMLNode newChild);

        // Supprime le noeud
        void erase();

        // Remplace un noeud
        void replace(WordXMLNode newChild, WordXMLNode oldChild);

        // Insère un nouveau noeud
        void insertBefore(WordXMLNode newChild, WordXMLNode refChild);

        // Clone le noeud
        WordXMLNode cloneNode(bool deep) const;

        // Ajoute du texte
        WordXMLNodeList appendString(bool trackedChanges, const enc::ucs::char_t* str);

        // Supprime du texte
        void eraseString(bool trackedChanges, size_t pos = 0, size_t length = NO_LENGTH);

        // Insère du texte
        WordXMLNodeList insertString(bool trackedChanges, size_t pos, const enc::ucs::char_t* str);
    };

NAMESPACE_END

#endif // _WORD_XML_NODE_H_
