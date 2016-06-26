#include "SimpleIDLHandler.hpp"
#include <boost/foreach.hpp>

using namespace dsg;

namespace sidl
{
    UniFileItr file_at(size_t index)
    {
        return UniDataModel::getInstance()->getWorkspace().beginFiles() + index;
    }

    UniEntityItr entity_at(size_t file_index, size_t entity_index)
    {
        return file_at(file_index)->beginEntities() + entity_index;
    }

    UniAttributeItr attribute_at(size_t file_index, size_t entity_index, size_t attribute)
    {
        return entity_at(file_index, entity_index)->beginAttributes() + attribute;
    }

    UniAttributeItr create_or_modify_attribute(UniEntityItr entity, UniString const& str)
    {
        UniAttributeNameEquality eq(str);
        UniAttributeItr attribute = std::find_if( entity->beginAttributes(), entity->endAttributes(), eq);
        if (attribute == entity->endAttributes())
        {
            attribute = entity->addNewAttribute(str);
        }
        return attribute;
    }

    UniEntityItr create_or_modify_entity(UniFileItr file, UniString const& str)
    {
        UniEntityNameEquality eq(str);
        UniEntityItr entity = std::find_if( file->beginEntities(), file->endEntities(), eq);
        if (entity == file->endEntities())
        {
            entity = file->addNewEntity(str);
        }
        return entity;
    }

    UniRelationItr create_relation(UniFileItr file, UniString const& str)
    {
        return file->addNewRelation(str);
    }

    UniString format_comment(vector<UniString> const& v)
    {
        UniString comments;
        BOOST_FOREACH(UniString const& str, v)
        {
            comments += str + L"\r\n";
        }
        return comments.size()>=2?
                comments.erase(comments.size()-2):
                comments;
    }

    type_handler::type_handler(size_t file, size_t entity, size_t attribute)
    : m_file(file), 
      m_entity(entity),
      m_attribute(attribute)
    {}

    void type_handler::operator()(dsg::type_t type)
    {
        attribute_at(m_file, m_entity, m_attribute)->setType(type);
    }

    void type_handler::operator()(UniString const& type)
    {
        UniFileItr      file      = file_at(m_file);
        UniEntityItr    entity    = entity_at(m_file, m_entity);
        UniAttributeItr attribute = attribute_at(m_file, m_entity, m_attribute);

        attribute->setType(ATTR_UINT64);
        attribute->setModifier(ATTR_REF);

        UniRelationItr relation = create_relation(file, L"R_" + entity->getName() + L"_" + type);
        relation->setTarget(entity->getName());
        relation->setTargetRef(attribute->getName());
        relation->setSource(type);
        relation->setSourceRef(L"Id");
    }

    member_handler::member_handler(size_t file, size_t entity)
    : m_file(file), 
      m_entity(entity)
    {}

    void member_handler::operator()(idl_attribute const& attr)
    {
        UniEntityItr    entity;
        UniAttributeItr attribute;
        UniRelationItr  relation;
        UniFileItr file = file_at(m_file);
        if (!attr.index)
        {
            entity = entity_at(m_file, m_entity);
        }
        else
        {
            UniEntity  source = *entity_at(m_file, m_entity);
            entity = create_or_modify_entity(file, source.getName() + L"_" + attr.name);
            entity->setClass(ENTITY_DATA);
            entity->setComment(format_comment(attr.comments));

            attribute = create_or_modify_attribute(entity, L"Id");
            attribute->setType(*(attr.index));
            attribute->setModifier(ATTR_ID | ATTR_CONST);

            attribute = create_or_modify_attribute(entity, source.getName());
            attribute->setType(ATTR_UINT64);
            attribute->setModifier(ATTR_REF | ATTR_CONTEXTUAL);

            relation = create_relation(file, L"R_" + entity->getName() + L"_" + source.getName());
            relation->setTarget(entity->getName());
            relation->setTargetRef(source.getName());
            relation->setSource(source.getName());
            relation->setSourceRef(L"Id");
        }
        attribute = create_or_modify_attribute(entity, attr.name);
        attribute->setComment(format_comment(attr.comments));

        BOOST_FOREACH(member_modifier_t const& modifier, attr.modifiers)
        {
            switch (modifier)
            {
            case IDL_MEMBER_READONLY :
                attribute->setModifier(ATTR_CONST);
                break;
            case IDL_MEMBER_STATIC :
                attribute->setModifier(ATTR_STATIC);
                break;
            default: break;
            }
        }
        if (attr.value)
        {
            attribute->setDefault(*(attr.value));
        }
        type_handler handler(m_file, entity - file->beginEntities(), attribute - entity->beginAttributes());
        boost::apply_visitor(handler, attr.type);  
    }

    void member_handler::operator()(idl_event const& ev)
    {
        int ev_modifier = ATTR_NORMAL;
        BOOST_FOREACH(member_modifier_t const& modifier, ev.modifiers)
        {
            switch (modifier)
            {
            case IDL_MEMBER_READONLY :
                ev_modifier |= ATTR_CONST;
                break;
            case IDL_MEMBER_STATIC :
                ev_modifier |= ATTR_STATIC;
                break;
            default: break;
            }
        }
        (*this)(ev.prototype, format_comment(ev.comments), (dsg::modifier_t)(ATTR_VIRTUAL | ev_modifier));
    }

    void member_handler::operator()(idl_method const& meth)
    {
        int meth_modifier = ATTR_NORMAL;
        BOOST_FOREACH(member_modifier_t const& modifier, meth.modifiers)
        {
            switch (modifier)
            {
            case IDL_MEMBER_READONLY :
                meth_modifier |= ATTR_CONST;
                break;
            case IDL_MEMBER_STATIC :
                meth_modifier |= ATTR_STATIC;
                break;
            default: break;
            }
        }
        (*this)(meth.prototype, format_comment(meth.comments), (dsg::modifier_t)meth_modifier);
    }

    dsg::UniString decorateTypeName(idl_type const& functionType)
    {
        dsg::UniString typeName = L"void";
        if ( const dsg::type_t* primitiveType = boost::get<const dsg::type_t>( &functionType ) )
        {
            switch (*primitiveType)
            {               
                case ATTR_BOOLEAN     : typeName = L"Boolean";     break;
                case ATTR_SBYTE       : typeName = L"SByte";       break;
                case ATTR_BYTE        : typeName = L"Byte";        break;
                case ATTR_ANSICHAR    : typeName = L"AnsiChar";    break;
                case ATTR_WIDECHAR    : typeName = L"WideChar";    break;
                case ATTR_CHAR        : typeName = L"Char";        break;
                case ATTR_INT16       : typeName = L"Int16";       break;
                case ATTR_UINT16      : typeName = L"UInt16";      break;
                case ATTR_INT32       : typeName = L"Int32";       break;
                case ATTR_UINT32      : typeName = L"UInt32";      break;
                case ATTR_INT64       : typeName = L"Int64";       break;
                case ATTR_UINT64      : typeName = L"UInt64";      break;
                case ATTR_INT         : typeName = L"Int";       break;
                case ATTR_UINT        : typeName = L"UInt";      break;
                case ATTR_SINGLE      : typeName = L"Single";      break;
                case ATTR_DOUBLE      : typeName = L"Double";      break;
                case ATTR_ANSISTRING  : typeName = L"AnsiString";  break;
                case ATTR_WIDESTRING  : typeName = L"WideString";  break;
                case ATTR_STRING      : typeName = L"String";    break;
                case ATTR_TEXT        : typeName = L"Text";        break;
                case ATTR_TIME        : typeName = L"Time";        break;
                case ATTR_DATE        : typeName = L"Date";        break;
                case ATTR_ANY         : typeName = L"Any";         break;
                case ATTR_BINARY      : typeName = L"Binary";      break;
                default               : typeName = L"Unknown";     break;
            }
        }
        else if ( const dsg::UniString* objectType = boost::get<const dsg::UniString>( &functionType ) )
        {
            typeName = *objectType;
        }
        return typeName;
    }

    dsg::UniString decorateFunctionName(dsg::UniString const& className, idl_prototype const& functionPrototype)
    {
        dsg::UniString functionName = className + L":" + functionPrototype.name;
        BOOST_FOREACH(idl_parameter const& parameter, functionPrototype.parameters)
        {
            functionName += L"@" + decorateTypeName(parameter.type);
            if (parameter.pointer)
            {
                functionName += *(parameter.pointer);
            }
        }
        dsg::UniString returnName = L"@void";
        if ( const idl_type* type = boost::get<const idl_type>( &(functionPrototype.return_type) ) )
        {
            returnName = L"@" + decorateTypeName(*type);
        }
        functionName = functionName + returnName;
        return functionName;
    }

    void member_handler::operator()(idl_prototype const& proto, dsg::UniString const& comments, dsg::modifier_t modifier)
    {
        UniRelationItr  relation;
        UniAttributeItr attribute;
        UniEntity  source = *entity_at(m_file, m_entity);
        UniFileItr file   = file_at(m_file);
        UniEntityItr entity = create_or_modify_entity(file, decorateFunctionName(source.getName(), proto));
        entity->setFunctionName(proto.name);
        entity->setClass(ENTITY_FUNCTION);
        entity->setComment(comments);

        size_t entityIndex = entity - file->beginEntities();
        UniString entityName = entity->getName();
        // Id
        attribute = create_or_modify_attribute(entity, L"Id");
        attribute->setType(ATTR_UINT64);
        attribute->setModifier(ATTR_ID | ATTR_CONST);
        // this
        attribute = create_or_modify_attribute(entity, source.getName());
        attribute->setType(ATTR_UINT64);
        attribute->setModifier(ATTR_REF | ATTR_CONTEXTUAL | modifier);
        // return
        if ( const idl_type* type = boost::get<const idl_type>( &(proto.return_type) ) )
        {
            attribute = create_or_modify_attribute(entity, proto.name);
            attribute->setModifier(ATTR_AUTO);
            type_handler handler(m_file, entityIndex, attribute - entity->beginAttributes());
            boost::apply_visitor(handler, *type);
        }
        // Parameter
        BOOST_FOREACH(idl_parameter const& parameter, proto.parameters)
        {
            attribute = create_or_modify_attribute(entity, parameter.name);
            switch (parameter.modifier)
            {
            case IDL_ARG_IN :
                attribute->setModifier(ATTR_CONST);
                break;
            case IDL_ARG_INOUT :
            case IDL_ARG_OUT :
            default:
                break;
            break;
            }
            if (parameter.pointer)
            {
                attribute->setModifier(ATTR_VIRTUAL);
            }
            if (parameter.array)
            {
                attribute->setModifier(ATTR_ARRAY);
            }
            type_handler handler(m_file, entityIndex, attribute - entity->beginAttributes());
            boost::apply_visitor(handler, parameter.type);
        }
        relation = create_relation(file, L"R_" + entityName + L"_" + source.getName());
        relation->setTarget(entityName);
        relation->setTargetRef(source.getName());
        relation->setSource(source.getName());
        relation->setSourceRef(L"Id");
    }

    package_handler::package_handler(idl_package const& pack)
    : m_package(pack)
    {}

    void struct_handler::operator()(idl_interface const& inter)
    {
        UniRelationItr  relation;
        UniAttributeItr attribute;
        UniWorkspace* wrk = &UniDataModel::getInstance()->getWorkspace();
        UniFileItr file   = wrk->openFile(inter.name, false);
        UniEntityItr entity = create_or_modify_entity(file, inter.name);
        entity->setClass(ENTITY_DATA);
        entity->setComment(format_comment(inter.comments));

        attribute = create_or_modify_attribute(entity, L"Id");
        attribute->setType(ATTR_UINT64);
        attribute->setModifier(ATTR_ID | ATTR_CONST);
        if (inter.base)
        {
            attribute = create_or_modify_attribute(entity, L"Base");
            attribute->setType(ATTR_UINT64);
            attribute->setModifier(ATTR_REF | ATTR_BASE);

            relation = create_relation(file, L"R_" + entity->getName() + L"_" + *(inter.base));
            relation->setTarget(entity->getName());
            relation->setTargetRef(L"Base");
            relation->setSource(*(inter.base));
            relation->setSourceRef(L"Id");
        }

        member_handler handler(file - wrk->beginFiles(), entity - file->beginEntities());
        BOOST_FOREACH(idl_member const& member, inter.members)
        {
            boost::apply_visitor(handler, member);
        }
    }

    void struct_handler::operator()(idl_enum const& en)
    {
        UniAttributeItr attribute;
        UniWorkspace* wrk = &UniDataModel::getInstance()->getWorkspace();
        UniFileItr file   = wrk->openFile(en.name, false);
        UniEntityItr entity = create_or_modify_entity(file, en.name);
        entity->setClass(ENTITY_ENUMERATION);
        entity->setComment(format_comment(en.comments));

        attribute = create_or_modify_attribute(entity, L"Id");
        attribute->setType(ATTR_UINT64);
        attribute->setModifier(ATTR_ID | ATTR_CONST);

        BOOST_FOREACH(idl_keyword const& keyword, en.keywords)
        {
            attribute = create_or_modify_attribute(entity, keyword.name);
            attribute->setComment(format_comment(keyword.comments));
            attribute->setModifier(ATTR_STATIC | ATTR_CONST);
            attribute->setType(ATTR_UINT64);
            if (keyword.value)
            {
                attribute->setDefault(*(keyword.value));
            }
        }
    }

    void struct_handler::operator()(idl_package const& pack)
    {
        UniAttributeItr attribute;
        UniWorkspace* wrk = &UniDataModel::getInstance()->getWorkspace();
        UniFileItr file   = wrk->openFile(pack.name, false);
        UniEntityItr entity = create_or_modify_entity(file, pack.name);
        entity->setClass(ENTITY_PACKAGE);
        entity->setComment(format_comment(pack.comments));

        attribute = create_or_modify_attribute(entity, L"Id");
        attribute->setType(ATTR_UINT64);
        attribute->setModifier(ATTR_ID | ATTR_CONST);

        struct_handler handler;
        package_handler pack_handler(pack);
        BOOST_FOREACH(idl_struct const& struc, pack.structs)
        {
            boost::apply_visitor(handler, struc);
            boost::apply_visitor(pack_handler, struc);
        }
    }

    void file_handler::operator()(idl_file const& file)
    {
        struct_handler handler;
        BOOST_FOREACH(idl_struct const& struc, file)
        {
            boost::apply_visitor(handler, struc);
        }
    }

}
