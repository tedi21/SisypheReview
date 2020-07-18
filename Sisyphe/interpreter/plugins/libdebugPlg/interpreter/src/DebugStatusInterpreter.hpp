/*
 * DebugStatusInterpreter.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _DEBUGSTATUS_INTERPRETER_H_
#define _DEBUGSTATUS_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
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

	public:
		DebugStatusInterpreter();

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_NO_CHANGE() const;

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_GO() const;

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_GO_HANDLED() const;

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_GO_NOT_HANDLED() const;

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_STEP_OVER() const;

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_STEP_INTO() const;

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_BREAK() const;

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_NO_DEBUGGEE() const;

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_STEP_BRANCH() const;

		boost::shared_ptr< Base<EncodingT> > getDEBUG_STATUS_IGNORE_EVENT() const;

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( DebugStatusInterpreter, UCS("DebugStatus") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_NO_CHANGE, const_t, UCS("DebugStatus::DEBUG_STATUS_NO_CHANGE") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_GO, const_t, UCS("DebugStatus::DEBUG_STATUS_GO") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_GO_HANDLED, const_t, UCS("DebugStatus::DEBUG_STATUS_GO_HANDLED") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_GO_NOT_HANDLED, const_t, UCS("DebugStatus::DEBUG_STATUS_GO_NOT_HANDLED") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_STEP_OVER, const_t, UCS("DebugStatus::DEBUG_STATUS_STEP_OVER") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_STEP_INTO, const_t, UCS("DebugStatus::DEBUG_STATUS_STEP_INTO") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_BREAK, const_t, UCS("DebugStatus::DEBUG_STATUS_BREAK") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_NO_DEBUGGEE, const_t, UCS("DebugStatus::DEBUG_STATUS_NO_DEBUGGEE") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_STEP_BRANCH, const_t, UCS("DebugStatus::DEBUG_STATUS_STEP_BRANCH") );
			METHOD_KEY_REGISTER ( DebugStatusInterpreter, boost::shared_ptr< Base<EncodingT> >, getDEBUG_STATUS_IGNORE_EVENT, const_t, UCS("DebugStatus::DEBUG_STATUS_IGNORE_EVENT") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( UCS("DebugStatus") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_NO_CHANGE") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_GO") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_GO_HANDLED") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_GO_NOT_HANDLED") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_STEP_OVER") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_STEP_INTO") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_BREAK") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_NO_DEBUGGEE") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_STEP_BRANCH") );
			METHOD_KEY_UNREGISTER ( UCS("DebugStatus::DEBUG_STATUS_IGNORE_EVENT") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "DebugStatusInterpreter_impl.hpp"

#endif