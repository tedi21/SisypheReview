#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <xercesc/dom/DOM.hpp>
#include "Logger.hpp"
#include "CoreExport.hpp"
#include "encoding.hpp"
#include "equality.hpp"
#include "Attribute.hpp"
#include <vector>

using namespace log4cpp;
using namespace xercesc;
using namespace std;
using namespace enc;

namespace dsg {

    template <class EncodingT>
    class CORE_API File;

    enum class_t
    {
        ENTITY_DATA = 0,
        ENTITY_FUNCTION,
        ENTITY_ENUMERATION,
        ENTITY_PACKAGE
    };

    #define EntityArray(EncodingT) vector<dsg::Entity<EncodingT> >

    template <class EncodingT>
    class CORE_API Entity 
	{
    private:
        Category *                    m_logger;
        typename EncodingT::string_t  m_name;
        typename EncodingT::string_t  m_functionName;
        typename EncodingT::string_t  m_alias;
        class_t                       m_class;
        typename EncodingT::string_t  m_comment;
        AttributeArray(EncodingT)     m_attributes;

    private :
        friend class File<EncodingT>;

        Entity()
        : m_name(EncodingT::EMPTY),
          m_functionName(EncodingT::EMPTY),
          m_alias(EncodingT::EMPTY),
          m_class(ENTITY_DATA),
          m_comment(EncodingT::EMPTY)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Entity() : creation new entity : empty";
        }

        Entity(const typename EncodingT::string_t & strName,
               const typename EncodingT::string_t & strFunctionName = EncodingT::EMPTY,
               const typename EncodingT::string_t & strAlias = EncodingT::EMPTY,
               class_t pClass = ENTITY_DATA,
               const typename EncodingT::string_t & strComment = EncodingT::EMPTY)
        : m_name(strName),
          m_functionName(strFunctionName),
          m_alias(strAlias),
          m_class(pClass),
          m_comment(strComment)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Entity() : creation new entity: " 
                                    << encode<EncodingT,ansi>(strName);
        }

        DOMNode* saveXML(DOMDocument* xml_doc) const;

        void loadXML(DOMElement* xml_entity);

    public :
        typedef typename vector<Attribute<EncodingT> >::iterator        attr_iterator;
        typedef typename vector<Attribute<EncodingT> >::const_iterator  const_attr_iterator;
        typedef typename vector<Attribute<EncodingT> >::reverse_iterator        reverse_attr_iterator;
        typedef typename vector<Attribute<EncodingT> >::const_reverse_iterator  const_reverse_attr_iterator;

        const typename EncodingT::string_t & getName() const
        {
            return m_name;
        }

        bool hasFunctionName() const
        {
            return !m_functionName.empty();
        }

        const typename EncodingT::string_t & getFunctionName() const
        {
            return m_functionName;
        }

        bool hasAlias() const
        {
            return !m_alias.empty();
        }

        const typename EncodingT::string_t & getAlias() const
        {
            return m_alias;
        }

        class_t getClass() const
        {
            return m_class;
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

        void setFunctionName(const typename EncodingT::string_t & strFunctionName)
        {
            m_functionName = strFunctionName;
        }

        void setAlias(const typename EncodingT::string_t & strAlias)
        {
            m_alias = strAlias;
        }

        void setClass(class_t pClass)
        {
            m_class = pClass;
        }

        void setComment(const typename EncodingT::string_t & strComment)
        {
            m_comment = strComment;
        }

        attr_iterator addNewAttribute(const typename EncodingT::string_t & strAttribute,
                                      const typename EncodingT::string_t & strAlias = EncodingT::EMPTY,
                                      type_t       pType     = ATTR_ANY,
                                      unsigned int pModifier = ATTR_NORMAL,
                                      const typename EncodingT::string_t & strDefault = EncodingT::EMPTY,
                                      const typename EncodingT::string_t & strComment = EncodingT::EMPTY)
        {
            m_attributes.push_back(Attribute<EncodingT>(strAttribute, 
                                                        strAlias,
                                                        pType, 
                                                        pModifier, 
                                                        strDefault,
                                                        strComment));
            return m_attributes.end()-1;
        }

        void deleteAttribute(attr_iterator position)
        {
            m_attributes.erase(position);
        }

        // begin
        attr_iterator beginAttributes()
        {
            return m_attributes.begin();
        }
        // end
        attr_iterator endAttributes()
        {
            return m_attributes.end();
        }
        // begin
        const_attr_iterator beginAttributes() const
        {
            return m_attributes.begin();
        }
        // end
        const_attr_iterator endAttributes() const
        {
            return m_attributes.end();
        }
        // begin
        reverse_attr_iterator rbeginAttributes()
        {
            return m_attributes.rbegin();
        }
        // end
        reverse_attr_iterator rendAttributes()
        {
            return m_attributes.rend();
        }
        // begin
        const_reverse_attr_iterator rbeginAttributes() const
        {
            return m_attributes.rbegin();
        }
        // end
        const_reverse_attr_iterator rendAttributes() const
        {
            return m_attributes.rend();
        }
        // size
        size_t sizeAttributes() const
        {
            return m_attributes.size();
        }
        // clear
        void clearAttributes()
        {
            m_attributes.clear();
        }
		
		bool operator<(const Entity& e) const
		{
			return (m_name < e.m_name);
        }

        bool operator==(const Entity& e) const
        {
            return (m_name == e.m_name);
        }
    };

    template <class EncodingT>
    class EntityNameEquality {
    private :
        typename EncodingT::string_t m_name;
    public:
        EntityNameEquality(const typename EncodingT::string_t & strName)
        :m_name(strName)
        {}
        bool operator() (const Entity<EncodingT> & e) const 
        {
          return equalNoCase(e.getName().c_str(), m_name.c_str());
        }
    };

}

#if !defined(HAS_CORE_DLL) || defined(BUILD_CORE_DLL)
#    include "impl/Entity_impl.hpp"
#endif

#endif // _ENTITY_HPP_
