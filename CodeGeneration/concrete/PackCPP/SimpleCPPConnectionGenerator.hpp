#pragma once

#include <iostream>
#include <string>
#include "SimpleCPPCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

    namespace generator {

        struct SimpleCPPConnectionGenerator
        : public report<SimpleCPPConnectionGenerator> {

            template <typename InfoT>
            struct etat : public SimpleCPPCommonGenerator {
                format<InfoT>        SourceHPP,
                                    CreateFile,
                                    CreateInclude,
                                    CreateClass;

                etat(SimpleCPPConnectionGenerator const& me)
                {
                    SourceHPP = 
                        CreateFile;

                    CreateFile =
                        CreateInclude
                        << CreateMacro_R2
                        << CreateNamespace_R2(str_g("data_access"))
                        << CreateClass
                        << CreateEndNamespace_R2
                        << CreateEndMacro_R2;            

                    CreateInclude =
                        str_g("#include \"BadSqlQueryException.hpp\"\r\n\r\n");

                    CreateClass =
                        str_g("// concrete class that must be implemented by the user\r\n\r\n")
                        << "// connection_type _DataConnection<EncodingT>::connection_handle = NULL;"   "\r\n\r\n" 
                          "// constructor"                                                    "\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "_DataConnection<EncodingT>::_DataConnection()"                    "\r\n"
                          "{"                                                                "\r\n"
                          "\tm_logger = &Category::getInstance(LOGNAME);"                    "\r\n"
                          "\tm_logger->debugStream() << \"creation DataConnection\";"        "\r\n"
                          "\ttransaction_inProgress = false;"                                "\r\n"
                          "\t//initialization code"                                            "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "bool _DataConnection<EncodingT>::openConnection(typename EncodingT::string_t const& host,"    "\r\n"
                          "                                                int port,"                                        "\r\n"
                          "                                                typename EncodingT::string_t const& db,"        "\r\n"
                          "                                                typename EncodingT::string_t const& user,"        "\r\n"
                          "                                                typename EncodingT::string_t const& passwd)"    "\r\n"
                          "{"                                                                "\r\n"
                          "\t//open connection"                                                "\r\n"
                          "\t//connection_handle = getConnection(host, port, db, user, passwd);"   "\r\n"
                          "\t//m_logger->debugStream() << \"open connection\";"                "\r\n"
                          "\treturn true;"                                                    "\r\n"
                          "}"                                                                "\r\n\r\n"
                            "template <class EncodingT>"                                        "\r\n"
                          "void _DataConnection<EncodingT>::closeConnection()"                "\r\n"
                          "{"                                                                "\r\n"
                          "\t//close connection"                                            "\r\n"
                          "\t//closeConnection(connection_handle);"                            "\r\n"
                          "\t//m_logger->debugStream() << \"close connection\";"            "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "_DataConnection<EncodingT> * _DataConnection<EncodingT>::getInstance()"        "\r\n"
                          "{"                                                                "\r\n"
                          "\t//check connection and create DataConnection"                    "\r\n"
                          "\t//if (connection_handle) return new _DataConnection<EncodingT>();"            "\r\n"
                          "\t//else return NULL;"                                            "\r\n"
                          "\treturn NULL;"                                                    "\r\n"
                          "}"                                                                "\r\n\r\n"

                          "template <class EncodingT>"                                        "\r\n"
                          "typename EncodingT::string_t _DataConnection<EncodingT>::formatSelect(vector<typename EncodingT::string_t> const& columns,"    "\r\n"
                          "                                                    vector<typename EncodingT::string_t> const& tables,"                    "\r\n"
                          "                                                    typename EncodingT::string_t const& filter, bool forUpdate, bool noWait) const"    "\r\n"
                          "{"                                                                "\r\n"
                          "\t//Create SQL query"                                            "\r\n"
                          "\ttypename EncodingT::string_t query = C(\"SELECT \");"            "\r\n"
                          "\tif (columns.size() == 0) {"                                    "\r\n"
                          "\t\tm_logger->fatalStream() << \"bad query : no columns defined in SELECT query\";"   "\r\n"
                          "\t\tthrow BadSqlQueryException(\"no columns defined in SELECT query\");"   "\r\n"
                          "\t}"                                                                "\r\n"
                          "\telse query += columns[0];"                                        "\r\n"
                          "\tfor (size_t i=1; i<columns.size(); i++) query += C(\", \") + columns[i];"   "\r\n"
                          "\tquery += C(\" FROM \");"                                        "\r\n"
                          "\tif (tables.size() == 0) {"                                        "\r\n"
                          "\t\tm_logger->fatalStream() << \"bad query : no tables defined in SELECT query\";"   "\r\n"
                          "\t\tthrow BadSqlQueryException(\"no tables defined in SELECT query\");"   "\r\n"
                          "\t}"                                                                "\r\n"
                          "\telse query += tables[0];"                                        "\r\n"
                          "\tfor (size_t i=1; i<tables.size(); i++) query += C(\", \") + tables[i];"   "\r\n"
                          "\tif (filter != EncodingT::EMPTY) {"                                        "\r\n"
                          "\t\tquery += C(\" WHERE \") + filter;"                            "\r\n"
                          "\t}"                                                                "\r\n"
                          "\tif (forUpdate) query += C(\" FOR UPDATE \");"                    "\r\n"
                          "\tif (noWait) query += C(\" NOWAIT \");"                            "\r\n"
                          "\tquery += C(\";\");"                                            "\r\n"
                          "\tm_logger->debugStream() << \"query : \" << A(query);"            "\r\n"
                          "\treturn query;"                                                    "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "typename _DataConnection<EncodingT>::resultset"                    "\r\n"
                          "_DataConnection<EncodingT>::select(vector<typename EncodingT::string_t> const& columns,"            "\r\n"
                          "                                                    vector<typename EncodingT::string_t> const& tables,"        "\r\n"
                          "                                                    typename EncodingT::string_t const& filter) const"            "\r\n"
                          "{"                                                                "\r\n"
                          "\tresultset result;"                                                "\r\n"
                          "\ttypename EncodingT::string_t query = formatSelect(columns, tables, filter, false, false);"    "\r\n"
                          "\t//result = connection_handle->executeQuery(query);"            "\r\n"
                          "\treturn result;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "typename _DataConnection<EncodingT>::resultset"                    "\r\n"
                          "_DataConnection<EncodingT>::selectForUpdate(vector<typename EncodingT::string_t> const& columns,"            "\r\n"
                          "                                                    vector<typename EncodingT::string_t> const& tables,"                "\r\n"
                          "                                                    typename EncodingT::string_t const& filter, bool nowait)"            "\r\n"
                          "{"                                                                "\r\n"
                          "\tresultset result;"                                                "\r\n"
                          "\ttypename EncodingT::string_t query = formatSelect(columns, tables, filter, true, nowait);"    "\r\n"
                          "\t//result = connection_handle->executeQuery(query);"            "\r\n"
                          "\treturn result;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "typename EncodingT::string_t _DataConnection<EncodingT>::formatInsert(typename EncodingT::string_t const& table,"    "\r\n"
                          "                                        vector<typename EncodingT::string_t> const& columns,"            "\r\n"
                          "                                        vector<typename EncodingT::string_t> const& values) const"        "\r\n"
                          "{"                                                                "\r\n"
                          "\t//Create SQL query"                                            "\r\n"
                          "\ttypename EncodingT::string_t query = C(\"INSERT INTO \");"        "\r\n"
                          "\tif (table == EncodingT::EMPTY) {"                                "\r\n"
                          "\t\tm_logger->fatalStream() << \"bad query : no table defined in INSERT query\";"   "\r\n"
                          "\t\tthrow BadSqlQueryException(\"no table defined in INSERT query\");"   "\r\n"
                          "\t}"                                                                "\r\n"
                          "\telse query += table;"                                            "\r\n"
                          "\tquery += C(\" ( \");"                                            "\r\n"
                          "\tif (columns.size() == 0) {"                                    "\r\n"
                          "\t\tm_logger->fatalStream() << \"bad query : no columns defined in INSERT query\";"   "\r\n"
                          "\t\tthrow BadSqlQueryException(\"no columns defined in INSERT query\");"   "\r\n"
                          "\t}"                                                                "\r\n"
                          "\telse query += columns[0];"                                        "\r\n"
                          "\tfor (size_t i=1; i<columns.size(); i++) query += C(\", \") + columns[i];"   "\r\n"
                          "\tquery += C(\" ) VALUES ( \");"                                    "\r\n"
                          "\tif (values.size() == 0) {"                                        "\r\n"
                          "\t\tm_logger->fatalStream() << \"bad query : no values defined in INSERT query\";"   "\r\n"
                          "\t\tthrow BadSqlQueryException(\"no values defined in INSERT query\");"   "\r\n"
                          "\t}"                                                                "\r\n"
                          "\telse query += values[0];"                                        "\r\n"
                          "\tfor (size_t i=1; i<values.size(); i++) query += C(\", \") + values[i];"   "\r\n"
                          "\tquery += C(\" );\");"                                            "\r\n"
                          "\tm_logger->debugStream() << \"query : \" << A(query);"            "\r\n"
                          "\treturn query;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "bool _DataConnection<EncodingT>::insert(typename EncodingT::string_t const& table,"                    "\r\n"
                          "                                        vector<typename EncodingT::string_t> const& columns,"            "\r\n"
                          "                                        vector<typename EncodingT::string_t> const& values)"            "\r\n"
                          "{"                                                                "\r\n"
                          "\tbool result = false;"                                            "\r\n"
                          "\ttypename EncodingT::string_t query = formatInsert(table, columns, values);"    "\r\n"
                          "\t//result = connection_handle->executeQuery(query);"            "\r\n"
                          "\treturn result;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "typename EncodingT::string_t _DataConnection<EncodingT>::formatDeleteFrom(typename EncodingT::string_t const& table,"        "\r\n"
                          "                                        typename EncodingT::string_t const& filter) const"        "\r\n"
                          "{"                                                                "\r\n"
                          "\t//Create SQL query"                                            "\r\n"
                          "\ttypename EncodingT::string_t query = C(\"DELETE FROM \");"        "\r\n"
                          "\tif (table == EncodingT::EMPTY) {"                                "\r\n"
                          "\t\tm_logger->fatalStream() << \"bad query : no table defined in DELETE query\";"    "\r\n"
                          "\t\tthrow BadSqlQueryException(\"no table defined in DELETE query\");"                "\r\n"
                          "\t}"                                                                "\r\n"
                          "\telse query += table;"                                            "\r\n"
                          "\tif (filter != EncodingT::EMPTY) {"                                "\r\n"
                          "\t\tquery += C(\" WHERE \") + filter;"                            "\r\n"
                          "\t}"                                                                "\r\n"
                          "\tquery += C(\";\");"                                            "\r\n"
                          "\tm_logger->debugStream() << \"query : \" << A(query);"            "\r\n"
                          "\treturn query;"                                                    "\r\n"
                          "}"                                                                "\r\n\r\n"


                          "template <class EncodingT>"                                        "\r\n"
                          "bool _DataConnection<EncodingT>::deleteFrom(typename EncodingT::string_t const& table,"        "\r\n"
                          "                                        typename EncodingT::string_t const& filter)"            "\r\n"
                          "{"                                                                "\r\n"
                          "\tbool result = false;"                                            "\r\n"
                          "\ttypename EncodingT::string_t query = formatDeleteFrom(table, filter);"    "\r\n"
                          "\t//result = connection_handle->executeQuery(query);"            "\r\n"
                          "\treturn result;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "typename EncodingT::string_t _DataConnection<EncodingT>::formatUpdate(typename EncodingT::string_t const& table,"            "\r\n"
                          "                                        vector<typename EncodingT::string_t> const& columns,"    "\r\n"
                          "                                        vector<typename EncodingT::string_t> const& values,"    "\r\n"
                          "                                        typename EncodingT::string_t const& filter) const"        "\r\n"
                          "{"                                                                "\r\n"
                          "\t//Create SQL query"                                            "\r\n"
                          "\ttypename EncodingT::string_t query = C(\"UPDATE \");"            "\r\n"
                          "\tif (table == EncodingT::EMPTY) {"                                "\r\n"
                          "\t\tm_logger->fatalStream() << \"bad query : no table defined in UPDATE query\";"   "\r\n"
                          "\t\tthrow BadSqlQueryException(\"no table defined in UPDATE query\");"   "\r\n"
                          "\t}"                                                                "\r\n"
                          "\telse query += table;"                                            "\r\n"
                          "\tquery += C(\" SET \");"                                        "\r\n"
                          "\tif (columns.size() == 0 || values.size() == 0) {"                "\r\n"
                          "\t\tm_logger->fatalStream() << \"bad query : no columns defined in UPDATE query\";"   "\r\n"
                          "\t\tthrow BadSqlQueryException(\"no columns defined in UPDATE query\");"   "\r\n"
                          "\t}"                                                                "\r\n"
                          "\tif (columns.size() != values.size()) {"                        "\r\n"
                          "\t\tm_logger->fatalStream() << \"bad query : invalid columns and values sizes in UPDATE query\";"   "\r\n"
                          "\t\tthrow BadSqlQueryException(\"invalid columns and values sizes in UPDATE query\");"   "\r\n"
                          "\t}"                                                                "\r\n"
                          "\telse query += columns[0] + C(\"=\") + values[0];"                "\r\n"
                          "\tfor (size_t i=1; i<columns.size(); i++) query += C(\", \") + columns[i] + C(\"=\") + values[i];"   "\r\n"
                          "\tif (filter != EncodingT::EMPTY) {"                                "\r\n"
                          "\t\tquery += C(\" WHERE \") + filter;"                            "\r\n"
                          "\t}"                                                                "\r\n"
                          "\tquery += C(\";\");"                                            "\r\n"
                          "\tm_logger->debugStream() << \"query : \" << A(query);"            "\r\n"
                          "\treturn query;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "bool _DataConnection<EncodingT>::update(typename EncodingT::string_t const& table,"            "\r\n"
                          "                                        vector<typename EncodingT::string_t> const& columns,"    "\r\n"
                          "                                        vector<typename EncodingT::string_t> const& values,"    "\r\n"
                          "                                        typename EncodingT::string_t const& filter)"            "\r\n"
                          "{"                                                                "\r\n"
                          "\tbool result = false;"                                           "\r\n"
                          "\ttypename EncodingT::string_t query = formatUpdate(table, columns, values, filter);"    "\r\n"
                          "\t//result = connection_handle->executeQuery(query);"             "\r\n"
                          "\treturn result;"                                                 "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                       "\r\n"
                          "int _DataConnection<EncodingT>::getLastInsertID() const"          "\r\n"
                          "{"                                                                "\r\n"
                          "\tint result = -1;"                                                "\r\n"
                          "\t//result = connection_handle->executeQuery(\"SELECT LAST ID FROM TAB;\");"   "\r\n"
                          "\treturn result;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "int _DataConnection<EncodingT>::selectMaxID(typename EncodingT::string_t const& id, "                        "\r\n"
                          "                                            typename EncodingT::string_t const& table) const"                "\r\n"
                          "{"                                                                "\r\n"
                          "\tint result = -1;"                                                "\r\n"
                          "\t//result = connection_handle->executeQuery(\"SELECT MAX ID FROM TAB FOR UPDATE;\");"   "\r\n"
                          "\treturn result;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "bool _DataConnection<EncodingT>::commit()"                        "\r\n"
                          "{"                                                                "\r\n"
                          "\tbool result = false;"                                            "\r\n"
                          "\t//result = connection_handle->commit();"                        "\r\n"
                          "\ttransaction_inProgress = false;"                                "\r\n"
                          "\treturn result;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "bool _DataConnection<EncodingT>::rollback()"                        "\r\n"
                          "{"                                                                "\r\n"
                          "\tbool result = false;"                                            "\r\n"
                          "\t//result = connection_handle->rollback();"                        "\r\n"
                          "\ttransaction_inProgress = false;"                                "\r\n"
                          "\treturn result;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "bool _DataConnection<EncodingT>::startTransaction()"                "\r\n"
                          "{"                                                                "\r\n"
                          "\tbool result = false;"                                            "\r\n"
                          "\t//result = connection_handle->startTransaction();"                "\r\n"
                          "\ttransaction_inProgress = true;"                                "\r\n"
                          "\treturn result;"                                                "\r\n"
                          "}"                                                                "\r\n\r\n"
                          "template <class EncodingT>"                                        "\r\n"
                          "bool _DataConnection<EncodingT>::isTransactionInProgress()"        "\r\n"
                          "{"                                                                "\r\n"
                          "\treturn transaction_inProgress;"                                "\r\n"
                          "}"                                                                "\r\n\r\n";

                }

                format<InfoT> const& start() const { return SourceHPP; }
            };
        };

    }
}