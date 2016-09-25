#include <boost/filesystem.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>

#include "config.hpp"
#include "ProgramInterpreter.hpp"
#include "dataconnection.hpp"

#include "CPlug.h"

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
  cout << "\t" << files::path(exe).filename().string() << " <file> -v <log level> [-module <moduleName> <moduleParameters>]" << endl << endl;
  cout << "\t<file>       : UTF-16LE input file" << endl;
  cout << "\t<log level>  : log level" << endl;
  cout << "\t<moduleName> : module name" << endl;
  cout << "\t<moduleParameters> : module parameters" << endl << endl;
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

bool end_with(const std::string& file, const std::string& extension)
{
    return file.size() > extension.size() &&
           (file.substr(file.size() - extension.size())) == extension;
}

bool find_file( const files::path& dir_path,        // in this directory,
                const std::string& ext_name,        // search for this name,
                vector<files::path>& path_found )   // placing path here if found
{
  if ( !exists( dir_path ) ) return false;
  files::directory_iterator end_itr; // default construction yields past-the-end
  for ( files::directory_iterator itr( dir_path );
        itr != end_itr;
        ++itr )
  {
    /*if ( files::is_directory(itr->status()) )
    {
        find_file( itr->path(), ext_name, path_found );
    }
    else */if ( end_with(itr->path().leaf().string(), ext_name) )
    {
        path_found.push_back(itr->path());
    }
  }
  if (path_found.empty()) return false;
  return true;
}

int main(int argc, char *argv[])
{
    string filename;
    map< string, vector<string> > modulesArgs;
    int log = 7;
    if ( argc>=4 )
    {
        int i = 1;
        while (i < argc)
        {
            if (0 == strcmp("-module", argv[i]))
            {
                string moduleName = argv[++i];
                vector<string> moduleParameters;
                while (i+1 < argc && argv[i+1][0] != '-')
                {
                    moduleParameters.push_back(argv[++i]);
                }
                modulesArgs.insert(make_pair(moduleName, moduleParameters));
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
        //::system("PAUSE");
        exit(-1);
    }
    
    initialize_log(LOGNAME, log);

    Category * logger = &Category::getInstance(LOGNAME);

    logger->debugStream() << "search modules ";
    files::path my_path = files::system_complete( files::path( argv[0] ) ).parent_path();
    vector<files::path> modules;
    vector<files::path>::iterator i;
    boost::ptr_vector<CPlug<char> > dllplugged;
    std::auto_ptr<CPlug<char> > dll;
    logger->debugStream() << "search in " << my_path.string();
    find_file(my_path, "Plg.dll", modules );
    for (i = modules.begin(); i < modules.end(); ++i)
    {
        dll.reset(new CPlug<char>);
        logger->debugStream() << "try to load " << i->filename().string();
        if(dll->LoadPlugin(i->c_str()))
        {
            string moduleName = i->filename().string().substr(0, i->filename().string().size()-7);
            logger->debugStream() << moduleName << " loaded";
            vector<string> args;
            map< string, vector<string> >::const_iterator i = modulesArgs.find(moduleName);
            if (i != modulesArgs.end())
            {
                args = i->second;
            }
            const char* plugName = dll->GetPlugIn(1, (const std::vector<string>*) &args);
            dllplugged.push_back(dll);
            initialize_log(plugName, log);
        }
    }

    logger->infoStream() << "Script parsing started";
    ucs::string_t buf;
    boost::shared_ptr< Term<ucs> > a;
    if (readFile(filename, buf) &&
        Program<ucs>::parse(buf, a))
    {
        logger->infoStream() << "Script parsed";
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

    logger->debugStream() << "unplug modules";
    ptr_vector<CPlug<void> >::iterator j;
    for (j = dllplugged.begin(); j < dllplugged.end(); ++j)
    {
        j->ReleasePlugIn();
    }
    dllplugged.clear();

    //::system("PAUSE");
    return EXIT_SUCCESS;
}
