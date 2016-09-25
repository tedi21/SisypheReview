#include "ParserHandlers.hpp"

namespace dsg {

    namespace parser {
        
        WorkspaceIndexor::WorkspaceIndexor()
        : m_logger(&Category::getInstance(LOGNAME))
        {}

        key_t WorkspaceIndexor::getIndex(short key) const
        {
            //m_logger->debugStream() << "WorkspaceIndexor " << key;
            return key_t(1, key);
        }

        FileIndexor::FileIndexor(const boost::shared_ptr<UniFileItr>& filePosition)
        : m_filePosition(filePosition)
        {}

        key_t FileIndexor::getIndex(short key) const
        {
            key_t val;
            val = WorkspaceIndexor::getIndex(key);
            CHECK_MODEL(IS_VALID_FILE, 
                        "FileIndexor : Cannot set index on file, files aren't initialized.")
            {
                val.push_back( (short) ((*m_filePosition) - UniDataModel::getInstance()->getWorkspace().beginFiles()) );
            }
            return val;
        }

        EntityIndexor::EntityIndexor(const boost::shared_ptr<UniFileItr>& filePosition,
                                     const boost::shared_ptr<UniEntityItr>& entityPosition)
        : FileIndexor(filePosition),
          m_entityPosition(entityPosition)
        {}

        key_t EntityIndexor::getIndex(short key) const
        {
            key_t val;
            val = FileIndexor::getIndex(key);
            CHECK_MODEL(IS_VALID_ENTITY, 
                        "EntityIndexor : Cannot set index on entity, entities aren't initialized.")
            {
                val.push_back( (short) ((*m_entityPosition) - (*m_filePosition)->beginEntities()) );
            }
            return val;
        }

        RelationIndexor::RelationIndexor(const boost::shared_ptr<UniFileItr>& filePosition,
                                         const boost::shared_ptr<UniRelationItr>& relationPosition)
        : FileIndexor(filePosition),
          m_relationPosition(relationPosition)
        {}

        key_t RelationIndexor::getIndex(short key) const
        {
            key_t val;
            val = FileIndexor::getIndex(key);
            CHECK_MODEL(IS_VALID_RELATION, 
                        "RelationIndexor : Cannot set index on relation, relations aren't initialized.")
            {
                val.push_back( (short) ((*m_relationPosition) - (*m_filePosition)->beginRelations()) );
            }
            return val;
        }

        AttributeIndexor::AttributeIndexor(const boost::shared_ptr<UniFileItr>& filePosition,
                                           const boost::shared_ptr<UniEntityItr>& entityPosition,
                                           const boost::shared_ptr<UniAttributeItr>& attributePosition)
        : EntityIndexor(filePosition, entityPosition),
          m_attributePosition(attributePosition)
        {}

        key_t AttributeIndexor::getIndex(short key) const
        {
            key_t val;
            val = EntityIndexor::getIndex(key);
            CHECK_MODEL(IS_VALID_ATTRIBUTE, 
                        "AttributeIndexor : Cannot set index on attribute, attributes aren't initialized.")
            {
                val.push_back( (short) ((*m_attributePosition) - (*m_entityPosition)->beginAttributes()) );
            }
            return val;
        }

        // AttributeCreationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(AttributeCreationHandler)
        {
            CHECK_MODEL(IS_VALID_ENTITY && 
                        NULL != m_attributePosition, 
                        "AttributeCreationHandler : Cannot create attribute, entities aren't initialized.")
            {
                (*m_attributePosition) = (*m_entityPosition)
                    ->addNewAttribute(UniString(szStart, szEnd));
            }
        }

        // AttributeCreationOrModificationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(AttributeCreationOrModificationHandler)
        {
            CHECK_MODEL(IS_VALID_ENTITY &&
                        NULL != m_attributePosition,
                        "AttributeCreationOrModificationHandler : Cannot modify attribute, entities aren't initialized.")
            {
                UniAttributeNameEquality eq(UniString(szStart, szEnd));
                UniAttributeItr attribute = std::find_if( (*m_entityPosition)->beginAttributes(),
                                                          (*m_entityPosition)->endAttributes(), eq);
                if (attribute != (*m_entityPosition)->endAttributes())
                {
                    (*m_attributePosition) = attribute;
                }
                else
                {
                    (*m_attributePosition) = (*m_entityPosition)
                        ->addNewAttribute(UniString(szStart, szEnd));
                }
            }
        }

        // AttributeModificationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(AttributeModificationHandler)
        {
            CHECK_MODEL(IS_VALID_ENTITY && 
                        NULL != m_attributePosition, 
                        "AttributeModificationHandler : Cannot modify attribute, entities aren't initialized.")
            {
                UniAttributeNameEquality eq(UniString(szStart, szEnd));
                UniAttributeItr attribute = std::find_if( (*m_entityPosition)->beginAttributes(), 
                                                          (*m_entityPosition)->endAttributes(), eq);
                if (attribute != (*m_entityPosition)->endAttributes())
                {
                    (*m_attributePosition) = attribute;
                }
                else
                {
                    m_logger->errorStream() << "AttributeModificationHandler : attribute named " 
                                            << ansi::string_t(szStart, szEnd)
                                            << " is not found.";
                }
            }
        }

        // AttributeDeletionHandler implementation
        IMPL_MODEL_PARSER_HANDLER(AttributeDeletionHandler)
        {
            CHECK_MODEL(IS_VALID_ENTITY && 
                        NULL != m_attributePosition, 
                        "AttributeDeletionHandler : Cannot delete attribute, entities aren't initialized.")
            {
                (*m_entityPosition)->deleteAttribute((*m_attributePosition));
                (*m_attributePosition) = (*m_entityPosition)->endAttributes();
                if ((*m_entityPosition)->beginAttributes() != (*m_entityPosition)->endAttributes())
                {
                    (*m_attributePosition) = (*m_entityPosition)->endAttributes()-1;
                }
            }
        }

        // AttributeNameHandler implementation
        IMPL_MODEL_PARSER_HANDLER(AttributeNameHandler)
        {
            CHECK_MODEL(IS_VALID_ATTRIBUTE, 
                        "AttributeNameHandler : Cannot rename attribute, attributes aren't initialized.")
            {
                (*m_attributePosition)->setName(UniString(szStart, szEnd));
            }
        }

        // AttributeAliasHandler implementation
        IMPL_MODEL_PARSER_HANDLER(AttributeAliasHandler)
        {
            CHECK_MODEL(IS_VALID_ATTRIBUTE,
                        "AttributeAliasHandler : Cannot set attribute alias, attributes aren't initialized.")
            {
                (*m_attributePosition)->setAlias(UniString(szStart, szEnd));
            }
        }

        // AttributeTypeHandler implementation
        IMPL_MODEL_PARSER_ENUM_HANDLER(AttributeTypeHandler, type_t, type)
        {
            CHECK_MODEL(IS_VALID_ATTRIBUTE, 
                        "AttributeTypeHandler : Cannot set attribute type, attributes aren't initialized.")
            {
                (*m_attributePosition)->setType(m_type);
            }
        }

        // AttributeModifierHandler implementation
        IMPL_MODEL_PARSER_ENUM_HANDLER(AttributeModifierHandler, modifier_t, modifier)
        {
            CHECK_MODEL(IS_VALID_ATTRIBUTE, 
                        "AttributeModifierHandler : Cannot set attribute modifier, attributes aren't initialized.")
            {
                (*m_attributePosition)->setModifier(m_modifier);
            }
        }

        // AttributeDefaultHandler implementation
        IMPL_MODEL_PARSER_HANDLER(AttributeDefaultHandler)
        {
            CHECK_MODEL(IS_VALID_ATTRIBUTE, 
                        "AttributeDefaultHandler : Cannot set attribute default, attributes aren't initialized.")
            {
                (*m_attributePosition)->setDefault(UniString(szStart, szEnd));
            }
        }

        // AttributeCommentHandler implementation
        IMPL_MODEL_PARSER_HANDLER(AttributeCommentHandler)
        {
            CHECK_MODEL(IS_VALID_ATTRIBUTE, 
                        "AttributeCommentHandler : Cannot set attribute comment, attributes aren't initialized.")
            {
                (*m_attributePosition)->setComment(UniString(szStart, szEnd));
            }
        }

        // EntityCreationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(EntityCreationHandler)
        {
            CHECK_MODEL(IS_VALID_FILE && 
                        NULL != m_entityPosition, 
                        "EntityCreationHandler : Cannot create entity, files aren't initialized.")
            {
                (*m_entityPosition) = (*m_filePosition)
                    ->addNewEntity(UniString(szStart, szEnd));
            }
        }

        // EntityCreationOrModificationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(EntityCreationOrModificationHandler)
        {
            CHECK_MODEL(IS_VALID_FILE &&
                        NULL != m_entityPosition,
                        "EntityCreationOrModificationHandler : Cannot modify entity, files aren't initialized.")
            {
                UniEntityNameEquality eq(UniString(szStart, szEnd));
                UniEntityItr entity = std::find_if( (*m_filePosition)->beginEntities(),
                                                    (*m_filePosition)->endEntities(), eq);
                if (entity != (*m_filePosition)->endEntities())
                {
                    (*m_entityPosition) = entity;
                }
                else
                {
                    (*m_entityPosition) = (*m_filePosition)
                        ->addNewEntity(UniString(szStart, szEnd));
                }
            }
        }

        // EntityModificationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(EntityModificationHandler)
        {
            CHECK_MODEL(IS_VALID_FILE && 
                        NULL != m_entityPosition, 
                        "EntityModificationHandler : Cannot modify entity, files aren't initialized.")
            {
                UniEntityNameEquality eq(UniString(szStart, szEnd));
                UniEntityItr entity = std::find_if( (*m_filePosition)->beginEntities(), 
                                                    (*m_filePosition)->endEntities(), eq);
                if (entity != (*m_filePosition)->endEntities())
                {
                    (*m_entityPosition) = entity;
                }
                else
                {
                    m_logger->errorStream() << "EntityModificationHandler : entity named " 
                                            << ansi::string_t(szStart, szEnd)
                                            << " is not found.";
                }
            }
        }

        // EntityDeletionHandler implementation
        IMPL_MODEL_PARSER_HANDLER(EntityDeletionHandler)
        {
            CHECK_MODEL(IS_VALID_FILE && 
                        NULL != m_entityPosition, 
                        "EntityDeletionHandler : Cannot delete entity, files aren't initialized.")
            {
                m_logger->debugStream() << "Delete";
                (*m_filePosition)->deleteEntity((*m_entityPosition));
                (*m_entityPosition) = (*m_filePosition)->endEntities();
                if ((*m_filePosition)->beginEntities() != (*m_filePosition)->endEntities())
                {
                    (*m_entityPosition) = (*m_filePosition)->endEntities()-1;
                }
            }
        }

        // EntityNameHandler implementation
        IMPL_MODEL_PARSER_HANDLER(EntityNameHandler)
        {
            CHECK_MODEL(IS_VALID_ENTITY, 
                        "EntityNameHandler : Cannot rename entity, entities aren't initialized.")
            {
                (*m_entityPosition)->setName(UniString(szStart, szEnd));
            }
        }

        // EntityFunctionNameHandler implementation
        IMPL_MODEL_PARSER_HANDLER(EntityFunctionNameHandler)
        {
            CHECK_MODEL(IS_VALID_ENTITY,
                        "EntityFunctionNameHandler : Cannot set entity functionName, entities aren't initialized.")
            {
                (*m_entityPosition)->setFunctionName(UniString(szStart, szEnd));
            }
        }

        // EntityAliasHandler implementation
        IMPL_MODEL_PARSER_HANDLER(EntityAliasHandler)
        {
            CHECK_MODEL(IS_VALID_ENTITY,
                        "EntityAliasHandler : Cannot set entity alias, entities aren't initialized.")
            {
                (*m_entityPosition)->setAlias(UniString(szStart, szEnd));
            }
        }

        // EntityClassHandler implementation
        IMPL_MODEL_PARSER_ENUM_HANDLER(EntityClassHandler, class_t, category)
        {
            CHECK_MODEL(IS_VALID_ENTITY, 
                        "EntityClassHandler : Cannot set entity class, entities aren't initialized.")
            {
                (*m_entityPosition)->setClass(m_category);
            }
        }

        // EntityCommentHandler implementation
        IMPL_MODEL_PARSER_HANDLER(EntityCommentHandler)
        {
            CHECK_MODEL(IS_VALID_ENTITY, 
                        "EntityCommentHandler : Cannot set entity comment, entities aren't initialized.")
            {
                (*m_entityPosition)->setComment(UniString(szStart, szEnd));
            }
        }

        // RelationCreationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationCreationHandler)
        {
            CHECK_MODEL(IS_VALID_FILE && 
                        NULL != m_relationPosition, 
                        "RelationCreationHandler : Cannot create relation, files aren't initialized.")
            {
                (*m_relationPosition) = (*m_filePosition)
                    ->addNewRelation(UniString(szStart, szEnd));
            }
        }

        // RelationCreationOrModificationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationCreationOrModificationHandler)
        {
            CHECK_MODEL(IS_VALID_FILE &&
                        NULL != m_relationPosition,
                        "RelationCreationOrModificationHandler : Cannot modify relation, files aren't initialized.")
            {
                UniRelationNameEquality eq(UniString(szStart, szEnd));
                UniRelationItr relation = std::find_if( (*m_filePosition)->beginRelations(),
                                                        (*m_filePosition)->endRelations(), eq);
                if (relation != (*m_filePosition)->endRelations())
                {
                    (*m_relationPosition) = relation;
                }
                else
                {
                    (*m_relationPosition) = (*m_filePosition)
                        ->addNewRelation(UniString(szStart, szEnd));
                }
            }
        }

        // RelationModificationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationModificationHandler)
        {
            CHECK_MODEL(IS_VALID_FILE && 
                        NULL != m_relationPosition, 
                        "RelationModificationHandler : Cannot modify relation, files aren't initialized.")
            {
                UniRelationNameEquality eq(UniString(szStart, szEnd));
                UniRelationItr relation = std::find_if( (*m_filePosition)->beginRelations(), 
                                                        (*m_filePosition)->endRelations(), eq);
                if (relation != (*m_filePosition)->endRelations())
                {
                    (*m_relationPosition) = relation;
                }
                else
                {
                    m_logger->errorStream() << "RelationModificationHandler : relation named " 
                                            << ansi::string_t(szStart, szEnd)
                                            << " is not found.";
                }
            }
        }

        // RelationDeletionHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationDeletionHandler)
        {
            CHECK_MODEL(IS_VALID_FILE && 
                        NULL != m_relationPosition, 
                        "RelationDeletionHandler : Cannot delete relation, files aren't initialized.")
            {
                (*m_filePosition)->deleteRelation((*m_relationPosition));
                (*m_relationPosition) = (*m_filePosition)->endRelations();
                if ((*m_filePosition)->beginRelations() != (*m_filePosition)->endRelations())
                {
                    (*m_relationPosition) = (*m_filePosition)->endRelations()-1;
                }
            }
        }

        // RelationNameHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationNameHandler)
        {
            CHECK_MODEL(IS_VALID_RELATION, 
                        "RelationNameHandler : Cannot rename relation, relations aren't initialized.")
            {
                (*m_relationPosition)->setName(UniString(szStart, szEnd));
            }
        }

        // RelationTargetHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationTargetHandler)
        {
            CHECK_MODEL(IS_VALID_RELATION, 
                        "RelationTargetHandler : Cannot set relation target, relations aren't initialized.")
            {
                (*m_relationPosition)->setTarget(UniString(szStart, szEnd));
            }
        }
        
        // RelationTargetRefHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationTargetRefHandler)
        {
            CHECK_MODEL(IS_VALID_RELATION, 
                        "RelationTargetRefHandler : Cannot set relation target reference, relations aren't initialized.")
            {
                (*m_relationPosition)->setTargetRef(UniString(szStart, szEnd));
            }
        }

        // RelationSourceHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationSourceHandler)
        {
            CHECK_MODEL(IS_VALID_RELATION, 
                        "RelationSourceHandler : Cannot set relation source, relations aren't initialized.")
            {
                (*m_relationPosition)->setSource(UniString(szStart, szEnd));
            }
        }

        // RelationSourceRefHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationSourceRefHandler)
        {
            CHECK_MODEL(IS_VALID_RELATION, 
                        "RelationSourceRefHandler : Cannot set relation source reference, relations aren't initialized.")
            {
                (*m_relationPosition)->setSourceRef(UniString(szStart, szEnd));
            }
        }

        // RelationMultiplicityHandler implementation
        IMPL_MODEL_PARSER_ENUM_HANDLER(RelationMultiplicityHandler, multiplicity_t, multiplicity)
        {
            CHECK_MODEL(IS_VALID_RELATION, 
                        "RelationMultiplicityHandler : Cannot set relation multiplicity, relations aren't initialized.")
            {
                (*m_relationPosition)->setMultiplicity(m_multiplicity);
            }
        }

        // RelationCommentHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationCommentHandler)
        {
            CHECK_MODEL(IS_VALID_RELATION, 
                        "RelationCommentHandler : Cannot set relation comment, relations aren't initialized.")
            {
                (*m_relationPosition)->setComment(UniString(szStart, szEnd));
            }
        }

        // RelationAliasHandler implementation
        IMPL_MODEL_PARSER_HANDLER(RelationAliasHandler)
        {
            CHECK_MODEL(IS_VALID_RELATION,
                        "RelationAliasHandler : Cannot set relation alias, relations aren't initialized.")
            {
                (*m_relationPosition)->setAlias(UniString(szStart, szEnd));
            }
        }

        // FileCreationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(FileCreationHandler)
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance() &&
                        NULL != m_filePosition, 
                        "FileCreationHandler : Cannot create file, DataModel isn't initialized.")
            {
                (*m_filePosition) = UniDataModel::getInstance()->getWorkspace()
                    .openFile(UniString(szStart, szEnd), true);
            }
        }

        // FileCreationOrModificationHandler implementation
        IMPL_MODEL_PARSER_HANDLER(FileCreationOrModificationHandler)
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance() &&
                        NULL != m_filePosition, 
                        "FileCreationOrModificationHandler : Cannot modify file, DataModel isn't initialized.")
            {
                (*m_filePosition) = UniDataModel::getInstance()->getWorkspace()
                    .openFile(UniString(szStart, szEnd), false);
            }
        }

        // FileDeletionHandler implementation
        IMPL_MODEL_PARSER_HANDLER(FileDeletionHandler)
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance() &&
                        NULL != m_filePosition, 
                        "FileDeletionHandler : Cannot delete file, DataModel isn't initialized.")
            {
                UniDataModel::getInstance()->getWorkspace()
                    .deleteFile((*m_filePosition));
                (*m_filePosition) = UniDataModel::getInstance()->getWorkspace().endFiles();
                if (UniDataModel::getInstance()->getWorkspace().beginFiles() != UniDataModel::getInstance()->getWorkspace().endFiles())
                {
                    (*m_filePosition) = UniDataModel::getInstance()->getWorkspace().endFiles()-1;
                }
            }
        }

        // FileNameHandler implementation
        IMPL_MODEL_PARSER_HANDLER(FileNameHandler)
        {
            CHECK_MODEL(IS_VALID_FILE, 
                        "FileNameHandler : Cannot rename file, files aren't initialized.")
            {
                (*m_filePosition)->setName(UniString(szStart, szEnd));
            }
        }

        // FileAliasHandler implementation
        IMPL_MODEL_PARSER_HANDLER(FileAliasHandler)
        {
            CHECK_MODEL(IS_VALID_FILE,
                        "FileAliasHandler : Cannot set file alias, files aren't initialized.")
            {
                (*m_filePosition)->setAlias(UniString(szStart, szEnd));
            }
        }

        // FileCommentHandler implementation
        IMPL_MODEL_PARSER_HANDLER(FileCommentHandler)
        {
            CHECK_MODEL(IS_VALID_FILE, 
                        "FileCommentHandler : Cannot set file comment, files aren't initialized.")
            {
                (*m_filePosition)->setComment(UniString(szStart, szEnd));
            }
        }
        
        // WorkspaceNameHandler implementation        
        IMPL_DEFAULT_PARSER_HANDLER(WorkspaceNameHandler)
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance(), 
                        "WorkspaceNameHandler : Cannot set workspace name, DataModel isn't initialized.")
            {
                UniDataModel::getInstance()->getWorkspace()
                    .setName(UniString(szStart, szEnd));
            } 
        }
        
        // WorkspaceCommentHandler implementation
        IMPL_DEFAULT_PARSER_HANDLER(WorkspaceCommentHandler)
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance(), 
                        "WorkspaceCommentHandler : Cannot set workspace comment, DataModel isn't initialized.")
            {
                UniDataModel::getInstance()->getWorkspace()
                    .setComment(UniString(szStart, szEnd));
            } 
        }

        // WorkspaceAuthorHandler implementation
        IMPL_DEFAULT_PARSER_HANDLER(WorkspaceAuthorHandler)
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance(), 
                        "WorkspaceAuthorHandler : Cannot set workspace author, DataModel isn't initialized.")
            {
                UniDataModel::getInstance()->getWorkspace()
                    .setAuthor(UniString(szStart, szEnd));
            } 
        }

        // WorkspaceBriefHandler implementation
        IMPL_DEFAULT_PARSER_HANDLER(WorkspaceBriefHandler)
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance(), 
                        "WorkspaceBriefHandler : Cannot set workspace brief, DataModel isn't initialized.")
            {
                UniDataModel::getInstance()->getWorkspace()
                    .setBrief(UniString(szStart, szEnd));
            } 
        }

        // WorkspaceVersionHandler implementation
        IMPL_DEFAULT_PARSER_HANDLER(WorkspaceVersionHandler)
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance(), 
                        "WorkspaceVersionHandler : Cannot set workspace version, DataModel isn't initialized.")
            {
                UniDataModel::getInstance()->getWorkspace()
                    .setVersion(UniString(szStart, szEnd));
            } 
        }

        // WorkspaceTypeHandler implementation
        IMPL_DEFAULT_PARSER_ENUM_HANDLER(WorkspaceTypeHandler, project_t, type)
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance(), 
                        "WorkspaceTypeHandler : Cannot set workspace type, DataModel isn't initialized.")
            {
                UniDataModel::getInstance()->getWorkspace()
                    .setType(m_type);
            } 
        }

        // WorkspaceOptionHandler implementation
        IMPL_DEFAULT_PARSER_ENUM_HANDLER(WorkspaceOptionHandler, int, option)       
        {
            CHECK_MODEL(NULL != UniDataModel::getInstance(), 
                        "WorkspaceOptionHandler : Cannot set workspace option, DataModel isn't initialized.")
            {
                UniDataModel::getInstance()->getWorkspace()
                    .setOption(m_option);
            } 
        }
        
    }

}
