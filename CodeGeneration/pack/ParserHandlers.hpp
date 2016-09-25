#ifndef _PARSER_HANDLERS_HPP_
#define _PARSER_HANDLERS_HPP_

#include <boost/shared_ptr.hpp>
#include "CoreTypes.hpp"
#include "PackExport.hpp"
#include "DataModel.hpp"
#include "ParserTypes.hpp"

using namespace log4cpp;
using namespace boost;
using namespace std;

namespace dsg {

    namespace parser {

        // Constructs a key for workspace
        class PACK_API WorkspaceIndexor
        {
        protected:
            Category* m_logger;
        public:
            WorkspaceIndexor();

            key_t getIndex(short key) const;
        };

        // Constructs a key for file
        class PACK_API FileIndexor
        : public WorkspaceIndexor
        {
        protected:
            boost::shared_ptr<UniFileItr> m_filePosition; 

        public:
            FileIndexor(const boost::shared_ptr<UniFileItr>& filePosition);

            key_t getIndex(short key) const;
        };

        // Constructs a key for entity
        class PACK_API EntityIndexor
        : public FileIndexor
        {
        protected:
            boost::shared_ptr<UniEntityItr> m_entityPosition; 

        public:
            EntityIndexor(const boost::shared_ptr<UniFileItr>&   filePosition,
                          const boost::shared_ptr<UniEntityItr>& entityPosition);

            key_t getIndex(short key) const;
        };

        // Constructs a key for relation
        class PACK_API RelationIndexor
        : public FileIndexor
        {
        protected:
            boost::shared_ptr<UniRelationItr> m_relationPosition; 

        public:
            RelationIndexor(const boost::shared_ptr<UniFileItr>&     filePosition,
                            const boost::shared_ptr<UniRelationItr>& relationPosition);

            key_t getIndex(short key) const;
        };

        // Constructs a key for attribute
        class PACK_API AttributeIndexor
        : public EntityIndexor
        {
        protected:
            boost::shared_ptr<UniAttributeItr> m_attributePosition; 

        public:
            AttributeIndexor(const boost::shared_ptr<UniFileItr>&      filePosition,
                             const boost::shared_ptr<UniEntityItr>&    entityPosition,
                             const boost::shared_ptr<UniAttributeItr>& attributePosition);

            key_t getIndex(short key) const;
        };

        // Memorizes the parsed value and associates it to a key
        template <class IndexorT> 
        class MemoHandler
        {
        private:
            dictionnary_ptr_t m_table;
            IndexorT      m_indexor;
            short         m_key;
            Category*     m_logger;

        public:
            MemoHandler(const dictionnary_ptr_t& table, 
                        const IndexorT& indexor,
                        short key);

            void operator()
                (UniChar const* szStart, UniChar const* szEnd) const;
        };

        // Memorizes the parsed value and Appends it of the previous value
        template <class IndexorT> 
        class MemoAppendHandler
        {
        private:
            dictionnary_ptr_t m_table;
            IndexorT      m_indexor;
            short         m_key;
            Category*     m_logger;

        public:
            MemoAppendHandler(const dictionnary_ptr_t& table, 
                              const IndexorT& indexor,
                              short key);

            void operator()
                (UniChar const* szStart, UniChar const* szEnd) const;
        };

        // Executes a handler with the value associated to a key if the key exists
        template <class IndexorT, class F1>
        class MemoExecutionHandler
        {
        private:
            dictionnary_ptr_t m_table;
            IndexorT      m_indexor;
            F1            m_handlerA;
            short         m_key;
            Category*     m_logger;

        public:
            MemoExecutionHandler(const dictionnary_ptr_t& table,
                                 const IndexorT& indexor,
                                 short key,
                                 const F1& handlerA);

            void operator()
                (UniChar const* szStart, UniChar const* szEnd) const;
        };

        // Executes the first handler with the value associated to a key if the key exists
        // Executes the second handler with the parsed value else
        template <class IndexorT, class F1, class F2>
        class MemoExecutionHandler2
        {
        private:
            dictionnary_ptr_t m_table;
            IndexorT      m_indexor;
            F1            m_handlerA;
            F2            m_handlerB;
            short         m_key;
            Category*     m_logger;

        public:
            MemoExecutionHandler2(const dictionnary_ptr_t& table,
                                  const IndexorT& indexor,
                                  short key,
                                  const F1& handlerA, 
                                  const F2& handlerB);

            void operator()
                (UniChar const* szStart, UniChar const* szEnd) const;
        };

        // Executes a handler with the value associated to a key if the key exists
        // and remove the memorized value from table
        template <class IndexorT, class F1>
        class MemoExecutionAndRemoveHandler
        {
        private:
            dictionnary_ptr_t m_table;
            IndexorT      m_indexor;
            F1            m_handlerA;
            short         m_key;
            Category*     m_logger;

        public:
            MemoExecutionAndRemoveHandler(const dictionnary_ptr_t& table,
                                          const IndexorT& indexor,
                                          short key,
                                          const F1& handlerA);

            void operator()
                (UniChar const* szStart, UniChar const* szEnd) const;
        };

    #define DECLARE_MODEL_PARSER_HANDLER(Api, NameHandler)                          \
        class Api NameHandler                                                       \
        {                                                                           \
        private:                                                                    \
            boost::shared_ptr<UniFileItr>            m_filePosition;                       \
            boost::shared_ptr<UniEntityItr>          m_entityPosition;                     \
            boost::shared_ptr<UniRelationItr>        m_relationPosition;                   \
            boost::shared_ptr<UniAttributeItr>       m_attributePosition;                  \
            Category*                         m_logger;                             \
                                                                                    \
        public:                                                                     \
            NameHandler(const boost::shared_ptr<UniFileItr>&      filePosition,            \
                        const boost::shared_ptr<UniEntityItr>&    entityPosition,          \
                        const boost::shared_ptr<UniRelationItr>&  relationPosition,        \
                        const boost::shared_ptr<UniAttributeItr>& attributePosition);      \
                                                                                    \
            void operator()                                                         \
                (UniChar const* szStart, UniChar const* szEnd) const;               \
        };

    #define DECLARE_CORE_MODEL_PARSER_HANDLER(NameHandler)\
        DECLARE_MODEL_PARSER_HANDLER(PACK_API, NameHandler)

    #define DECLARE_MODEL_PARSER_ENUM_HANDLER(Api, NameHandler, Enum, NameEnum)     \
        class Api NameHandler                                                       \
        {                                                                           \
        private:                                                                    \
            boost::shared_ptr<UniFileItr>            m_filePosition;                       \
            boost::shared_ptr<UniEntityItr>          m_entityPosition;                     \
            boost::shared_ptr<UniRelationItr>        m_relationPosition;                   \
            boost::shared_ptr<UniAttributeItr>       m_attributePosition;                  \
            Enum                              m_##NameEnum;                         \
            Category*                         m_logger;                             \
                                                                                    \
        public:                                                                     \
            NameHandler(const boost::shared_ptr<UniFileItr>&      filePosition,            \
                        const boost::shared_ptr<UniEntityItr>&    entityPosition,          \
                        const boost::shared_ptr<UniRelationItr>&  relationPosition,        \
                        const boost::shared_ptr<UniAttributeItr>& attributePosition,       \
                        Enum NameEnum);                                             \
                                                                                    \
            void operator()                                                         \
                (UniChar const* szStart, UniChar const* szEnd) const;               \
        };

    #define DECLARE_CORE_MODEL_PARSER_ENUM_HANDLER(NameHandler, Enum, NameEnum)\
        DECLARE_MODEL_PARSER_ENUM_HANDLER(PACK_API, NameHandler, Enum, NameEnum)

        // Creates a new attribute named with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(AttributeCreationHandler)
        // Retrieves the attribute named with parsed value if exists or creates the attribute if not exists
        DECLARE_CORE_MODEL_PARSER_HANDLER(AttributeCreationOrModificationHandler)
        // Retrieves the attribute named with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(AttributeModificationHandler)
        // Deletes the attribute named with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(AttributeDeletionHandler)
        // Sets attribute name with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(AttributeNameHandler)
        // Sets attribute alias with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(AttributeAliasHandler)
        // Sets attribute type with parameter type
        DECLARE_CORE_MODEL_PARSER_ENUM_HANDLER(AttributeTypeHandler, type_t, type)
        // Sets attribute modifier with parameter modifier
        DECLARE_CORE_MODEL_PARSER_ENUM_HANDLER(AttributeModifierHandler, modifier_t, modifier)
        // Sets attribute default value with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(AttributeDefaultHandler)
        // Sets attribute comment with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(AttributeCommentHandler)

        // Creates a new entity named with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(EntityCreationHandler)
        // Retrieves the entity named with parsed value if exists or creates the entity if not exists
        DECLARE_CORE_MODEL_PARSER_HANDLER(EntityCreationOrModificationHandler)
        // Retrieves the entity named with parsed value 
        DECLARE_CORE_MODEL_PARSER_HANDLER(EntityModificationHandler)
        // Deletes the entity named with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(EntityDeletionHandler)
        // Sets entity name with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(EntityNameHandler)
        // Sets entity functionName with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(EntityFunctionNameHandler)
        // Sets entity alias with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(EntityAliasHandler)
        // Sets entity class with parameter category
        DECLARE_CORE_MODEL_PARSER_ENUM_HANDLER(EntityClassHandler, class_t, category)
        // Sets entity comment with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(EntityCommentHandler)

        // Creates a new relation named with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationCreationHandler)
        // Retrieves the relation named with parsed value if exists or creates the relations if not exists
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationCreationOrModificationHandler)
        // Retrieves the relation named with parsed value 
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationModificationHandler)
        // Deletes the relation named with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationDeletionHandler)
        // Sets relation name with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationNameHandler)
        // Sets relation target with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationTargetHandler)
        // Sets relation target reference with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationTargetRefHandler)
        // Sets relation source with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationSourceHandler)
        // Sets relation source reference  with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationSourceRefHandler)
        // Sets relation multiplicity with parameter multiplicity
        DECLARE_CORE_MODEL_PARSER_ENUM_HANDLER(RelationMultiplicityHandler, multiplicity_t, multiplicity)
        // Sets relation alias with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationAliasHandler)
        // Sets relation comment with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(RelationCommentHandler)

        // Creates a new file named with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(FileCreationHandler)
        // Retrieves the file named with parsed value if exists or creates the file if not exists
        DECLARE_CORE_MODEL_PARSER_HANDLER(FileCreationOrModificationHandler)
        // Deletes the files names with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(FileDeletionHandler)
        // Sets file name with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(FileNameHandler)
        // Sets file alias with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(FileAliasHandler)
        // Sets file comment with parsed value
        DECLARE_CORE_MODEL_PARSER_HANDLER(FileCommentHandler)

    #define DECLARE_DEFAULT_PARSER_HANDLER(Api, NameHandler)                        \
        class Api NameHandler                                                       \
        {                                                                           \
        private:                                                                    \
            Category*                         m_logger;                             \
                                                                                    \
        public:                                                                     \
            NameHandler();                                                          \
                                                                                    \
            void operator()                                                         \
                (UniChar const* szStart, UniChar const* szEnd) const;               \
        };

    #define DECLARE_CORE_DEFAULT_PARSER_HANDLER(NameHandler)\
        DECLARE_DEFAULT_PARSER_HANDLER(PACK_API, NameHandler)

    #define DECLARE_DEFAULT_PARSER_ENUM_HANDLER(Api, NameHandler, Enum, NameEnum)   \
        class Api NameHandler                                                       \
        {                                                                           \
        private:                                                                    \
            Enum                              m_##NameEnum;                         \
            Category*                         m_logger;                             \
                                                                                    \
        public:                                                                     \
            NameHandler(Enum NameEnum);                                             \
                                                                                    \
            void operator()                                                         \
                (UniChar const* szStart, UniChar const* szEnd) const;               \
        };

    #define DECLARE_CORE_DEFAULT_PARSER_ENUM_HANDLER(NameHandler, Enum, NameEnum)\
        DECLARE_DEFAULT_PARSER_ENUM_HANDLER(PACK_API, NameHandler, Enum, NameEnum)
        
        // Sets workspace name with parsed value
        DECLARE_CORE_DEFAULT_PARSER_HANDLER(WorkspaceNameHandler)
        // Sets workspace comment with parsed value
        DECLARE_CORE_DEFAULT_PARSER_HANDLER(WorkspaceCommentHandler)
        // Sets workspace author with parsed value
        DECLARE_CORE_DEFAULT_PARSER_HANDLER(WorkspaceAuthorHandler)
        // Sets workspace brief with parsed value
        DECLARE_CORE_DEFAULT_PARSER_HANDLER(WorkspaceBriefHandler)
        // Sets workspace version with parsed value
        DECLARE_CORE_DEFAULT_PARSER_HANDLER(WorkspaceVersionHandler)
        // Sets workspace type with parameter type
        DECLARE_CORE_DEFAULT_PARSER_ENUM_HANDLER(WorkspaceTypeHandler, project_t, type)
        // Sets workspace option with parameter option
        DECLARE_CORE_DEFAULT_PARSER_ENUM_HANDLER(WorkspaceOptionHandler, int, option)
             
    }
    
}

#include "impl/ParserHandlers_impl.hpp"

#endif // _PARSER_HANDLERS_HPP_
