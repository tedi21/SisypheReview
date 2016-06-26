#ifndef _ATTRIBUTE_HPP_
#define _ATTRIBUTE_HPP_

#include <xercesc/dom/DOM.hpp>
#include "Logger.hpp"
#include "encoding.hpp"
#include "equality.hpp"
#include "CoreExport.hpp"
#include <vector>


using namespace log4cpp;
using namespace xercesc;
using namespace std;
using namespace enc;

namespace dsg {

    template <class EncodingT>
    class CORE_API Entity;

    enum modifier_t 
    {
        ATTR_NORMAL     = 0,
        ATTR_ID         = 1,   // Attribute that uniquely identifies an entity.
        ATTR_REF        = 2,   // Attribute that refers to an other entity.
        ATTR_AUTO       = 4,   // Attribute that indicates that the value will be automatically generated.
        ATTR_CONST      = 8,   // Attribute that indicates that the value is a read only attribute.
        ATTR_CONTEXTUAL = 16,  // Attribute that refers to the “owner” of the function we're executing, or rather, to the object that a function is a method of. Information with contextual attributes need to be updated when contextual data change.
        ATTR_BASE       = 32,  // Attribute that refers to the base class. It always implies a multiplicity of 1, as no more than one object at a time can have lifetime responsibility for another object.
        ATTR_VIRTUAL    = 64,  // Attribute that indicates that the value needs to be implemented. It always implies a multiplicity of 0..1. A polymorphic data type or a generalized type from which such specializations are made.
        ATTR_STATIC     = 128, // Attribute that indicates that the value exists throughout the lifetime of the program.
        ATTR_ARRAY      = 256  // Attribute that refers to N entities.
    };

    enum type_t
    {
        ATTR_BOOLEAN        = 0,
        ATTR_SBYTE          = 1,
        ATTR_BYTE           = 2,
        ATTR_ANSICHAR       = 3,
        ATTR_WIDECHAR       = 4,
        ATTR_CHAR           = 5, /*Platform Dependant*/
        ATTR_INT16          = 6,
        ATTR_UINT16         = 7,
        ATTR_INT32          = 8,
        ATTR_UINT32         = 9,
        ATTR_INT64          = 10,
        ATTR_UINT64         = 11,
        ATTR_INT            = 12, /*Platform Dependant*/
        ATTR_UINT           = 13, /*Platform Dependant*/
        ATTR_SINGLE         = 14,
        ATTR_DOUBLE         = 15,
        ATTR_ANSISTRING     = 16,
        ATTR_WIDESTRING     = 17,
        ATTR_STRING         = 18, /*Platform Dependant*/
        ATTR_TEXT           = 19,
        ATTR_TIME           = 20,
        ATTR_DATE           = 21,
        ATTR_ANY            = 22,
        ATTR_BINARY         = 23
    };

    #define AttributeArray(EncodingT) vector<dsg::Attribute<EncodingT> >

    template <class EncodingT>
    class CORE_API Attribute 
    {
    private :
        Category *                   m_logger;
        typename EncodingT::string_t m_name;
        typename EncodingT::string_t m_alias;
        type_t                       m_type;
        unsigned int                 m_modifier;
        typename EncodingT::string_t m_default;
        typename EncodingT::string_t m_comment;

    private :
        friend class Entity<EncodingT>;

        Attribute()
        : m_name(EncodingT::EMPTY),
          m_alias(EncodingT::EMPTY),
          m_type(ATTR_ANY),
          m_modifier(ATTR_NORMAL),
          m_default(EncodingT::EMPTY),
          m_comment(EncodingT::EMPTY)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Attribute() : creation new attribute : empty";
        }

        Attribute(const typename EncodingT::string_t& strAttribute,
                  const typename EncodingT::string_t& strAlias   = EncodingT::EMPTY,
                  type_t                              pType      = ATTR_ANY,
                  unsigned int                        pModifier  = ATTR_NORMAL,
                  const typename EncodingT::string_t& strDefault = EncodingT::EMPTY,
                  const typename EncodingT::string_t& strComment = EncodingT::EMPTY)
        : m_name(strAttribute),
          m_alias(strAlias),
          m_type(pType),
          m_modifier(pModifier),
          m_default(strDefault),
          m_comment(strComment)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Attribute() : creation new attribute : "
                                    << encode<EncodingT,ansi>(strAttribute);
        }

        DOMNode* saveXML(DOMDocument* xml_doc) const;

        void loadXML(DOMElement* xml_attribute);

    public :

        const typename EncodingT::string_t& getName() const
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

        type_t getType() const
        {
            return m_type;
        }
        
        bool isModifier(unsigned int pModifier) const
        {
            return pModifier==(m_modifier & pModifier);
        }

        bool isId() const
        {
            return m_modifier & ATTR_ID;
        }

        bool isRef() const
        {
            return m_modifier & ATTR_REF;
        }

        bool isAuto() const
        {
            return m_modifier & ATTR_AUTO;
        }

        bool isConst() const
        {
            return m_modifier & ATTR_CONST;
        }

        bool isContextual() const
        {
            return m_modifier & ATTR_CONTEXTUAL;
        }

        bool isBase() const
        {
            return m_modifier & ATTR_BASE;
        }

        bool isVirtual() const
        {
            return m_modifier & ATTR_VIRTUAL;
        }

        bool isStatic() const
        {
            return m_modifier & ATTR_STATIC;
        }

        bool isArray() const
        {
            return m_modifier & ATTR_ARRAY;
        }

        bool hasDefault() const
        {
            return !m_default.empty();
        }

        const typename EncodingT::string_t& getDefault() const
        {
            return m_default;
        }

        bool hasComment() const
        {
            return !m_comment.empty();
        }

        const typename EncodingT::string_t& getComment() const
        {
            return m_comment;
        }

        void setName(const typename EncodingT::string_t& strName)
        {
            m_name = strName;
        }

        void setAlias(const typename EncodingT::string_t& strAlias)
        {
            m_alias = strAlias;
        }

        void setType(type_t strType)
        {
            m_type = strType;
        }

        void setModifier(unsigned int pModifier)
        {
            m_modifier |= pModifier;
        }

        void resetModifier()
        {
            m_modifier = ATTR_NORMAL;
        }

        void setDefault(const typename EncodingT::string_t& strDefault)
        {
            m_default = strDefault;
        }

        void setComment(const typename EncodingT::string_t& strComment)
        {
            m_comment = strComment;
        }
		
		bool operator<(const Attribute& a) const
		{
			return (m_name < a.m_name);
        }

        bool operator==(const Attribute& a) const
        {
            return (m_name == a.m_name);
        }
    };

    template <class EncodingT>
    class AttributeNameEquality {
    private :
        typename EncodingT::string_t m_name;
    public:
        AttributeNameEquality(const typename EncodingT::string_t& strName)
        :m_name(strName)
        {}
        bool operator() (const Attribute<EncodingT>& a) const 
        {
          return equalNoCase(a.getName().c_str(), m_name.c_str());
        }
    };

}

#if !defined(HAS_CORE_DLL) || defined(BUILD_CORE_DLL)
#    include "impl/Attribute_impl.hpp"
#endif

#endif  // _ATTRIBUTE_HPP_
