/*
 * DebugOutCTLInterpreter.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _DEBUGOUTCTL_INTERPRETER_H_
#define _DEBUGOUTCTL_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"


#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	template <class EncodingT>
	class DebugOutCTLInterpreter
	: public Base<EncodingT>
	{
	private:

		void tidyValue();

	public:
		DebugOutCTLInterpreter();

		~DebugOutCTLInterpreter();

		virtual typename EncodingT::string_t toString() const;

		virtual shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

		shared_ptr< Base<EncodingT> > getDEBUG_OUTCTL_THIS_CLIENT() const;

		shared_ptr< Base<EncodingT> > getDEBUG_OUTCTL_ALL_CLIENTS() const;

		shared_ptr< Base<EncodingT> > getDEBUG_OUTCTL_ALL_OTHER_CLIENTS() const;

		shared_ptr< Base<EncodingT> > getDEBUG_OUTCTL_IGNORE() const;

		shared_ptr< Base<EncodingT> > getDEBUG_OUTCTL_LOG_ONLY() const;

		shared_ptr< Base<EncodingT> > getDEBUG_OUTCTL_SEND_MASK() const;

		shared_ptr< Base<EncodingT> > getDEBUG_OUTCTL_NOT_LOGGED() const;

		shared_ptr< Base<EncodingT> > getDEBUG_OUTCTL_OVERRIDE_MASK() const;

		shared_ptr< Base<EncodingT> > getDEBUG_OUTCTL_AMBIENT() const;

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( DebugOutCTLInterpreter, C("DebugOutCTL") );
			METHOD_KEY_REGISTER ( DebugOutCTLInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_OUTCTL_THIS_CLIENT, const_t, C("DebugOutCTL::DEBUG_OUTCTL_THIS_CLIENT") );
			METHOD_KEY_REGISTER ( DebugOutCTLInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_OUTCTL_ALL_CLIENTS, const_t, C("DebugOutCTL::DEBUG_OUTCTL_ALL_CLIENTS") );
			METHOD_KEY_REGISTER ( DebugOutCTLInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_OUTCTL_ALL_OTHER_CLIENTS, const_t, C("DebugOutCTL::DEBUG_OUTCTL_ALL_OTHER_CLIENTS") );
			METHOD_KEY_REGISTER ( DebugOutCTLInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_OUTCTL_IGNORE, const_t, C("DebugOutCTL::DEBUG_OUTCTL_IGNORE") );
			METHOD_KEY_REGISTER ( DebugOutCTLInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_OUTCTL_LOG_ONLY, const_t, C("DebugOutCTL::DEBUG_OUTCTL_LOG_ONLY") );
			METHOD_KEY_REGISTER ( DebugOutCTLInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_OUTCTL_SEND_MASK, const_t, C("DebugOutCTL::DEBUG_OUTCTL_SEND_MASK") );
			METHOD_KEY_REGISTER ( DebugOutCTLInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_OUTCTL_NOT_LOGGED, const_t, C("DebugOutCTL::DEBUG_OUTCTL_NOT_LOGGED") );
			METHOD_KEY_REGISTER ( DebugOutCTLInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_OUTCTL_OVERRIDE_MASK, const_t, C("DebugOutCTL::DEBUG_OUTCTL_OVERRIDE_MASK") );
			METHOD_KEY_REGISTER ( DebugOutCTLInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_OUTCTL_AMBIENT, const_t, C("DebugOutCTL::DEBUG_OUTCTL_AMBIENT") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("DebugOutCTL") );
			METHOD_KEY_UNREGISTER ( C("DebugOutCTL::DEBUG_OUTCTL_THIS_CLIENT") );
			METHOD_KEY_UNREGISTER ( C("DebugOutCTL::DEBUG_OUTCTL_ALL_CLIENTS") );
			METHOD_KEY_UNREGISTER ( C("DebugOutCTL::DEBUG_OUTCTL_ALL_OTHER_CLIENTS") );
			METHOD_KEY_UNREGISTER ( C("DebugOutCTL::DEBUG_OUTCTL_IGNORE") );
			METHOD_KEY_UNREGISTER ( C("DebugOutCTL::DEBUG_OUTCTL_LOG_ONLY") );
			METHOD_KEY_UNREGISTER ( C("DebugOutCTL::DEBUG_OUTCTL_SEND_MASK") );
			METHOD_KEY_UNREGISTER ( C("DebugOutCTL::DEBUG_OUTCTL_NOT_LOGGED") );
			METHOD_KEY_UNREGISTER ( C("DebugOutCTL::DEBUG_OUTCTL_OVERRIDE_MASK") );
			METHOD_KEY_UNREGISTER ( C("DebugOutCTL::DEBUG_OUTCTL_AMBIENT") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "DebugOutCTLInterpreter_impl.hpp"

#endif