#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <xercesc/dom/DOM.hpp>
#include "Logger.hpp"
#include "CoreExport.hpp"
#include "equality.hpp"
#include <vector>
#include <algorithm>
#include "Entity.hpp"
#include "Relation.hpp"
#include "Content.hpp"
#include "encoding.hpp"

using namespace log4cpp;
using namespace xercesc;
using namespace std;
using namespace enc;

namespace dsg {

    template <class EncodingT>
    class CORE_API Workspace;

    #define FileArray(EncodingT)    vector<dsg::File<EncodingT> >

    template <class EncodingT>
    class CORE_API File 
    {
    private:
        typename EncodingT::string_t    m_name;
        typename EncodingT::string_t    m_alias;
        typename EncodingT::string_t    m_comment;
        EntityArray(EncodingT)          m_entities;
        RelationArray(EncodingT)        m_relations;
        ContentArray(EncodingT)         m_contents;
        Category*                       m_logger;

    private:
        friend class Workspace<EncodingT>;

        File()
        : m_name(EncodingT::EMPTY),
          m_alias(EncodingT::EMPTY),
          m_comment(EncodingT::EMPTY)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "File() : creation new File : empty";
        }

        File(const typename EncodingT::string_t & strFilename,
             const typename EncodingT::string_t & strAlias = EncodingT::EMPTY,
             const typename EncodingT::string_t & strComment = EncodingT::EMPTY)
        : m_name(strFilename),
          m_alias(strAlias),
          m_comment(strComment)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "File() : creation new File: "
                                    << encode<EncodingT,ansi>(strFilename);
        }

        DOMNode* saveXML(DOMDocument* xml_doc) const;

        void loadXML(DOMElement* xml_file);

    public:
        // entities
        typedef typename vector<Entity<EncodingT> >::iterator           ent_iterator;
        typedef typename vector<Entity<EncodingT> >::const_iterator     const_ent_iterator;
        typedef typename vector<Entity<EncodingT> >::reverse_iterator   reverse_ent_iterator;
        typedef typename vector<Entity<EncodingT> >::const_reverse_iterator const_reverse_ent_iterator;
        // relations
        typedef typename vector<Relation<EncodingT> >::iterator         rel_iterator;
        typedef typename vector<Relation<EncodingT> >::const_iterator   const_rel_iterator;
        typedef typename vector<Relation<EncodingT> >::reverse_iterator reverse_rel_iterator;
        typedef typename vector<Relation<EncodingT> >::const_reverse_iterator const_reverse_rel_iterator;
        // contents
        typedef typename vector<Content<EncodingT> >::iterator         cnt_iterator;
        typedef typename vector<Content<EncodingT> >::const_iterator   const_cnt_iterator;
        typedef typename vector<Content<EncodingT> >::reverse_iterator reverse_cnt_iterator;
        typedef typename vector<Content<EncodingT> >::const_reverse_iterator const_reverse_cnt_iterator;

        // add Entity
        ent_iterator addNewEntity(const typename EncodingT::string_t & strName,
                                  const typename EncodingT::string_t & strFunctionName = EncodingT::EMPTY,
                                  const typename EncodingT::string_t & strAlias = EncodingT::EMPTY,
                                  class_t pClass = ENTITY_DATA,
                                  const typename EncodingT::string_t & strComment = EncodingT::EMPTY)
        {
            m_entities.push_back(Entity<EncodingT>(strName, strFunctionName, strAlias, pClass, strComment));
            return m_entities.end()-1;
        }

        void deleteEntity(ent_iterator position)
        {
            m_entities.erase(position);
        }

        // add Relation
        rel_iterator addNewRelation(const typename EncodingT::string_t & strName,
                                    const typename EncodingT::string_t & strAlias = EncodingT::EMPTY,
                                    const typename EncodingT::string_t & strTarget = EncodingT::EMPTY,
                                    const typename EncodingT::string_t & strTargetRef = EncodingT::EMPTY,
                                    const typename EncodingT::string_t & strSource = EncodingT::EMPTY,
                                    const typename EncodingT::string_t & strSourceRef = EncodingT::EMPTY,
                                    multiplicity_t                       multiplicity = RELATION_ZERO_ONE,
                                    const typename EncodingT::string_t & strComment = EncodingT::EMPTY)
        {
            m_relations.push_back(Relation<EncodingT>(strName, strAlias, strTarget, strTargetRef, strSource, strSourceRef, multiplicity, strComment));
            return m_relations.end()-1;
        }

        void deleteRelation(rel_iterator position)
        {
            m_relations.erase(position);
        }
        
        // add Content
        cnt_iterator addNewContent(const typename EncodingT::string_t & strType,
                                   const typename EncodingT::string_t & strData,
                                   const typename EncodingT::string_t & strTarget = EncodingT::EMPTY,
                                   const typename EncodingT::string_t & strTargetREF = EncodingT::EMPTY)
        {
            m_contents.push_back(Content<EncodingT>(strType, strData, strTarget, strTargetREF));
            return m_contents.end()-1;
        }

        void deleteContent(cnt_iterator position)
        {
            m_contents.erase(position);
        }

        const typename EncodingT::string_t & getName() const
        {
            return m_name;
        }

        bool hasAlias() const
        {
            return !m_alias.empty();
        }

        const typename EncodingT::string_t & getAlias() const
        {
            return m_alias;
        }

        bool hasComment() const
        {
            return !m_comment.empty();
        }

        const typename EncodingT::string_t & getComment() const
        {
            return m_comment;
        }

        void setName(const typename EncodingT::string_t & strName)
        {
            m_name = strName;
        }

        void setAlias(const typename EncodingT::string_t & strAlias)
        {
            m_alias = strAlias;
        }

        void setComment(const typename EncodingT::string_t & strComment)
        {
            m_comment = strComment;
        }

        // entities
        // begin
        ent_iterator beginEntities()
        {
            return m_entities.begin();
        }
        // end
        ent_iterator endEntities()
        {
            return m_entities.end();
        }
        // begin
        const_ent_iterator beginEntities() const
        {
            return m_entities.begin();
        }
        // end
        const_ent_iterator endEntities() const
        {
            return m_entities.end();
        }
        // begin
        reverse_ent_iterator rbeginEntities()
        {
            return m_entities.rbegin();
        }
        // end
        reverse_ent_iterator rendEntities()
        {
            return m_entities.rend();
        }
        // begin
        const_reverse_ent_iterator rbeginEntities() const
        {
            return m_entities.rbegin();
        }
        // end
        const_reverse_ent_iterator rendEntities() const
        {
            return m_entities.rend();
        }
        // size
        size_t sizeEntities() const
        {
            return m_entities.size();
        }
        // clear
        void clearEntities()
        {
            m_entities.clear();
        }

        // relations
        // begin
        rel_iterator beginRelations()
        {
            return m_relations.begin();
        }
        // end
        rel_iterator endRelations()
        {
            return m_relations.end();
        }
        // begin
        const_rel_iterator beginRelations() const
        {
            return m_relations.begin();
        }
        // end
        const_rel_iterator endRelations() const
        {
            return m_relations.end();
        }
        // begin
        reverse_rel_iterator rbeginRelations()
        {
            return m_relations.rbegin();
        }
        // end
        reverse_rel_iterator rendRelations()
        {
            return m_relations.rend();
        }
        // begin
        const_reverse_rel_iterator rbeginRelations() const
        {
            return m_relations.rbegin();
        }
        // end
        const_reverse_rel_iterator rendRelations() const
        {
            return m_relations.rend();
        }
        // size
        size_t sizeRelations() const
        {
            return m_relations.size();
        }
        // clear
        void clearRelations()
        {
            m_relations.clear();
        }
        
        // contents
        // begin
        cnt_iterator beginContents()
        {
            return m_contents.begin();
        }
        // end
        cnt_iterator endContents()
        {
            return m_contents.end();
        }
        // begin
        const_cnt_iterator beginContents() const
        {
            return m_contents.begin();
        }
        // end
        const_cnt_iterator endContents() const
        {
            return m_contents.end();
        }
        // begin
        reverse_cnt_iterator rbeginContents()
        {
            return m_contents.rbegin();
        }
        // end
        reverse_cnt_iterator rendContents()
        {
            return m_contents.rend();
        }
        // begin
        const_reverse_cnt_iterator rbeginContents() const
        {
            return m_contents.rbegin();
        }
        // end
        const_reverse_cnt_iterator rendContents() const
        {
            return m_contents.rend();
        }
        // size
        size_t sizeContents() const
        {
            return m_contents.size();
        }
        // clear
        void clearContents()
        {
            m_contents.clear();
        }
        // find
        const_cnt_iterator findContent(const typename EncodingT::string_t & type,
                                       const typename EncodingT::string_t & target = EncodingT::EMPTY,
                                       const typename EncodingT::string_t & targetREF = EncodingT::EMPTY) const
        {
            return std::find_if(m_contents.begin(), m_contents.end(), ContentTypeEquality<EncodingT>(type, target, targetREF));
        }

		bool operator<(const File& f) const
		{
			return (m_name < f.m_name);
		}

        bool operator==(const File& f) const
        {
            return (m_name == f.m_name);
        }
    };

    template <class EncodingT>
    class FileNameEquality 
    {
    private :
        typename EncodingT::string_t m_name;
    public:
        FileNameEquality(const typename EncodingT::string_t & strName)
        :m_name(strName)
        {}
        bool operator() (const File<EncodingT> & f) const 
        {
          return equalNoCase(f.getName().c_str(), m_name.c_str());
        }
    };

}

#if !defined(HAS_CORE_DLL) || defined(BUILD_CORE_DLL)
#    include "impl/File_impl.hpp"
#endif

#endif // _FILE_HPP_
