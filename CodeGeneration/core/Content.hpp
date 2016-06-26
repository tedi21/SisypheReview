#ifndef _CONTENT_HPP_
#define _CONTENT_HPP_

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

    #define ContentArray(EncodingT)    vector<dsg::Content<EncodingT> >

    template <class EncodingT>
    class CORE_API Content 
    {
    private:
        typename EncodingT::string_t    m_type;
        typename EncodingT::string_t    m_target;
        typename EncodingT::string_t    m_targetREF;
        typename EncodingT::string_t    m_data;
        Category*                       m_logger;

    private:
        friend class File<EncodingT>;

        Content()
        : m_type(EncodingT::EMPTY),
          m_target(EncodingT::EMPTY),
          m_targetREF(EncodingT::EMPTY),
          m_data(EncodingT::EMPTY)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Content() : creation new Content : empty";
        }

        Content(const typename EncodingT::string_t & strType,
                const typename EncodingT::string_t & strData,
                const typename EncodingT::string_t & strTarget = EncodingT::EMPTY,
                const typename EncodingT::string_t & strTargetREF = EncodingT::EMPTY)
        : m_type(strType),
          m_target(strTarget),
          m_targetREF(strTargetREF),
          m_data(strData)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Content() : creation new Content: "
                                    << encode<EncodingT,ansi>(strType);
        }

        DOMNode* saveXML(DOMDocument* xml_doc) const;

        void loadXML(DOMElement* xml_content);

    public:
        const typename EncodingT::string_t & getType() const
        {
            return m_type;
        }

        const typename EncodingT::string_t & getTarget() const
        {
            return m_target;
        }

        const typename EncodingT::string_t & getTargetREF() const
        {
            return m_targetREF;
        }

        const typename EncodingT::string_t & getData() const
        {
            return m_data;
        }

        void setType(const typename EncodingT::string_t & strType)
        {
            m_type = strType;
        }

        void setTarget(const typename EncodingT::string_t & strTarget)
        {
            m_target = strTarget;
        }

        void setTargetREF(const typename EncodingT::string_t & strTargetREF)
        {
            m_targetREF = strTargetREF;
        }

        void setData(const typename EncodingT::string_t & strData)
        {
            m_data = strData;
        }

		bool operator<(const Content& c) const
		{
            return (m_type < c.m_type ||
                   (m_type == c.m_type && m_target < c.m_target) ||
                   (m_type == c.m_type && m_target == c.m_target && m_targetREF < c.m_targetREF));
		}

        bool operator==(const Content& c) const
        {
            return (m_type == c.m_type &&  m_target == c.m_target &&  m_targetREF == c.m_targetREF);
        }
    };

    template <class EncodingT>
    class ContentTypeEquality
    {
    private :
        typename EncodingT::string_t m_type;
        typename EncodingT::string_t m_target;
        typename EncodingT::string_t m_targetREF;

    public:
        ContentTypeEquality(const typename EncodingT::string_t & strType,
                            const typename EncodingT::string_t & strTarget = EncodingT::EMPTY,
                            const typename EncodingT::string_t & strTargetREF = EncodingT::EMPTY)
        :m_type(strType),
         m_target(strTarget),
         m_targetREF(strTargetREF)
        {}
        bool operator() (const Content<EncodingT> & f) const 
        {
          return equalNoCase(f.getType().c_str(), m_type.c_str()) &&
                 equalNoCase(f.getTarget().c_str(), m_target.c_str()) &&
                 equalNoCase(f.getTargetREF().c_str(), m_targetREF.c_str());
        }
    };

}

#if !defined(HAS_CORE_DLL) || defined(BUILD_CORE_DLL)
#    include "impl/Content_impl.hpp"
#endif

#endif // _CONTENT_HPP_
