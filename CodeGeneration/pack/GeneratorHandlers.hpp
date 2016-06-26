#ifndef _GENERATOR_HANDLERS_HPP_
#define _GENERATOR_HANDLERS_HPP_

#include <boost/shared_ptr.hpp>
#include "GeneratorTypes.hpp"
#include "CoreTypes.hpp"
#include "PackExport.hpp"
#include "DataModel.hpp"

using namespace log4cpp;
using namespace boost;
using namespace std;

namespace dsg {

    namespace generator {

    enum name_kind_t
    {
        KIND_NAME      = 1,
        KIND_ALIAS     = 2
    };
        
    #define DECLARE_MODEL_GEN_HANDLER(Api, NameHandler, Element, Return)            \
        class Api NameHandler                                                       \
        {                                                                           \
        private:                                                                    \
            Category* m_logger;                                                     \
                                                                                    \
        public:                                                                     \
            NameHandler();                                                          \
                                                                                    \
            Return operator()                                                       \
                (const_Uni##Element##Itr& i) const;                                 \
        };

    #define DECLARE_CORE_MODEL_GEN_HANDLER(NameHandler, Element, Return)\
        DECLARE_MODEL_GEN_HANDLER(PACK_API, NameHandler, Element, Return)

    #define DECLARE_MODEL_GEN_MEMBER_HANDLER(Api, NameHandler, Element, Member, NameMember, Return)\
        class Api NameHandler                                                       \
        {                                                                           \
        private:                                                                    \
            Member m_##NameMember;                                                  \
            Category* m_logger;                                                     \
                                                                                    \
        public:                                                                     \
            NameHandler(Member NameMember);                                         \
                                                                                    \
            Return operator()                                                       \
                (const_Uni##Element##Itr& i) const;                                 \
        };

    #define DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(NameHandler, Element, Member, NameMember, Return)\
        DECLARE_MODEL_GEN_MEMBER_HANDLER(PACK_API, NameHandler, Element, Member, NameMember, Return)

    #define DECLARE_MODEL_GEN_ENUM_HANDLER(Api, NameHandler, Element, Enum, NameEnum)\
        DECLARE_MODEL_GEN_MEMBER_HANDLER(Api, NameHandler, Element, Enum, NameEnum, bool)

    #define DECLARE_CORE_MODEL_GEN_ENUM_HANDLER(NameHandler, Element, Enum, NameEnum)\
        DECLARE_MODEL_GEN_ENUM_HANDLER(PACK_API, NameHandler, Element, Enum, NameEnum)

        // Returns the attribute name
        DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(AttributeNameHandler, Attribute, name_kind_t, alias, UniString)
        // Returns if the attribute has alias
        DECLARE_CORE_MODEL_GEN_HANDLER(HasAttributeAliasHandler, Attribute, bool)
        // Returns true if the attribute type is equal with the expected type
        DECLARE_CORE_MODEL_GEN_ENUM_HANDLER(IsAttributeTypeHandler, Attribute, type_t, type)
        // Returns true if the attribute modifier is equal with the expected modifier
        DECLARE_CORE_MODEL_GEN_ENUM_HANDLER(IsAttributeModifierHandler, Attribute, unsigned int, modifier)
        // Returns the attribute default value
        DECLARE_CORE_MODEL_GEN_HANDLER(AttributeDefaultHandler, Attribute, UniString)
        // Returns if the attribute has default value
        DECLARE_CORE_MODEL_GEN_HANDLER(HasAttributeDefaultHandler, Attribute, bool)
        // Returns the attribute comment
        DECLARE_CORE_MODEL_GEN_HANDLER(AttributeCommentHandler, Attribute, UniString)
        // Returns if the attribute has comment
        DECLARE_CORE_MODEL_GEN_HANDLER(HasAttributeCommentHandler, Attribute, bool)

        // Returns the entity name
        DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(EntityNameHandler, Entity, name_kind_t, alias, UniString)
        // Returns if the entity has alias
        DECLARE_CORE_MODEL_GEN_HANDLER(HasEntityAliasHandler, Entity, bool)
        // Returns the entity functionName
        DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(EntityFunctionNameHandler, Entity, name_kind_t, alias, UniString)
        // Returns if the entity has functionName
        DECLARE_CORE_MODEL_GEN_HANDLER(HasEntityFunctionNameHandler, Entity, bool)
        // Returns true if the entity class is equal with the expected class
        DECLARE_CORE_MODEL_GEN_ENUM_HANDLER(IsEntityClassHandler, Entity, class_t, category)        
        // Returns the entity comment 
        DECLARE_CORE_MODEL_GEN_HANDLER(EntityCommentHandler, Entity, UniString)  
        // Returns if the entity has comment
        DECLARE_CORE_MODEL_GEN_HANDLER(HasEntityCommentHandler, Entity, bool)

        // Returns the relation name
        DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(RelationNameHandler, Relation, name_kind_t, alias, UniString)
        // Returns if the relation has alias
        DECLARE_CORE_MODEL_GEN_HANDLER(HasRelationAliasHandler, Relation, bool)
        // Returns the relation target
        DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(RelationTargetHandler, Relation, name_kind_t, alias, UniString)
        // Returns if the relation target has alias
        DECLARE_CORE_MODEL_GEN_HANDLER(HasRelationTargetAliasHandler, Relation, bool)
        // Returns the relation target reference
        DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(RelationTargetRefHandler, Relation, name_kind_t, alias, UniString)
        // Returns if the relation target reference has alias
        DECLARE_CORE_MODEL_GEN_HANDLER(HasRelationTargetRefAliasHandler, Relation, bool)
        // Returns the relation source
        DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(RelationSourceHandler, Relation, name_kind_t, alias, UniString)
        // Returns if the relation source has alias
        DECLARE_CORE_MODEL_GEN_HANDLER(HasRelationSourceAliasHandler, Relation, bool)
        // Returns the relation source reference
        DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(RelationSourceRefHandler, Relation, name_kind_t, alias, UniString)
        // Returns if the relation source reference has alias
        DECLARE_CORE_MODEL_GEN_HANDLER(HasRelationSourceRefAliasHandler, Relation, bool)
        // Returns true if the relation multiplicity is equal with the expected multiplicity
        DECLARE_CORE_MODEL_GEN_ENUM_HANDLER(IsRelationMultiplicityHandler, Relation, multiplicity_t, multiplicity) 
        // Returns the relation comment
        DECLARE_CORE_MODEL_GEN_HANDLER(RelationCommentHandler, Relation, UniString)  
        // Returns if the relation has comment
        DECLARE_CORE_MODEL_GEN_HANDLER(HasRelationCommentHandler, Relation, bool)

        // Returns the content data
        DECLARE_CORE_MODEL_GEN_HANDLER(ContentDataHandler, Content, UniString)

        // Returns the file name
        DECLARE_CORE_MODEL_GEN_MEMBER_HANDLER(FileNameHandler, File, name_kind_t, alias, UniString)
        // Returns if the file has alias
        DECLARE_CORE_MODEL_GEN_HANDLER(HasFileAliasHandler, File, bool)
        // Returns the file comment
        DECLARE_CORE_MODEL_GEN_HANDLER(FileCommentHandler, File, UniString) 
        // Returns if the file has comment
        DECLARE_CORE_MODEL_GEN_HANDLER(HasFileCommentHandler, File, bool)

    #define DECLARE_DEFAULT_GEN_HANDLER(Api, NameHandler, Return)                   \
        class Api NameHandler                                                       \
        {                                                                           \
        private:                                                                    \
            Category* m_logger;                                                     \
                                                                                    \
        public:                                                                     \
            NameHandler();                                                          \
                                                                                    \
            Return operator()                                                       \
                () const;                                                           \
        };

    #define DECLARE_CORE_DEFAULT_GEN_HANDLER(NameHandler, Return)\
        DECLARE_DEFAULT_GEN_HANDLER(PACK_API, NameHandler, Return)

    #define DECLARE_DEFAULT_GEN_ENUM_HANDLER(Api, NameHandler, Enum, NameEnum)      \
        class Api NameHandler                                                       \
        {                                                                           \
        private:                                                                    \
            Enum m_##NameEnum;                                                      \
            Category* m_logger;                                                     \
                                                                                    \
        public:                                                                     \
            NameHandler(Enum NameEnum);                                             \
                                                                                    \
            bool operator()                                                         \
                () const;                                                           \
        };

    #define DECLARE_CORE_DEFAULT_GEN_ENUM_HANDLER(NameHandler, Enum, NameEnum)\
        DECLARE_DEFAULT_GEN_ENUM_HANDLER(PACK_API, NameHandler, Enum, NameEnum)
               
        // Returns the workspace name
        DECLARE_CORE_DEFAULT_GEN_HANDLER(WorkspaceNameHandler, UniString)       
        // Returns the workspace comment
        DECLARE_CORE_DEFAULT_GEN_HANDLER(WorkspaceCommentHandler, UniString)    
        // Returns the workspace author
        DECLARE_CORE_DEFAULT_GEN_HANDLER(WorkspaceAuthorHandler, UniString)
        // Returns the workspace brief
        DECLARE_CORE_DEFAULT_GEN_HANDLER(WorkspaceBriefHandler, UniString)
        // Returns the workspace version
        DECLARE_CORE_DEFAULT_GEN_HANDLER(WorkspaceVersionHandler, UniString)
        // Returns true if the workspace type is equal with the expected type
        DECLARE_CORE_DEFAULT_GEN_ENUM_HANDLER(IsWorkspaceTypeHandler, project_t, type)
        // Returns the workspace option
        DECLARE_CORE_DEFAULT_GEN_ENUM_HANDLER(IsWorkspaceOptionHandler, int, option)
        
        // Returns the current date
        class PACK_API DateHandler 
        {
        private:
            string m_format;
            Category* m_logger;
    
        public:
            DateHandler(const char * frmt = "dd-mm-yyyy");
    
            UniString operator()
                () const;
        };  

        // Returns new uuid 
        class PACK_API UuidHandler 
        {
        private:
            Category* m_logger;
    
        public:
            UuidHandler();
    
            UniString operator()
                () const;
        }; 
 
        class PACK_API FileRange 
        {    
        public:
            gen::range<file_context> operator()
                (file_context const& f) const;
        };
                
        class PACK_API EntityRange 
        {    
        public:
            gen::range<ent_context> operator()
                (const_UniFileItr& f) const;
        };
        
        class PACK_API RelationRange 
        {
        public:
            gen::range<rel_context> operator()
                (const_UniFileItr& f) const;
        };
      
        class PACK_API AttributeRange 
        {    
        public:
            gen::range<attr_context> operator()
                (const_UniEntityItr& e) const;
        };

        enum filter_t
        {
            FILTER_SOURCE      = 1,
            FILTER_TARGET      = 2,
            FILTER_ERASE_REF   = 4,
            FILTER_CONTEXTUAL  = 8
        };

        class PACK_API RelationByEntityRange 
        {    
		private:
			int m_filter;
            UniRelationArray m_relations;
        public:
			RelationByEntityRange(int filter);

            void filterAllFiles(const_UniEntityItr& e);

            gen::range<rel_context> operator()
                (const_UniFileItr& f, const_UniEntityItr& e);
        };

        class PACK_API RelationByAttributeRange 
        {    
		private:
			int m_filter;
            UniRelationArray m_relations;
        public:
			RelationByAttributeRange(int filter);

            void filterAllFiles(const_UniEntityItr& e, const_UniAttributeItr& a);

            gen::range<rel_context> operator()
                (const_UniFileItr& f, const_UniEntityItr& e, const_UniAttributeItr& a);
        };

        class PACK_API EntityByRelationRange 
        {    
		private:
			int m_filter;
            UniEntityArray m_entities;
        public:
			EntityByRelationRange(int filter);

            void filterAllFiles(const_UniRelationItr& r);

            gen::range<ent_context> operator()
                (const_UniFileItr& f, const_UniRelationItr& r);
        };

        class PACK_API ContentByTypeRange
        {
        private:
            UniString  m_type;
            UniContentArray m_contents;
        public:
            ContentByTypeRange(const UniString& type);

            gen::range<cnt_context> operator()
                (const_UniFileItr& f);
        };

        class PACK_API ContentByEntityRange
        {
        private:
            UniString  m_type;
            UniContentArray m_contents;
        public:
            ContentByEntityRange(const UniString& type);

            gen::range<cnt_context> operator()
                (const_UniFileItr& f, const_UniEntityItr& e);
        };

        class PACK_API ContentByAttributeRange
        {
        private:
            UniString  m_type;
            UniContentArray m_contents;
        public:
            ContentByAttributeRange(const UniString& type);

            gen::range<cnt_context> operator()
                (const_UniFileItr& f, const_UniEntityItr& e, const_UniAttributeItr& a);
        };

    //////////////////////////////////////////////////////
    // Type declaration
    //////////////////////////////////////////////////////
        typedef marker<FileRange,file_context>                   file_limit;
        typedef marker<EntityRange,file_context>                 ent_limit;
        typedef marker<RelationRange,file_context>               rel_limit;
        typedef marker<AttributeRange,ent_context>               attr_limit;

        typedef marker<RelationByAttributeRange,attr_context>    attr_relation_limit;
        typedef marker<RelationByEntityRange,ent_context>        ent_relation_limit;
        typedef marker<EntityByRelationRange,rel_context >       rel_entity_limit;
        typedef marker<ContentByTypeRange,file_context>          cnt_limit;
        typedef marker<ContentByEntityRange,ent_context>         ent_content_limit;
        typedef marker<ContentByAttributeRange,attr_context>     attr_content_limit;
    }
}

#include "impl/GeneratorHandlers_impl.hpp"

#endif // _GENERATOR_HANDLERS_HPP_

