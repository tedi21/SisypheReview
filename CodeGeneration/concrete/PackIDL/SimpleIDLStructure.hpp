#ifndef _SIMPLE_IDL_STRUCTURE_HPP_
#define _SIMPLE_IDL_STRUCTURE_HPP_

#include <vector>
#include <string>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include "CoreTypes.hpp"

namespace sidl
{
    enum member_modifier_t
    {
        IDL_MEMBER_READONLY,
        IDL_MEMBER_STATIC,
    };

    enum void_t
    {
        IDL_VOID,
    };

    typedef boost::variant<dsg::type_t,std::wstring> idl_type;

    struct idl_attribute
    {
        std::vector<std::wstring> comments;
        std::vector<member_modifier_t> modifiers;
        idl_type                  type;
        std::wstring              name;
        boost::optional<dsg::type_t>  index;
        boost::optional<std::wstring> value;
    };

    enum parameter_modifier_t
    {
        IDL_ARG_IN,
        IDL_ARG_OUT,
        IDL_ARG_INOUT
    };

    struct idl_parameter
    {
        parameter_modifier_t modifier;
        idl_type             type;
        boost::optional<wchar_t> pointer;
        std::wstring         name;
        boost::optional<std::wstring> array;
    };

    typedef boost::variant<void_t,idl_type> idl_return;

    struct idl_prototype
    {
        idl_return                 return_type;
        std::wstring               name;
        std::vector<idl_parameter> parameters;
    };

    struct idl_method
    {
        std::vector<std::wstring>           comments;
        std::vector<member_modifier_t>      modifiers;
        idl_prototype                       prototype;
    };

    struct idl_event
    {
        std::vector<std::wstring>           comments;
        std::vector<member_modifier_t>      modifiers;
        idl_prototype                       prototype;
    };

    typedef boost::variant<idl_attribute,idl_method,idl_event> idl_member;

    typedef boost::optional<std::wstring> idl_base;

    struct idl_interface
    {
        std::vector<std::wstring>  comments;
        std::wstring               name;
        idl_base                   base;
        std::vector<idl_member>    members;
    };

    struct idl_keyword
    {
        std::vector<std::wstring>  comments;
        std::wstring               name;
        boost::optional<std::wstring> value;
    };

    struct idl_enum
    {
        std::vector<std::wstring>  comments;
        std::wstring               name;
        std::vector<idl_keyword>   keywords;
    };

    struct idl_package;

    typedef boost::variant<idl_interface,idl_enum,idl_package> idl_struct;

    struct idl_package
    {
        std::vector<std::wstring>  comments;
        std::wstring               name;
        std::vector<idl_struct>    structs;
    };

    typedef std::vector<idl_struct> idl_file;

}

#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
    sidl::idl_attribute,
    (std::vector<std::wstring>,  comments)
    (std::vector<sidl::member_modifier_t>, modifiers)
    (sidl::idl_type,             type)
    (std::wstring,               name)
    (boost::optional<dsg::type_t>,  index)
    (boost::optional<std::wstring>, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    sidl::idl_parameter,
    (sidl::parameter_modifier_t, modifier)
    (sidl::idl_type,             type)
    (boost::optional<wchar_t>,   pointer)
    (std::wstring,               name)
    (boost::optional<std::wstring>,  array)
)

BOOST_FUSION_ADAPT_STRUCT(
    sidl::idl_event,
    (std::vector<std::wstring>,              comments)
    (std::vector<sidl::member_modifier_t>,   modifiers)
    (sidl::idl_prototype,                    prototype)
)

BOOST_FUSION_ADAPT_STRUCT(
    sidl::idl_method,
    (std::vector<std::wstring>,              comments)
    (std::vector<sidl::member_modifier_t>,   modifiers)
    (sidl::idl_prototype,                    prototype)
)

BOOST_FUSION_ADAPT_STRUCT(
    sidl::idl_prototype,
    (sidl::idl_return,                 return_type)
    (std::wstring,                     name)
    (std::vector<sidl::idl_parameter>, parameters)
)

BOOST_FUSION_ADAPT_STRUCT(
    sidl::idl_interface,
    (std::vector<std::wstring>,        comments)
    (std::wstring,                     name)
    (sidl::idl_base,                   base)
    (std::vector<sidl::idl_member>,    members)
)

BOOST_FUSION_ADAPT_STRUCT(
    sidl::idl_package,
    (std::vector<std::wstring>,        comments)
    (std::wstring,                     name)
    (std::vector<sidl::idl_struct>,    structs)
)

BOOST_FUSION_ADAPT_STRUCT(
    sidl::idl_keyword,
    (std::vector<std::wstring>,        comments)
    (std::wstring,                     name)
    (boost::optional<std::wstring>,    value)
)

BOOST_FUSION_ADAPT_STRUCT(
    sidl::idl_enum,
    (std::vector<std::wstring>,        comments)
    (std::wstring,                     name)
    (std::vector<sidl::idl_keyword>,   keywords)
)

#endif // _SIMPLE_IDL_STRUCTURE_HPP_
