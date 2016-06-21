/*
 * IDebugBreakpointPtrInterpreter.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _IDEBUGBREAKPOINTPTR_INTERPRETER_H_
#define _IDEBUGBREAKPOINTPTR_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "DebugPtr.h"
typedef CDebugPtr<IDebugBreakpoint> IDebugBreakpointPtr;

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe permettant d'accéder aux informations d'un breakpoint.
	template <class EncodingT>
	class IDebugBreakpointPtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDebugBreakpointPtr m_object;

		void initValue(const IDebugBreakpointPtr& object);

		IDebugBreakpointPtr& value();

		const IDebugBreakpointPtr& value() const;

		void tidyValue();

	public:
		IDebugBreakpointPtrInterpreter();

		~IDebugBreakpointPtrInterpreter();

		IDebugBreakpointPtrInterpreter(const IDebugBreakpointPtr& object);

		IDebugBreakpointPtrInterpreter(const IDebugBreakpointPtrInterpreter<EncodingT>& rhs);

		IDebugBreakpointPtrInterpreter<EncodingT>& operator=(const IDebugBreakpointPtrInterpreter<EncodingT>& rhs);

		const IDebugBreakpointPtr& getValue() const;

		void setValue(IDebugBreakpointPtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

		// Sets the location that triggers a breakpoint.
		FACTORY_PROTOTYPE1(setOffset, In< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > setOffset(const shared_ptr< Base<EncodingT> >& offset);

		// Sets the flags for a breakpoint.
		FACTORY_PROTOTYPE1(setFlags, In< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > setFlags(const shared_ptr< Base<EncodingT> >& flags);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDebugBreakpointPtrInterpreter, C("IDebugBreakpointPtr") );
			METHOD_KEY_REGISTER1( IDebugBreakpointPtrInterpreter, shared_ptr< Base<EncodingT> >, setOffset, no_const_t, C("IDebugBreakpointPtr::SetOffset") );
			METHOD_KEY_REGISTER1( IDebugBreakpointPtrInterpreter, shared_ptr< Base<EncodingT> >, setFlags, no_const_t, C("IDebugBreakpointPtr::SetFlags") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("IDebugBreakpointPtr") );
			METHOD_KEY_UNREGISTER1( C("IDebugBreakpointPtr::SetOffset") );
			METHOD_KEY_UNREGISTER1( C("IDebugBreakpointPtr::SetFlags") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDebugBreakpointPtr(shared_ptr< Base<EncodingT> > const& val, IDebugBreakpointPtr& a);

	template <class EncodingT>
	bool reset_IDebugBreakpointPtr(shared_ptr< Base<EncodingT> >& val, IDebugBreakpointPtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDebugBreakpointPtrInterpreter_impl.hpp"

#endif