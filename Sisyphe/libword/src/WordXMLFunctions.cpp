#include "xstring.hpp"
#include "WordXMLNode.h"
#include "WordXMLNodeList.h"
#include "WordXMLDocument.h"
#include "WordXMLFunctions.h"
#include <boost/algorithm/string.hpp>

NAMESPACE_BEGIN(libword)

    // Split text into paragraphs
    std::vector<std::wstring> splitParagraphs(const wchar_t* str)
    {
        // Découpage de la string en paragraphe
        std::vector<std::wstring> texts;
        std::wstring sentence = str;
        typedef std::vector< boost::iterator_range<std::wstring::iterator> > find_vector_type;
        find_vector_type separators;

        boost::ifind_all( separators, sentence, L"\r\n" );
        std::wstring::iterator start = sentence.begin();
        for (find_vector_type::const_iterator i = separators.begin();
             i != separators.end();
             ++i)
        {
            texts.push_back(std::wstring(start, i->begin()));
            start = i->end();
        }
        texts.push_back(std::wstring(start, sentence.end()));
        return texts;
    }

    // Get text position
    void getTextPosition(const WordXMLNode& node, WordXMLNode& paragraph, WordXMLNode& revision, WordXMLNode& run, bool reverse)
    {
        // Recherche du paragraphe de départ
        if(node.getParent(WordXMLNode::PARAGRAPH_TAG).isValid())
        {
            // Fixe le paragraphe de départ
            paragraph = node.getParent(WordXMLNode::PARAGRAPH_TAG);
            // Recherche de la révision de départ
            if (node.getTagName() == WordXMLNode::REVISION_TAG)
            {
                revision = node;
            }
            else if (node.getParent(WordXMLNode::REVISION_TAG).isValid())
            {
                revision = node.getParent(WordXMLNode::REVISION_TAG);
            }
            // Recherche du run de départ
            if (node.getTagName() == WordXMLNode::RUN_TAG)
            {
                run = node;
            }
            else if (node.getParent(WordXMLNode::RUN_TAG).isValid())
            {
                run = node.getParent(WordXMLNode::RUN_TAG);
            }
            else if (revision.isValid())
            {
                WordXMLNodeList child = revision.getNodes(WordXMLNode::RUN_TAG);
                if (child.length() != 0)
                {
                    size_t i = 0;
                    if (reverse)
                    {
                        i = child.length()-1;
                    }
                    run = child.item(i);
                }
            }
            else
            {
                WordXMLNodeList child = paragraph.getNodes(WordXMLNode::RUN_TAG);
                if (child.length() != 0)
                {
                    size_t i = 0;
                    if (reverse)
                    {
                        i = child.length()-1;
                    }
                    run = child.item(i);
                }
            }
        }
        else
        {
            // Recherche du paragraphe de départ
            if (node.getTagName() == WordXMLNode::PARAGRAPH_TAG)
            {
                paragraph = node;
            }
            else
            {
                WordXMLNodeList child = node.getNodes(WordXMLNode::PARAGRAPH_TAG);
                if (child.length() != 0)
                {
                    size_t i = 0;
                    if (reverse)
                    {
                        i = child.length()-1;
                    }
                    paragraph = child.item(i);
                }
            }
            if (paragraph.isValid())
            {
                // Recherche du run de départ
                WordXMLNodeList child = paragraph.getNodes(WordXMLNode::RUN_TAG);
                if (child.length() != 0)
                {
                    size_t i = 0;
                    if (reverse)
                    {
                        i = child.length()-1;
                    }
                    run = child.item(i);
                }
                // Fixe la révision de départ
                if (run.isValid())
                {
                    revision = run.getParent(WordXMLNode::REVISION_TAG);
                }
            }
        }
    }

    // Advance position
    void advancePosition(WordXMLNode& paragraph, WordXMLNode& revision, WordXMLNode& run, size_t distance)
    {
        int pPos = distance;
        // Parcours des noeuds jusqu'à avoir pPos < 0
        WordXMLNode tmpNode;
        while ((run.isValid() && (pPos -= run.getString().length()) >= 0) ||
               (!run.isValid() && paragraph.isValid() && (pPos -= 2) >= 0))
        {
            if (run.isValid())
            {
                tmpNode = run.getNextNode();
                if (!tmpNode.isValid() && revision.isValid())
                {
                    tmpNode = revision.getNextNode();
                    revision = WordXMLNode();
                }
                if (tmpNode.isValid() && tmpNode.getTagName() == WordXMLNode::REVISION_TAG)
                {
                    revision = tmpNode;
                    tmpNode = revision.getNodes(WordXMLNode::RUN_TAG).item(0);
                }
                run = tmpNode;
            }
            else if (paragraph.isValid())
            {
                paragraph = paragraph.getNextNode();
                if (paragraph.isValid() && paragraph.getTagName() == WordXMLNode::PARAGRAPH_TAG)
                {
                    run = paragraph.getNodes(WordXMLNode::RUN_TAG).item(0);
                    if (run.isValid())
                    {
                        revision = run.getParent(WordXMLNode::REVISION_TAG);
                    }
                }
                else
                {
                    // Le noeud suivant n'est pas un paragraphe, on s'arrête.
                    paragraph = WordXMLNode();
                }
            }
        }
        // Recherche si le point d'insertion se trouve à l'intérieur d'un run
        if (pPos < 0 && run.isValid() && -((int)run.getString().length()) < pPos)
        {
            WordXMLDocument* document = run.getDocument();
            std::wstring str = run.getString();
            size_t separation = str.length() + pPos;
            std::wstring before = str.substr(0, separation);
            std::wstring after = str.substr(separation);
            WordXMLNode previousRun = run.cloneNode(true);
            // Scission du run
            WordXMLNode text1 = document->createTextNode(before.c_str());
            previousRun.replace(text1, previousRun.getNodes(L"w:t").item(0));
            WordXMLNode text2 = document->createTextNode(after.c_str());
            run.replace(text2, run.getNodes(L"w:t").item(0));
            if (revision.isValid())
            {
                // Scission de la révision
                revision.insertBefore(previousRun, run);
                divideRevisionNode(revision, run);
            }
            else
            {
                paragraph.insertBefore(previousRun, run);
            }
        }
    }

    // Move nodes to destination parent node
    void moveNodes(WordXMLNode& parent, WordXMLNode& node)
    {
        WordXMLNode tmpNode;
        while (node.isValid())
        {
            parent.append(node.cloneNode(true));
            tmpNode = node.getNextNode();
            node.erase();
            node = tmpNode;
        }
    }

    // Divide revision node in two parts
    WordXMLNode divideRevisionNode(const WordXMLNode& revision, WordXMLNode& firstNewNode)
    {
        WordXMLDocument* document  = revision.getDocument();
        WordXMLNode parent         = revision.getParent();
        WordXMLNode nextAnnotation = document->createNode(L"aml:content");
        WordXMLNode nextRevision   = revision.cloneNode(false);
        nextRevision.append(nextAnnotation);
        parent.insertBefore(nextRevision, revision.getNextNode());
        moveNodes(nextAnnotation, firstNewNode);
        return nextRevision;
    }

    // Create revision node
    WordXMLNode createRevisionNode(WordXMLNode& parent, const WordXMLNode& refNode, const wchar_t* type, WordXMLNode& content)
    {
        WordXMLDocument* document = parent.getDocument();
        WordXMLNode annotation    = document->createNode(WordXMLNode::REVISION_TAG);
        annotation.setAttribute(L"w:type", type);
        parent.insertBefore(annotation, refNode);
        content = document->createNode(L"aml:content");
        annotation.append(content);
        return annotation;
    }

    // Set paragraph revision property
    WordXMLNode setParagraphRevisionProperty(WordXMLNode& paragraph, const wchar_t* type)
    {
        WordXMLDocument* document       = paragraph.getDocument();
        WordXMLNode paragraphProperties = document->createNode(L"w:pPr");
        WordXMLNode runProperties       = document->createNode(L"w:rPr");
        WordXMLNode paragraphAnnotation = document->createNode(WordXMLNode::REVISION_TAG);
        paragraphAnnotation.setAttribute(L"w:type", type);
        runProperties.append(paragraphAnnotation);
        paragraphProperties.append(runProperties);
        paragraph.setPropertiesNode(paragraphProperties);
        return paragraphAnnotation;
    }
    
NAMESPACE_END
