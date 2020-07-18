#ifndef _GIT_REPOSITORY_HPP_
#define _GIT_REPOSITORY_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include <git2.h>

using namespace boost;
using namespace log4cpp;
namespace files = boost::filesystem;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class GitRepositoryInterpreter
    : public Base<EncodingT>
    {
	private:
        git_repository* m_value;
        files::path m_path;

        std::string toGitPath(const typename EncodingT::string_t& str) const;

    public:
        // Constructor
        GitRepositoryInterpreter();

        // Destructor
        ~GitRepositoryInterpreter();

        GitRepositoryInterpreter(git_repository* value, const files::path& path);

        // Accessors
        git_repository* value() const;
        void value(git_repository* value, const files::path& path);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        FACTORY_PROTOTYPE2(blame, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > blame(boost::shared_ptr< Base<EncodingT> >& blame, const boost::shared_ptr< Base<EncodingT> >& path) const;

        FACTORY_PROTOTYPE1(isUntracked, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > isUntracked(const boost::shared_ptr< Base<EncodingT> >& path) const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER    (GitRepositoryInterpreter, UCS("GitRepository"));
            METHOD_KEY_REGISTER2  (GitRepositoryInterpreter, boost::shared_ptr< Base<EncodingT> >, blame, const_t, UCS("GitRepository::Blame") );
            METHOD_KEY_REGISTER1  (GitRepositoryInterpreter, boost::shared_ptr< Base<EncodingT> >, isUntracked, const_t, UCS("GitRepository::IsUntracked") );
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  (UCS("GitRepository"));
            METHOD_KEY_UNREGISTER2(UCS("GitRepository::Blame") );
            METHOD_KEY_UNREGISTER1(UCS("GitRepository::IsUntracked") );
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#include "GitRepositoryInterpreter_impl.hpp"

#endif
