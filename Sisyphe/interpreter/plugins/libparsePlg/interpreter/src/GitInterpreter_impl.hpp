/*
 * GitInterpreter_impl.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#include <git2.h>
#include "GitRepositoryInterpreter.hpp"
#include "Folder.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)
#define P(str) encode<EncodingT,enc::path>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
GitInterpreter<EncodingT>::GitInterpreter()
{
    git_libgit2_init();
}

template <class EncodingT>
GitInterpreter<EncodingT>::~GitInterpreter()
{
    git_libgit2_shutdown();
}


template <class EncodingT>
typename EncodingT::string_t GitInterpreter<EncodingT>::toString() const
{
    return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > GitInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new GitInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t GitInterpreter<EncodingT>::getClassName() const
{
    return UCS("Git");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > GitInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
    boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
    ParameterArray args, ret;
    if (check_parameters_array(params, args))
    {
        if (tryInvoke(this, UCS("Git"), method, args, ret) ||
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
            Category* logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Unexpected call in Git, no method \"" << A(method) << "\" exists.";
        }
    }
    return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > GitInterpreter<EncodingT>::openRepository(boost::shared_ptr< Base<EncodingT> >& repository, const boost::shared_ptr< Base<EncodingT> >& path) const
{
    boost::shared_ptr< Bool<EncodingT> > ret = boost::make_shared< Bool<EncodingT> >(false);
    boost::shared_ptr< String<EncodingT> > nativePath = dynamic_pointer_cast< String<EncodingT> >(path);
    boost::shared_ptr< GitRepositoryInterpreter<EncodingT> > nativeRepository = dynamic_pointer_cast< GitRepositoryInterpreter<EncodingT> >(repository);
    if (nativePath != nullptr && nativeRepository != nullptr)
    {
        files::path path = files::system_complete(P(nativePath->value()));
        while ((!files::exists(path/".git")) && path.has_parent_path())
        {
            path = path.parent_path();
        }
        git_repository* gitRepository = nullptr;
        int res = git_repository_open(&gitRepository, path.generic_string().c_str());
        ret->value(res == 0);
        if (res == 0)
        {
            nativeRepository->value(gitRepository, path);
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(GitRepository, String) expected, got (" << A(repository->getClassName()) << ", " << A(path->getClassName()) << ")";
    }
    return ret;
}

NAMESPACE_END

#undef A
#undef C
#undef P
