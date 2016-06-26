#include "EtatHandler.hpp"

namespace dsg {

    namespace generator {
    
        EtatHandler::EtatHandler()
        : m_logger(&Category::getInstance(LOGNAME))
        {
            file_limit::factory_t file = file_limit::factory_t();
            file0 = file.make(gen::beg);
            fileN = file.make(gen::end);

            ent_limit::factory_t entity = ent_limit::factory_t();
            ent0 = entity.make(gen::beg);
            entN = entity.make(gen::end);

            rel_limit::factory_t relation = rel_limit::factory_t();
            rel0 = relation.make(gen::beg);
            relN = relation.make(gen::end);

            attr_limit::factory_t attribute = attr_limit::factory_t();
            attr0 = attribute.make(gen::beg);
            attrN = attribute.make(gen::end);
        }

        AttributeNameHandler EtatHandler::getAttributeNameHandler(name_kind_t alias) const
        {
            return AttributeNameHandler(alias);
		}

        HasAttributeAliasHandler EtatHandler::getHasAttributeAliasHandler() const
        {
            return HasAttributeAliasHandler();
        }

        IsAttributeTypeHandler EtatHandler::getIsAttributeTypeHandler(type_t type) const
        {
            return IsAttributeTypeHandler(type);
        }
        
        IsAttributeModifierHandler EtatHandler::getIsAttributeModifierHandler(unsigned int modifier) const
        {
            return IsAttributeModifierHandler(modifier);
        }

        HasAttributeDefaultHandler EtatHandler::getHasAttributeDefaultHandler() const
        {
            return HasAttributeDefaultHandler();
        }
        
        AttributeDefaultHandler EtatHandler::getAttributeDefaultHandler() const
        {
            return AttributeDefaultHandler();
        }
        
        AttributeCommentHandler EtatHandler::getAttributeCommentHandler() const
        {
            return AttributeCommentHandler();
        }

        HasAttributeCommentHandler EtatHandler::getHasAttributeCommentHandler() const
        {
            return HasAttributeCommentHandler();
        }
        
        EntityNameHandler EtatHandler::getEntityNameHandler(name_kind_t alias) const
        {
            return EntityNameHandler(alias);
        }

        EntityFunctionNameHandler EtatHandler::getEntityFunctionNameHandler(name_kind_t alias) const
        {
            return EntityFunctionNameHandler(alias);
        }

        HasEntityAliasHandler EtatHandler::getHasEntityAliasHandler() const
        {
            return HasEntityAliasHandler();
        }

        HasEntityFunctionNameHandler EtatHandler::getHasEntityFunctionNameHandler() const
        {
            return HasEntityFunctionNameHandler();
        }
        
        IsEntityClassHandler EtatHandler::getIsEntityClassHandler(class_t category) const
        {
            return IsEntityClassHandler(category);
        }
        
        EntityCommentHandler EtatHandler::getEntityCommentHandler() const
        {
            return EntityCommentHandler();
        }

        HasEntityCommentHandler EtatHandler::getHasEntityCommentHandler() const
        {
            return HasEntityCommentHandler();
        }
        
        RelationNameHandler EtatHandler::getRelationNameHandler(name_kind_t alias) const
        {
            return RelationNameHandler(alias);
        }

        HasRelationAliasHandler EtatHandler::getHasRelationAliasHandler() const
        {
            return HasRelationAliasHandler();
        }

        RelationTargetHandler EtatHandler::getRelationTargetHandler(name_kind_t alias) const
        {
            return RelationTargetHandler(alias);
        }

        HasRelationTargetAliasHandler EtatHandler::getHasRelationTargetAliasHandler() const
        {
            return HasRelationTargetAliasHandler();
        }
        
        RelationTargetRefHandler EtatHandler::getRelationTargetRefHandler(name_kind_t alias) const
        {
            return RelationTargetRefHandler(alias);
        }

        HasRelationTargetRefAliasHandler EtatHandler::getHasRelationTargetRefAliasHandler() const
        {
            return HasRelationTargetRefAliasHandler();
        }
        
        RelationSourceHandler EtatHandler::getRelationSourceHandler(name_kind_t alias) const
        {
            return RelationSourceHandler(alias);
        }

        HasRelationSourceAliasHandler EtatHandler::getHasRelationSourceAliasHandler() const
        {
            return HasRelationSourceAliasHandler();
        }
        
        RelationSourceRefHandler EtatHandler::getRelationSourceRefHandler(name_kind_t alias) const
        {
            return RelationSourceRefHandler(alias);
        }

        HasRelationSourceRefAliasHandler EtatHandler::getHasRelationSourceRefAliasHandler() const
        {
            return HasRelationSourceRefAliasHandler();
        }
        
        IsRelationMultiplicityHandler EtatHandler::getIsRelationMultiplicityHandler(multiplicity_t multiplicity) const
        {
            return IsRelationMultiplicityHandler(multiplicity);
        }
        
        RelationCommentHandler EtatHandler::getRelationCommentHandler() const
        {
            return RelationCommentHandler();
        }

        HasRelationCommentHandler EtatHandler::getHasRelationCommentHandler() const
        {
            return HasRelationCommentHandler();
        }

        ContentDataHandler EtatHandler::getContentDataHandler() const
        {
            return ContentDataHandler();
        }
        
        FileNameHandler EtatHandler::getFileNameHandler(name_kind_t alias) const
        {
            return FileNameHandler(alias);
        }

        HasFileAliasHandler EtatHandler::getHasFileAliasHandler() const
        {
            return HasFileAliasHandler();
        }

        FileCommentHandler EtatHandler::getFileCommentHandler() const
        {
            return FileCommentHandler();
        }

        HasFileCommentHandler EtatHandler::getHasFileCommentHandler() const
        {
            return HasFileCommentHandler();
        }

        WorkspaceNameHandler EtatHandler::getWorkspaceNameHandler() const
        {
            return WorkspaceNameHandler();
        }

        WorkspaceCommentHandler EtatHandler::getWorkspaceCommentHandler() const
        {
            return WorkspaceCommentHandler();
        }

        WorkspaceAuthorHandler EtatHandler::getWorkspaceAuthorHandler() const
        {
            return WorkspaceAuthorHandler();
        }

        WorkspaceBriefHandler EtatHandler::getWorkspaceBriefHandler() const
        {
            return WorkspaceBriefHandler();
        }

        WorkspaceVersionHandler EtatHandler::getWorkspaceVersionHandler() const
        {
            return WorkspaceVersionHandler();
        }

        IsWorkspaceTypeHandler EtatHandler::getIsWorkspaceTypeHandler(project_t type) const
        {
            return IsWorkspaceTypeHandler(type);
        }

        IsWorkspaceOptionHandler EtatHandler::getIsWorkspaceOptionHandler(int option) const
        {
            return IsWorkspaceOptionHandler(option);
        }

        DateHandler EtatHandler::getDateHandler(const char * frmt) const
        {
            return DateHandler(frmt);
        }

        UuidHandler EtatHandler::getUuidHandler() const
        {
            return UuidHandler();
        }

        limits<attr_relation_limit> EtatHandler::relationsByAttr(int filter) const
        {
            attr_relation_limit::factory_t relation = attr_relation_limit::factory_t(RelationByAttributeRange(filter));
            return limits<attr_relation_limit>(
                relation.make(gen::beg),
                relation.make(gen::end));
        }

        limits<ent_relation_limit> EtatHandler::relationsByEnt(int filter) const
        {
            ent_relation_limit::factory_t relation = ent_relation_limit::factory_t(RelationByEntityRange(filter));
            return limits<ent_relation_limit>(
                relation.make(gen::beg),
                relation.make(gen::end));
        }

        limits<rel_entity_limit> EtatHandler::entitiesByRel(int filter) const
        {
            rel_entity_limit::factory_t entity = rel_entity_limit::factory_t(EntityByRelationRange(filter));
            return limits<rel_entity_limit>(
                entity.make(gen::beg),
                entity.make(gen::end));
        }

        limits<cnt_limit> EtatHandler::contentByType(const UniString& type) const
        {
            cnt_limit::factory_t content = cnt_limit::factory_t(ContentByTypeRange(type));
            return limits<cnt_limit>(
                content.make(gen::beg),
                content.make(gen::end));
        }

        limits<ent_content_limit> EtatHandler::contentByEnt(const UniString& type) const
        {
            ent_content_limit::factory_t content = ent_content_limit::factory_t(ContentByEntityRange(type));
            return limits<ent_content_limit>(
                content.make(gen::beg),
                content.make(gen::end));
        }

        limits<attr_content_limit> EtatHandler::contentByAttr(const UniString& type) const
        {
            attr_content_limit::factory_t content = attr_content_limit::factory_t(ContentByAttributeRange(type));
            return limits<attr_content_limit>(
                content.make(gen::beg),
                content.make(gen::end));
        }

    }

}

