#ifndef _SIMPLE_SQL_PARSER_HPP_
#define _SIMPLE_SQL_PARSER_HPP_

#include <boost/spirit/include/classic_core.hpp>
#include <iostream>
#include <string>
#include "DefinitionHandler.hpp"

using namespace std;
using namespace boost::spirit::classic;

namespace dsg {

    namespace parser {

        DECLARE_MODEL_PARSER_HANDLER( , SqlExtensionHandler)

        class SimpleSQLParser 
        : public grammar<SimpleSQLParser> 
        {
        public :

            template <typename ScannerT>
            struct definition 
            : public DefinitionHandler 
            {
                // SQL tokens used to memorize value
                enum sqltoken_t 
                {
                    SQL_TABLE    = 1,
                    SQL_NOT_NULL = 2,
                    SQL_COMMENTS = 3
                };

                // Custom SQL Handler
                SqlExtensionHandler getSqlExtensionHandler() const
                {
                    return SqlExtensionHandler(filePosition, 
                                               entityPosition,
                                               relationPosition,
                                               attributePosition);
                }

                // SQL rules
                rule<ScannerT>  ScriptSQL, 
                                CreateDatabase, 
                                Comments, 
                                CreateTable,
                                Authorization,
                                UseDatabase,
                                CreateAttribute, 
                                Type, 
                                Option,
                                CreateConstraint, 
                                PrimaryKey, 
                                ForeignKey,
                                SQLString, 
                                Identifier, 
                                Drop, 
                                Delete,
                                Privilege, 
                                Insert, 
                                Update, 
                                Value, 
                                Where,
                                Expression, 
                                CommentSymbol;

                // SQL grammar
                definition(SimpleSQLParser const& me) 
                {    
                    ScriptSQL = 
                        *( CreateDatabase   |
                           CreateTable      | 
                           Authorization    | 
                           UseDatabase      | 
                           Drop             | 
                           Delete           | 
                           Insert           | 
                           Update           | 
                           Privilege        | 
                           Comments ) 
                         >> end_p ;
                    
                    CreateDatabase = 
                        as_lower_d["create database"] >> Identifier >> ch_p(';') ;

                    UseDatabase = 
                        as_lower_d["use"] >> Identifier ;

                    CommentSymbol = 
                        str_p("--") ;

                    Comments = 
                        CommentSymbol >> lexeme_d[(*(anychar_p - eol_p))]   [getMemoAppendHandler(workspace, SQL_COMMENTS)];

                    CreateTable = 
                        as_lower_d["create"] >> !(as_lower_d["virtual"]) >> as_lower_d["table"] 
                        >> Identifier                                       [getFileCreationOrModificationHandler()]
                                                                            [getEntityCreationOrModificationHandler()]
                                                                            [getMemoHandler(entity, SQL_TABLE)]
                                                                            [getMemoExecutionAndRemoveHandler(workspace, SQL_COMMENTS, getEntityCommentHandler())]
                        >> !(as_lower_d["using"] >> Identifier              [getSqlExtensionHandler()]) 
                        >> ch_p('(')
                        >> *(CreateConstraint | CreateAttribute | Comments) 
                        >> ch_p(')') >> ch_p(';') ;

                    Authorization = 
                        as_lower_d["grant"] >> Identifier 
                        >> as_lower_d["on"] >> Identifier >> '.' >> (Identifier | '*') 
                        >> as_lower_d["to"] >> Identifier >> !('@' >> Identifier)
                        >> as_lower_d["identified by"] >> SQLString >> ch_p(';') ;

                    CreateAttribute = 
                        Identifier                                          [getAttributeCreationOrModificationHandler()]
                                                                            [getMemoExecutionAndRemoveHandler(workspace, SQL_COMMENTS, getAttributeCommentHandler())]
                        >> Type >> *Option >> !ch_p(',');
                    
                    Type = 
                        (as_lower_d["varchar"] >> '(' >>  uint_p >> ')')    [getAttributeTypeHandler(ATTR_STRING)] | 
                        (as_lower_d["numeric"] >> '(' >>  uint_p >> ')')    [getAttributeTypeHandler(ATTR_DOUBLE)] | 
                        (as_lower_d["integer"])                             [getAttributeTypeHandler(ATTR_INT64)]  |
                        (as_lower_d["tinyint"])                             [getAttributeTypeHandler(ATTR_SBYTE)]  |
                        (as_lower_d["smallint"])                            [getAttributeTypeHandler(ATTR_INT16)]  | 
                        (as_lower_d["mediumint"])                           [getAttributeTypeHandler(ATTR_INT32)]  | 
                        (as_lower_d["int"])                                 [getAttributeTypeHandler(ATTR_INT)]    |
                        (as_lower_d["bigint"])                              [getAttributeTypeHandler(ATTR_INT64)]  |
                        (as_lower_d["text"])                                [getAttributeTypeHandler(ATTR_TEXT)]   |
                        (as_lower_d["date"])                                [getAttributeTypeHandler(ATTR_DATE)]   |
                        (as_lower_d["time"])                                [getAttributeTypeHandler(ATTR_TIME)]   |
                        (as_lower_d["float"] >> '(' >>  uint_p >> ')')      [getAttributeTypeHandler(ATTR_DOUBLE)] |
                        (as_lower_d["blob"])                                [getAttributeTypeHandler(ATTR_BINARY)];

                    Option = 
                        (as_lower_d["not null"])                            [getMemoHandler(attribute, SQL_NOT_NULL)] | 
                         as_lower_d["auto_increment"]                       [getAttributeModifierHandler(ATTR_AUTO)]  | 
                         as_lower_d["unique"] ;

                    CreateConstraint = 
                        (PrimaryKey | ForeignKey) >> !ch_p(',') ;

                    PrimaryKey = 
                        as_lower_d["constraint"] >> Identifier >> as_lower_d["primary key"] 
                        >> '('
                        >> *(Identifier                                     [getAttributeModificationHandler()]
                                                                            [getAttributeModifierHandler(ATTR_ID)]
                                                                            [getMemoHandler(attribute, SQL_NOT_NULL)]
                        >> !ch_p(',')) >> ')' ;

                    ForeignKey = 
                        as_lower_d["constraint"] >> Identifier              [getRelationCreationOrModificationHandler()]
                                                                            [getMemoExecutionAndRemoveHandler(workspace, SQL_COMMENTS, getRelationCommentHandler())]            
                        >> as_lower_d["foreign key"] 
                        >> eps_p                                            [getMemoExecutionHandler(entity, SQL_TABLE, getRelationTargetHandler())]
                        >> '(' 
                        >> Identifier                                       [getAttributeModificationHandler()]
                                                                            [getAttributeModifierHandler(ATTR_REF)]
                                                                            [getRelationTargetRefHandler()]
                                                                            [getMemoExecutionHandler(attribute, SQL_NOT_NULL, getRelationMultiplicityHandler(RELATION_ONE), getRelationMultiplicityHandler(RELATION_ZERO_ONE))] 
                        >> ')' 
                        >> as_lower_d["references"] 
                        >> Identifier                                       [getRelationSourceHandler()] 
                        >> '(' 
                        >> Identifier                                       [getRelationSourceRefHandler()] 
                        >> ')' ;

                    SQLString = 
                        ('\'' >> lexeme_d[(*(anychar_p - ch_p('\'')))] >> '\'') | 
                        ('\"' >> lexeme_d[(*(anychar_p - ch_p('\"')))] >> '\"') ;

                    Identifier = 
                        lexeme_d[(+(alnum_p | ch_p('_')))] ;

                    Drop = 
                        as_lower_d["drop"] 
                        >> (as_lower_d["table"] | as_lower_d["database"]) 
                        >> Identifier >> ch_p(';') ;

                    Delete = 
                        as_lower_d["delete from"] >> Identifier >> !Where >> ';' ;

                    Insert = 
                        as_lower_d["insert into"] >> Identifier >> '(' >> *(Identifier >> !ch_p(',')) >> ')' 
                        >> as_lower_d["values"] >> '(' >> *(Value >> !ch_p(',')) >> ')' >> ch_p(';') ;

                    Update = 
                        as_lower_d["update"] >> Identifier >> as_lower_d["set"] >> +Expression >> !Where >> ';' ;

                    Privilege = 
                        as_lower_d["flush privileges"] >> ch_p(';') ;

                    Where = 
                        as_lower_d["where"] >> +Expression ;

                    Expression = 
                        Identifier >> '=' >> Value >> !ch_p(',') ;

                    Value = 
                        real_p | SQLString ;
                }

                rule<ScannerT> const& start() const { return ScriptSQL; }
            };
        };
    
    }

}

#endif // _SIMPLE_SQL_PARSER_HPP_
