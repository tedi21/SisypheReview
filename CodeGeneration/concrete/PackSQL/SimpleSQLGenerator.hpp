#ifndef _SIMPLE_SQL_GENERATOR_HPP_
#define _SIMPLE_SQL_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "EtatHandler.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleSQLGenerator
		: public report<SimpleSQLGenerator> {

			template <typename InfoT>
			struct etat : public EtatHandler {
				format<InfoT>   ScriptSQL,
								CreateFile,
								CreateHeader,
								CreateDatabase,
								CreateAuthorization,
								SetUsage,
								CreateTable,
								CreatePrimaryKey,
								CreateForeignKey,
								CreateAttribute,
								CreateOption;

				etat(SimpleSQLGenerator const& me)
				{
					ScriptSQL = 
						CreateFile;

					CreateFile =
						CreateHeader
						<< +( CreateDatabase
						<<    CreateAuthorization )
						<< SetUsage
						<< (CreateTable << "\r\n") [ent0, entN];                

					CreateHeader =
						str_g("-- \r\n")
            << "-- " << file_g(getFileNameHandler(KIND_ALIAS)) << ".sql\r\n"
						<< "--\r\n"
						<< "--\r\n"
						<< "-- date: " << call_g(getDateHandler("dd-mm-yyyy")) << "\r\n"
						<< "-- author: " << call_g(getWorkspaceAuthorHandler()) << "\r\n"
						<< "-- version: " << call_g(getWorkspaceVersionHandler()) << "\r\n"
						<< "-- brief: " << call_g(getWorkspaceBriefHandler()) << "\r\n"
						<< "\r\n\r\n";

					CreateDatabase =
						str_g("-- Data Base creation\r\n")
						<< "--__________________________\r\n\r\n"
						<< "CREATE DATABASE " << call_g(getWorkspaceNameHandler()) << ";\r\n"
						<< "\r\n";

					CreateAuthorization =
						str_g("GRANT ALL ON ") << call_g(getWorkspaceNameHandler()) <<".* TO login IDENTIFIED BY \'passwd\';\r\n"
						<< "GRANT ALL ON " << call_g(getWorkspaceNameHandler()) <<".* TO login@localhost IDENTIFIED BY \'passwd\';\r\n"
						<< "\r\n";

					SetUsage =
						str_g("use ") << call_g(getWorkspaceNameHandler()) << "\r\n\r\n";

					CreateTable = 
                        str_g("-- ") << ent_g(getEntityNameHandler(KIND_ALIAS)) << " table\r\n"
						<< "--__________________________\r\n\r\n"
                        << "CREATE TABLE " << ent_g(getEntityNameHandler(KIND_ALIAS)) << " (\r\n\t\t"
							<< ( '\t' << CreateAttribute << ~(-str_g(",\r\n\t\t"))) [attr0, attrN]
							<< CreatePrimaryKey  
							<< CreateForeignKey 
						<< "\r\n);\r\n\r\n" ;

					CreateAttribute = 
                        attr_g(getAttributeNameHandler(KIND_ALIAS)) << ' '
                        << (str_g("VARCHAR(256)") [attr_g(getIsAttributeTypeHandler(ATTR_STRING))])
                        << (str_g("VARCHAR(256)") [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))])
                        << (str_g("VARCHAR(256)") [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))])
                        << (str_g("NUMERIC(8)")   [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))])
                        << (str_g("INT")          [attr_g(getIsAttributeTypeHandler(ATTR_INT))])
                        << (str_g("TINYINT")      [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))])
                        << (str_g("SMALLINT")     [attr_g(getIsAttributeTypeHandler(ATTR_INT16))])
                        << (str_g("MEDIUMINT")    [attr_g(getIsAttributeTypeHandler(ATTR_INT32))])
                        << (str_g("BIGINT")       [attr_g(getIsAttributeTypeHandler(ATTR_INT64))])
                        << (str_g("INT")          [attr_g(getIsAttributeTypeHandler(ATTR_UINT))])
                        << (str_g("TINYINT")      [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))])
                        << (str_g("SMALLINT")     [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))])
                        << (str_g("MEDIUMINT")    [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))])
                        << (str_g("BIGINT")       [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))])
                        << (str_g("TEXT")         [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))])
                        << (str_g("DATE")         [attr_g(getIsAttributeTypeHandler(ATTR_DATE))])
                        << (str_g("TIME")         [attr_g(getIsAttributeTypeHandler(ATTR_TIME))])
                        << (str_g("BLOB")         [attr_g(getIsAttributeTypeHandler(ATTR_BINARY))])
                        << CreateOption;
	                
					CreateOption =
						(str_g(" NOT NULL")            [attr_g(getIsAttributeModifierHandler(ATTR_REF))])
						<< str_g(" AUTO_INCREMENT")    [attr_g(getIsAttributeModifierHandler(ATTR_ID | ATTR_AUTO))];

					CreatePrimaryKey =
						str_g(",\r\n\t\t\t")
                        << "CONSTRAINT PK_" << upper_g(ent_g(getEntityNameHandler(KIND_ALIAS)),0,1)
						<< " PRIMARY KEY(" 
                        << ((attr_g(getAttributeNameHandler(KIND_ALIAS)) << ~(-str_g(", ")))
                                                                                    [attr_g(getIsAttributeModifierHandler(ATTR_ID))])
																					[attr0, attrN]
						<< ")";

					CreateForeignKey = 
						(str_g(",\r\n\t\t\t")
                        << "CONSTRAINT FK_" << upper_g(rel_g(getRelationTargetHandler(KIND_ALIAS)),0,1)
                        << "_" << upper_g(rel_g(getRelationSourceHandler(KIND_ALIAS)),0,1)
                        << " FOREIGN KEY(" << rel_g(getRelationTargetRefHandler(KIND_ALIAS))
                        << ") REFERENCES " << rel_g(getRelationSourceHandler(KIND_ALIAS))
                        << " (" << rel_g(getRelationSourceRefHandler(KIND_ALIAS))    << ")")
                                                                                    [relationsByAttr(FILTER_TARGET)]
																					[attr_g(getIsAttributeModifierHandler(ATTR_REF))]
																					[attr0, attrN];
				}

				format<InfoT> const& start() const { return ScriptSQL; }
			};
		};
	}
}

#endif
