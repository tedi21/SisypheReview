#ifndef _SIMPLE_IDL_HANDLER_HPP_
#define _SIMPLE_IDL_HANDLER_HPP_

#include <SimpleIDLStructure.hpp>
#include "CoreTypes.hpp"

namespace sidl
{

    dsg::UniFileItr file_at(size_t index);

    dsg::UniEntityItr entity_at(size_t file_index, size_t entity_index);

    dsg::UniAttributeItr attribute_at(size_t file_index, size_t entity_index, size_t attribute);

    dsg::UniAttributeItr create_or_modify_attribute(dsg::UniEntityItr entity, dsg::UniString const& str);

    dsg::UniEntityItr create_or_modify_entity(dsg::UniFileItr file, dsg::UniString const& str);

    dsg::UniRelationItr create_relation(dsg::UniFileItr file, dsg::UniString const& str);

    struct type_handler : boost::static_visitor<>
    {
        type_handler(size_t file, size_t entity, size_t attr);
        void operator()(dsg::type_t type);
        void operator()(dsg::UniString const& type);

        size_t m_file;
        size_t m_entity;
        size_t m_attribute;
    };

    struct member_handler : boost::static_visitor<>
    {
        member_handler(size_t file, size_t entity);
        void operator()(idl_attribute const& attr);
        void operator()(idl_method const& meth);
        void operator()(idl_event const& ev);
        void operator()(idl_prototype const& proto, dsg::UniString const& comments, dsg::modifier_t modifier = dsg::ATTR_NORMAL);

        size_t m_file;
        size_t m_entity;
    };

    struct package_handler : boost::static_visitor<>
    {
        package_handler(idl_package const& pack);
        template <class T>
        void operator()(T const& src)
        {
            dsg::UniWorkspace* wrk = &dsg::UniDataModel::getInstance()->getWorkspace();
            dsg::UniFileItr file   = wrk->openFile(m_package.name, false);
            dsg::UniRelationItr  relation;
            relation = create_relation(file, L"R_" + m_package.name + L"_" + src.name);
            relation->setTarget(m_package.name);
            relation->setTargetRef(L"Id");
            relation->setSource(src.name);
            relation->setSourceRef(L"Id");
        }

        idl_package m_package;
    };

    struct struct_handler : boost::static_visitor<>
    {
        void operator()(idl_package const& pack);
        void operator()(idl_interface const& inter);
        void operator()(idl_enum const& en);
    };

    struct file_handler
    {
        void operator()(idl_file const& file);
    };

}

#endif // _SIMPLE_IDL_HANDLER_HPP_
