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


struct Content {
    std::wstring text;
    unsigned int type;
};

std::wstring tdscript(const std::vector<Content>& contents)
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
        boost::shared_ptr<Array<ucs>> arr(new Array<ucs>());
        for (auto it = contents.begin(); it != contents.end(); ++it)
        {
            boost::shared_ptr<Structure<ucs>> str(new Structure<ucs>());
            str->insertField(L"Text", boost::shared_ptr<Base<ucs>>(new String<ucs>(it->text)));
            str->insertField(L"Type", boost::shared_ptr<Base<ucs>>(new Numeric<ucs>(it->type)));
            arr->addValue(str);
        }
        c.add(L"FILES", arr);
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

std::wstring filter(const std::vector<unsigned char>& base, const std::wstring& expr, const unsigned int limit, const unsigned int offset)
{ 
    std::wstring result;  
    Category* logger = Category::exists(LOGNAME);
    if (logger == nullptr)
    {
        logger = initialize_log(LOGNAME, 6);
    }

	try
	{
		const data_access::UniDataConnection* const db = data_access::UniDataConnection::getInstance(encode<ansi,ucs>("cppbase.db"));
		if (db == nullptr)
		{
			// Création du fichier db
			std::ofstream m_fstream("cppbase.db", ios_base::out | ios_base::binary);
			m_fstream.write(reinterpret_cast<const char*>(base.data()), base.size());
			m_fstream.close();

		    logger->debugStream() << "try to open DB connection " << "cppbase.db";
		    if (!data_access::UniDataConnection::openConnection(UCS(""), 0, encode<ansi,ucs>("cppbase.db"), UCS(""), UCS("")))
		    {
		        logger->errorStream() << "cannot open DB connection " << "cppbase.db" << ".";
		    }
		}

		data_access::UniDataConnection* connection = data_access::UniDataConnection::getInstance();
		logger->debugStream() << "prepare sql query ";
		std::vector<std::wstring> tables { L"cppFile f", L"cppNotice n" };
		std::vector<std::wstring> columns { L"n.identifier", L"f.path", L"f.name", L"f.idType", L"f.linesCount", L"n.ruleNumber", L"n.category", L"n.description", L"n.lineNumber", L"n.startBlock", L"n.isNew", L"f.isTracked", L"n.commitHash", L"n.commitDate", L"n.commitAuthor", L"n.commitLine" };
		std::wstring query = L"f.identifier=n.idFile";
		if (!expr.empty())
		{
			query += L" and (" + expr + L")";
		}
        std::wstring queryWithoutLimit = query;
		query += L" ORDER BY f.path, n.startBlock, n.ruleNumber";
		if (limit != static_cast<unsigned int>(-1))
		{
			query += L" LIMIT " + std::to_wstring(limit) + L" OFFSET " + std::to_wstring(offset);
		}
		data_access::UniDataStatement& statement = connection->select(columns, tables, query);

		while( statement.executeStep() ) 
		{
			long long identifier;
			std::wstring path;
			std::wstring name;
			long long type;
			long long linesCount;
			long long ruleNumber;
			std::wstring category;
			std::wstring description;
			long long lineNumber;
			long long startBlock;
			long long isNew;
			long long isTracked;
			std::wstring commitHash;
			std::wstring commitDate;
			std::wstring commitAuthor;
			long long commitLine;

			if (statement.getInt64( 0, identifier ) &&
				statement.getText( 1, path ) &&				
				statement.getText( 2, name ) &&
				statement.getInt64( 3, type ) &&
				statement.getInt64( 4, linesCount ) &&
				statement.getInt64( 5, ruleNumber ) &&
				statement.getText( 6, category ) &&
				statement.getText( 7, description ) &&
				statement.getInt64( 8, lineNumber ) &&
				statement.getInt64( 9, startBlock ) &&
				statement.getInt64( 10, isNew ) &&
				statement.getInt64( 11, isTracked ) &&
				statement.getText( 12, commitHash ) &&
				statement.getText( 13, commitDate ) &&
				statement.getText( 14, commitAuthor ) &&
				statement.getInt64( 15, commitLine )) {
				result += std::to_wstring(identifier) + L'\t' + path + L'\t' + name + L'\t' + std::to_wstring(type) + L'\t' + std::to_wstring(linesCount) + L'\t' + std::to_wstring(ruleNumber) + L'\t' +category + L'\t' + description + L'\t' + std::to_wstring(lineNumber) + L'\t' + std::to_wstring(startBlock) + L'\t' + std::to_wstring(isNew) + L'\t' + std::to_wstring(isTracked) + L'\t' + commitHash + L'\t' + commitDate + L'\t' + commitAuthor + L'\t' + std::to_wstring(commitLine) + L'\n';
			}
		}

		if (limit != static_cast<unsigned int>(-1))
		{
			std::vector<std::wstring> countRows { L"COUNT(*)" };
			data_access::UniDataStatement& statementCount = connection->select(countRows, tables, queryWithoutLimit);

			while( statementCount.executeStep() ) 
			{
				long long max;
				if (statement.getInt64( 0, max )) {
					result += std::to_wstring(max) + L'\n';
				}
			}
		}
	}
	catch(const data_access::BadSqlQueryException& e)
	{
		logger->errorStream() << e.what();
	}

    return result;
}


EMSCRIPTEN_BINDINGS(module) {
    emscripten::value_object<Content>("Content")
        .field("Text", &Content::text)
        .field("Type", &Content::type);

    emscripten::register_vector<Content>("VectorContent");

    emscripten::function("tdscript", &tdscript);

    emscripten::register_vector<unsigned char>("VectorByte");

    emscripten::function("filter", &filter);
}
