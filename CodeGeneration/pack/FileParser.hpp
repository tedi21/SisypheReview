#ifndef _FILE_PARSER_HPP_
#define _FILE_PARSER_HPP_

#include "Parser.hpp"
#include "Locale.hpp"
#include "FactoryTypes.hpp"

namespace dsg {

    template <class DerivedT>
    class FileParser
    : public Parser {
    protected:
        Category*       m_logger;
        string          m_filename;
        file_encoding_t m_encoding;

    public:
        // constructor
        FileParser(const string& filename, file_encoding_t encoding)
        : m_filename(filename), m_encoding(encoding)
        {
            m_logger = &Category::getInstance(LOGNAME);
        }

        // parsing method
        int parse();

        // factory methods
        static void register_class()
        {
            ParserManager* manager = ParserManager::getInstance();
            manager->registerClass( new fctr::Factory2<
                                            Parser,                                             // Base
                                            FileParser<DerivedT>,                               // Class
                                            fctr::Prototype2< fctr::In<string>, fctr::In<file_encoding_t> > >     // Parameters
                                        (DerivedT::Family_Name) );                              // Name
        }

        static void unregister_class()
        {
            ParserManager* manager = ParserManager::getInstance();
            manager->unRegisterClass(DerivedT::Family_Name);
        }
    };

}

#include "impl/FileParser_impl.hpp"

#endif // _FILE_PARSER_HPP_
