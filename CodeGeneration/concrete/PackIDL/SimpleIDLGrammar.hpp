#ifndef _SIMPLE_IDL_GRAMMAR_HPP_
#define _SIMPLE_IDL_GRAMMAR_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include "SimpleIDLStructure.hpp"

namespace sidl
{

    namespace qi = boost::spirit::qi;
    namespace standard_wide = boost::spirit::standard_wide;

    struct member_modifier_
    : qi::symbols<char, member_modifier_t>
    {
        member_modifier_()
        {
            add
                ("readonly", IDL_MEMBER_READONLY)
                ("static",   IDL_MEMBER_STATIC)
            ;
        }
    } member_modifier;

    struct arg_modifier_ 
    : qi::symbols<char, parameter_modifier_t>
    {
        arg_modifier_()
        {
            add
                ("in",      IDL_ARG_IN)
                ("out",     IDL_ARG_OUT)
                ("inout",   IDL_ARG_INOUT)
            ;
        }
    } arg_modifier;

    struct type_base_ 
    : qi::symbols<char, dsg::type_t>
    {
        type_base_()
        {
            add
                ("boolean",              dsg::ATTR_BOOLEAN)
                ("byte",                 dsg::ATTR_SBYTE)
                ("unsigned byte",        dsg::ATTR_BYTE)
                ("char",                 dsg::ATTR_CHAR)
                ("wchar",                dsg::ATTR_WIDECHAR)
                ("achar",                dsg::ATTR_ANSICHAR)
                ("int",                  dsg::ATTR_INT)
                ("unsigned int",         dsg::ATTR_UINT)
                ("short",                dsg::ATTR_INT16)
                ("unsigned short",       dsg::ATTR_UINT16)
                ("long",                 dsg::ATTR_INT32)
                ("unsigned long",        dsg::ATTR_UINT32)
                ("long long",            dsg::ATTR_INT64)
                ("unsigned long long",   dsg::ATTR_UINT64)
                ("float",                dsg::ATTR_SINGLE)
                ("double",               dsg::ATTR_DOUBLE)
                ("string",               dsg::ATTR_STRING)
                ("wstring",              dsg::ATTR_WIDESTRING)
                ("astring",              dsg::ATTR_ANSISTRING)
                ("date",                 dsg::ATTR_DATE)
                ("any",                  dsg::ATTR_ANY)
            ;
        }
    } type_base;

    struct type_void_
    : qi::symbols<char, void_t>
    {
        type_void_()
        {
            add
                ("void",            IDL_VOID)
            ;
        }
    } type_void;

    template <typename Iterator>
    struct simple_idl_grammar
    : qi::grammar<Iterator, idl_file(), standard_wide::space_type>
    {
        simple_idl_grammar()
        : simple_idl_grammar::base_type(file)
        {
            using qi::lexeme;
            using qi::eol;
            using qi::omit;
            using qi::lit;
            using standard_wide::char_;
            using standard_wide::string;
            using standard_wide::alnum;
            using standard_wide::alpha;
            using standard_wide::space;

            comments %=
                    *(lexeme[omit[lit("//")] >> *(char_ - eol) >> eol])
            ;

            identifier %=
                    lexeme[(alpha | char_('_')) >> *(alnum | char_('_'))]
            ;
			
			type %=
                    type_base | identifier
			;

            attribute %=
                    comments
                >>  *member_modifier
                >>  "attribute"
                >>  type
                >>  identifier
                >>  -('[' >> type_base >> ']')
                >>  -('=' >> lexeme[*(char_ - ';')])
                >> ';'
            ;

            parameter %=
                    arg_modifier
                >>  type
                >>  -char_('*')
                >>  identifier
                >>  -(string("[]"))
            ;

            method %=
                    comments
                >>  *member_modifier
                >>  prototype
            ;

            event_ %=
                    comments
                >>  *member_modifier
                >>  "event"
                >>  prototype
            ;

            prototype %=
                    (type_void | type)
                >>  identifier
                >>  '('
                >>  -(parameter % ',')
                >>  ");"
            ;

            base %=
                    ':' >> identifier
            ;

            interface_ %=
                    comments
                >>  "interface"
                >>  identifier
                >>  -base
                >>  '{'
                >>  *(attribute | method | event_)
                >>  '}'
            ;

            package %=
                    comments
                >>  "package"
                >>  identifier
                >>  '{'
                >>  *(package | interface_ | enum_)
                >>  '}'
            ;

            keyword %=
                    comments
                >>  identifier
                >>  -('=' >> lexeme[*(char_ - (space | ',' | '}'))])
            ;

            enum_ %=
                    comments
                >>  "enum"
                >>  identifier
                >>  '{'
                >>  (keyword % ',')
                >>  '}'
            ;

            file %=
                    *(package | interface_ | enum_)
            ;
        }

        qi::rule<Iterator, idl_file(),      standard_wide::space_type> file;
        qi::rule<Iterator, idl_enum(),      standard_wide::space_type> enum_;
        qi::rule<Iterator, idl_keyword(),   standard_wide::space_type> keyword;
        qi::rule<Iterator, idl_package(),   standard_wide::space_type> package;
        qi::rule<Iterator, idl_interface(), standard_wide::space_type> interface_;
        qi::rule<Iterator, idl_base(),      standard_wide::space_type> base;
        qi::rule<Iterator, idl_method(),    standard_wide::space_type> method;
        qi::rule<Iterator, idl_event(),     standard_wide::space_type> event_;
        qi::rule<Iterator, idl_prototype(), standard_wide::space_type> prototype;
        qi::rule<Iterator, idl_parameter(), standard_wide::space_type> parameter;
        qi::rule<Iterator, idl_attribute(), standard_wide::space_type> attribute;
		qi::rule<Iterator, idl_type(),      standard_wide::space_type> type;
        qi::rule<Iterator, std::wstring(),  standard_wide::space_type> identifier;
        qi::rule<Iterator, std::vector<std::wstring>(), standard_wide::space_type> comments;
    };

}

#endif // _SIMPLE_IDL_GRAMMAR_HPP_
