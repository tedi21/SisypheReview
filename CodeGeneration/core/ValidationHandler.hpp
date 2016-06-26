#ifndef _VALIDATION_HANDLER_HPP_
#define _VALIDATION_HANDLER_HPP_

#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include "xstring.hpp"

using namespace log4cpp;
using namespace xercesc;
using namespace enc;

namespace dsg {

    #define X(str) encode<ansi,xml>(str).c_str()
    #define C(str) encode<xml,ansi>(str).c_str()

    class ValidationHandler 
    : public ErrorHandler
    {
    private:
        bool mIsValid;
        Category* m_logger;

    public:
        ValidationHandler()
        {
            m_logger = &Category::getInstance(LOGNAME);
            mIsValid = true;
        }

        virtual ~ValidationHandler()
        {}

        virtual void warning (const SAXParseException &e)
        {
            m_logger->warnStream() << "XML DTD warning (" 
                                   << e.getLineNumber() << ") : " 
                                   << C(e.getMessage());
        }

        virtual void error (const SAXParseException &e)
        {
            mIsValid = false;
            m_logger->errorStream() << "XML DTD error (" 
                                    << e.getLineNumber() << ") : " 
                                    << C(e.getMessage());
        }
        virtual void fatalError (const SAXParseException &e)
        {
            mIsValid = false;
            m_logger->fatalStream() << "XML DTD fatal error (" 
                                    << e.getLineNumber() << ") : " 
                                    << C(e.getMessage());
        }

        virtual void resetErrors ()
        {
            mIsValid = true;
        }

        bool IsValid()
        {
            return mIsValid;
        }
    };

    #undef X
    #undef C

}

#endif // _VALIDATION_HANDLER_HPP_
