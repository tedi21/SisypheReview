#ifndef _WORKSPACE_HPP_
#define _WORKSPACE_HPP_

#include <xercesc/dom/DOM.hpp>
#include "Logger.hpp"
#include "CoreExport.hpp"
#include "equality.hpp"
#include <vector>
#include "File.hpp"
#include "encoding.hpp"

using namespace log4cpp;
using namespace xercesc;
using namespace std;
using namespace enc;

namespace dsg {

    enum project_t
    {
        WRK_FILE = 0,
        WRK_PROJECT
    };

    enum option_t
    {
        WRK_NO_OPTION = 0
    };

    template <class EncodingT>
    class CORE_API DataModel;

    #define WorkspaceArray(EncodingT)    vector<dsg::Workspace<EncodingT> >

    template <class EncodingT>
    class CORE_API Workspace 
	{
    private:
        typename EncodingT::string_t    m_name;
        typename EncodingT::string_t    m_author;
        typename EncodingT::string_t    m_brief;
        typename EncodingT::string_t    m_version;
        project_t                       m_type;
        int                             m_option;
        typename EncodingT::string_t    m_comment;
        FileArray(EncodingT)            m_files;
        Category*                       m_logger;

    private:
        friend class DataModel<EncodingT>;

        Workspace()
        : m_name(EncodingT::EMPTY),
          m_author(EncodingT::EMPTY),
          m_brief(EncodingT::EMPTY),
          m_version(EncodingT::EMPTY),
          m_type(WRK_PROJECT),
          m_option(WRK_NO_OPTION),
          m_comment(EncodingT::EMPTY)
        {
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Workspace() : creation new Workspace: empty";
        }

        Workspace(const typename EncodingT::string_t & strName,
                  const typename EncodingT::string_t & strAuthor  = EncodingT::EMPTY,
                  const typename EncodingT::string_t & strBrief   = EncodingT::EMPTY,
                  const typename EncodingT::string_t & strVersion = EncodingT::EMPTY,
                  project_t   pType   = WRK_PROJECT,
                  int         pOption = WRK_NO_OPTION,
                  const typename EncodingT::string_t & strComment = EncodingT::EMPTY)
        : m_name(strName),
          m_author(strAuthor),
          m_brief(strBrief),
          m_version(strVersion),
          m_type(pType),
          m_option(pOption),
          m_comment(strComment)
        {
            if (m_type==WRK_FILE)
            {
                m_files.push_back(File<EncodingT>(strName));
            }
            m_logger = &Category::getInstance(LOGNAME);
            m_logger->debugStream() << "Workspace() : creation new Workspace: "
                                    << encode<EncodingT,ansi>(strName);
        }

        DOMNode* saveXML(DOMDocument* xml_doc) const;

        void loadXML(DOMElement* xml_file);

    public:
        typedef typename vector<File<EncodingT> >::iterator         file_iterator;
        typedef typename vector<File<EncodingT> >::const_iterator   const_file_iterator;
        typedef typename vector<File<EncodingT> >::reverse_iterator       reverse_file_iterator;
        typedef typename vector<File<EncodingT> >::const_reverse_iterator const_reverse_file_iterator;

        // add File
        file_iterator openFile( const typename EncodingT::string_t & strFile,
                                bool bErase = false)
        {
            bool exist = true;
            file_iterator file = beginFiles();
            if (m_type==WRK_PROJECT)
            {
                FileNameEquality<EncodingT> eq(strFile);
                file = std::find_if(beginFiles(), endFiles(), eq);
                if (file==endFiles())
                {
                    m_files.push_back(File<EncodingT>(strFile));
                    file = endFiles()-1;
                    exist = false;
                }
                if (bErase && exist)
                {
                    deleteFile(file);
                    m_files.push_back(File<EncodingT>(strFile));
                    file = endFiles()-1;
                }
            }
            else if (bErase)
            {
                clearFiles();
                m_files.push_back(File<EncodingT>(getName()));
                file = endFiles()-1;
            }
            return file;
        }

        void deleteFile(file_iterator position)
        {
            if (m_type==WRK_PROJECT)
            {
                m_files.erase(position);
            }
        }

        const typename EncodingT::string_t & getName() const
        {
            return m_name;
        }

        bool hasComment() const
        {
            return !m_comment.empty();
        }

        const typename EncodingT::string_t & getComment() const
        {
            return m_comment;
        }

        const typename EncodingT::string_t & getAuthor() const
        {
            return m_author;
        }

        const typename EncodingT::string_t & getBrief() const
        {
            return m_brief;
        }

        const typename EncodingT::string_t & getVersion() const
        {
            return m_version;
        }

        project_t getType() const
        {
            return m_type;
        }

        bool isOption(int pOption) const
        {
            return pOption==(m_option & pOption);
        }
      
        void setName(const typename EncodingT::string_t & name)
        {
            m_name = name;
        }

        void setComment(const typename EncodingT::string_t & comment)
        {
            m_comment = comment;
        }

        void setAuthor(const typename EncodingT::string_t & author)
        {
            m_author = author;
        }

        void setBrief(const typename EncodingT::string_t & brief)
        {
            m_brief = brief;
        }

        void setVersion(const typename EncodingT::string_t & version)
        {
            m_version = version;
        }

        void setType(project_t type)
        {
            m_type = type;
        }

        void setOption(int pOption)
        {
            m_option |= pOption;
        }
        
        void resetOption()
        {
            m_option = WRK_NO_OPTION;
        }
        
        // begin
        file_iterator beginFiles()
        {
            return m_files.begin();
        }
        // end
        file_iterator endFiles()
        {
            return m_files.end();
        }
        // begin
        const_file_iterator beginFiles() const
        {
            return m_files.begin();
        }
        // end
        const_file_iterator endFiles() const
        {
            return m_files.end();
        }
        // begin
        reverse_file_iterator rbeginFiles()
        {
            return m_files.rbegin();
        }
        // end
        reverse_file_iterator rendFiles()
        {
            return m_files.rend();
        }
        // begin
        const_reverse_file_iterator rbeginFiles() const
        {
            return m_files.rbegin();
        }
        // end
        const_reverse_file_iterator rendFiles() const
        {
            return m_files.rend();
        }
        // size
        size_t sizeFiles() const
        {
            return m_files.size();
        }
        // clear
        void clearFiles()
        {
            m_files.clear();
        }

    };

}

#if !defined(HAS_CORE_DLL) || defined(BUILD_CORE_DLL)
#    include "impl/Workspace_impl.hpp"
#endif

#endif // _WORKSPACE_HPP_
