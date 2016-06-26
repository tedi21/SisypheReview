#ifndef _FILE_CFG_PARSER_HPP_
#define _FILE_CFG_PARSER_HPP_

#include "Parser.hpp"
#include "Locale.hpp"
#include "Logger.hpp"
#include <string>

namespace cfg
{

    class FileCFGParser
    : public dsg::Parser {
    protected:
        log4cpp::Category*   m_logger;
        std::string          m_filename;
        dsg::file_encoding_t m_encoding;

        static const char* PLUG_IN_NAME;

    public:
        // constructor
        FileCFGParser(const std::string& filename, dsg::file_encoding_t encoding);

        // parsing method
        int parse();

        // factory methods
        static void register_class();
        static void unregister_class();
    };

}

#endif // _FILE_CFG_PARSER_HPP_
