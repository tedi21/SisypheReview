#include "WordXMLNodeList.h"
#include "WordXMLDocument.h"
#include "WordXMLNode.h"

NAMESPACE_BEGIN(libword)

    WordXMLNodeList::WordXMLNodeXercesList::WordXMLNodeXercesList(WordXMLDocument* doc, xercesc::DOMNodeList* list)
    : m_document(doc),
      m_list(list)
    {
    }

    WordXMLNode WordXMLNodeList::WordXMLNodeXercesList::item(size_t i) const
    {
        WordXMLNode node;
        if (m_list)
        {
            node = WordXMLNode(m_document, m_list->item(i));
        }
        return node;
    }

    size_t WordXMLNodeList::WordXMLNodeXercesList::length() const
    {
        size_t res = 0;
        if (m_list)
        {
            res = m_list->getLength();
        }
        return res;
    }

    WordXMLNodeList::WordXMLNodeXalanList::WordXMLNodeXalanList(WordXMLDocument* doc, const xalanc::NodeRefList& list)
    : m_document(doc),
      m_list(list)
    {
    }

    WordXMLNode WordXMLNodeList::WordXMLNodeXalanList::item(size_t i) const
    {
        WordXMLNode node;
        if (m_document             &&
            m_document->m_wrapper  &&
            m_list.item(i))
        {
            node = WordXMLNode(m_document,
                               const_cast<xercesc::DOMNode*>(m_document->m_wrapper->mapNode(m_list.item(i))));
        }
        return WordXMLNode(node);
    }

    size_t WordXMLNodeList::WordXMLNodeXalanList::length() const
    {
        return m_list.getLength();
    }

    WordXMLNodeList::WordXMLNodeVector::WordXMLNodeVector(const std::vector<WordXMLNode>& list)
    : m_list(list)
    {
    }

    WordXMLNode WordXMLNodeList::WordXMLNodeVector::item(size_t i) const
    {
        return m_list[i];
    }

    size_t WordXMLNodeList::WordXMLNodeVector::length() const
    {
        return m_list.size();
    }

    WordXMLNodeList::WordXMLNodeList()
    {
        m_logger = &log4cpp::Category::getInstance(LOGNAME);
    }

    WordXMLNodeList::WordXMLNodeList(WordXMLDocument* doc, const xalanc::NodeRefList& list)
    {
        m_logger = &log4cpp::Category::getInstance(LOGNAME);
        m_list.reset(new WordXMLNodeXalanList(doc, list));
    }

    WordXMLNodeList::WordXMLNodeList(WordXMLDocument* doc, xercesc::DOMNodeList* list)
    {
        m_logger = &log4cpp::Category::getInstance(LOGNAME);
        m_list.reset(new WordXMLNodeXercesList(doc, list));
    }

    WordXMLNodeList::WordXMLNodeList(const std::vector<WordXMLNode>& list)
    {
        m_logger = &log4cpp::Category::getInstance(LOGNAME);
        m_list.reset(new WordXMLNodeVector(list));
    }

    WordXMLNodeList::~WordXMLNodeList()
    {}

    // Retourne le noeud à l'index i
    WordXMLNode WordXMLNodeList::item(size_t i) const
    {
        WordXMLNode node;
        if (m_list)
        {
            node = m_list->item(i);
        }
        else
        {
            m_logger->errorStream() << "Unable to get item because the xml list is invalid.";
        }
        return WordXMLNode(node);
    }

    // Retourne la taille de la liste
    size_t WordXMLNodeList::length() const
    {
        size_t res = 0;
        if (m_list)
        {
            res = m_list->length();
        }
        else
        {
            m_logger->errorStream() << "Unable to get item because the xml list is invalid.";
        }
        return res;
    }

NAMESPACE_END
