#include "WordXMLDocument.h"
#include "WordXMLNode.h"
#include "xstring.hpp"
#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>
#include <LocalMsgIndex.hpp>

NAMESPACE_BEGIN(libword)

    using namespace enc;

    WordXMLDocument::WordXMLDocument()
    : m_parser(NULL),
      m_liaison(NULL),
      m_evaluator(NULL),
      m_domsupport(NULL),
      m_xmldocument(NULL),
      m_xlstdocument(NULL),
      m_wrapper(NULL)
    {
        m_logger = &log4cpp::Category::getInstance(LOGNAME);
        m_parser = new xercesc::XercesDOMParser();
        m_liaison = new xalanc::XercesParserLiaison();
        m_evaluator = new xalanc::XPathEvaluator();
        m_domsupport = new xalanc::XercesDOMSupport(*m_liaison);
    }

    WordXMLDocument::~WordXMLDocument()
    {
        delete m_parser;
        delete m_liaison;
        delete m_evaluator;
        delete m_domsupport;
    }

    // Ouvre un fichier Word XML
    void WordXMLDocument::parse(const ucs::string_t& doc)
    {
        m_documentName = doc;
        // Create XML DOM document
        if (m_parser)
        {
            m_parser->setDoNamespaces(true);
            m_parser->parse(encode<ucs,xml>(m_documentName).c_str());

            m_xmldocument = m_parser->getDocument();
            if (m_xmldocument)
            {
                m_xmldocument->normalize();
                // Create Xalan document
                m_xlstdocument = m_liaison->createDocument(m_xmldocument, false, false);
                m_wrapper = m_liaison->mapDocumentToWrapper(m_xlstdocument);
            }
            else
            {
                m_logger->errorStream() << "Unable to parse xml because the xml document " << encode<ucs,ansi>(doc) << " is invalid.";
            }
        }
        else
        {
             m_logger->errorStream() << "Unable to parse xml because parser isn't initialized.";
        }
    }

    // Retourne le noeud racine du document
    WordXMLNode WordXMLDocument::getDocumentNode()
    {
        WordXMLNode node;
        if (m_xmldocument)
        {
            node = WordXMLNode(this, m_xmldocument->getDocumentElement());
        }
        else
        {
            m_logger->errorStream() << "Unable to get node because the xml document is invalid.";
        }
        return node;
    }

    // Crée un nouveau noeud
    WordXMLNode WordXMLDocument::createNode(const ucs::char_t* tagName)
    {
        WordXMLNode node;
        if (m_xmldocument)
        {
            node = WordXMLNode(this, m_xmldocument->createElement(encode<ucs,xml>(tagName).c_str()));
        }
        else
        {
            m_logger->errorStream() << "Unable to create node because the xml document is invalid.";
        }
        return node;
    }

    // Create text node
    WordXMLNode WordXMLDocument::createTextNode(const ucs::char_t* str)
    {
        WordXMLNode text;
        if (m_xmldocument)
        {
            text = createNode(UCS("w:t"));
            text.setContent(str);
        }
        else
        {
            m_logger->errorStream() << "Unable to create text node because the xml document is invalid.";
        }
        return text;
    }

    // Enregistre le document
    void WordXMLDocument::save() const
    {
        if (m_xmldocument)
        {
            //Return the first registered implementation that has the desired features. In this case, we are after a DOM implementation that has the LS feature... or Load/Save.
            xercesc::DOMImplementation *implementation = xercesc::DOMImplementationRegistry::getDOMImplementation(XML("LS"));

            // Create a DOMLSSerializer which is used to serialize a DOM tree into an XML document.
            xercesc::DOMLSSerializer *serializer = ((xercesc::DOMImplementationLS*)implementation)->createLSSerializer();

            // Specify the target for the XML output.
            xercesc::LocalFileFormatTarget *formatTarget = new xercesc::LocalFileFormatTarget(encode<ucs,xml>(m_documentName).c_str());

            // Create a new empty output destination object.
            xercesc::DOMLSOutput *output = ((xercesc::DOMImplementationLS*)implementation)->createLSOutput();

            // Set the stream to our target.
            output->setByteStream(formatTarget);

            // Write the serialized output to the destination.
            serializer->write(m_xmldocument, output);

            // optionally, you can flush the buffer to ensure all contents are written
            formatTarget->flush();

            // Cleanup.
            serializer->release();
            delete formatTarget;
            output->release();
        }
        else
        {
            m_logger->errorStream() << "Unable to write invalid xml document.";
        }
    }

    // Initialise le parser XML
    void WordXMLDocument::initialize()
    {
        xercesc::XMLPlatformUtils::Initialize();
        xalanc::XalanTransformer::initialize();
        log4cpp::Category* logger = &log4cpp::Category::getInstance(LOGNAME);
        logger->debugStream() << "XML initialization.";
    }

    // Libère le parser XML
    void WordXMLDocument::terminate()
    {
        xalanc::XalanTransformer::terminate();
        xercesc::XMLPlatformUtils::Terminate();
        log4cpp::Category* logger = &log4cpp::Category::getInstance(LOGNAME);
        logger->debugStream() << "XML termination.";
    }

NAMESPACE_END
