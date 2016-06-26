#pragma once

#include <iostream>
#include <string>
#include "SimpleCPPCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

    namespace generator {

        struct SimpleHPPConnectionGenerator
        : public report<SimpleHPPConnectionGenerator> {

            template <typename InfoT>
            struct etat : public SimpleCPPCommonGenerator {
                format<InfoT>       SourceHPP,
                                    CreateFile, 
                                    CreateInclude, 
                                    CreateEndInclude, 
                                    CreateClass;

                etat(SimpleHPPConnectionGenerator const& me)
                {
                    SourceHPP = 
                        CreateFile;

                    CreateFile =
                        CreateHeader_R2(str_g("DataConnection.hpp"))
                        << CreateHPPDefine_R2(str_g("_data_connection_hpp_"))
                        << CreateInclude
                        << CreateNamespace_R2(str_g("data_access"))
                        << CreateClass
                        << CreateEndNamespace_R2
                        << CreateEndInclude
                        << CreateHPPEndDefine_R2;            

                    CreateInclude =
                        str_g("#include \"config.hpp\""          "\r\n"
                          "#include \"encoding.hpp\""            "\r\n"
                          "#include <vector>"                    "\r\n\r\n"
                          "using namespace std;\r\n"
                          "using namespace log4cpp;\r\n"
                          "using namespace enc;\r\n\r\n");

                    CreateClass =
                        str_g("// concrete class that must be implemented by the user\r\n")
                        << "template <class EncodingT>\r\n"
                          "class _DataConnection \r\n"   
                          "{ \r\n"
                          "private:"                                                                "\r\n"
                          "\t// static member that must be declared"                                "\r\n"
                          "\t// static connection_type connection_handle;"                            "\r\n"
                          "\tbool transaction_inProgress;"                                            "\r\n"
                          "\tCategory * m_logger;"                                                    "\r\n\r\n" 
                          "\t// private constructor"                                                "\r\n"
                          "\t_DataConnection();"                                                    "\r\n\r\n"
                          "\t// private methods"                                                    "\r\n"
                          "\ttypename EncodingT::string_t formatSelect(vector<typename EncodingT::string_t> const& columns,"            "\r\n"    
                          "                    vector<typename EncodingT::string_t> const& tables,"                                        "\r\n"        
                          "                    typename EncodingT::string_t const& filter = EncodingT::EMPTY,"            "\r\n"
                          "                    bool forUpdate = false, bool noWait = false) const;"                    "\r\n\r\n"
                          "\ttypename EncodingT::string_t formatInsert(typename EncodingT::string_t const& table,"    "\r\n"                    
                          "                    vector<typename EncodingT::string_t> const& columns,"                    "\r\n"
                          "                    vector<typename EncodingT::string_t> const& values) const;"                "\r\n\r\n"
                          "\ttypename EncodingT::string_t formatDeleteFrom(typename EncodingT::string_t const& table,"    "\r\n"
                          "                    typename EncodingT::string_t const& filter = EncodingT::EMPTY) const;"        "\r\n\r\n"
                          "\ttypename EncodingT::string_t formatUpdate(typename EncodingT::string_t const& table,"    "\r\n"
                          "                    vector<typename EncodingT::string_t> const& columns,"                    "\r\n"
                          "                    vector<typename EncodingT::string_t> const& values,"                    "\r\n"
                          "                    typename EncodingT::string_t const& filter = EncodingT::EMPTY) const;"    "\r\n\r\n"
                          "public:"                                                                    "\r\n"
                          "\t// type"                                                                "\r\n"
                          "\ttypedef vector<vector<typename EncodingT::string_t> >    resultset;"        "\r\n\r\n"
                          "\t// static methods that must be implemented"                            "\r\n"
                          "\tstatic bool openConnection(typename EncodingT::string_t const& host,"    "\r\n"
                          "                    int port,"                                                "\r\n"
                          "                    typename EncodingT::string_t const& db,"                "\r\n"
                          "                    typename EncodingT::string_t const& user,"                "\r\n"
                          "                    typename EncodingT::string_t const& passwd);"            "\r\n\r\n"
                          "\tstatic void closeConnection();"                                        "\r\n\r\n"
                          "\tstatic _DataConnection<EncodingT> * getInstance();"                    "\r\n\r\n"
                          "\t// class methods that must be implemented"                                "\r\n"
                          "\tresultset select(vector<typename EncodingT::string_t> const& columns,"                    "\r\n"    
                          "                    vector<typename EncodingT::string_t> const& tables,"                    "\r\n"        
                          "                    typename EncodingT::string_t const& filter = EncodingT::EMPTY) const;"  "\r\n\r\n"
                          "\tresultset selectForUpdate(vector<typename EncodingT::string_t> const& columns,"        "\r\n"    
                          "                    vector<typename EncodingT::string_t> const& tables,"                    "\r\n"        
                          "                    typename EncodingT::string_t const& filter = EncodingT::EMPTY,"            "\r\n"
                          "                    bool nowait = false);"                                                    "\r\n\r\n"
                          "\tbool\tinsert(typename EncodingT::string_t const& table,"                                "\r\n"                    
                          "                    vector<typename EncodingT::string_t> const& columns,"                    "\r\n"
                          "                    vector<typename EncodingT::string_t> const& values);"                    "\r\n\r\n"
                          "\tbool\tdeleteFrom(typename EncodingT::string_t const& table,"                            "\r\n"
                          "                    typename EncodingT::string_t const& filter = EncodingT::EMPTY);"        "\r\n\r\n"
                          "\tbool\tupdate(typename EncodingT::string_t const& table,"                                "\r\n"
                          "                    vector<typename EncodingT::string_t> const& columns,"                    "\r\n"
                          "                    vector<typename EncodingT::string_t> const& values,"                    "\r\n"
                          "                    typename EncodingT::string_t const& filter = EncodingT::EMPTY);"        "\r\n\r\n"
                          "\tint\t\tgetLastInsertID() const;"                                                       "\r\n\r\n"
                          "\tint\t\tselectMaxID(typename EncodingT::string_t const& id, "                           "\r\n"
                          "                     typename EncodingT::string_t const& table) const;"                  "\r\n\r\n"
                          "\tbool\tcommit();"                                                    "\r\n\r\n"
                          "\tbool\trollback();"                                                    "\r\n\r\n"
                          "\tbool\tstartTransaction();"                                            "\r\n\r\n"
                          "\tbool\tisTransactionInProgress();"                                    "\r\n\r\n"
                          "};"                                                                    "\r\n\r\n"
                          "typedef _DataConnection<ucs>\t    UniDataConnection;"                    "\r\n"
                          "typedef _DataConnection<ansi>\t    DataConnection;"                    "\r\n\r\n";

                    CreateEndInclude =
                        str_g("#include \"DataConnection_impl.hpp\"\r\n");

                }

                format<InfoT> const& start() const { return SourceHPP; }
            };
        };
    }
}