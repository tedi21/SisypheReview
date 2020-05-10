#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>

#include "config.hpp"
#include "dataconnection.hpp"
#include "ProgramInterpreter.hpp"
#include "CPPParserInterpreter.hpp"

#include <emscripten/bind.h>


using namespace std;
using namespace interp;
using namespace log4cpp;
using namespace boost;
using namespace enc;
using namespace fctr;

//////////////////////////////////////////
// Exportation des classes plugin
//////////////////////////////////////////

FACTORY_EXPORT(CPPParserInterpreter<ucs>)

//////////////////////////////////////////
// Fonction d'initialisation du log
//////////////////////////////////////////

Category* initialize_log(const char* name, int verbose)
{
    // 1 instantiate an appender object that 
    // will append to a log file
    Appender* app = new OstreamAppender(name, &std::cout);

    // 2. Instantiate a layout object
    // Two layouts come already available in log4cpp
    // unless you create your own.
    // BasicLayout includes a time stamp
    Layout* layout = new BasicLayout();

    // 3. attach the layout object to the 
    // appender object
    app->setLayout(layout);

    // 4. Instantiate the category object
    // you may extract the root category, but it is
    // usually more practical to directly instance
    // a child category
    Category* main_cat = &Category::getInstance(name);

    // 5. Step 1 
    // an Appender when added to a category becomes
    // an additional output destination unless 
    // Additivity is set to false when it is false,
    // the appender added to the category replaces
    // all previously existing appenders
    main_cat->setAdditivity(false);

    // 5. Step 2
    // this appender becomes the only one
    main_cat->setAppender(app);

    // 6. Set up the priority for the category
    // and is given INFO priority
    // attempts to log DEBUG messages will fail
    main_cat->setPriority( verbose*100 );

    return main_cat;
}

std::wstring tdscript(const std::wstring& text)
{ 
    std::wstring result;  
    Category* logger = Category::exists(LOGNAME);
    if (logger == nullptr)
    {
        logger = initialize_log(LOGNAME, 6);
    }

    const data_access::UniDataConnection* const db = data_access::UniDataConnection::getInstance(encode<ansi,ucs>("/cppbase.db"));
    if (db == nullptr)
    {
        logger->debugStream() << "try to open DB connection " << "cppbase.db";
        if (!data_access::UniDataConnection::openConnection(UCS(""), 0, encode<ansi,ucs>("/cppbase.db"), UCS(""), UCS("")))
        {
            logger->errorStream() << "cannot open DB connection " << "cppbase.db" << ".";
        }
    }

    logger->infoStream() << "Script parsing started";
    ucs::string_t buf;
    boost::shared_ptr< Term<ucs> > a;
    if (readFile("/Main.td", buf) &&
        Program<ucs>::parse(buf, a))
    {
        logger->infoStream() << "Script parsed";
        Context<ucs> c;
        c.add(L"TEXT", boost::shared_ptr<Base<ucs>>(new String<ucs>(text)));
        a->interpret(c);
        for (Context<ucs>::iterator_t i = c.begin(); i != c.end(); ++i)
        {
            logger->debugStream() << "[" << encode<ucs,ansi>(c.getIdentifier(i)) << "] = " 
            << encode<ucs,ansi>(c.getObject(i)->toString());
        }
        result = c.getObject(L"RESULT")->toString();
        logger->noticeStream() << "script OK\n";
    }  
    else
    {
        logger->noticeStream() << "script NOK\n";
    }
    return result;
}


EMSCRIPTEN_BINDINGS(module) {
  emscripten::function("tdscript", &tdscript);
}
