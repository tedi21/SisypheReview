#ifndef _FOLDER_HPP_
#define _FOLDER_HPP_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost;
using namespace log4cpp;
namespace files = boost::filesystem;

namespace enc {

    struct path {
        typedef files::path::value_type char_t;
        typedef files::path::string_type string_t;
    };

    template<>
    inline path::string_t
    encode<path,path>(const path::string_t & from)
    {
        return from;
    }

    template<>
    inline path::string_t
    encode<path,path>(const path::char_t * from)
    {
        return path::string_t(from);
    }

}

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Folder
    : public Base<EncodingT>
    {
    private:
        files::path  m_path;

    public:
        // Constructor
        Folder();

        Folder(const typename EncodingT::string_t& path);

        FACTORY_PROTOTYPE1(Folder, In< boost::shared_ptr< Base<EncodingT> > >)
        Folder(boost::shared_ptr< Base<EncodingT> > const& path);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        // Dynamic methods
        boost::shared_ptr< Base<EncodingT> > getPath() const;

        boost::shared_ptr< Base<EncodingT> > getAbsolutePath() const;
        
        boost::shared_ptr< Base<EncodingT> > getParentPath() const;
        
        boost::shared_ptr< Base<EncodingT> > getFilename() const;

        boost::shared_ptr< Base<EncodingT> > getFiles() const;

        boost::shared_ptr< Base<EncodingT> > getFolders() const;

        boost::shared_ptr< Base<EncodingT> > exists() const;

        FACTORY_PROTOTYPE1(createFolder, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > createFolder(boost::shared_ptr< Base<EncodingT> > const& newName);

        FACTORY_PROTOTYPE2(copyTo, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void copyTo(boost::shared_ptr< Base<EncodingT> > const& name, boost::shared_ptr< Base<EncodingT> > const& folder);

        FACTORY_PROTOTYPE1(remove, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > remove(boost::shared_ptr< Base<EncodingT> > const& name);

        FACTORY_PROTOTYPE2(rename, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void rename(boost::shared_ptr< Base<EncodingT> > const& oldName, boost::shared_ptr< Base<EncodingT> > const& newName);

        boost::shared_ptr< Base<EncodingT> > getModificationDate() const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER      (Folder)
            CLASS_REGISTER1     (Folder)
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getPath, const_t, UCS("Folder::Path") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getAbsolutePath, const_t, UCS("Folder::AbsolutePath") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getParentPath, const_t, UCS("Folder::ParentPath") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getFilename, const_t, UCS("Folder::Filename") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getFiles, const_t, UCS("Folder::Files") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getFolders, const_t, UCS("Folder::Folders") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, exists, const_t, UCS("Folder::Exists") )
            METHOD_KEY_REGISTER1(Folder, boost::shared_ptr< Base<EncodingT> >, createFolder, no_const_t, UCS("Folder::CreateFolder") )
            METHOD_KEY_REGISTER2(Folder, void, copyTo, no_const_t, UCS("Folder::CopyTo") )
            METHOD_KEY_REGISTER1(Folder, boost::shared_ptr< Base<EncodingT> >, remove, no_const_t, UCS("Folder::Remove") )
            METHOD_KEY_REGISTER2(Folder, void, rename, no_const_t, UCS("Folder::Rename") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getModificationDate, const_t, UCS("Folder::ModificationDate") )
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER      (Folder)
            CLASS_UNREGISTER1     (Folder)
            METHOD_KEY_UNREGISTER (UCS("Folder::Path"))
            METHOD_KEY_UNREGISTER (UCS("Folder::AbsolutePath"))
            METHOD_KEY_UNREGISTER (UCS("Folder::ParentPath"))
            METHOD_KEY_UNREGISTER (UCS("Folder::Filename"))
            METHOD_KEY_UNREGISTER (UCS("Folder::Files"))
            METHOD_KEY_UNREGISTER (UCS("Folder::Folders"))
            METHOD_KEY_UNREGISTER (UCS("Folder::Exists"))
            METHOD_KEY_UNREGISTER1(UCS("Folder::CreateFolder"))
            METHOD_KEY_UNREGISTER2(UCS("Folder::CopyTo"))
            METHOD_KEY_UNREGISTER1(UCS("Folder::Remove"))
            METHOD_KEY_UNREGISTER2(UCS("Folder::Rename"))
            METHOD_KEY_UNREGISTER (UCS("Folder::ModificationDate"))
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#include "Folder_impl.hpp"

#endif
