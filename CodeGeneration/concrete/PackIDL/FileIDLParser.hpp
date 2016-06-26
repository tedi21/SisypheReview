#ifndef _FILE_IDL_PARSER_HPP_
#define _FILE_IDL_PARSER_HPP_

#include "Parser.hpp"
#include "Locale.hpp"
#include "Logger.hpp"
#include <string>

namespace sidl
{

    class FileIDLParser
    : public dsg::Parser {
    protected:
        log4cpp::Category*   m_logger;
        std::string          m_filename;
        dsg::file_encoding_t m_encoding;

        static const char* PLUG_IN_NAME;

    public:
        // constructor
        FileIDLParser(const std::string& filename, dsg::file_encoding_t encoding);

        // parsing method
        int parse();

        // factory methods
        static void register_class();
        static void unregister_class();
    };

}

#endif // _FILE_IDL_PARSER_HPP_