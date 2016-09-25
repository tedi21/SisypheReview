#ifndef _FOLDER_HPP_
#define _FOLDER_HPP_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost;
using namespace log4cpp;
namespace files = boost::filesystem;

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Folder
    : public String<EncodingT>
    {
    private:
        files::path  m_path;

    public:
        // Constructor
        Folder();

        Folder(const typename EncodingT::string_t& path);

        FACTORY_PROTOTYPE1(Folder, In< boost::shared_ptr< Base<EncodingT> > >)
        Folder(boost::shared_ptr< Base<EncodingT> > const& path);

        // Destructor
        ~Folder();

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        // Dynamic methods
        boost::shared_ptr< Base<EncodingT> > getPath() const;

        boost::shared_ptr< Base<EncodingT> > getAbsolutePath() const;

        boost::shared_ptr< Base<EncodingT> > getFiles() const;

        boost::shared_ptr< Base<EncodingT> > getFolders() const;

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
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getPath, const_t, C("Folder::Path") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getAbsolutePath, const_t, C("Folder::AbsolutePath") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getFiles, const_t, C("Folder::Files") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getFolders, const_t, C("Folder::Folders") )
            METHOD_KEY_REGISTER1(Folder, boost::shared_ptr< Base<EncodingT> >, createFolder, no_const_t, C("Folder::CreateFolder") )
            METHOD_KEY_REGISTER2(Folder, void, copyTo, no_const_t, C("Folder::CopyTo") )
            METHOD_KEY_REGISTER1(Folder, boost::shared_ptr< Base<EncodingT> >, remove, no_const_t, C("Folder::Remove") )
            METHOD_KEY_REGISTER2(Folder, void, rename, no_const_t, C("Folder::Rename") )
            METHOD_KEY_REGISTER (Folder, boost::shared_ptr< Base<EncodingT> >, getModificationDate, const_t, C("Folder::ModificationDate") )
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER      (Folder)
            CLASS_UNREGISTER1     (Folder)
            METHOD_KEY_UNREGISTER (C("Folder::Path"))
            METHOD_KEY_UNREGISTER (C("Folder::AbsolutePath"))
            METHOD_KEY_UNREGISTER (C("Folder::Files"))
            METHOD_KEY_UNREGISTER (C("Folder::Folders"))
            METHOD_KEY_UNREGISTER1(C("Folder::CreateFolder"))
            METHOD_KEY_UNREGISTER2(C("Folder::CopyTo"))
            METHOD_KEY_UNREGISTER1(C("Folder::Remove"))
            METHOD_KEY_UNREGISTER2(C("Folder::Rename"))
            METHOD_KEY_UNREGISTER (C("Folder::ModificationDate"))
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#undef C
#undef A

#include "folder_impl.hpp"

#endif
