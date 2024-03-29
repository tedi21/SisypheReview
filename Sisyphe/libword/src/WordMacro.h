#ifndef _WORD_MACRO_H_
#define _WORD_MACRO_H_

#include "LibWordExport.h"
#include "Word.h"
#include "config.hpp"
#include "encoding.hpp"

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
        bool convertTo(word::WdSaveFormat format, const enc::ucs::string_t& file, const enc::ucs::string_t& xmlFile, bool acceptAllRevisions = false) const;
		
    public:
        WordMacro();

        ~WordMacro();

        // Convertit un fichier en xml
        bool convertToXML(const enc::ucs::string_t& file, const enc::ucs::string_t& xmlFile, bool acceptAllRevisions = false) const;

        // Convertit un fichier en doc
        bool convertToDOC(const enc::ucs::string_t& file, const enc::ucs::string_t& docFile, bool acceptAllRevisions = false) const;

        // Convertit un fichier en pdf
        bool convertToPDF(const enc::ucs::string_t& file, const enc::ucs::string_t& pdfFile, bool acceptAllRevisions = false) const;
		
        // Convertit un fichier en xdoc
        bool convertToXDOC(const enc::ucs::string_t& file, const enc::ucs::string_t& xdocFile, bool acceptAllRevisions = false) const;
    };

NAMESPACE_END

#endif // _WORD_MACRO_H_
