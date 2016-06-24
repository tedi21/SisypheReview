/*
 * DebugStatusInterpreter.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _DEBUGSTATUS_INTERPRETER_H_
#define _DEBUGSTATUS_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"


#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Spécifie l'état du moteur de débogage
	template <class EncodingT>
	class DebugStatusInterpreter
	: public Base<EncodingT>
	{
	private:

		void tidyValue();

	public:
		DebugStatusInterpreter();

		~DebugStatusInterpreter();

		virtual typename EncodingT::string_t toString() const;

		virtual shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_NO_CHANGE() const;

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_GO() const;

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_GO_HANDLED() const;

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_GO_NOT_HANDLED() const;

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_STEP_OVER() const;

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_STEP_INTO() const;

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_BREAK() const;

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_NO_DEBUGGEE() const;

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_STEP_BRANCH() const;

		shared_ptr< Base<EncodingT> > getDEBUG_STATUS_IGNORE_EVENT() const;

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( DebugStatusInterpreter, C("DebugStatus") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_NO_CHANGE, const_t, C("DebugStatus::DEBUG_STATUS_NO_CHANGE") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_GO, const_t, C("DebugStatus::DEBUG_STATUS_GO") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_GO_HANDLED, const_t, C("DebugStatus::DEBUG_STATUS_GO_HANDLED") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_GO_NOT_HANDLED, const_t, C("DebugStatus::DEBUG_STATUS_GO_NOT_HANDLED") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_STEP_OVER, const_t, C("DebugStatus::DEBUG_STATUS_STEP_OVER") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_STEP_INTO, const_t, C("DebugStatus::DEBUG_STATUS_STEP_INTO") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_BREAK, const_t, C("DebugStatus::DEBUG_STATUS_BREAK") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_NO_DEBUGGEE, const_t, C("DebugStatus::DEBUG_STATUS_NO_DEBUGGEE") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_STEP_BRANCH, const_t, C("DebugStatus::DEBUG_STATUS_STEP_BRANCH") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_IGNORE_EVENT, const_t, C("DebugStatus::DEBUG_STATUS_IGNORE_EVENT") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("DebugStatus") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_NO_CHANGE") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_GO") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_GO_HANDLED") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_GO_NOT_HANDLED") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_STEP_OVER") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_STEP_INTO") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_BREAK") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_NO_DEBUGGEE") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_STEP_BRANCH") );
			METHOD_KEY_UNREGISTER ( C("DebugStatus::DEBUG_STATUS_IGNORE_EVENT") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "DebugStatusInterpreter_impl.hpp"

#endif