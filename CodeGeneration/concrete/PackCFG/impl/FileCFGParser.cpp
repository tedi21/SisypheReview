#include "FileCFGParser.hpp"
#include "SimpleCFGGrammar.hpp"
#include "SimpleCFGHandler.hpp"
#include "FactoryTypes.hpp"

using namespace std;
using namespace log4cpp;
using namespace dsg;
using namespace fctr;

namespace cfg
{
    const char* FileCFGParser::PLUG_IN_NAME = "cfg";

    FileCFGParser::FileCFGParser(const string& filename, file_encoding_t encoding)
    : m_filename(filename), m_encoding(encoding)
    {
        m_logger = &Category::getInstance(LOGNAME);
    }

    int FileCFGParser::parse()
    {
        int ret = 0;
        std::wstring in;

        if (read_file(m_filename.c_str(), m_encoding, in))
        {
            // parse data
            typedef cfg::simple_cfg_grammar<std::wstring::const_iterator> simple_cfg_grammar;
            simple_cfg_grammar grammar; // Our grammar
            cfg::config_file file;        // Our file

            using boost::spirit::standard_wide::space;
            std::wstring::const_iterator iter = in.begin();
            std::wstring::const_iterator end = in.end();
            bool r = phrase_parse(iter, end, grammar, space, file);

            if (r && iter == end)
            {
                cfg::simple_cfg_handler handler;
                handler.setData(file);
                m_logger->noticeStream() << "Parsing succeeded";
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

    void FileCFGParser::register_class()
    {
        ParserManager* manager = ParserManager::getInstance();
        manager->registerClass( new Factory2<
                                        Parser,                                             // Base
                                        FileCFGParser,                                      // Class
                                        Prototype2< In<string>, In<file_encoding_t> > >     // Parameters
                                    (PLUG_IN_NAME) );                                       // Name
    }

    void FileCFGParser::unregister_class()
    {
        ParserManager* manager = ParserManager::getInstance();
        manager->unRegisterClass(PLUG_IN_NAME);
    }
}
