#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include "../ValidationHandler.hpp"

namespace dsg {

    #define CX(str) encode<EncodingT,xml>(str).c_str()
    #define C(str)  encode<xml,EncodingT>(str).c_str()
    #define AX(str) encode<ansi,xml>(str).c_str()
    #define A(str)  encode<xml,ansi>(str).c_str()

    template <class EncodingT>
    DataModel<EncodingT>* DataModel<EncodingT>::m_instance = NULL;

    template <class EncodingT>
    DataModel<EncodingT>::DataModel()
    : m_xmlDoc(), 
      m_logger(&Category::getInstance(LOGNAME))
    {
        try
        {
            XMLPlatformUtils::Initialize();
            DOMImplementation * impl = DOMImplementationRegistry::getDOMImplementation( AX("LS") );
            DOMDocumentType * docType = impl->createDocumentType( AX("document_schema"), NULL, AX("document_schema.dtd"));  
            m_xmlDoc.reset(impl->createDocument( 0, AX("document_schema"), docType));
            m_logger->debug("DataModel() : DataModel initialized");
        } 
        catch ( const XMLException& e ) 
        {
            m_logger->fatalStream() << "DataModel() : XML toolkit initialization error: " 
                                    << A(e.getMessage());
            //throw;
        }
    }

    template <class EncodingT>
    DataModel<EncodingT>::~DataModel()
    {
        try
        {
            XMLPlatformUtils::Terminate();
            m_logger->debug("~DataModel() : DataModel destructed");
        }
        catch( const XMLException& e )
        {
            m_logger->fatalStream() << "~DataModel() : XML toolkit teardown error: " 
                                    << A(e.getMessage());
            //throw;
        }
    }

    template <class EncodingT>
    DataModel<EncodingT>* DataModel<EncodingT>::getInstance()
    {
        if (!m_instance)
        {
            m_instance = new DataModel();
        }
        return m_instance;
    }

    template <class EncodingT>
    DOMNode* DataModel<EncodingT>::saveXML() const
    {
        DOMNode* node = NULL;
        try 
        {
            // erase old nodes
            node = m_xmlDoc->getDocumentElement();
            while (node->hasChildNodes()) 
            {
                node->removeChild(node->getLastChild());
            }
            // add new node
            node->appendChild(m_workspace.saveXML(m_xmlDoc.get()));
            m_logger->debug("DataModel::saveXML() : XML Document saved");
        } 
        catch ( const DOMException& e ) 
        {
            m_logger->fatalStream() << "DataModel::saveXML() : XML Document save error: " 
                                    << A(e.getMessage());
            //throw e;
        }
        return m_xmlDoc.get();
    }

    template <class EncodingT>
    void DataModel<EncodingT>::loadXML(DOMElement* xml_doc)
    {
        DOMNodeList* xml_list     = NULL;
        DOMElement*  xml_wrkspc   = NULL;

        if (!xml_doc || string("document_schema") != A(xml_doc->getTagName()))
        {
            m_logger->fatalStream() << "DataModel::loadXML() : XML document element expected";
            //throw BadXmlFormatException("XML document element expected");
        }
        else 
        {
            if (xml_doc->hasChildNodes()) 
            {
                 xml_list =    xml_doc->getChildNodes();
                 for (unsigned int i=0; i<xml_list->getLength(); ++i)
                 {
                     xml_wrkspc = (DOMElement*) xml_list->item(i);
                     if (xml_wrkspc && string("Workspace") == A(xml_wrkspc->getTagName())) 
                     {
                         m_workspace.loadXML(xml_wrkspc);
                     }
                 }
            }
            m_logger->debug("DataModel::loadXML() : XML document loaded");
        }
    }

    template <class EncodingT>
    void DataModel<EncodingT>::save(const char* filename) const 
    {
        // DOMImplementationLS contains factory methods for creating objects
        // that implement the DOMBuilder and the DOMWriter interfaces
        DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation( AX("LS") );
        // construct the DOMLSSerializer
        DOMLSSerializer* serializer = ((DOMImplementationLS*)impl)->createLSSerializer();
        // Create a new empty output destination object.
        DOMLSOutput* output = ((DOMImplementationLS*)impl)->createLSOutput();
        // construct the LocalFileFormatTarget
        boost::scoped_ptr<XMLFormatTarget> formatTarget(new LocalFileFormatTarget(filename));

        m_logger->infoStream() << "DataModel::save() : start writing XML document : " << filename;

        // optionally, set some DOMWriter features
        // set the format-pretty-print feature
        if (serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
            serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

        // set the byte-order-mark feature
        if (serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTBOM, true))
            serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTBOM, true);

        // The end-of-line sequence of characters to be used in the XML being written out.
        serializer->setNewLine( AX("\r\n") );

        // Set the stream to our target.
        output->setByteStream(formatTarget.get());

        // Write the serialized output to the destination.
        serializer->write(saveXML(), output);

        // optionally, you can flush the buffer to ensure all contents are written
        formatTarget->flush();

        // Cleanup
        serializer->release();
        output->release();

        m_logger->infoStream() << "DataModel::save() : XML document written : " << filename;
    }

    template <class EncodingT>
    void DataModel<EncodingT>::load(const char* filename)
    {
        boost::scoped_ptr<XercesDOMParser> fileParser(new XercesDOMParser());
        ValidationHandler valHandler;

        m_logger->infoStream() << "DataModel::load() : start parsing XML document : " << filename;
        fileParser->setErrorHandler(&valHandler);
        fileParser->setValidationScheme(XercesDOMParser::Val_Auto);
        fileParser->setLoadExternalDTD(true);
        fileParser->setExitOnFirstFatalError(true);
        fileParser->setValidationConstraintFatal(true);

        fileParser->parse(filename);

        if (valHandler.IsValid()) 
        {
            m_xmlDoc.reset((DOMDocument*) fileParser->getDocument()->cloneNode(true));
        }
        m_logger->infoStream() << "DataModel::load() : XML document parsed : " << filename;
        loadXML(m_xmlDoc->getDocumentElement());
    }

    #undef CX
    #undef AX
    #undef C
    #undef A

}
