#pragma once

#include <xercesc/dom/DOM.hpp>
#include <boost/iterator/iterator_facade.hpp>

using namespace xercesc;

/// Helper functions browse DOMElement in DOMNode

template <class Node>
Node* getFirstChildElement(Node* node){
    Node*  tmp_node = NULL;
    if (node && node->hasChildNodes()) {
        tmp_node = node->getFirstChild();
        while (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE &&
               tmp_node->hasChildNodes())
            tmp_node = tmp_node->getFirstChild();
        if (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE) tmp_node = NULL;
    }
    return tmp_node;
}

template <class Node>
Node* getNextElement(Node* node){
    Node*  tmp_node = NULL;
    if (node && node->getNextSibling()) {
        tmp_node = node->getNextSibling();
        while (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE &&
               tmp_node->getNextSibling())
            tmp_node = tmp_node->getNextSibling();
        if (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE) tmp_node = NULL;
    }
    return tmp_node;
}

template <class Node>
Node* getLastChildElement(Node* node){
    Node*  tmp_node = NULL;
    if (node && node->hasChildNodes()) {
        tmp_node = node->getLastChild();
        while (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE &&
               tmp_node->hasChildNodes())
            tmp_node = tmp_node->getLastChild();
        if (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE) tmp_node = NULL;
    }
    return tmp_node;
}

template <class Node>
Node* getPreviousElement(Node* node){
    Node*  tmp_node = NULL;
    if (node && node->getPreviousSibling()) {
        tmp_node = node->getPreviousSibling();
        while (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE &&
               tmp_node->getPreviousSibling())
            tmp_node = tmp_node->getPreviousSibling();
        if (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE) tmp_node = NULL;
    }
    return tmp_node;
}

/// iterator browses only child elements

template <class Node, class Element>
class _element_iterator : 
    public boost::iterator_facade< _element_iterator<Node, Element>,
                                   Node,
                                   boost::bidirectional_traversal_tag,
                                   Element*> {
public:
    _element_iterator() : m_node(0){}

    explicit _element_iterator(Node* p)
    : m_node(getFirstChildElement<Node>(p)) {}

private:
    friend class boost::iterator_core_access;

    void increment() { 
        if (m_node) {
            Node* tmp_node = getFirstChildElement<Node>(m_node);
            if (!tmp_node) {
                tmp_node = getNextElement<Node>(m_node);
                if (!tmp_node && m_node->getParentNode()) {
                    tmp_node = m_node->getParentNode();
                    while (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE && tmp_node->getParentNode())
                        tmp_node = tmp_node->getParentNode();
                    tmp_node = getNextElement<Node>(tmp_node);
                }
            }
            m_node = tmp_node;
        }
    }

    void decrement() { 
        if (m_node) {
            Node* tmp_node = getPreviousElement<Node>(m_node);
            if (tmp_node && tmp_node->hasChildNodes())
                tmp_node = getLastChildElement<Node>(tmp_node);
            else if(!tmp_node && m_node->getParentNode()) {
                tmp_node = m_node->getParentNode();
                while (tmp_node->getNodeType()!=DOMNode::ELEMENT_NODE && tmp_node->getParentNode())
                    tmp_node = tmp_node->getParentNode();
            }
            m_node = tmp_node;
        }
    }


    inline bool equal(_element_iterator const& other) const {
        return this->m_node == other.m_node;
    }

    inline const Element* dereference() const {  
        return (Element*) m_node;
    }

private:
    Node* m_node;
};
typedef _element_iterator<DOMNode, DOMElement>               element_iterator;
typedef _element_iterator<DOMNode const, DOMElement const> const_element_iterator;

////////////////////////////////////////////////////////////////////////////////////

template <class Node>
class _child_node_iterator : 
    public boost::iterator_facade< _child_node_iterator<Node>,
                                   Node,
                                   boost::bidirectional_traversal_tag>
{
public:
    _child_node_iterator() 
    : m_node(0), m_pos(0)
    {}

    explicit _child_node_iterator(Node* p)
    : m_node(p), m_pos(0)
    {}

private:
    friend class boost::iterator_core_access;

    void increment() { 
        m_pos++;
    }

    void decrement() { 
        m_pos--;
    }

    bool equal(_child_node_iterator const& other) const {
        return (this->m_node == other.m_node && this->m_pos == other.m_pos);
    }

    Node & dereference() const {   
        return *(m_node->getChildNodes()->item(pos));        
    }

private:
    int m_pos;
    Node * m_node;
};