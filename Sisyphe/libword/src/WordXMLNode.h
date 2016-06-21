#ifndef _WORD_XML_NODE_H_
#define _WORD_XML_NODE_H_

#include "LibWordExport.h"
#include "config.hpp"
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
        static const wchar_t* DOCUMENT_TAG;
        static const wchar_t* BODY_TAG;
        static const wchar_t* SECTION_TAG;
        static const wchar_t* SUBSECTION_TAG;
        static const wchar_t* TABLE_TAG;
        static const wchar_t* ROW_TAG;
        static const wchar_t* CELL_TAG;
        static const wchar_t* PARAGRAPH_TAG;
        static const wchar_t* REVISION_TAG;
        static const wchar_t* RUN_TAG;

        static const size_t NO_LENGTH = -1;

        WordXMLNode();

        WordXMLNode(WordXMLDocument* doc, xercesc::DOMNode* node);

        // Retourne le nom du noeud
        std::wstring getTagName() const;

        // Execute une requête XPath
        WordXMLNodeList evaluate(const wchar_t* xpath) const;

        // Retourne les noeuds fils
        WordXMLNodeList getNodes() const;

        // Retourne les noeuds fils avec le nom tagName
        WordXMLNodeList getNodes(const wchar_t* tagName) const;

        // Retourne le noeud suivant
        WordXMLNode getNextNode() const;

        // Retourne le noeud suivant
        WordXMLNode getNextNode(const wchar_t* tagName) const;

        // Retourne le noeud précèdent
        WordXMLNode getPreviousNode() const;

        // Retourne le noeud précèdent
        WordXMLNode getPreviousNode(const wchar_t* tagName) const;

        // Retourne le noeud parent
        WordXMLNode getParent() const;

        // Retourne le noeud parent avec le nom tagName
        WordXMLNode getParent(const wchar_t* tagName) const;

        // Retourne le contenu d'un noeud
        std::wstring getContent() const;

        // Indique si le noeud à un attribut attrName
        bool hasAttribute(const wchar_t* attrName) const;

        // Retourne la valeur de l'attribut attrName
        std::wstring getAttribute(const wchar_t* attrName) const;

        // retourne les noms des attributs du noeud
        std::list<std::wstring> getAttributesNames() const;

        // Retourne le texte brut du noeud
        std::wstring getString() const;

        // Retourne le noeud Propriétés correspondant au noeud conteneur en cours
        WordXMLNode getPropertiesNode() const;

        // Retourne le document
        WordXMLDocument* getDocument() const;

        // Indique si le noeud est valide
        bool isValid() const;

        // Définit le contenu
        void setContent(const wchar_t* content);

        // Définit un attribut
        void setAttribute(const wchar_t* attrName, const wchar_t* attrValue);

        // Supprime un attribut
        void eraseAttribute(const wchar_t* attrName);

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
        WordXMLNodeList appendString(bool trackedChanges, const wchar_t* str);

        // Supprime du texte
        void eraseString(bool trackedChanges, size_t pos = 0, size_t length = NO_LENGTH);

        // Insère du texte
        WordXMLNodeList insertString(bool trackedChanges, size_t pos, const wchar_t* str);
    };

NAMESPACE_END

#endif // _WORD_XML_NODE_H_
