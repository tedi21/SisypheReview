#include "GitBlameInterpreter.hpp"
#include "Folder.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define P(str) encode<EncodingT,enc::path>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    GitRepositoryInterpreter<EncodingT>::GitRepositoryInterpreter()
    {
        m_value = nullptr;
    }

    template <class EncodingT>
    GitRepositoryInterpreter<EncodingT>::~GitRepositoryInterpreter()
    {
        if (m_value != nullptr)
        {
            git_repository_free(m_value);
        }
    }

    template <class EncodingT>
    GitRepositoryInterpreter<EncodingT>::GitRepositoryInterpreter(git_repository* value, const files::path& path)
    {
        m_value = value;
        m_path = path;
    }

    template <class EncodingT>
    git_repository* GitRepositoryInterpreter<EncodingT>::value() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void GitRepositoryInterpreter<EncodingT>::value(git_repository* value, const files::path& path)
    {
        if (m_value != nullptr)
        {
            git_repository_free(m_value);
        }
        m_value = value;
        m_path = path;
    }

    template <class EncodingT>
    typename EncodingT::string_t GitRepositoryInterpreter<EncodingT>::toString() const
    {
        return EncodingT::EMPTY;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitRepositoryInterpreter<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new GitRepositoryInterpreter<EncodingT>(m_value, m_path));
    }

    template <class EncodingT>
    typename EncodingT::string_t GitRepositoryInterpreter<EncodingT>::getClassName() const
    {
        return UCS("GitRepository");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitRepositoryInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, UCS("GitRepository"), method, args, ret)   ||
                tryInvoke(this, UCS("Base"), method, args, ret))
            {
                find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
                for (size_t i = 0; i < params.size(); ++i)
                {
                    find_parameter(ret, i, params[i]);
                }
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Unexpected call in GitRepository, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    std::string GitRepositoryInterpreter<EncodingT>::toGitPath(const typename EncodingT::string_t& str) const
    {
        files::path rel = files::relative(files::system_complete(P(str)), m_path);
        return rel.generic_string();
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitRepositoryInterpreter<EncodingT>::blame(boost::shared_ptr< Base<EncodingT> >& blame, const boost::shared_ptr< Base<EncodingT> >& path) const
    {
        boost::shared_ptr< Bool<EncodingT> > ret = boost::make_shared< Bool<EncodingT> >(false);
        if (m_value)
        {
            boost::shared_ptr< String<EncodingT> > nativePath = dynamic_pointer_cast< String<EncodingT> >(path);
            boost::shared_ptr< GitBlameInterpreter<EncodingT> > nativeBlame = dynamic_pointer_cast< GitBlameInterpreter<EncodingT> >(blame);
            if (nativePath != nullptr && nativeBlame != nullptr)
            {
                git_blame* gitBlame = nullptr;
                std::string strPath = toGitPath(nativePath->value());
                int res = git_blame_file(&gitBlame, m_value, strPath.c_str(), nullptr);
                ret->value(res == 0);
                if (res == 0)
                {
                    nativeBlame->value(gitBlame);
                }
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "(GitBlame, String) expected, got (" << A(blame->getClassName()) << ", " << A(path->getClassName()) << ")";
            }
        }
        return ret;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitRepositoryInterpreter<EncodingT>::isUntracked(const boost::shared_ptr< Base<EncodingT> >& path) const
    {
        boost::shared_ptr< Bool<EncodingT> > ret = boost::make_shared< Bool<EncodingT> >(true);
        if (m_value)
        {
            boost::shared_ptr< String<EncodingT> > nativePath = dynamic_pointer_cast< String<EncodingT> >(path);
            if (nativePath != nullptr)
            {
                unsigned int gitStatus = 0U;
                std::string strPath = toGitPath(nativePath->value());
                int res = git_status_file(&gitStatus, m_value, strPath.c_str());
                ret->value(res == GIT_ENOTFOUND || gitStatus == GIT_STATUS_WT_NEW);
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "String expected, got " << A(path->getClassName());
            }
        }
        return ret;
    }

NAMESPACE_END

#undef A
#undef P
