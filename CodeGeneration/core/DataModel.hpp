#ifndef _DATA_MODEL_HPP_
#define _DATA_MODEL_HPP_

#include <xercesc/dom/DOM.hpp>
#include "Logger.hpp"
#include <vector>
#include <boost/shared_ptr.hpp>
#include "CoreExport.hpp"
#include "Workspace.hpp"

using namespace log4cpp;
using namespace xercesc;
using namespace std;

namespace dsg {

template <class EncodingT>
class CORE_API DataModel 
{
private:
    boost::shared_ptr<DOMDocument>  m_xmlDoc;
    Workspace<EncodingT>            m_workspace;
    Category*                       m_logger;
    // singleton
    static DataModel* m_instance;

private:
    // constructor
    DataModel();
    // destructor
    ~DataModel();

    DOMNode* saveXML() const;

    void loadXML(DOMElement* xml_doc);

public:
    // get singleton
    static DataModel* getInstance();

    // add Workspace
    Workspace<EncodingT>& createWorkspace(const typename EncodingT::string_t & strName,
                                          const typename EncodingT::string_t & strAuthor  = EncodingT::EMPTY,
                                          const typename EncodingT::string_t & strBrief   = EncodingT::EMPTY,
                                          const typename EncodingT::string_t & strVersion = EncodingT::EMPTY,
                                          project_t ptype   = WRK_PROJECT,
                                          int       pOption = WRK_NO_OPTION,
                                          const typename EncodingT::string_t & strComment = EncodingT::EMPTY)
    {
        m_workspace = Workspace<EncodingT>(strName, strAuthor, strBrief, strVersion, ptype, pOption, strComment);
        return m_workspace;
    }

    // get Workspace
    const Workspace<EncodingT>& getWorkspace() const
    {
        return m_workspace;
    }

    Workspace<EncodingT>& getWorkspace()
    {
        return m_workspace;
    }

    // set Workspace
    void setWorkspace(const Workspace<EncodingT>& copy)
    {
        m_workspace = copy;
    }

    void save(const char* filename) const;

    void load(const char* filename);
};

}

#if !defined(HAS_CORE_DLL) || defined(BUILD_CORE_DLL)
#    include "impl/DataModel_impl.hpp"
#endif

#endif // _DATA_MODEL_HPP_
