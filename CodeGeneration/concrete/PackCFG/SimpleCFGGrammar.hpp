#ifndef _SIMPLE_CFG_GRAMMAR_HPP_
#define _SIMPLE_CFG_GRAMMAR_HPP_

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include "SimpleCFGStructure.hpp"

namespace cfg
{
    namespace qi = boost::spirit::qi;
    namespace standard_wide = boost::spirit::standard_wide;

    template <typename Iterator>
    struct simple_cfg_grammar
    : qi::grammar<Iterator, config_file(), standard_wide::space_type>
    {
        simple_cfg_grammar()
        : simple_cfg_grammar::base_type(file)
        {
            using qi::lexeme;
            using qi::eol;
            using qi::omit;
            using qi::raw;
            using qi::skip;
            using qi::lit;
            using standard_wide::char_;
            using standard_wide::alnum;
            using standard_wide::alpha;
            using standard_wide::space;
            using standard_wide::blank;

            comments %=
                    lexeme[omit[+lit("//")] >> *(char_ - eol) >> eol]
            ;

            name %=
                    lexeme[(alpha | char_('_')) >> *(alnum | char_('_'))]
            ;
			
            type %=
                    raw[-standard_wide::string("unsigned") >> name >>  -char_('*')]
			;

            parameter %=
                    type
            ;

            attribute_prototype %=
                    type
                >>  name
                >>  lit("::")
                >>  name
            ;

            function_prototype %=
                    type
                >>  name
                >>  lit("::")
                >>  name
                >>  '('
                >>  -(parameter % ',')
                >>  ')'
            ;

            identifier %=
                  '[' >> (function_prototype | attribute_prototype | lexeme[+(alnum | char_('_') | char_('-'))]) >> ']'
            ;

            branch %=
                    +char_('-') | name
            ;

            element %=
                    branch
                >>  *identifier
            ;

            path %=
                    ((char_('.') | element) % '/')
            ;

            value %=
                    raw[+(char_ - ';')] >> ';'
            ;

            text %=
                   "${"
                >> lexeme[+(char_ - lit("}$"))]
                >> "}$"
            ;

            content %=
                    (text | value)
            ;

            property %=
                    path
                >>  '='
                >>  content
            ;

            line %=
                    (property | path) >> eol
            ;

            file %=
                    *(skip(blank)[omit[comments] | line | eol])
            ;
        }

        qi::rule<Iterator, config_file(),      standard_wide::space_type> file;
        qi::rule<Iterator, config_line(),      standard_wide::blank_type> line;
        qi::rule<Iterator, config_property(),  standard_wide::blank_type> property;
        qi::rule<Iterator, config_path(),      standard_wide::blank_type> path;
        qi::rule<Iterator, config_content(),   standard_wide::blank_type> content;
        qi::rule<Iterator, config_value(),     standard_wide::blank_type> value;
        qi::rule<Iterator, config_text(),      standard_wide::blank_type> text;
        qi::rule<Iterator, config_element(),   standard_wide::blank_type> element;
        qi::rule<Iterator, config_branch(),    standard_wide::blank_type> branch;
        qi::rule<Iterator, config_identifier(),standard_wide::blank_type> identifier;
        qi::rule<Iterator, config_attribute(), standard_wide::blank_type> attribute_prototype;
        qi::rule<Iterator, config_function(),  standard_wide::blank_type> function_prototype;
        qi::rule<Iterator, fct_parameter(),    standard_wide::blank_type> parameter;
        qi::rule<Iterator, std::wstring(),     standard_wide::blank_type> type;
        qi::rule<Iterator, std::wstring(),     standard_wide::blank_type> name;
        qi::rule<Iterator, std::vector<std::wstring>(), standard_wide::blank_type> comments;
    };

}

#endif // _SIMPLE_CFG_GRAMMAR_HPP_
