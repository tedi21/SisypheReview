#ifndef _WORD_XML_FUNCTIONS_H_
#define _WORD_XML_FUNCTIONS_H_

#include "LibWordExport.h"
#include "WordXMLNode.h"

NAMESPACE_BEGIN(libword)

    // Split text into paragraphs
    std::vector<enc::ucs::string_t> splitParagraphs(const enc::ucs::char_t* str);

    // Get text position
    void getTextPosition(const WordXMLNode& node, WordXMLNode& paragraph, WordXMLNode& revision, WordXMLNode& run, bool reverse = false);

    // Advance position
    void advancePosition(WordXMLNode& paragraph, WordXMLNode& revision, WordXMLNode& run, size_t distance);

    // Move nodes to destination parent node
    void moveNodes(WordXMLNode& parent, WordXMLNode& node);

    // Divide revision node in two parts
    WordXMLNode divideRevisionNode(const WordXMLNode& revision, WordXMLNode& firstNewNode);

    // Create revision node
    WordXMLNode createRevisionNode(WordXMLNode& parent, const WordXMLNode& refNode, const enc::ucs::char_t* type, WordXMLNode& content);

    // Set paragraph revision property
    WordXMLNode setParagraphRevisionProperty(WordXMLNode& paragraph, const enc::ucs::char_t* type);

NAMESPACE_END

#endif // _WORD_XML_FUNCTIONS_H_
