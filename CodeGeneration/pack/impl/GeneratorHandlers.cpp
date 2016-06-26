#include "GeneratorHandlers.hpp"
#include "bebop.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace dsg {

    namespace generator {

        // AttributeNameHandler implementation
        IMPL_MODEL_GEN_MEMBER_HANDLER(AttributeNameHandler, Attribute, name_kind_t, alias, UniString)
        {
            return (i->hasAlias() && m_alias == KIND_ALIAS)? i->getAlias(): i->getName();
        }

        // HasAttributeAliasHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasAttributeAliasHandler, Attribute, bool)
        {
            return i->hasAlias();
        }

        // IsAttributeTypeHandler implementation
        IMPL_MODEL_GEN_ENUM_HANDLER(IsAttributeTypeHandler, Attribute, type_t, type)
        {
            return (i->getType() == m_type);
        }
        
        // IsAttributeModifierHandler implementation
        IMPL_MODEL_GEN_ENUM_HANDLER(IsAttributeModifierHandler, Attribute, unsigned int, modifier)
        {
            return i->isModifier(m_modifier);
        }
        
        // AttributeDefaultHandler implementation
        IMPL_MODEL_GEN_HANDLER(AttributeDefaultHandler, Attribute, UniString)
        {
            return i->getDefault();
        }

        // HasAttributeDefaultHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasAttributeDefaultHandler, Attribute, bool)
        {
            return i->hasDefault();
        }
        
        // AttributeCommentHandler implementation
        IMPL_MODEL_GEN_HANDLER(AttributeCommentHandler, Attribute, UniString)
        {
            return i->getComment();
        }

        // HasAttributeCommentHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasAttributeCommentHandler, Attribute, bool)
        {
            return i->hasComment();
        }

        // EntityNameHandler implementation
        IMPL_MODEL_GEN_MEMBER_HANDLER(EntityNameHandler, Entity, name_kind_t, alias, UniString)
        {
            return (i->hasAlias() && m_alias == KIND_ALIAS)? i->getAlias(): i->getName();
        }

        // HasEntityAliasHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasEntityAliasHandler, Entity, bool)
        {
            return i->hasAlias();
        }

        // EntityFunctionNameHandler implementation
        IMPL_MODEL_GEN_MEMBER_HANDLER(EntityFunctionNameHandler, Entity, name_kind_t, alias, UniString)
        {
            return (i->hasAlias() && m_alias == KIND_ALIAS)? i->getAlias(): i->getFunctionName();
        }

        // HasEntityFunctionNameHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasEntityFunctionNameHandler, Entity, bool)
        {
            return i->hasFunctionName();
        }

        // IsEntityClassHandler implementation
        IMPL_MODEL_GEN_ENUM_HANDLER(IsEntityClassHandler, Entity, class_t, category)
        {
            return (i->getClass() == m_category);
        }
        
        // EntityCommentHandler implementation
        IMPL_MODEL_GEN_HANDLER(EntityCommentHandler, Entity, UniString)
        {
            return i->getComment();
        }

        // HasEntityCommentHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasEntityCommentHandler, Entity, bool)
        {
            return i->hasComment();
        }

        // RelationNameHandler implementation
        IMPL_MODEL_GEN_MEMBER_HANDLER(RelationNameHandler, Relation, name_kind_t, alias, UniString)
        {
            return (i->hasAlias() && m_alias == KIND_ALIAS)? i->getAlias(): i->getName();
        }

        // HasRelationAliasHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasRelationAliasHandler, Relation, bool)
        {
            return i->hasAlias();
        }

        // RelationTargetHandler implementation
        IMPL_MODEL_GEN_MEMBER_HANDLER(RelationTargetHandler, Relation, name_kind_t, alias, UniString)
        {
            UniString target = i->getTarget();
            if (m_alias == KIND_ALIAS)
            {
                UniEntityNameEquality name(i->getTarget());
                UniEntityGroup allEntities;
                UniEntityGroup::const_iterator e =
                        find_if(allEntities.begin(), allEntities.end(), name);
                if (e != allEntities.end() && e->hasAlias())
                {
                    target = e->getAlias();
                }
            }
            return target;
        }

        // HasRelationTargetAliasHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasRelationTargetAliasHandler, Relation, bool)
        {
            bool hasAlias = false;
            UniEntityNameEquality name(i->getTarget());
            UniEntityGroup allEntities;
            UniEntityGroup::const_iterator e =
                    find_if(allEntities.begin(), allEntities.end(), name);
            if (e != allEntities.end() && e->hasAlias())
            {
                hasAlias = e->hasAlias();
            }
            return hasAlias;
        }
        
        // RelationTargetRefHandler implementation
        IMPL_MODEL_GEN_MEMBER_HANDLER(RelationTargetRefHandler, Relation, name_kind_t, alias, UniString)
        {
            UniString targetRef = i->getTargetRef();
            if (m_alias == KIND_ALIAS)
            {
                UniEntityNameEquality entity(i->getTarget());
                UniAttributeNameEquality name(i->getTargetRef());
                UniEntityGroup allEntities;
                UniEntityGroup::const_iterator e =
                        find_if(allEntities.begin(), allEntities.end(), entity);
                if (e != allEntities.end())
                {
                    const_UniAttributeItr a =
                            find_if(e->beginAttributes(), e->endAttributes(), name);
                    if (a != e->endAttributes() && a->hasAlias())
                    {
                        targetRef = a->getAlias();
                    }
                }
            }
            return targetRef;
        }

        // HasRelationTargetRefAliasHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasRelationTargetRefAliasHandler, Relation, bool)
        {
            bool hasAlias = false;
            UniEntityNameEquality entity(i->getTarget());
            UniAttributeNameEquality name(i->getTargetRef());
            UniEntityGroup allEntities;
            UniEntityGroup::const_iterator e =
                    find_if(allEntities.begin(), allEntities.end(), entity);
            if (e != allEntities.end())
            {
                const_UniAttributeItr a =
                        find_if(e->beginAttributes(), e->endAttributes(), name);
                if (a != e->endAttributes() && a->hasAlias())
                {
                    hasAlias = a->hasAlias();
                }
            }
            return hasAlias;
        }
        
        // RelationSourceHandler implementation
        IMPL_MODEL_GEN_MEMBER_HANDLER(RelationSourceHandler, Relation, name_kind_t, alias, UniString)
        {
            UniString source = i->getSource();
            if (m_alias == KIND_ALIAS)
            {
                UniEntityNameEquality name(i->getSource());
                UniEntityGroup allEntities;
                UniEntityGroup::const_iterator e =
                        find_if(allEntities.begin(), allEntities.end(), name);
                if (e != allEntities.end() && e->hasAlias())
                {
                    source = e->getAlias();
                }
            }
            return source;
        }

        // HasRelationSourceAliasHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasRelationSourceAliasHandler, Relation, bool)
        {
            bool hasAlias = false;
            UniEntityNameEquality name(i->getSource());
            UniEntityGroup allEntities;
            UniEntityGroup::const_iterator e =
                    find_if(allEntities.begin(), allEntities.end(), name);
            if (e != allEntities.end() && e->hasAlias())
            {
                hasAlias = e->hasAlias();
            }
            return hasAlias;
        }
        
        // RelationSourceRefHandler implementation
        IMPL_MODEL_GEN_MEMBER_HANDLER(RelationSourceRefHandler, Relation, name_kind_t, alias, UniString)
        {
            UniString sourceRef = i->getSourceRef();
            if (m_alias == KIND_ALIAS)
            {
                UniEntityNameEquality entity(i->getSource());
                UniAttributeNameEquality name(i->getSourceRef());
                UniEntityGroup allEntities;
                UniEntityGroup::const_iterator e =
                        find_if(allEntities.begin(), allEntities.end(), entity);
                if (e != allEntities.end())
                {
                    const_UniAttributeItr a =
                            find_if(e->beginAttributes(), e->endAttributes(), name);
                    if (a != e->endAttributes() && a->hasAlias())
                    {
                        sourceRef = a->getAlias();
                    }
                }
            }
            return sourceRef;
        }

        // HasRelationSourceRefAliasHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasRelationSourceRefAliasHandler, Relation, bool)
        {
            bool hasAlias = false;
            UniEntityNameEquality entity(i->getSource());
            UniAttributeNameEquality name(i->getSourceRef());
            UniEntityGroup allEntities;
            UniEntityGroup::const_iterator e =
                    find_if(allEntities.begin(), allEntities.end(), entity);
            if (e != allEntities.end())
            {
                const_UniAttributeItr a =
                        find_if(e->beginAttributes(), e->endAttributes(), name);
                if (a != e->endAttributes() && a->hasAlias())
                {
                    hasAlias = a->hasAlias();
                }
            }
            return hasAlias;
        }
        
        // IsRelationMultiplicityHandler implementation
        IMPL_MODEL_GEN_ENUM_HANDLER(IsRelationMultiplicityHandler, Relation, multiplicity_t, multiplicity)
        {
            return (i->getMultiplicity() == m_multiplicity);
        }
        
        // RelationCommentHandler implementation
        IMPL_MODEL_GEN_HANDLER(RelationCommentHandler, Relation, UniString)
        {
            return i->getComment();
        }

        // HasRelationCommentHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasRelationCommentHandler, Relation, bool)
        {
            return i->hasComment();
        }

        // ContentDataHandler implementation
        IMPL_MODEL_GEN_HANDLER(ContentDataHandler, Content, UniString)
        {
            UniString data = i->getData();
            boost::algorithm::trim(data);
            return data;
        }

        // FileNameHandler implementation
        IMPL_MODEL_GEN_MEMBER_HANDLER(FileNameHandler, File, name_kind_t, alias, UniString)
        {
            return (i->hasAlias() && m_alias == KIND_ALIAS)? i->getAlias(): i->getName();
        }

        // HasFileAliasHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasFileAliasHandler, File, bool)
        {
            return i->hasAlias();
        }

        // FileCommentHandler implementation
        IMPL_MODEL_GEN_HANDLER(FileCommentHandler, File, UniString)
        {
            return i->getComment();
        }

        // HasFileCommentHandler implementation
        IMPL_MODEL_GEN_HANDLER(HasFileCommentHandler, File, bool)
        {
            return i->hasComment();
        }

        // WorkspaceNameHandler implementation
        IMPL_DEFAULT_GEN_HANDLER(WorkspaceNameHandler, UniString)
        {
            return UniDataModel::getInstance()->getWorkspace()
                        .getName();
        }
        
        // WorkspaceCommentHandler implementation
        IMPL_DEFAULT_GEN_HANDLER(WorkspaceCommentHandler, UniString)
        {
            return UniDataModel::getInstance()->getWorkspace()
                        .getComment();
        }
        
        // WorkspaceAuthorHandler implementation
        IMPL_DEFAULT_GEN_HANDLER(WorkspaceAuthorHandler, UniString)
        {
            return UniDataModel::getInstance()->getWorkspace()
                        .getAuthor();
        }
        
        // WorkspaceBriefHandler implementation
        IMPL_DEFAULT_GEN_HANDLER(WorkspaceBriefHandler, UniString)
        {
            return UniDataModel::getInstance()->getWorkspace()
                        .getBrief();
        }
        
        // WorkspaceVersionHandler implementation
        IMPL_DEFAULT_GEN_HANDLER(WorkspaceVersionHandler, UniString)
        {
            return UniDataModel::getInstance()->getWorkspace()
                        .getVersion();
        }
        
        // IsWorkspaceTypeHandler implementation
        IMPL_DEFAULT_GEN_ENUM_HANDLER(IsWorkspaceTypeHandler, project_t, type)
        {
            return (UniDataModel::getInstance()->getWorkspace()
                        .getType() == m_type);
        }
        
        // IsWorkspaceOptionHandler implementation
        IMPL_DEFAULT_GEN_ENUM_HANDLER(IsWorkspaceOptionHandler, int, option)
        {
            return (UniDataModel::getInstance()->getWorkspace()
                        .isOption(m_option));
        }
        
        // DateHandler implementation
        DateHandler::DateHandler(const char * frmt)
        : m_format(frmt),
          m_logger(&Category::getInstance(LOGNAME))
        {}
    
        UniString DateHandler::operator()
                () const
        {
            struct tm today;
            time_t now;
            string date;

            time(&now);
            today = *localtime(&now);
            date = m_format;

            date = ireplace_all_copy(date,"yyyy",fctr::ToString::parse(today.tm_year + 1900));
            date = ireplace_all_copy(date,"mm",fctr::ToString::parse(today.tm_mon + 1, ios::fixed, 0, 2, '0'));
            date = ireplace_all_copy(date,"dd",fctr::ToString::parse(today.tm_mday, ios::fixed, 0, 2, '0'));

            return encode<ansi,ucs>(date);
        }

        // UuidHandler implementation
        UuidHandler::UuidHandler()
        : m_logger(&Category::getInstance(LOGNAME))
        {}
    
        UniString UuidHandler::operator()
                () const
        {
            boost::uuids::uuid u = boost::uuids::random_generator()();
            std::wstringstream stream;
            stream << u;
            return stream.str();
        }
        
        // FileRange implementation
        gen::range<file_context> FileRange::operator()
                (file_context const& f) const
        {
            return gen::range<file_context>(f.domain().first(), f.domain().end());
        }
        
        // EntityRange implementation
        gen::range<ent_context> EntityRange::operator()
                (const_UniFileItr& f) const
        {
            return gen::range<ent_context>(f->beginEntities(), f->endEntities());
        }
        
        // RelationRange implementation
        gen::range<rel_context> RelationRange::operator()
                (const_UniFileItr& f) const
        {
            return gen::range<rel_context>(f->beginRelations(), f->endRelations());
        }
                
        // AttributeRange implementation
        gen::range<attr_context> AttributeRange::operator()
                (const_UniEntityItr& e) const
        {
            return gen::range<attr_context>(e->beginAttributes(), e->endAttributes());
        }

        //
        RelationByEntityRange::RelationByEntityRange(int filter)
        : m_filter(filter)
        {}

        void RelationByEntityRange::filterAllFiles
                (const_UniEntityItr& e)
        {
			UniRelationGroup allRelations;
            UniString filterEntityName;
			m_relations.clear();
			for ( UniRelationGroup::const_iterator r = allRelations.begin();
				  r != allRelations.end();
				  ++r)
			{
                if ((m_filter&FILTER_SOURCE) == FILTER_SOURCE)
                {
                    filterEntityName = r->getSource();
                }
                else
                {
                    filterEntityName = r->getTarget();
                }
				if (equalNoCase(e->getName().c_str(), filterEntityName.c_str()))
				{
					m_relations.push_back(*r);
				}
			}
        }

        gen::range<rel_context> RelationByEntityRange::operator()
                (const_UniFileItr& f, const_UniEntityItr& e)
        {
            filterAllFiles(e);
            return gen::range<rel_context>(m_relations.begin(), m_relations.end());
        }

        //
        RelationByAttributeRange::RelationByAttributeRange(int filter)
        : m_filter(filter)
        {}

        void RelationByAttributeRange::filterAllFiles
                (const_UniEntityItr& e, const_UniAttributeItr& a)
        {
			UniRelationGroup allRelations;
			m_relations.clear();
			UniString filterEntityName;
			UniString filterAttributeName;
			for ( UniRelationGroup::const_iterator r = allRelations.begin();
				  r != allRelations.end();
				  ++r)
			{
                if ((m_filter&FILTER_SOURCE) == FILTER_SOURCE)
                {
                    filterEntityName = r->getSource();
                    filterAttributeName = r->getSourceRef();
                }
                else
                {
                    filterEntityName = r->getTarget();
                    filterAttributeName = r->getTargetRef();
                }
				if (equalNoCase(e->getName().c_str(), filterEntityName.c_str()) && 
					equalNoCase(a->getName().c_str(), filterAttributeName.c_str()))
				{
					m_relations.push_back(*r);
				}
			}
        }

        gen::range<rel_context> RelationByAttributeRange::operator()
                (const_UniFileItr& f, const_UniEntityItr& e, const_UniAttributeItr& a)
        {
            filterAllFiles(e, a);
            return gen::range<rel_context>(m_relations.begin(), m_relations.end());
        }

        //
        EntityByRelationRange::EntityByRelationRange(int filter)
        : m_filter(filter)
        {}

        void EntityByRelationRange::filterAllFiles
                (const_UniRelationItr& r)
        {
            UniEntityGroup allEntities;
            m_entities.clear();
			UniString filterEntityName;
            UniString filterAttributeName;
            if ((m_filter&FILTER_SOURCE) == FILTER_SOURCE)
            {
                filterEntityName = r->getSource();
                filterAttributeName = r->getSourceRef();
            }
            else
            {
                filterEntityName = r->getTarget();
                filterAttributeName = r->getTargetRef();
            }
			for ( UniEntityGroup::const_iterator e = allEntities.begin();
				  e != allEntities.end();
				  ++e)
			{
                if (equalNoCase(e->getName().c_str(), filterEntityName.c_str()))
                {
                    UniEntity tmp = *e;
                    UniAttributeNameEquality name(filterAttributeName);
                    UniAttributeItr a = find_if(tmp.beginAttributes(), tmp.endAttributes(), name);
                    if (((m_filter&FILTER_CONTEXTUAL) != FILTER_CONTEXTUAL) ||
                        (a != tmp.endAttributes() && a->isModifier(ATTR_CONTEXTUAL)))
                    {
                        if ((m_filter&FILTER_ERASE_REF) == FILTER_ERASE_REF)
                        {
                            if (a != tmp.endAttributes())
                            {
                                tmp.deleteAttribute(a);
                            }
                        }
                        m_entities.push_back(tmp);
                    }
                }
			}
        }

        gen::range<ent_context> EntityByRelationRange::operator()
                (const_UniFileItr& f, const_UniRelationItr& r)
        {
            filterAllFiles(r);
            return gen::range<ent_context>(m_entities.begin(), m_entities.end());
        }

        //
        ContentByTypeRange::ContentByTypeRange(const UniString& type)
        : m_type(type)
        {}

        gen::range<cnt_context> ContentByTypeRange::operator()
                (const_UniFileItr& f)
        {
            m_contents.clear();
            const_UniContentItr i = f->findContent(m_type);
            if (i != f->endContents())
            {
                m_contents.push_back(*i);
            }
            return gen::range<cnt_context>(m_contents.begin(), m_contents.end());
        }

        //
        ContentByEntityRange::ContentByEntityRange(const UniString& type)
        : m_type(type)
        {}

        gen::range<cnt_context> ContentByEntityRange::operator()
                (const_UniFileItr& f, const_UniEntityItr& e)
        {
            m_contents.clear();
            const_UniContentItr i = f->findContent(m_type, e->getName());
            if (i != f->endContents())
            {
                m_contents.push_back(*i);
            }
            return gen::range<cnt_context>(m_contents.begin(), m_contents.end());
        }

        //
        ContentByAttributeRange::ContentByAttributeRange(const UniString& type)
        : m_type(type)
        {}

        gen::range<cnt_context> ContentByAttributeRange::operator()
                (const_UniFileItr& f, const_UniEntityItr& e, const_UniAttributeItr& a)
        {
            m_contents.clear();
            const_UniContentItr i = f->findContent(m_type, e->getName(), a->getName());
            if (i != f->endContents())
            {
                m_contents.push_back(*i);
            }
            return gen::range<cnt_context>(m_contents.begin(), m_contents.end());
        }
    }

}
