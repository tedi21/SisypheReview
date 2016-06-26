#ifndef _ETAT_HANDLER_HPP_
#define _ETAT_HANDLER_HPP_

#include <boost/shared_ptr.hpp>
#include "CoreTypes.hpp"
#include "PackExport.hpp"
#include "DataModel.hpp"
#include "GeneratorHandlers.hpp"
#include "GeneratorTypes.hpp"

using namespace log4cpp;
using namespace boost;
using namespace gen;

namespace dsg {

    namespace generator {

        class PACK_API EtatHandler 
		{
        private :
        //////////////////////////////////////////////////////
        // Data member declaration
        //////////////////////////////////////////////////////
        private :
            Category* m_logger;    
            
        protected :
        //////////////////////////////////////////////////////
        // Protected Data declaration
        //////////////////////////////////////////////////////
            file_limit file0;
            file_limit fileN;

            ent_limit ent0;
            ent_limit entN;

            rel_limit rel0;
            rel_limit relN;

            attr_limit attr0;
            attr_limit attrN;
            
        public :
            EtatHandler();

            //////////////////////////////////////////////////////
            // Public Method declaration
            ////////////////////////////////////////////////////// 
            AttributeNameHandler             getAttributeNameHandler(name_kind_t alias) const;
            HasAttributeAliasHandler         getHasAttributeAliasHandler() const;
            IsAttributeTypeHandler           getIsAttributeTypeHandler(type_t type) const;
            IsAttributeModifierHandler       getIsAttributeModifierHandler(unsigned int modifier) const;
            HasAttributeDefaultHandler       getHasAttributeDefaultHandler() const;
            AttributeDefaultHandler          getAttributeDefaultHandler() const;
            HasAttributeCommentHandler       getHasAttributeCommentHandler() const;
            AttributeCommentHandler          getAttributeCommentHandler() const;
            
            EntityNameHandler                getEntityNameHandler(name_kind_t alias) const;
            HasEntityAliasHandler            getHasEntityAliasHandler() const;
            HasEntityFunctionNameHandler     getHasEntityFunctionNameHandler() const;
            EntityFunctionNameHandler        getEntityFunctionNameHandler(name_kind_t alias) const;
            IsEntityClassHandler             getIsEntityClassHandler(class_t category) const;
            HasEntityCommentHandler          getHasEntityCommentHandler() const;
            EntityCommentHandler             getEntityCommentHandler() const;
           
            RelationNameHandler              getRelationNameHandler(name_kind_t alias) const;
            HasRelationAliasHandler          getHasRelationAliasHandler() const;
            RelationTargetHandler            getRelationTargetHandler(name_kind_t alias) const;
            HasRelationTargetAliasHandler    getHasRelationTargetAliasHandler() const;
            RelationTargetRefHandler         getRelationTargetRefHandler(name_kind_t alias) const;
            HasRelationTargetRefAliasHandler getHasRelationTargetRefAliasHandler() const;
            RelationSourceHandler            getRelationSourceHandler(name_kind_t alias) const;
            HasRelationSourceAliasHandler    getHasRelationSourceAliasHandler() const;
            RelationSourceRefHandler         getRelationSourceRefHandler(name_kind_t alias) const;
            HasRelationSourceRefAliasHandler getHasRelationSourceRefAliasHandler() const;
            IsRelationMultiplicityHandler    getIsRelationMultiplicityHandler(multiplicity_t multiplicity) const;
            HasRelationCommentHandler        getHasRelationCommentHandler() const;
            RelationCommentHandler           getRelationCommentHandler() const;

            ContentDataHandler               getContentDataHandler() const;
          
            FileNameHandler                  getFileNameHandler(name_kind_t alias) const;
            HasFileAliasHandler              getHasFileAliasHandler() const;
            HasFileCommentHandler            getHasFileCommentHandler() const;
            FileCommentHandler               getFileCommentHandler() const;

            WorkspaceNameHandler             getWorkspaceNameHandler() const;
            WorkspaceCommentHandler          getWorkspaceCommentHandler() const;
            WorkspaceAuthorHandler           getWorkspaceAuthorHandler() const;
            WorkspaceBriefHandler            getWorkspaceBriefHandler() const;
            WorkspaceVersionHandler          getWorkspaceVersionHandler() const;
            IsWorkspaceTypeHandler           getIsWorkspaceTypeHandler(project_t type) const;
            IsWorkspaceOptionHandler         getIsWorkspaceOptionHandler(int option) const;
            
            DateHandler                      getDateHandler(const char * frmt = "dd-mm-yyyy") const;
            UuidHandler                      getUuidHandler() const;

            limits<attr_relation_limit>      relationsByAttr(int filter) const;
            limits<ent_relation_limit>       relationsByEnt(int filter) const;
            limits<rel_entity_limit>         entitiesByRel(int filter) const;
            limits<cnt_limit>                contentByType(const UniString& type) const;
            limits<ent_content_limit>        contentByEnt(const UniString& type) const;
            limits<attr_content_limit>       contentByAttr(const UniString& type) const;
		};
       
    }
}

#endif // _ETAT_HANDLER_HPP_
