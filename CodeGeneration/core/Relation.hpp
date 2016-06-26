#ifndef _RELATION_HPP_
#define _RELATION_HPP_

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
    class CORE_API File;

    enum multiplicity_t 
    {
        RELATION_ZERO_ONE = 0,
        RELATION_ONE = 1
    };

    #define RelationArray(EncodingT) vector<dsg::Relation<EncodingT> >

    // In a uni-directional association, two classes are related,
    // but only one class knows that the relation exists.
    // For bi-directionnal association : use two uni-directional associations.
    template <class EncodingT>
    class CORE_API Relation 
    {
    private:
        Category *                    m_logger;
        typename EncodingT::string_t  m_name;
        typename EncodingT::string_t  m_alias;
        typename EncodingT::string_t  m_target;
        typename EncodingT::string_t  m_targetRef;
        typename EncodingT::string_t  m_source;
        typename EncodingT::string_t  m_sourceRef;
        multiplicity_t                m_multiplicity;
        typename EncodingT::string_t  m_comment;

    private :
        friend class File<EncodingT>;

        Relation()
        : m_name(EncodingT::EMPTY),
          m_alias(EncodingT::EMPTY),
          m_target(EncodingT::EMPTY),
          m_targetRef(EncodingT::EMPTY),
          m_source(EncodingT::EMPTY),
          m_sourceRef(EncodingT::EMPTY),
          m_multiplicity(RELATION_ZERO_ONE),
          m_comment(EncodingT::EMPTY)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Relation() : creation new relation : empty";
        }

        Relation(const typename EncodingT::string_t & strName,
                 const typename EncodingT::string_t & strAlias     = EncodingT::EMPTY,
                 const typename EncodingT::string_t & strTarget    = EncodingT::EMPTY,
                 const typename EncodingT::string_t & strTargetRef = EncodingT::EMPTY,
                 const typename EncodingT::string_t & strSource    = EncodingT::EMPTY,
                 const typename EncodingT::string_t & strSourceRef = EncodingT::EMPTY,
                 multiplicity_t                       multiplicity = RELATION_ZERO_ONE,
                 const typename EncodingT::string_t & strComment   = EncodingT::EMPTY)
        : m_name(strName),
          m_alias(strAlias),
          m_target(strTarget),
          m_targetRef(strTargetRef),
          m_source(strSource),
          m_sourceRef(strSourceRef),
          m_multiplicity(multiplicity),
          m_comment(strComment)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Relation() : creation new relation : " 
                                    << encode<EncodingT,ansi>(strName)
                                    << " Value " << encode<EncodingT,ansi>(strTarget)
                                    << " (" << encode<EncodingT,ansi>(strTargetRef)
                                    << ") is a reference of " << encode<EncodingT,ansi>(strSource)
                                    << " (" << encode<EncodingT,ansi>(strSourceRef)
                                    << ")";
        }

        DOMNode* saveXML(DOMDocument* xml_doc) const;

        void loadXML(DOMElement* xml_relation);

    public :
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

        const typename EncodingT::string_t & getTarget() const
        {
            return m_target;
        }

        const typename EncodingT::string_t & getTargetRef() const
        {
            return m_targetRef;
        }

        const typename EncodingT::string_t & getSource() const
        {
            return m_source;
        }

        const typename EncodingT::string_t & getSourceRef() const
        {
            return m_sourceRef;
        }

        multiplicity_t getMultiplicity() const
        {
            return m_multiplicity;
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

        void setAlias(const typename EncodingT::string_t& strAlias)
        {
            m_alias = strAlias;
        }

        void setTarget(const typename EncodingT::string_t & strTarget)
        {
            m_target = strTarget;
        }

        void setTargetRef(const typename EncodingT::string_t & strTargetRef)
        {
            m_targetRef = strTargetRef;
        }

        void setSource(const typename EncodingT::string_t & strSource)
        {
            m_source = strSource;
        }

        void setSourceRef(const typename EncodingT::string_t & strSourceRef)
        {
            m_sourceRef = strSourceRef;
        }

        void setMultiplicity(multiplicity_t multiplicity)
        {
            m_multiplicity = multiplicity;
        }

        void setComment(const typename EncodingT::string_t & strComment)
        {
            m_comment = strComment;
        }
		
		bool operator<(const Relation& r) const
		{
			return (m_name < r.m_name);
		}

        bool operator==(const Relation& r) const
        {
            return (m_name == r.m_name);
        }
    };

    template <class EncodingT>
    class RelationNameEquality {
    private :
        typename EncodingT::string_t m_name;
    public:
        RelationNameEquality(const typename EncodingT::string_t & strName)
        :m_name(strName)
        {}
        bool operator() (const Relation<EncodingT> & r) const 
		{
          return equalNoCase(r.getName().c_str(), m_name.c_str());
        }
    };

}

#if !defined(HAS_CORE_DLL) || defined(BUILD_CORE_DLL)
#    include "impl/Relation_impl.hpp"
#endif

#endif //_RELATION_HPP_
