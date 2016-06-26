/**                                                                                     **
  * Creates Data Sources from sql scripts or another languages                          *
  *                                                                                     *
  * DataBase Interface required for Data Access layer                                   *    
  * implementation by user program                                                      *    
  *                                                                                     *    
  * usage :                                                                             *    
  *    genSources [<files>] -to <output> [-UTF8 -group -log <file> -v <priority> -dir <folder>]
  *                                                                                     *
  *    <files>         : input file                                                     *
  *    -to <output>    : output format                                                  *
  *    -group          : one file by layer                                              *
  *    -log <file>     : log file (stdout by default)                                   *
  *    -UTF8           : UTF-8 encoding (latin-1 encoding by default)                   *
  *    -UTF16BE        : UTF-16 big endian encoding                                     *
  *    -UTF16LE        : UTF-16 little endian encoding                                  *
  *    -v <priority>   : verbose mode according to priority number (3 by default)       *
  *    -import <file>  : import xml data file                                           *
  *    -export <file>  : export xml data file                                           *
  *    -dir <folder>   : destination folder                                             *
  *                                                                                     *    
  * example :                                                                           *    
  *    genSources *.sql -to cpp                                                         *
  **                                                                                    **/

#include <vector>
#include <string>
#include <iostream>
#include "Convert.hpp"
#include "Logger.hpp"
#include "Locale.hpp"
#include "FactoryTypes.hpp"
#include "CoreTypes.hpp"
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <boost/filesystem.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "CPlug.h"


using namespace log4cpp;
using namespace boost;
using namespace dsg;
using namespace fctr;
using namespace std;
namespace files = boost::filesystem;

void usage() {
  cout << "usage :" << endl;
  cout << "\tgenSources <files> [-to <output> -UTF* -group <file> -log <file> -v <priority> -import <file> -export <file> -dir <folder>]" << endl << endl;
  cout << "\t<files>       : input file" << endl;
  cout << "\t-to <output>  : output format" << endl;
  cout << "\t-import <file>: import xml data file" << endl;
  cout << "\t-export <file>: export xml data file" << endl;
  cout << "\t-UTF8         : UTF-8 encoding (ansi encoding by default)" << endl;
  cout << "\t-UTF16BE      : UTF-16 big endian encoding" << endl;
  cout << "\t-UTF16LE      : UTF-16 little endian encoding" << endl;
  cout << "\t-group        : one file by layer" << endl;
  cout << "\t-log <file>   : log file (stdout by default)" << endl;
  cout << "\t-v <priority> : verbose mode according to priority number (3 by default)" << endl;
  cout << "\t-dir <folder> : destination folder (execution folder by default)" << endl << endl;

  cout << "\t======================" << endl;
  cout << "\t| priority ! verbose |" << endl;
  cout << "\t======================" << endl;
  cout << "\t|     0    !  FATAL  |" << endl;
  cout << "\t----------------------" << endl;
  cout << "\t|     1    !  ALERT  |" << endl;
  cout << "\t----------------------" << endl;
  cout << "\t|     2    !  CRIT   |" << endl;
  cout << "\t----------------------" << endl;
  cout << "\t|     3    !  ERROR  |" << endl;
  cout << "\t----------------------" << endl;
  cout << "\t|     4    !  WARN   |" << endl;
  cout << "\t----------------------" << endl;
  cout << "\t|     5    !  NOTICE |" << endl;
  cout << "\t----------------------" << endl;
  cout << "\t|     6    !  INFO   |" << endl;
  cout << "\t----------------------" << endl;
  cout << "\t|     7    !  DEBUG  |" << endl;
  cout << "\t======================" << endl << endl;
}

void initialize_log(int verbose, string const& file_log = "") {
    // 1 instantiate an appender object that
    // will append to a log file
    Appender* app;
    if (file_log.empty())
        app = new OstreamAppender(LOGNAME, &std::cout);
    else
        app = new FileAppender(LOGNAME, file_log);

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
    Category * main_cat = &Category::getInstance(LOGNAME);

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

string extension(const string & file) {
    string ext;
    size_t pos = file.find_last_of('.');
    if (pos != string::npos) {
        ext = file.substr(pos+1);
    }
    return ext;
}

bool find_file( const files::path & dir_path,        // in this directory,
                const std::string & ext_name,        // search for this name,
                vector<files::path> & path_found )   // placing path here if found
{
  if ( !exists( dir_path ) ) return false;
  files::directory_iterator end_itr; // default construction yields past-the-end
  for ( files::directory_iterator itr( dir_path );
        itr != end_itr;
        ++itr )
  {
    if ( files::is_directory(itr->status()) )
    {
        find_file( itr->path(), ext_name, path_found );
    }
    else if ( extension(itr->path().leaf()) == ext_name ) // see below
    {
        path_found.push_back(itr->path());
    }
  }
  if (path_found.empty()) return false;
  return true;
}

int main(int argc, char *argv[]) {
    bool group    = false;
    int  verbose  = 3;
    file_encoding_t encoding = FILE_ANSI;
    string file_log, import_file, export_file;
    string out_format;
    files::path out_folder;
    vector<string> files;

    // test arguments
    unsigned char control = 0;
    int iarg              = 1;
    bool arg_error        = false;
    static const char * param_to      = "-to";
    static const char * param_utf8    = "-UTF8";
    static const char * param_utf16LE = "-UTF16LE";
    static const char * param_utf16BE = "-UTF16BE";
    static const char * param_group   = "-group";
    static const char * param_log     = "-log";
    static const char * param_verb    = "-v";
    static const char * param_import  = "-import";
    static const char * param_export  = "-export";
    static const char * param_iso885915 = "-ISO_885915";
    static const char * param_dir     = "-dir";

    while ( iarg<argc && !arg_error ) {
        if (strcmp(param_to,argv[iarg]) == 0) {
            // -to
            if ((control & 0x2) || (++iarg==argc)) {
                arg_error = true;
                break;
            }
            control |= 0x2;
            out_format = argv[iarg];
        }
        else if (strcmp(param_group,argv[iarg]) == 0) {
            // -group
            if ((control & 0x4)) {
                arg_error = true;
                break;
            }
            control |= 0x4;
            group = true;
        }
        else if (strcmp(param_log,argv[iarg]) == 0) {
            // -log
            if ((control & 0x8) || (++iarg==argc)) {
                arg_error = true;
                break;
            }
            control |= 0x8;
            file_log = argv[iarg];
        }
        else if (strcmp(param_verb,argv[iarg]) == 0) {
            // -v
            if ((control & 0x10) || (++iarg==argc) ||
                (strlen(argv[iarg])!=1) || argv[iarg][0]<'0' ||  argv[iarg][0]>'7' ) {
                arg_error = true;
                break;
            }
            control |= 0x10;
            verbose = ToInt::parse(argv[iarg]);
        }
        else if (strcmp(param_utf8,argv[iarg]) == 0) {
            // -UTF8
            if ((control & 0x20)) {
                arg_error = true;
                break;
            }
            control |= 0x20;
            encoding = FILE_UTF_8;
        }
        else if (strcmp(param_utf16LE,argv[iarg]) == 0) {
            // -UTF16LE
            if ((control & 0x40)) {
                arg_error = true;
                break;
            }
            control |= 0x40;
            encoding = FILE_UTF_16LE;
        }
        else if (strcmp(param_utf16BE,argv[iarg]) == 0) {
            // -UTF16BE
            if ((control & 0x80)) {
                arg_error = true;
                break;
            }
            control |= 0x80;
            encoding = FILE_UTF_16BE;
        }
        else if (strcmp(param_import,argv[iarg]) == 0) {
            // -IMPORT <file>
            if ((control & 0x100) || (++iarg==argc)) {
                arg_error = true;
                break;
            }
            control |= 0x100;
            import_file = argv[iarg];
        }
        else if (strcmp(param_export,argv[iarg]) == 0) {
            // -EXPORT <file>
            if ((control & 0x200) || (++iarg==argc)) {
                arg_error = true;
                break;
            }
            control |= 0x200;
            export_file = argv[iarg];
        }
        else if (strcmp(param_iso885915,argv[iarg]) == 0) {
            // -ISO_885915
            if ((control & 0x400)) {
                arg_error = true;
                break;
            }
            control |= 0x400;
            encoding = FILE_ISO_8859_15;
        }
        else if (strcmp(param_dir,argv[iarg]) == 0) {
            // -dir
            if ((control & 0x800) || (++iarg==argc)) {
                arg_error = true;
                break;
            }
            control |= 0x800;
            out_folder = argv[iarg];
        }
        else {
            // files
            control |= 0x1;
            files.push_back(argv[iarg]);
        }
        iarg++;
    }

    // check required arguments
    if ( ((control & 0x01) != 0x01) || arg_error) {
        usage();
        //::system("pause");
        exit(-1);
    }

    initialize_log(verbose, file_log);

    // start
    Category * main_cat = &Category::getInstance(LOGNAME);
    int err = 0;
    main_cat->notice("start program");

    main_cat->debug("search modules");
    files::path my_path = files::current_path() / files::path("\\packs\\");
    vector<files::path> modules;
    vector<files::path>::iterator i;
    boost::ptr_vector<CPlug<void> > dllplugged;
    std::auto_ptr<CPlug<void> > dll;
    main_cat->debugStream() << "search in " << my_path.string();
    find_file(my_path, ".dll", modules );
    for (i = modules.begin(); i < modules.end(); ++i) {
        dll.reset(new CPlug<void>);
        main_cat->debugStream() << "try to load " << i->filename().string();
        if(dll->LoadPlugin(i->c_str())) {
            main_cat->debugStream() << i->filename().string() << " loaded";
            dll->GetPlugIn(0);
            dllplugged.push_back(dll);
        }
    }

    UniDataModel* data = UniDataModel::getInstance();
    main_cat->debug("class data initialized");

    if (!import_file.empty()) {
        main_cat->debugStream() << "import data from " << import_file;
        data->load(import_file.c_str());
    }
    else {
        project_t ptype = WRK_PROJECT;
        if (group) ptype = WRK_FILE;
        data->createWorkspace(  L"Project",
                                L"Teddy DIDE",
                                L"Project generated by gensources",
                                L"1.00", ptype, 1);
    }

    {
        vector<string>::iterator ite;
        ParserManager * manager = ParserManager::getInstance();
        main_cat->debug("start parsing");
        for (ite = files.begin(); ite != files.end() && !err; ++ite) {
            // file information
            ParameterArray p;
            p.push_back(Parameter(size_t(0), *ite));
            p.push_back(Parameter(size_t(1), encoding));
            string ext = extension(*ite);
            if (ext.empty()) ext = *ite;

            // try to parse
            main_cat->debugStream() << "try to load " << ext << " parser with parameters\n"
                << "file: " << *ite << ", encoding: " << encoding;
            try {
                Parser* parser = manager->create(ext.c_str(), p);
                if (parser) err = parser->parse();
                else {
                    err = -1;
                    main_cat->fatalStream() << "parser isn't correctly implemented";
                }
                manager->release(ext.c_str(), parser);
            } catch (UnRegisteredClassException & reg){
                err = -1;
                main_cat->errorStream() << "Unable to load parser, error message: " << reg.what();
            }
        }
    }

    if (!err && !export_file.empty()) {
        main_cat->debugStream() << "export data to " << export_file;
        data->save(export_file.c_str());
    }

    if (!err && !out_format.empty()) {
        main_cat->debug("start generation");

        {
            vector<string> * tab;
            FamilyManager * family = FamilyManager::getInstance();
            GeneratorManager * manager = GeneratorManager::getInstance();
            typedef vector<string>::iterator iterator_t;

            try {
                tab = family->getObject(out_format);
                for (iterator_t i = tab->begin(); i<tab->end() && !err; ++i) {
                    // file information
                    ParameterArray p;
                    p.push_back(Parameter(size_t(0), *i));
                    p.push_back(Parameter(size_t(1), encoding));
                    p.push_back(Parameter(size_t(2), out_folder.generic_string()));

                    // try to parse
                    main_cat->debugStream() << "try to load " << *i << " generator with parameters\n"
                        << "file: " << out_folder.generic_string() + ' ' + *i << ", encoding: " << encoding;
                    try {
                        std::string className = out_format + "::" + i->c_str();
                        dsg::Generator* generator = manager->create(className, p);
                        if (generator) err = generator->generate();
                        else {
                            err = -1;
                            main_cat->fatalStream() << "generator isn't correctly implemented";
                        }
                        manager->release(className, generator);
                    } catch (UnRegisteredClassException & reg){
                        err = -1;
                        main_cat->errorStream() << "Unable to load generator, error message: " << reg.what();
                    }
                }
            } catch (UnRegisteredObjectException & ex) {
                main_cat->errorStream() << "Unable to load family generator, error message: " << ex.what();
                err = -1;
            }
        }
    }

    main_cat->debug("unplug modules");
    ptr_vector<CPlug<void> >::iterator j;
    for (j = dllplugged.begin(); j < dllplugged.end(); ++j) {
        j->ReleasePlugIn();
    }
    dllplugged.clear();

    main_cat->notice("end program");
    //::system("pause");
}


