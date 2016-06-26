#ifndef _DEFINITION_HANDLER_HPP_
#define _DEFINITION_HANDLER_HPP_

#include <boost/shared_ptr.hpp>
#include "CoreTypes.hpp"
#include "PackExport.hpp"
#include "DataModel.hpp"
#include "ParserHandlers.hpp"
#include "ParserTypes.hpp"

using namespace log4cpp;
using namespace boost;
using namespace std;

namespace dsg {

    namespace parser {

        class PACK_API DefinitionHandler 
        {
        //////////////////////////////////////////////////////
        // Data member declaration
        //////////////////////////////////////////////////////
        private :
            Category* m_logger;

        //////////////////////////////////////////////////////
        // Shared Data declaration
        //////////////////////////////////////////////////////
        protected :
            shared_ptr<UniFileItr>            filePosition;
            shared_ptr<UniEntityItr>          entityPosition;
            shared_ptr<UniRelationItr>        relationPosition;
            shared_ptr<UniAttributeItr>       attributePosition;

            dictionnary_ptr_t                 table;
            WorkspaceIndexor                  workspace;
            FileIndexor                       file;
            EntityIndexor                     entity;
            RelationIndexor                   relation;
            AttributeIndexor                  attribute;

        public :
            DefinitionHandler();

        //////////////////////////////////////////////////////
        // Public Method declaration
        //////////////////////////////////////////////////////
            template <class IndexorT>
            MemoHandler<IndexorT>                      getMemoHandler(const IndexorT& indexor, short key) const;
            template <class IndexorT>
            MemoAppendHandler<IndexorT>                getMemoAppendHandler(const IndexorT& indexor, short key) const;
            template <class IndexorT, class F1>
            MemoExecutionHandler<IndexorT,F1>          getMemoExecutionHandler(const IndexorT& indexor, short key, const F1& handlerA) const;
            template <class IndexorT, class F1, class F2>
            MemoExecutionHandler2<IndexorT,F1,F2>      getMemoExecutionHandler(const IndexorT& indexor, short key, const F1& handlerA, const F2& handlerB) const;
            template <class IndexorT, class F1>
            MemoExecutionAndRemoveHandler<IndexorT,F1> getMemoExecutionAndRemoveHandler(const IndexorT& indexor, short key, const F1& handlerA) const;
            
            AttributeCreationHandler               getAttributeCreationHandler() const;
            AttributeCreationOrModificationHandler getAttributeCreationOrModificationHandler() const;
            AttributeModificationHandler    getAttributeModificationHandler() const;
            AttributeDeletionHandler        getAttributeDeletionHandler() const;
            AttributeNameHandler            getAttributeNameHandler() const;
            AttributeAliasHandler           getAttributeAliasHandler() const;
            AttributeTypeHandler            getAttributeTypeHandler(type_t type) const;
            AttributeModifierHandler        getAttributeModifierHandler(modifier_t modifier) const;
            AttributeDefaultHandler         getAttributeDefaultHandler() const;
            AttributeCommentHandler         getAttributeCommentHandler() const;

            EntityCreationHandler               getEntityCreationHandler() const;
            EntityCreationOrModificationHandler getEntityCreationOrModificationHandler() const;
            EntityModificationHandler       getEntityModificationHandler() const;
            EntityDeletionHandler           getEntityDeletionHandler() const;        
            EntityNameHandler               getEntityNameHandler() const;
            EntityFunctionNameHandler       getEntityFunctionNameHandler() const;
            EntityAliasHandler              getEntityAliasHandler() const;
            EntityClassHandler              getEntityClassHandler(class_t category) const;
            EntityCommentHandler            getEntityCommentHandler() const;

            RelationCreationHandler               getRelationCreationHandler() const;
            RelationCreationOrModificationHandler getRelationCreationOrModificationHandler() const;
            RelationModificationHandler     getRelationModificationHandler() const;
            RelationDeletionHandler         getRelationDeletionHandler() const;        
            RelationNameHandler             getRelationNameHandler() const;
            RelationTargetHandler           getRelationTargetHandler() const;
            RelationTargetRefHandler        getRelationTargetRefHandler() const;
            RelationSourceHandler           getRelationSourceHandler() const;
            RelationSourceRefHandler        getRelationSourceRefHandler() const;
            RelationMultiplicityHandler     getRelationMultiplicityHandler(multiplicity_t multiplicity) const;
            RelationCommentHandler          getRelationCommentHandler() const;
            RelationAliasHandler            getRelationAliasHandler() const;

            FileCreationHandler               getFileCreationHandler() const;
            FileCreationOrModificationHandler getFileCreationOrModificationHandler() const;
            FileDeletionHandler             getFileDeletionHandler() const;        
            FileNameHandler                 getFileNameHandler() const;
            FileAliasHandler                getFileAliasHandler() const;
            FileCommentHandler              getFileCommentHandler() const;
            
            WorkspaceNameHandler            getWorkspaceNameHandler() const;
            WorkspaceCommentHandler         getWorkspaceCommentHandler() const;
            WorkspaceAuthorHandler          getWorkspaceAuthorHandler() const;
            WorkspaceBriefHandler           getWorkspaceBriefHandler() const;
            WorkspaceVersionHandler         getWorkspaceVersionHandler() const;
            WorkspaceTypeHandler            getWorkspaceTypeHandler(project_t type) const;
            WorkspaceOptionHandler          getWorkspaceOptionHandler(int option) const;            
        };

        //////////////////////////////////////////////////////
        // Template Method implementation
        //////////////////////////////////////////////////////

        template <class IndexorT>
        MemoHandler<IndexorT> DefinitionHandler::getMemoHandler(const IndexorT& indexor, short key) const
        {
            //m_logger->debugStream() << "getMemoHandler " << key;
            return MemoHandler<IndexorT>(table, indexor, key);
        }

        template <class IndexorT>
        MemoAppendHandler<IndexorT> DefinitionHandler::getMemoAppendHandler(const IndexorT& indexor, short key) const
        {
            //m_logger->debugStream() << "getMemoAppendHandler " << key;
            return MemoAppendHandler<IndexorT>(table, indexor, key);
        }

        template <class IndexorT, class F1>
        MemoExecutionHandler<IndexorT,F1> DefinitionHandler::getMemoExecutionHandler(const IndexorT& indexor, short key, const F1& handlerA) const
        {
            //m_logger->debugStream() << "getMemoExecutionHandler " << key;
            return MemoExecutionHandler<IndexorT,F1>(table, 
                                                     indexor, key,
                                                     handlerA);
        }

        template <class IndexorT, class F1, class F2>
        MemoExecutionHandler2<IndexorT,F1,F2> DefinitionHandler::getMemoExecutionHandler(const IndexorT& indexor, short key, const F1& handlerA, const F2& handlerB) const
        {
            //m_logger->debugStream() << "getMemoExecutionHandler " << key;
            return MemoExecutionHandler2<IndexorT,F1,F2>(table, 
                                                         indexor, key,
                                                         handlerA,
                                                         handlerB);
        }

        template <class IndexorT, class F1>
        MemoExecutionAndRemoveHandler<IndexorT,F1> DefinitionHandler::getMemoExecutionAndRemoveHandler(const IndexorT& indexor, short key, const F1& handlerA) const
        {
            //m_logger->debugStream() << "getMemoExecutionAndRemoveHandler " << key;
            return MemoExecutionAndRemoveHandler<IndexorT,F1>(table, 
                                                              indexor, key,
                                                              handlerA);
        }

    
    }

}

#endif  // _DEFINITION_HANDLER_HPP_
