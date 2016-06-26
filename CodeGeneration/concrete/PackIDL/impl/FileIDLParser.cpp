#include "FileIDLParser.hpp"
#include "SimpleIDLGrammar.hpp"
#include "SimpleIDLHandler.hpp"
#include "FactoryTypes.hpp"

using namespace std;
using namespace log4cpp;
using namespace dsg;
using namespace fctr;

namespace sidl
{
    const char* FileIDLParser::PLUG_IN_NAME = "sidl";

    FileIDLParser::FileIDLParser(const string& filename, file_encoding_t encoding)
    : m_filename(filename), m_encoding(encoding)
    {
        m_logger = &Category::getInstance(LOGNAME);
    }

    int FileIDLParser::parse()
    {
        int ret = 0;
        std::wstring in;

        if (read_file(m_filename.c_str(), m_encoding, in))
        {
            // parse data
            typedef sidl::simple_idl_grammar<std::wstring::const_iterator> simple_idl_grammar;
            simple_idl_grammar grammar; // Our grammar
            sidl::idl_file file;        // Our file

            using boost::spirit::standard_wide::space;
            std::wstring::const_iterator iter = in.begin();
            std::wstring::const_iterator end = in.end();
            bool r = phrase_parse(iter, end, grammar, space, file);

            if (r && iter == end)
            {
                m_logger->noticeStream() << "Parsing succeeded";
                sidl::file_handler handler;
                handler(file);
            }
            else
            {
                std::wstring::const_iterator some = iter+30;
                std::wstring context(iter, (some>end)?end:some);
                m_logger->noticeStream() << "Parsing failed";
                m_logger->noticeStream() << "stopped at: \""
                                         << encode<ucs,ansi>(context) << "\"";
                ret = -2;
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to read the file :" << m_filename;
            ret = -1;
        }
        return ret;
    }

    void FileIDLParser::register_class()
    {
        ParserManager* manager = ParserManager::getInstance();
        manager->registerClass( new Factory2<
                                        Parser,                                             // Base
                                        FileIDLParser,                                      // Class
                                        Prototype2< In<string>, In<file_encoding_t> > >     // Parameters
                                    (PLUG_IN_NAME) );                                       // Name
    }

    void FileIDLParser::unregister_class()
    {
        ParserManager* manager = ParserManager::getInstance();
        manager->unRegisterClass(PLUG_IN_NAME);
    }
}