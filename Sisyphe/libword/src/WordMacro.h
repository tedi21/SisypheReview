#ifndef _WORD_MACRO_H_
#define _WORD_MACRO_H_

#include "LibWordExport.h"
#include "Word.h"
#include "config.hpp"

NAMESPACE_BEGIN(libword)

    // Classe initialisant des paramètres permettant
    // l'execution d'actions du logiciel Word plus rapidement
    class MacroOptimizer
    {
    private:
        word::Document* m_doc;
        int  m_viewType;
        bool m_screenUpdating;
        bool m_pagination;
    public:
        MacroOptimizer(word::Document* doc);
        ~MacroOptimizer();
    };

    class LIBWORD_API WordMacro
    {
    private:
        log4cpp::Category* m_logger;

        // Convertit un fichier
        bool convertTo(word::WdSaveFormat format, const std::wstring& file, const std::wstring& xmlFile, bool acceptAllRevisions = false) const;
		
    public:
        WordMacro();

        ~WordMacro();

        // Convertit un fichier en xml
        bool convertToXML(const std::wstring& file, const std::wstring& xmlFile, bool acceptAllRevisions = false) const;

        // Convertit un fichier en doc
        bool convertToDOC(const std::wstring& file, const std::wstring& docFile, bool acceptAllRevisions = false) const;

        // Convertit un fichier en pdf
        bool convertToPDF(const std::wstring& file, const std::wstring& pdfFile, bool acceptAllRevisions = false) const;
		
        // Convertit un fichier en xdoc
        bool convertToXDOC(const std::wstring& file, const std::wstring& xdocFile, bool acceptAllRevisions = false) const;
    };

NAMESPACE_END

#endif // _WORD_MACRO_H_
