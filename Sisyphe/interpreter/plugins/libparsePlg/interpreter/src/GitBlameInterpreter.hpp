#ifndef _GIT_BLAME_HPP_
#define _GIT_BLAME_HPP_

#include <boost/shared_ptr.hpp>
#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include <git2.h>

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class GitBlameInterpreter
    : public Base<EncodingT>
    {
	private:
        git_blame* m_value;
        size_t m_line;
        const git_blame_hunk* m_hunk;
		
    public:
        // Constructor
        GitBlameInterpreter();

        // Destructor
        ~GitBlameInterpreter();

        GitBlameInterpreter(git_blame* value);

        // Accessors
        git_blame* value() const;
        void value(git_blame* value);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);
        
        FACTORY_PROTOTYPE1(setLine, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > setLine(const boost::shared_ptr< Base<EncodingT> >& line);

        FACTORY_PROTOTYPE1(getCommitId, InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > getCommitId(boost::shared_ptr< Base<EncodingT> >& commitId) const;

        FACTORY_PROTOTYPE1(getCommitDate, InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > getCommitDate(boost::shared_ptr< Base<EncodingT> >& date) const;

        FACTORY_PROTOTYPE1(getCommitAuthor, InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > getCommitAuthor(boost::shared_ptr< Base<EncodingT> >& author) const;

        FACTORY_PROTOTYPE1(getCommitLine, InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > getCommitLine(boost::shared_ptr< Base<EncodingT> >& line) const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER    (GitBlameInterpreter, UCS("GitBlame"));
            METHOD_KEY_REGISTER1  (GitBlameInterpreter, boost::shared_ptr< Base<EncodingT> >, setLine, no_const_t, UCS("GitBlame::Line") );
            METHOD_KEY_REGISTER1  (GitBlameInterpreter, boost::shared_ptr< Base<EncodingT> >, getCommitId, const_t, UCS("GitBlame::GetCommitId") );
            METHOD_KEY_REGISTER1  (GitBlameInterpreter, boost::shared_ptr< Base<EncodingT> >, getCommitAuthor, const_t, UCS("GitBlame::GetCommitAuthor") );
            METHOD_KEY_REGISTER1  (GitBlameInterpreter, boost::shared_ptr< Base<EncodingT> >, getCommitDate, const_t, UCS("GitBlame::GetCommitDate") );
            METHOD_KEY_REGISTER1  (GitBlameInterpreter, boost::shared_ptr< Base<EncodingT> >, getCommitLine, const_t, UCS("GitBlame::GetCommitLine") );
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  (UCS("GitBlame"));
            METHOD_KEY_UNREGISTER1(UCS("GitBlame::Line") );
            METHOD_KEY_UNREGISTER1(UCS("GitBlame::GetCommitId") );
            METHOD_KEY_UNREGISTER1(UCS("GitBlame::GetCommitAuthor") );
            METHOD_KEY_UNREGISTER1(UCS("GitBlame::GetCommitDate") );
            METHOD_KEY_UNREGISTER1(UCS("GitBlame::GetCommitLine") );
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#include "GitBlameInterpreter_impl.hpp"

#endif
