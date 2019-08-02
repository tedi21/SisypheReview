#include "xstring.hpp"
#include "WordXMLNode.h"
#include "WordXMLNodeList.h"
#include "WordXMLDocument.h"
#include "WordXMLFunctions.h"
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xalanc/XPath/XalanXPathException.hpp>

NAMESPACE_BEGIN(libword)

    using namespace enc;

    const ucs::char_t* WordXMLNode::DOCUMENT_TAG    = UCS("w:wordDocument");
    const ucs::char_t* WordXMLNode::BODY_TAG        = UCS("w:body");
    const ucs::char_t* WordXMLNode::SECTION_TAG     = UCS("wx:sect");
    const ucs::char_t* WordXMLNode::SUBSECTION_TAG  = UCS("wx:sub-section");
    const ucs::char_t* WordXMLNode::TABLE_TAG       = UCS("w:tbl");
    const ucs::char_t* WordXMLNode::ROW_TAG         = UCS("w:tr");
    const ucs::char_t* WordXMLNode::CELL_TAG        = UCS("w:tc");
    const ucs::char_t* WordXMLNode::PARAGRAPH_TAG   = UCS("w:p");
    const ucs::char_t* WordXMLNode::REVISION_TAG    = UCS("aml:annotation");
    const ucs::char_t* WordXMLNode::RUN_TAG         = UCS("w:r");

    WordXMLNode::WordXMLNode()
    : m_document(NULL),
      m_node(NULL)
    {
        m_logger = &log4cpp::Category::getInstance(LOGNAME);
    }

    WordXMLNode::WordXMLNode(WordXMLDocument* doc, xercesc::DOMNode *node)
    : m_document(doc),
      m_node(node)
    {
        m_logger = &log4cpp::Category::getInstance(LOGNAME);
    }

    // Retourne le nom du noeud
    enc::ucs::string_t WordXMLNode::getTagName() const
    {
        enc::ucs::string_t res;
        if (m_node)
        {
            if (m_node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
            {
                xercesc::DOMElement* element = (xercesc::DOMElement*) m_node;
                res = encode<xml,ucs>(element->getTagName());
            }
            else
            {
                m_logger->warnStream() << "Unable to get tag because the xml node isn't an element.";
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to get tag because the xml node is invalid.";
        }
        return res;
    }

    // Execute une requête XPath
    WordXMLNodeList WordXMLNode::evaluate(const ucs::char_t* xpath) const
    {
        xalanc::NodeRefList result;
        if (m_node && m_document        &&
            m_document->m_evaluator     &&
            m_document->m_xlstdocument  &&
            m_document->m_domsupport    &&
            m_document->m_wrapper)
        {
            try
            {
                // Execute XPath query
                m_document->m_evaluator->selectNodeList(result,
                                                        *(m_document->m_domsupport),
                                                        m_document->m_wrapper->mapNode(m_node),
                                                        encode<ucs,xml>(xpath).c_str(),
                                                        m_document->m_xlstdocument->getDocumentElement());
            }
            catch (xalanc::XalanXPathException& ex)
            {
                m_logger->warnStream() << "Unable to evaluate xpath because the query is invalid : " << encode<xml,ansi>(ex.getMessage().c_str()) << ".";
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to evaluate xpath because the xml node is invalid.";
        }
        return WordXMLNodeList(m_document, result);
    }

    // Retourne les noeuds fils
    WordXMLNodeList WordXMLNode::getNodes() const
    {
        xercesc::DOMNodeList* nodes = NULL;
        if (m_node)
        {
            nodes = m_node->getChildNodes();
        }
        else
        {
            m_logger->errorStream() << "Unable to get child nodes because the xml node is invalid.";
        }
        return WordXMLNodeList(m_document, nodes);
    }

    // Retourne les noeuds fils avec le nom tagName
    WordXMLNodeList WordXMLNode::getNodes(const ucs::char_t* tagName) const
    {
        xercesc::DOMNodeList* nodes = NULL;
        if (m_node)
        {
            if (m_node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
            {
                xercesc::DOMElement* element = (xercesc::DOMElement*) m_node;
                nodes = element->getElementsByTagName(encode<ucs,xml>(tagName).c_str());
            }
            else
            {
                m_logger->warnStream() << "Unable to get child nodes because the xml node isn't an element.";
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to get child nodes because the xml node is invalid.";
        }
        return WordXMLNodeList(m_document, nodes);
    }

    // Retourne le noeud suivant
    WordXMLNode WordXMLNode::getNextNode() const
    {
        xercesc::DOMNode* node = NULL;
        if (m_node)
        {
            node = m_node->getNextSibling();
        }
        else
        {
            m_logger->errorStream() << "Unable to get next node because the xml node is invalid.";
        }
        return WordXMLNode(m_document, node);
    }

    // Retourne le noeud suivant
    WordXMLNode WordXMLNode::getNextNode(const ucs::char_t* tagName) const
    {
        xercesc::DOMNode* node = m_node;
        if (m_node)
        {
            bool found = false;
            do
            {
                node = node->getNextSibling();
                if (node)
                {
                    if (node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
                    {
                        xercesc::DOMElement* element = (xercesc::DOMElement*) node;
                        found = (encode<xml,ucs>(element->getTagName()) == tagName);
                    }
                }
            }
            while (!found && node);
        }
        else
        {
            m_logger->errorStream() << "Unable to get next node because the xml node is invalid.";
        }
        return WordXMLNode(m_document, node);
    }

    // Retourne le noeud précèdent
    WordXMLNode WordXMLNode::getPreviousNode() const
    {
        xercesc::DOMNode* node = NULL;
        if (m_node)
        {
            node = m_node->getPreviousSibling();
        }
        else
        {
            m_logger->errorStream() << "Unable to get previous node because the xml node is invalid.";
        }
        return WordXMLNode(m_document, node);
    }

    // Retourne le noeud précèdent
    WordXMLNode WordXMLNode::getPreviousNode(const ucs::char_t* tagName) const
    {
        xercesc::DOMNode* node = m_node;
        if (m_node)
        {
            bool found = false;
            do
            {
                node = node->getPreviousSibling();
                if (node)
                {
                    if (node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
                    {
                        xercesc::DOMElement* element = (xercesc::DOMElement*) node;
                        found = (encode<xml,ucs>(element->getTagName()) == tagName);
                    }
                }
            }
            while (!found && node);
        }
        else
        {
            m_logger->errorStream() << "Unable to get previous node because the xml node is invalid.";
        }
        return WordXMLNode(m_document, node);
    }

    // Retourne le noeud parent
    WordXMLNode WordXMLNode::getParent() const
    {
        xercesc::DOMNode* node = m_node;
        if (m_node)
        {
            node = node->getParentNode();
        }
        else
        {
            m_logger->errorStream() << "Unable to get parent node because the xml node is invalid.";
        }
        return WordXMLNode(m_document, node);
    }

    // Retourne le noeud parent avec le nom tagName
    WordXMLNode WordXMLNode::getParent(const ucs::char_t* tagName) const
    {
        xercesc::DOMNode* node = m_node;
        if (m_node)
        {
            bool found = false;
            do
            {
                node = node->getParentNode();
                if (node)
                {
                    if (node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
                    {
                        xercesc::DOMElement* element = (xercesc::DOMElement*) node;
                        found = (encode<xml,ucs>(element->getTagName()) == tagName);
                    }
                }
            }
            while (!found && node);
        }
        else
        {
            m_logger->errorStream() << "Unable to get parent node because the xml node is invalid.";
        }
        return WordXMLNode(m_document, node);
    }

    // Retourne le contenu d'un noeud
    ucs::string_t WordXMLNode::getContent() const
    {
        ucs::string_t res;
        if (m_node)
        {
            if (m_node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
            {
                xercesc::DOMElement* element = (xercesc::DOMElement*) m_node;
                res = encode<xml,ucs>(element->getTextContent());
            }
            else
            {
                m_logger->warnStream() << "Unable to get content because the xml node isn't an element.";
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to get content because the xml node is invalid.";
        }
        return res;
    }

    // Indique si le noeud à un attribut attrName
    bool WordXMLNode::hasAttribute(const ucs::char_t* attrName) const
    {
        bool res = false;
        if (m_node)
        {
            if (m_node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
            {
                xercesc::DOMElement* element = (xercesc::DOMElement*) m_node;
                res = element->hasAttribute(encode<ucs,xml>(attrName).c_str());
            }
            else
            {
                m_logger->warnStream() << "Unable to get attribute because the xml node isn't an element.";
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to get attribute because the xml node is invalid.";
        }
        return res;
    }

    // Retourne la valeur de l'attribut attrName
    ucs::string_t WordXMLNode::getAttribute(const ucs::char_t* attrName) const
    {
        ucs::string_t res;
        if (m_node)
        {
            if (m_node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
            {
                xercesc::DOMElement* element = (xercesc::DOMElement*) m_node;
                res = encode<xml,ucs>(element->getAttribute(encode<ucs,xml>(attrName).c_str()));
            }
            else
            {
                m_logger->warnStream() << "Unable to get attribute because the xml node isn't an element.";
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to get attribute because the xml node is invalid.";
        }
        return res;
    }

    // retourne les noms des attributs du noeud
    std::list<ucs::string_t> WordXMLNode::getAttributesNames() const
    {
        std::list<ucs::string_t> res;
        if (m_node)
        {
            xercesc::DOMNamedNodeMap* map = m_node->getAttributes();
            for (size_t i=0; i<map->getLength(); ++i)
            {
                xercesc::DOMNode* node = map->item(i);
                if (node)
                {
                    if (node->getNodeType() == xercesc::DOMNode::ATTRIBUTE_NODE)
                    {
                        xercesc::DOMAttr* attribute = (xercesc::DOMAttr*) node;
                        res.push_back(encode<xml,ucs>(attribute->getName()));
                    }
                }
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to get attributs names because the xml node is invalid.";
        }
        return res;
    }

    // Retourne le texte brut du noeud
    ucs::string_t WordXMLNode::getString() const
    {
        ucs::string_t res;
        if (m_node)
        {
            WordXMLNodeList paragraphs = getNodes(PARAGRAPH_TAG);
            for (size_t i=0; i<paragraphs.length(); ++i)
            {
                WordXMLNode paragraph = paragraphs.item(i);
                WordXMLNodeList texts = paragraph.getNodes(UCS("w:t"));
                for (size_t j=0; j<texts.length(); ++j)
                {
                    res += texts.item(j).getContent();
                }
                if (i<paragraphs.length()-1 &&
                    (!paragraph.getPropertiesNode().isValid() ||
                     paragraph.getPropertiesNode().evaluate(UCS(".//aml:annotation[@w:type='Word.Deletion']")).length() == 0))
                {
                    res += UCS("\r\n");
                }
            }
            if (paragraphs.length() == 0)
            {
                WordXMLNodeList texts = getNodes(UCS("w:t"));
                for (size_t j=0; j<texts.length(); ++j)
                {
                    res += texts.item(j).getContent();
                }
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to get string because the xml node is invalid.";
        }
        return res;
    }

    // Retourne le noeud Propriétés correspondant au noeud conteneur en cours
    WordXMLNode WordXMLNode::getPropertiesNode() const
    {
        WordXMLNode res;
        if (m_node)
        {
            ucs::string_t tagName = getTagName() + UCS("Pr");
            xercesc::DOMNodeList* list = m_node->getChildNodes();
            if (list)
            {
                size_t i = 0;
                bool found = false;
                while (!found && i < list->getLength())
                {
                    if (list->item(i)->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
                    {
                        xercesc::DOMElement* element = (xercesc::DOMElement*) list->item(i);
                        if (encode<xml,ucs>(element->getTagName()) == tagName)
                        {
                            res = WordXMLNode(m_document, element);
                            found = true;
                        }
                    }
                    i++;
                }
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to get properties node because the xml node is invalid.";
        }
        return res;
    }

    // Retourne le document
    WordXMLDocument* WordXMLNode::getDocument() const
    {
        return m_document;
    }

    // Indique si le noeud est valide
    bool WordXMLNode::isValid() const
    {
        return m_node != NULL;
    }

    // Définit le contenu
    void WordXMLNode::setContent(const ucs::char_t* content)
    {
        if (m_node && m_document)
        {
            if (m_node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
            {
                xercesc::DOMElement* element = (xercesc::DOMElement*) m_node;
                element->appendChild((xercesc::DOMNode*) m_document->m_xmldocument->createTextNode(
                                      encode<ucs,xml>(content).c_str()));
            }
            else
            {
                m_logger->warnStream() << "Unable to set content because the xml node isn't an element.";
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to set content because the xml node is invalid.";
        }
    }

    // Définit un attribut
    void WordXMLNode::setAttribute(const ucs::char_t* attrName, const ucs::char_t* attrValue)
    {
        if (m_node)
        {
            if (m_node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
            {
                xercesc::DOMElement* element = (xercesc::DOMElement*) m_node;
                element->setAttribute(encode<ucs,xml>(attrName).c_str(), encode<ucs,xml>(attrValue).c_str());
            }
            else
            {
                m_logger->warnStream() << "Unable to set attribute because the xml node isn't an element.";
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to set attribute because the xml node is invalid.";
        }
    }

    // Supprime un attribut
    void WordXMLNode::eraseAttribute(const ucs::char_t* attrName)
    {
        if (m_node)
        {
            if (m_node->getNodeType() == xercesc::DOMNode::ELEMENT_NODE)
            {
                xercesc::DOMElement* element = (xercesc::DOMElement*) m_node;
                element->removeAttribute(encode<ucs,xml>(attrName).c_str());
            }
            else
            {
                m_logger->warnStream() << "Unable to erase attribute because the xml node isn't an element.";
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to erase attribute because the xml node is invalid.";
        }
    }

    // Retourne le noeud Propriétés correspondant au noeud conteneur en cours
    // ou crée le noeud si celui-ci n'existe pas
    WordXMLNode WordXMLNode::createPropertiesNode()
    {
        WordXMLNode res;
        if (m_node && m_document)
        {
            res = getPropertiesNode();
            if (!res.m_node)
            {
                res = m_document->createNode((getTagName() + UCS("Pr")).c_str());
                WordXMLNodeList nodes = getNodes();
                WordXMLNode ref;
                if (nodes.length() > 0)
                {
                    ref = nodes.item(0);
                }
                insertBefore(res, ref);
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to create properties node because the xml node is invalid.";
        }
        return res;
    }

    // Définit le noeud Propriétés
    void WordXMLNode::setPropertiesNode(WordXMLNode node)
    {
        if (m_node)
        {
            xercesc::DOMNode* oldNode = getPropertiesNode().m_node;
            if (oldNode)
            {
                m_node->replaceChild(node.m_node, oldNode);
            }
            else
            {
                m_node->insertBefore(node.m_node, m_node->getFirstChild());
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to set properties node because the xml node is invalid.";
        }
    }

    // Supprime le noeud Propriétés
    void WordXMLNode::erasePropertiesNode()
    {
        if (m_node)
        {
            xercesc::DOMNode* oldNode = getPropertiesNode().m_node;
            if (oldNode)
            {
                m_node->removeChild(oldNode);
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to erase properties node because the xml node is invalid.";
        }
    }

    // Ajoute un nouveau noeud
    void WordXMLNode::append(WordXMLNode newChild)
    {
        if (m_node)
        {
            m_node->appendChild(newChild.m_node);
        }
        else
        {
            m_logger->errorStream() << "Unable to append node because the xml node is invalid.";
        }
    }

    // Supprime le noeud
    void WordXMLNode::erase()
    {
        if (m_node && m_node->getParentNode())
        {
            xercesc::DOMNode* parent = m_node->getParentNode();
            parent->removeChild(m_node);
            m_node = NULL;
        }
        else
        {
            m_logger->errorStream() << "Unable to erase node because the xml node is invalid.";
        }
    }

    // Remplace un noeud
    void WordXMLNode::replace(WordXMLNode newChild, WordXMLNode oldChild)
    {
        if (m_node)
        {
            m_node->replaceChild(newChild.m_node, oldChild.m_node);
        }
        else
        {
            m_logger->errorStream() << "Unable to replace node because the xml node is invalid.";
        }
    }

    // Insère un nouveau noeud
    void WordXMLNode::insertBefore(WordXMLNode newChild, WordXMLNode refChild)
    {
        if (m_node)
        {
            m_node->insertBefore(newChild.m_node, refChild.m_node);
        }
        else
        {
            m_logger->errorStream() << "Unable to insert node because the xml node is invalid.";
        }
    }

    // Clone le noeud
    WordXMLNode WordXMLNode::cloneNode(bool deep) const
    {
        WordXMLNode res;
        if (m_node)
        {
            res = WordXMLNode(m_document, m_node->cloneNode(deep));
        }
        else
        {
            m_logger->errorStream() << "Unable to clone node because the xml node is invalid.";
        }
        return res;
    }
    
    // Ajoute du texte
    WordXMLNodeList WordXMLNode::appendString(bool trackedChanges, const ucs::char_t* str)
    {
        std::vector<WordXMLNode> res;
        if (m_node)
        {
            WordXMLNode previousRun;
            WordXMLNode nextRun;
            WordXMLNode refRun;
            WordXMLNode runParent;
            WordXMLNode refParagraph;
            WordXMLNode startParagraph;
            WordXMLNode paragraphParent;
            // Recherche de la position en cours à partir de la fin
            WordXMLNode paragraph, revision, run;
            getTextPosition(*this, paragraph, revision, run, true);
            // Fixe le run précèdent
            previousRun = run;
            // Fixe les noeuds référence pour l'insertion
            if (paragraph.isValid())
            {
                refParagraph = paragraph.getNextNode();
                if (revision.isValid())
                {
                    if (run.isValid())
                    {
                        refRun = run.getNextNode();
                        if (refRun.isValid())
                        {
                            // Séparation de la révision afin d'insérer le run entre les runs de la révision
                            refRun = divideRevisionNode(revision, refRun);
                        }
                    }
                    else
                    {
                        refRun = revision.getNextNode();
                    }
                }
                else if (run.isValid())
                {
                    refRun = run.getNextNode();
                }
            }
            else
            {
                // Aucun paragraphe trouvé, création d'un paragraphe
                paragraph = m_document->createNode(PARAGRAPH_TAG);
                append(paragraph);
            }
            startParagraph  = paragraph;
            paragraphParent = paragraph.getParent();
            runParent = paragraph;

            // Mise en place du suivi de modification
            if (trackedChanges)
            {
                createRevisionNode(paragraph, refRun, UCS("Word.Insertion"), runParent);
                nextRun = refRun;
                refRun = WordXMLNode(m_document, NULL);
            }
            // Découpage du texte en paragraphe
            std::vector<ucs::string_t> texts = splitParagraphs(str);
            // Création des noeuds run
            for (std::vector<ucs::string_t>::const_iterator i = texts.begin();
                 i != texts.end();
                 ++i)
            {
                // Ajout du run
                WordXMLNode text = m_document->createTextNode(i->c_str());
                if (previousRun.isValid())
                {
                    run = previousRun.cloneNode(true);
                    WordXMLNodeList nodeList = run.getNodes(UCS("w:t"));
                    if (nodeList.length() == 0)
                    {
                        nodeList = run.getNodes(UCS("w:delText"));
                    }
                    run.replace(text, nodeList.item(0));
                }
                else
                {
                    run = m_document->createNode(RUN_TAG);
                    run.append(text);
                }
                runParent.insertBefore(run, refRun);
                // Mémorisation du run
                res.push_back(run);
                // Création du paragraphe
                if (i != texts.end()-1)
                {
                    runParent = m_document->createNode(PARAGRAPH_TAG);
                    paragraphParent.insertBefore(runParent, refParagraph);
                    // Mise en place du suivi de modification
                    if (trackedChanges)
                    {
                        setParagraphRevisionProperty(paragraph, UCS("Word.Insertion"));
                        paragraph = runParent;
                        createRevisionNode(paragraph, refRun, UCS("Word.Insertion"), runParent);
                    }
                    else
                    {
                        paragraph = runParent;
                        nextRun = refRun;
                        refRun = WordXMLNode(m_document, NULL);
                    }
                }
                else
                {
                    // Recopie des noeuds run suivant dans le dernier paragraphe
                    if (nextRun.isValid() &&
                        startParagraph.isValid() && paragraph.isValid() &&
                        startParagraph.m_node != paragraph.m_node)
                    {
                        moveNodes(paragraph, nextRun);
                    }
                }
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to append string because the xml node is invalid.";
        }
        return WordXMLNodeList(res);
    }

    // Supprime du texte
    void WordXMLNode::eraseString(bool trackedChanges, size_t pos, size_t length)
    {
        if (m_node && m_document)
        {
            // Récupération des noeuds de départ
            WordXMLNode refRun, refRevision, refParagraph;
            getTextPosition(*this, refParagraph, refRevision, refRun);
            // Avance jusqu'à la position de supression
            advancePosition(refParagraph, refRevision, refRun, pos);

            WordXMLNode startParagraph = refParagraph;
            int pLength = length;
            // Création du suivi de modification
            WordXMLNode revisionNode;
            WordXMLNode tmpNode;
            if (trackedChanges)
            {
                tmpNode = refRun;
                if (refRevision.isValid())
                {
                    tmpNode = refRevision;
                }
                createRevisionNode(refParagraph, tmpNode, UCS("Word.Deletion"), revisionNode);
            }
            // Parcours des noeuds à supprimer
            while ((refRun.isValid() && (length == NO_LENGTH || (pLength -= refRun.getString().length()) >= 0)) ||
                   (!refRun.isValid() && refParagraph.isValid() && (length == NO_LENGTH || (pLength -= 2) >= 0)))
            {
                if (refRun.isValid())
                {
                    tmpNode = refRun.getNextNode();
                    if (trackedChanges)
                    {
                        // Marquage du texte comme supprimé
                        WordXMLNode delRun  = refRun.cloneNode(true);
                        WordXMLNode delText = m_document->createNode(UCS("w:delText"));
                        if (delText.m_node && m_document->m_xmldocument)
                        {
                            delText.m_node->appendChild(
                                        (xercesc::DOMNode*) m_document->m_xmldocument->createTextNode(
                                            encode<ucs,xml>(delRun.getString()).c_str()));
                        }
                        delRun.replace(delText, delRun.getNodes(UCS("w:t")).item(0));
                        // recopie du noeud dans la révision Deletion
                        revisionNode.append(delRun);
                    }
                    // suppression du noeud
                    refRun.erase();
                    if (!tmpNode.isValid() && refRevision.isValid())
                    {
                        tmpNode = refRevision.getNextNode();
                        if (refRevision.getNodes(RUN_TAG).length() == 0)
                        {
                            refRevision.erase();
                        }
                        refRevision = WordXMLNode();
                    }
                    if (tmpNode.isValid() && tmpNode.getTagName() == REVISION_TAG)
                    {
                        refRevision = tmpNode;
                        tmpNode = refRevision.getNodes(RUN_TAG).item(0);
                    }
                    refRun = tmpNode;
                }
                else if (refParagraph.isValid())
                {
                    tmpNode = refParagraph.getNextNode();
                    // suppression du paragraphe si celui-ci est vide
                    if (refParagraph.getNodes(UCS("w:t")).length() == 0)
                    {
                        if (trackedChanges)
                        {
                            setParagraphRevisionProperty(refParagraph, UCS("Word.Deletion"));
                        }
                        else
                        {
                            refParagraph.erase();
                        }
                    }
                    refParagraph = tmpNode;
                    if (refParagraph.isValid() && refParagraph.getTagName() == PARAGRAPH_TAG)
                    {
                        refRun = refParagraph.getNodes(RUN_TAG).item(0);
                    }
                    else
                    {
                        refParagraph = WordXMLNode();
                    }
                }
            }
            // Recherche si le point de fin se trouve à l'intérieur d'un run
            if (length != NO_LENGTH && pLength < 0 && refRun.isValid() && -((int)refRun.getString().length()) < pLength)
            {
                ucs::string_t str = refRun.getString();
                size_t separation = str.length() + pLength;
                ucs::string_t after = str.substr(separation);
                refRun.replace(m_document->createTextNode(after.c_str()), refRun.getNodes(UCS("w:t")).item(0));
                if (trackedChanges)
                {
                    ucs::string_t before = str.substr(0, separation);
                    WordXMLNode delRun  = refRun.cloneNode(true);
                    WordXMLNode delText = m_document->createNode(UCS("w:delText"));
                    if (delText.m_node && m_document->m_xmldocument)
                    {
                        delText.m_node->appendChild(
                                    (xercesc::DOMNode*) m_document->m_xmldocument->createTextNode(
                                        encode<ucs,xml>(before).c_str()));
                    }
                    delRun.replace(delText, delRun.getNodes(UCS("w:t")).item(0));
                    // recopie du noeud dans la révision Deletion
                    revisionNode.append(delRun);
                }
            }
            // Recherche du noeud référence du dernier paragraphe
            WordXMLNode nextNode = refRun;
            if (refRevision.isValid())
            {
                nextNode = refRevision;
            }
            // Recopie des noeuds du dernier paragraphe dans le premier
            if (startParagraph.isValid() && refParagraph.isValid() &&
                startParagraph.m_node != refParagraph.m_node)
            {
                if (trackedChanges)
                {
                    // Marquage du noeud comme supprimé
                    setParagraphRevisionProperty(startParagraph, UCS("Word.Deletion"));
                }
                else
                {
                    moveNodes(startParagraph, nextNode);
                    // Suppression du dernier paragraphe
                    refParagraph.erase();
                }
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to erase string because the xml node is invalid.";
        }
    }

    // Insère du texte
    WordXMLNodeList WordXMLNode::insertString(bool trackedChanges, size_t pos, const ucs::char_t* str)
    {
        WordXMLNodeList res;
        if (m_node)
        {
            // Récupération des noeuds de départ
            WordXMLNode refRun, refRevision, refParagraph;
            getTextPosition(*this, refParagraph, refRevision, refRun);
            // Avance jusqu'à la position d'insertion
            advancePosition(refParagraph, refRevision, refRun, pos);
            // Ajout du texte à la position refRun
            if (refRun.isValid())
            {
                // Récupération du run précèdent
                bool tempRun = false;
                WordXMLNode previousRun = refRun.getPreviousNode();
                if (!previousRun.isValid())
                {
                    // Création d'un run vide temporaire pour l'insertion
                    previousRun = m_document->createNode(RUN_TAG);
                    if (refRevision.isValid())
                    {
                        refRevision.insertBefore(previousRun, refRun);
                    }
                    else
                    {
                        refParagraph.insertBefore(previousRun, refRun);
                    }
                    tempRun = true;
                }
                res = previousRun.appendString(trackedChanges, str);
                // Suppression du run temporaire
                if (tempRun)
                {
                    previousRun.erase();
                }
            }
            else if (refParagraph.isValid())
            {
                res = refParagraph.appendString(trackedChanges, str);
            }
            else
            {
                res = appendString(trackedChanges, str);
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to erase string because the xml node is invalid.";
        }
        return res;
    }

NAMESPACE_END
