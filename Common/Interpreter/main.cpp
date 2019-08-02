#include <boost/filesystem.hpp>

#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>

#include "config.hpp"
#include "ProgramInterpreter.hpp"
#include "dataconnection.hpp"

using namespace std;
using namespace interp;
using namespace log4cpp;
using namespace boost;
using namespace enc;
using namespace fctr;
namespace files = boost::filesystem;

//////////////////////////////////////////
// Fonction d'utilisation
//////////////////////////////////////////

void usage(const char* exe)
{
  cout << "usage :" << endl;
  cout << "\t" << files::path(exe).filename().string() << " <file> -base <base> -v <log>" << endl << endl;
  cout << "\t<file>       : UTF-16LE input file" << endl;
  cout << "\t<log>        : log level" << endl;
  cout << "\t<base>       : database name" << endl << endl;
}

//////////////////////////////////////////
// Fonction d'initialisation du log
//////////////////////////////////////////

void initialize_log(const char* name, int verbose, string const& file_log = "")
{
    // 1 instantiate an appender object that 
    // will append to a log file
    Appender* app;
    if (file_log.empty())
        app = new OstreamAppender(name, &std::cout);
    else 
        app = new FileAppender(name, file_log);

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
    Category * main_cat = &Category::getInstance(name);

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
}

int main(int argc, char *argv[])
{
    string filename;
    string base;
    int log = 7;
    if ( argc==6 )
    {
        int i = 1;
        while (i < 6)
        {
            if (0 == strcmp("-base", argv[i]))
            {
                base = argv[++i];
            }
            else if (0 == strcmp("-v", argv[i]))
            {
                log = atoi(argv[++i]);
            }
            else
            {
                filename = argv[i];
            }
            ++i;
        }
    }
    else
    {
        usage(argv[0]);
        ::system("PAUSE");
        exit(-1);
    }
    
    initialize_log(LOGNAME, log);

    Category * logger = &Category::getInstance(LOGNAME);

    //if (!data_access::UniDataConnection::openConnection(L"localhost", 3306, L"base", L"teddy", L"teddy"))
    if (!data_access::UniDataConnection::openConnection(UCS(""), 0, encode<ansi,ucs>(base), UCS(""), UCS(""))) 
    {
        cout << "cannot open DB connection." << endl;
        ::system("PAUSE");
        exit(-1);
    }
    
    ucs::string_t buf;
    shared_ptr< Term<ucs> > a;
    if (readFile(filename, buf) &&
        Program<ucs>::parse(buf, a))
    {
        Context<ucs> c;
        a->interpret(c);
        for (Context<ucs>::iterator_t i = c.begin(); i != c.end(); ++i)
        {
            logger->debugStream() << "[" << encode<ucs,ansi>(c.getIdentifier(i)) << "] = " 
            << encode<ucs,ansi>(c.getObject(i)->toString());
        }
        logger->noticeStream() << "script OK\n";
    }  
    else
    {
        logger->noticeStream() << "script NOK\n";
    }

    ::system("PAUSE");
    return EXIT_SUCCESS;
}
