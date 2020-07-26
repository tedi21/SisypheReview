#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>

#include <boost/algorithm/string/replace.hpp>

#include "config.hpp"
#include "dataconnection.hpp"
#include "dataparameters.hpp"
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

struct Derogation {
	std::wstring commitHash;
	unsigned int commitLine;
	unsigned int orderOfError;
	std::wstring comment;
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
    std::wstring result = L"Identifier\tFile Path\tFile Name\tFile Type\tRule Number\tRule Category\tRule Description\tLine Number\tNew Error\tCommit Hash\tCommit Date\tCommit Author\tCommit Origine Line\tOrder Of Error\tError Derogation\n";  
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

		std::wstring query = L"WITH commitRows(identifier, orderOfError) AS (\n"
                             L"SELECT n1.identifier, ROW_NUMBER() OVER (PARTITION BY n1.commitLine) orderOfError\n"
                             L"FROM cppNotice n1, cppNotice n2\n"
                             L"WHERE n1.commitHash=n2.commitHash and n1.commitLine=n2.commitLine\n"
                             L"GROUP BY n1.identifier)\n"
                             L"SELECT n.identifier, f.path, f.name, f.idType, n.ruleNumber, n.category, n.description, n.lineNumber, n.isNew, n.commitHash, n.commitDate, n.commitAuthor, n.commitLine, r.orderOfError, n.derogation\n"
                             L"FROM cppFile f, cppNotice n, commitRows r\n"
							 L"WHERE r.identifier=n.identifier and f.identifier=n.idFile\n";

		std::wstring count = L"SELECT COUNT(*)\n"
                             L"FROM cppFile f, cppNotice n\n"
							 L"WHERE f.identifier=n.idFile\n";

		if (!expr.empty())
		{
			std::wstring sqlExpr = expr;
			boost::ireplace_all(sqlExpr, "FilePath", "f.path");
			boost::ireplace_all(sqlExpr, "FileName", "f.name");
			boost::ireplace_all(sqlExpr, "FileType", "f.idType");
			boost::ireplace_all(sqlExpr, "RuleNumber", "n.ruleNumber"); 
			boost::ireplace_all(sqlExpr, "RuleCategory", "n.category"); 
			boost::ireplace_all(sqlExpr, "RuleDescription", "n.description"); 
			boost::ireplace_all(sqlExpr, "LineNumber", "n.lineNumber"); 
			boost::ireplace_all(sqlExpr, "NewError", "n.isNew"); 
			boost::ireplace_all(sqlExpr, "CommitHash", "n.commitHash"); 
			boost::ireplace_all(sqlExpr, "CommitDate", "n.commitDate"); 
			boost::ireplace_all(sqlExpr, "CommitAuthor", "n.commitAuthor"); 
			boost::ireplace_all(sqlExpr, "CommitOrigineLine", "n.commitLine"); 
			boost::ireplace_all(sqlExpr, "ErrorDerogation", "n.derogation"); 
			query += L" and (" + sqlExpr + L")\n";
			count += L" and (" + sqlExpr + L")\n";
		}
		query += L" ORDER BY f.path, n.lineNumber, n.ruleNumber";
		if (limit != static_cast<unsigned int>(-1))
		{
			query += L" LIMIT " + std::to_wstring(limit) + L" OFFSET " + std::to_wstring(offset);
		}
		data_access::UniDataStatement& statement = connection->statement(query);

		while( statement.executeStep() ) 
		{
			long long identifier;
			std::wstring path;
			std::wstring name;
			long long type;
			long long ruleNumber;
			std::wstring category;
			std::wstring description;
			long long lineNumber;
			long long isNew;
			std::wstring commitHash;
			std::wstring commitDate;
			std::wstring commitAuthor;
			long long commitLine;
			long long orderOfError;
			std::wstring derogation;

			if (statement.getInt64( 0, identifier ) &&
				statement.getText( 1, path ) &&				
				statement.getText( 2, name ) &&
				statement.getInt64( 3, type ) &&
				statement.getInt64( 4, ruleNumber ) &&
				statement.getText( 5, category ) &&
				statement.getText( 6, description ) &&
				statement.getInt64( 7, lineNumber ) &&
				statement.getInt64( 8, isNew ) &&
				statement.getText( 9, commitHash ) &&
				statement.getText( 10, commitDate ) &&
				statement.getText( 11, commitAuthor ) &&
				statement.getInt64( 12, commitLine ) &&
				statement.getInt64( 13, orderOfError ) &&
				statement.getText( 14, derogation )) {
				result += std::to_wstring(identifier) + L'\t' + path + L'\t' + name + L'\t' + std::to_wstring(type) + L'\t' + std::to_wstring(ruleNumber) + L'\t' + category + L'\t' + description + L'\t' + std::to_wstring(lineNumber) + L'\t' + std::to_wstring(isNew) + L'\t' + commitHash + L'\t' + commitDate + L'\t' + commitAuthor + L'\t' + std::to_wstring(commitLine) + L'\t' + std::to_wstring(orderOfError) + L'\t' + derogation + L'\n';
			}
		}

		if (limit != static_cast<unsigned int>(-1))
		{
			data_access::UniDataStatement& statementCount = connection->statement(count);

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

void addDerogations(const std::vector<Derogation>& derogationsList)
{
    Category* logger = Category::exists(LOGNAME);
    if (logger == nullptr)
    {
        logger = initialize_log(LOGNAME, 6);
    }
	try
	{
		data_access::UniDataConnection* connection = data_access::UniDataConnection::getInstance();
		if (connection != nullptr)
		{
			std::wstring query = L"WITH commitRows(identifier, orderOfError) AS (\n"
								 L"SELECT n.identifier, ROW_NUMBER() OVER (PARTITION BY commitLine) orderOfError\n"
								 L"FROM cppNotice n\n"
								 L"WHERE commitHash=? and commitLine=?)\n"
								 L"UPDATE cppNotice\n"
								 L"SET derogation=?\n"
								 L"WHERE identifier=(\n"
								 L"SELECT r.identifier\n"
								 L"FROM commitRows r\n"
								 L"WHERE r.orderOfError=?);";

			data_access::UniDataStatement& statement = connection->statement(query); 
			connection->startTransaction();
			for (const Derogation& derog : derogationsList)
			{		
				data_access::UniDataParameters values;
				values.addText(derog.commitHash);
				values.addInt64(derog.commitLine);
				values.addText(derog.comment);
				values.addInt64(derog.orderOfError);
				values.fill(statement);
				statement.executeQuery();
			}	
			connection->commit();
		}
	}
	catch(const data_access::BadSqlQueryException& e)
	{
		logger->errorStream() << e.what();
	}
}

void resetDerogations()
{
    Category* logger = Category::exists(LOGNAME);
    if (logger == nullptr)
    {
        logger = initialize_log(LOGNAME, 6);
    }
	try
	{
		data_access::UniDataConnection* connection = data_access::UniDataConnection::getInstance();
		if (connection != nullptr)
		{
			std::vector<std::wstring> fields { L"derogation" };
			std::wstring where = L"";
			data_access::UniDataStatement& statement = connection->update(L"cppNotice", fields, where); 
			data_access::UniDataParameters values;
			connection->startTransaction();
			values.addText(L"");
			values.fill(statement);
			statement.executeQuery();
			connection->commit();
		}
	}
	catch(const data_access::BadSqlQueryException& e)
	{
		logger->errorStream() << e.what();
	}
}

void loadDerogations(const std::wstring& content) 
{
	std::vector<Derogation> vec;
	std::vector<std::wstring> lines;
	boost::algorithm::split(lines, content, boost::is_any_of("\n"));
	if (!lines.empty())
	{
		for (size_t i = 1; i < lines.size(); ++i)
		{
			std::vector<std::wstring> item;
			boost::algorithm::split(item, lines[i], boost::is_any_of("\t"));
			Derogation derog;
			if ((item.size() > 14) && (!item[9].empty())) 
			{
				derog.commitHash = item[9];
				derog.commitLine = std::stoul(item[12]);
				derog.orderOfError = std::stoul(item[13]);
				derog.comment = item[14];
				vec.push_back(derog);
			}
		}
	}
	resetDerogations();
	addDerogations(vec);
}


EMSCRIPTEN_BINDINGS(module) {
    emscripten::value_object<Content>("Content")
        .field("Text", &Content::text)
        .field("Type", &Content::type);

    emscripten::register_vector<Content>("VectorContent");

    emscripten::function("tdscript", &tdscript);

    emscripten::register_vector<unsigned char>("VectorByte");

    emscripten::function("filter", &filter);

    emscripten::value_object<Derogation>("Derogation")
        .field("CommitHash", &Derogation::commitHash)
        .field("CommitLine", &Derogation::commitLine)
        .field("OrderOfError", &Derogation::orderOfError)
        .field("Comment", &Derogation::comment);

	emscripten::register_vector<Derogation>("VectorDerogation");

	emscripten::function("addDerogations", &addDerogations);

	emscripten::function("resetDerogations", &resetDerogations);

	emscripten::function("loadDerogations", &loadDerogations);
}
