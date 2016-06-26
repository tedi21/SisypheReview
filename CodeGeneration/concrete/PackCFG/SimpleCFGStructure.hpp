#ifndef _SIMPLE_CFG_STRUCTURE_HPP_
#define _SIMPLE_CFG_STRUCTURE_HPP_

#include <vector>
#include <string>
#include <boost/variant.hpp>
#include <boost/optional.hpp>

namespace cfg
{
    typedef std::wstring fct_parameter;

    struct config_attribute
    {
        std::wstring               type;
        std::wstring               class_name;
        std::wstring               name;
    };

    struct config_function
    {
        std::wstring               return_type;
        std::wstring               class_name;
        std::wstring               name;
        std::vector<fct_parameter> parameters;
    };

    typedef std::wstring config_branch;

    typedef boost::variant<cfg::config_function,cfg::config_attribute,std::wstring> config_identifier;

    struct config_element
    {
        cfg::config_branch branch;
        std::vector<cfg::config_identifier> identifiers;
    };

    typedef wchar_t config_dot;

    typedef boost::variant<config_dot,config_element> config_dot_element;

    typedef std::vector<cfg::config_dot_element> config_path;

    struct config_value
    {
        std::wstring value;
    };

    struct config_text
    {
        std::wstring text;
    };

    typedef boost::variant<config_text,config_value> config_content;

    struct config_property
    {
        cfg::config_path path;
        cfg::config_content content;
    };

    typedef boost::variant<cfg::config_property,cfg::config_path> config_line;

    typedef std::vector<config_line> config_file;
}

#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
    cfg::config_attribute,
    (std::wstring,               type)
    (std::wstring,               class_name)
    (std::wstring,               name)
)

BOOST_FUSION_ADAPT_STRUCT(
    cfg::config_function,
    (std::wstring,               return_type)
    (std::wstring,               class_name)
    (std::wstring,               name)
    (std::vector<cfg::fct_parameter>, parameters)
)

BOOST_FUSION_ADAPT_STRUCT(
    cfg::config_value,
    (std::wstring,               value)
)

BOOST_FUSION_ADAPT_STRUCT(
    cfg::config_text,
    (std::wstring,               text)
)

BOOST_FUSION_ADAPT_STRUCT(
    cfg::config_element,
    (cfg::config_branch,                    branch)
    (std::vector<cfg::config_identifier>,   identifiers)
)

BOOST_FUSION_ADAPT_STRUCT(
    cfg::config_property,
    (cfg::config_path,      path)
    (cfg::config_content,   content)
)

#endif // _SIMPLE_CFG_STRUCTURE_HPP_
