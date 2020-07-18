/*
 * GitInterpreter.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _GIT_INTERPRETER_H_
#define _GIT_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "String.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	template <class EncodingT>
    class GitInterpreter
	: public Base<EncodingT>
	{
    public:
        GitInterpreter();
        virtual ~GitInterpreter();

        virtual typename EncodingT::string_t toString() const;

        virtual boost::shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        FACTORY_PROTOTYPE2(openRepository, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > openRepository(boost::shared_ptr< Base<EncodingT> >& repository, const boost::shared_ptr< Base<EncodingT> >& path) const;

		FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( GitInterpreter, UCS("Git") );
            METHOD_KEY_REGISTER2( GitInterpreter, boost::shared_ptr< Base<EncodingT> >, openRepository, const_t, UCS("Git::OpenRepository") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( UCS("Git") );
            METHOD_KEY_UNREGISTER2( UCS("Git::OpenRepository") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "GitInterpreter_impl.hpp"

#endif
