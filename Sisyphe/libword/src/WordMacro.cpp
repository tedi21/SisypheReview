#include "WordMacro.h"
#include "encoding.hpp"

NAMESPACE_BEGIN(libword)

    using namespace enc;

    MacroOptimizer::MacroOptimizer(word::Document* doc)
    : m_doc(doc)
    {
        word::Application* application = word::Word::getApplication();
        if (application)
        {
            m_screenUpdating = application->getScreenUpdating();
            application->setScreenUpdating(false);
            if (m_doc)
            {
                m_viewType = m_doc->getActiveWindow().getView().getType();
                doc->getActiveWindow().getView().setType(1);

                m_pagination = application->getOptions().getPagination();
                application->getOptions().setPagination(false);
            }
        }
    }

    MacroOptimizer::~MacroOptimizer()
    {
        word::Application* application = word::Word::getApplication();
        if (application)
        {
            application->setScreenUpdating(m_screenUpdating);
            if (m_doc)
            {
                // Restore options
                application->getOptions().setPagination(m_pagination);
                m_doc->getActiveWindow().getView().setType(m_viewType);
            }
        }
    }

    WordMacro::WordMacro()
    {
        m_logger = &log4cpp::Category::getInstance(LOGNAME);
        // Création de l'instance de Word
        if (word::Word::Initialize())
        {
            word::Application* app = word::Word::getApplication();
            app->setVisible(false);
        }
        else
        {
            m_logger->debugStream() << "Unable to initialize WORD application.";
        }
    }

    WordMacro::~WordMacro()
    {
        // Fermeture de l'instance de Word
        word::Application* app = word::Word::getApplication();
        if (NULL != app)
        {
            app->Quit();
        }
        if (!word::Word::UnInitialize())
        {
           m_logger->debugStream() << "Unable to uninitialize WORD application.";
        }
    }
	
    // Convertit un fichier
    bool WordMacro::convertTo(word::WdSaveFormat format, const std::wstring& file, const std::wstring& xmlFile, bool acceptAllRevisions) const
    {
        bool res = false;
        word::Document doc;
        word::Application* app = word::Word::getApplication();
        if (app)
        {
            doc = app->getDocuments().Open(file, false, true, false);
        }
        else
        {
            m_logger->errorStream() << "Unable to open file " << encode<ucs,ansi>(file) << ".";
        }
        {
            MacroOptimizer optimizer(&doc);
            if (acceptAllRevisions)
            {
                // Accepter les révisions
                doc.AcceptAllRevisions();
            }
            // Convertir le document
            doc.SaveAs(xmlFile, format);
            doc.Close(word::wdDoNotSaveChanges, word::wdOriginalDocumentFormat, false);
            res = true;
        }
        return res;
    }

    // Convertit un fichier en xml
    bool WordMacro::convertToXML(const std::wstring& file, const std::wstring& xmlFile, bool acceptAllRevisions) const
    {
        return convertTo(word::wdFormatXML, file, xmlFile, acceptAllRevisions);
    }

    // Convertit un fichier en doc
    bool WordMacro::convertToDOC(const std::wstring& file, const std::wstring& docFile, bool acceptAllRevisions) const
    {
        return convertTo(word::wdFormatDocument, file, docFile, acceptAllRevisions);
    }
	
	// Convertit un fichier en pdf
	bool WordMacro::convertToPDF(const std::wstring& file, const std::wstring& pdfFile, bool acceptAllRevisions) const
    {
        return convertTo(word::wdFormatPDF, file, pdfFile, acceptAllRevisions);
    }
	
	// Convertit un fichier en xdoc
	bool WordMacro::convertToXDOC(const std::wstring& file, const std::wstring& xdocFile, bool acceptAllRevisions) const
    {
        return convertTo(word::wdFormatXMLDocument, file, xdocFile, acceptAllRevisions);
    }

NAMESPACE_END
