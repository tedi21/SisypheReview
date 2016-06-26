#include "DefinitionHandler.hpp"

using namespace enc;

namespace dsg {

    namespace parser {

        DefinitionHandler::DefinitionHandler()
        : m_logger(&Category::getInstance(LOGNAME)),
          filePosition(new UniFileItr()),
          entityPosition(new UniEntityItr()),
          relationPosition(new UniRelationItr()),
          attributePosition(new UniAttributeItr()),
          table(new dictionnary_t()),
          workspace(),
          file(filePosition),
          entity(filePosition, entityPosition),
          relation(filePosition, relationPosition),
          attribute(filePosition, entityPosition, attributePosition)
        {}
        
        AttributeCreationHandler DefinitionHandler::getAttributeCreationHandler() const
        {
            return AttributeCreationHandler(filePosition, 
                                            entityPosition,
                                            relationPosition,
                                            attributePosition);
        }

        AttributeCreationOrModificationHandler DefinitionHandler::getAttributeCreationOrModificationHandler() const
        {
            return AttributeCreationOrModificationHandler(filePosition,
                                                          entityPosition,
                                                          relationPosition,
                                                          attributePosition);
        }

        AttributeModificationHandler DefinitionHandler::getAttributeModificationHandler() const
        {
            return AttributeModificationHandler(filePosition, 
                                                entityPosition,
                                                relationPosition,
                                                attributePosition);
        }

        AttributeDeletionHandler DefinitionHandler::getAttributeDeletionHandler() const
        {
            return AttributeDeletionHandler(filePosition, 
                                            entityPosition,
                                            relationPosition,
                                            attributePosition);
        }

        AttributeNameHandler DefinitionHandler::getAttributeNameHandler() const
        {
            return AttributeNameHandler(filePosition, 
                                        entityPosition,
                                        relationPosition,
                                        attributePosition);
        }

        AttributeAliasHandler DefinitionHandler::getAttributeAliasHandler() const
        {
            return AttributeAliasHandler(filePosition,
                                         entityPosition,
                                         relationPosition,
                                         attributePosition);
        }

        AttributeTypeHandler DefinitionHandler::getAttributeTypeHandler(type_t type) const
        {
            return AttributeTypeHandler(filePosition, 
                                        entityPosition,
                                        relationPosition,
                                        attributePosition,
                                        type);
        }

        AttributeModifierHandler DefinitionHandler::getAttributeModifierHandler(modifier_t modifier) const
        {
            return AttributeModifierHandler(filePosition, 
                                            entityPosition,
                                            relationPosition,
                                            attributePosition,
                                            modifier);
        }

        AttributeDefaultHandler DefinitionHandler::getAttributeDefaultHandler() const
        {
            return AttributeDefaultHandler(filePosition, 
                                           entityPosition,
                                           relationPosition,
                                           attributePosition);
        }

        AttributeCommentHandler DefinitionHandler::getAttributeCommentHandler() const
        {
            return AttributeCommentHandler(filePosition, 
                                           entityPosition,
                                           relationPosition,
                                           attributePosition);
        }

        EntityCreationHandler DefinitionHandler::getEntityCreationHandler() const
        {
            return EntityCreationHandler(filePosition, 
                                         entityPosition,
                                         relationPosition,
                                         attributePosition);
        }

        EntityCreationOrModificationHandler DefinitionHandler::getEntityCreationOrModificationHandler() const
        {
            return EntityCreationOrModificationHandler(filePosition,
                                                       entityPosition,
                                                       relationPosition,
                                                       attributePosition);
        }

        EntityModificationHandler DefinitionHandler::getEntityModificationHandler() const
        {
            return EntityModificationHandler(filePosition, 
                                             entityPosition,
                                             relationPosition,
                                             attributePosition);
        }

        EntityDeletionHandler DefinitionHandler::getEntityDeletionHandler() const
        {
            return EntityDeletionHandler(filePosition, 
                                         entityPosition,
                                         relationPosition,
                                         attributePosition);
        }

        EntityNameHandler DefinitionHandler::getEntityNameHandler() const
        {
            return EntityNameHandler(filePosition, 
                                     entityPosition,
                                     relationPosition,
                                     attributePosition);
        }

        EntityFunctionNameHandler DefinitionHandler::getEntityFunctionNameHandler() const
        {
            return EntityFunctionNameHandler(filePosition,
                                             entityPosition,
                                             relationPosition,
                                             attributePosition);
        }

        EntityAliasHandler DefinitionHandler::getEntityAliasHandler() const
        {
            return EntityAliasHandler(filePosition,
                                      entityPosition,
                                      relationPosition,
                                      attributePosition);
        }

        EntityClassHandler DefinitionHandler::getEntityClassHandler(class_t category) const
        {
            return EntityClassHandler(filePosition, 
                                      entityPosition,
                                      relationPosition,
                                      attributePosition,
                                      category);
        }

        EntityCommentHandler DefinitionHandler::getEntityCommentHandler() const
        {
            return EntityCommentHandler(filePosition, 
                                        entityPosition,
                                        relationPosition,
                                        attributePosition);
        }

        RelationCreationHandler DefinitionHandler::getRelationCreationHandler() const
        {
            return RelationCreationHandler(filePosition, 
                                           entityPosition,
                                           relationPosition,
                                           attributePosition);
        }

        RelationCreationOrModificationHandler DefinitionHandler::getRelationCreationOrModificationHandler() const
        {
            return RelationCreationOrModificationHandler(filePosition,
                                                         entityPosition,
                                                         relationPosition,
                                                         attributePosition);
        }

        RelationModificationHandler DefinitionHandler::getRelationModificationHandler() const
        {
            return RelationModificationHandler(filePosition, 
                                               entityPosition,
                                               relationPosition,
                                               attributePosition);
        }

        RelationDeletionHandler DefinitionHandler::getRelationDeletionHandler() const
        {
            return RelationDeletionHandler(filePosition, 
                                           entityPosition,
                                           relationPosition,
                                           attributePosition);
        }

        RelationNameHandler DefinitionHandler::getRelationNameHandler() const
        {
            return RelationNameHandler(filePosition, 
                                       entityPosition,
                                       relationPosition,
                                       attributePosition);
        }

        RelationTargetHandler DefinitionHandler::getRelationTargetHandler() const
        {
            return RelationTargetHandler(filePosition, 
                                         entityPosition,
                                         relationPosition,
                                         attributePosition);
        }

        RelationTargetRefHandler DefinitionHandler::getRelationTargetRefHandler() const
        {
            return RelationTargetRefHandler(filePosition, 
                                            entityPosition,
                                            relationPosition,
                                            attributePosition);
        }

        RelationSourceHandler DefinitionHandler::getRelationSourceHandler() const
        {
            return RelationSourceHandler(filePosition, 
                                         entityPosition,
                                         relationPosition,
                                         attributePosition);
        }

        RelationSourceRefHandler DefinitionHandler::getRelationSourceRefHandler() const
        {
            return RelationSourceRefHandler(filePosition, 
                                            entityPosition,
                                            relationPosition,
                                            attributePosition);
        }

        RelationMultiplicityHandler DefinitionHandler::getRelationMultiplicityHandler(multiplicity_t multiplicity) const
        {
            return RelationMultiplicityHandler(filePosition, 
                                               entityPosition,
                                               relationPosition,
                                               attributePosition,
                                               multiplicity);
        }

        RelationAliasHandler DefinitionHandler::getRelationAliasHandler() const
        {
            return RelationAliasHandler(filePosition,
                                        entityPosition,
                                        relationPosition,
                                        attributePosition);
        }

        RelationCommentHandler DefinitionHandler::getRelationCommentHandler() const
        {
            return RelationCommentHandler(filePosition, 
                                          entityPosition,
                                          relationPosition,
                                          attributePosition);
        }

        FileCreationHandler DefinitionHandler::getFileCreationHandler() const
        {
            return FileCreationHandler(filePosition, 
                                       entityPosition,
                                       relationPosition,
                                       attributePosition);
        }

        FileCreationOrModificationHandler DefinitionHandler::getFileCreationOrModificationHandler() const
        {
            return FileCreationOrModificationHandler(filePosition, 
                                                     entityPosition,
                                                     relationPosition,
                                                     attributePosition);
        }

        FileDeletionHandler DefinitionHandler::getFileDeletionHandler() const
        {
            return FileDeletionHandler(filePosition, 
                                       entityPosition,
                                       relationPosition,
                                       attributePosition);
        }

        FileNameHandler DefinitionHandler::getFileNameHandler() const
        {
            return FileNameHandler(filePosition, 
                                   entityPosition,
                                   relationPosition,
                                   attributePosition);
        }

        FileAliasHandler DefinitionHandler::getFileAliasHandler() const
        {
            return FileAliasHandler(filePosition,
                                    entityPosition,
                                    relationPosition,
                                    attributePosition);
        }

        FileCommentHandler DefinitionHandler::getFileCommentHandler() const
        {
            return FileCommentHandler(filePosition, 
                                      entityPosition,
                                      relationPosition,
                                      attributePosition);
        }
        
        WorkspaceNameHandler DefinitionHandler::getWorkspaceNameHandler() const
        {
            return WorkspaceNameHandler();
        }
        
        WorkspaceCommentHandler DefinitionHandler::getWorkspaceCommentHandler() const
        {
            return WorkspaceCommentHandler();
        }
        
        WorkspaceAuthorHandler DefinitionHandler::getWorkspaceAuthorHandler() const
        {
            return WorkspaceAuthorHandler();
        }
        
        WorkspaceBriefHandler DefinitionHandler::getWorkspaceBriefHandler() const
        {
            return WorkspaceBriefHandler();
        }
        
        WorkspaceVersionHandler DefinitionHandler::getWorkspaceVersionHandler() const
        {
            return WorkspaceVersionHandler();
        }
        
        WorkspaceTypeHandler DefinitionHandler::getWorkspaceTypeHandler(project_t type) const
        {
            return WorkspaceTypeHandler(type);
        }
        
        WorkspaceOptionHandler DefinitionHandler::getWorkspaceOptionHandler(int option) const
        {
            return WorkspaceOptionHandler(option);
        }       
    
    }

}
