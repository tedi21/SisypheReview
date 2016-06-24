/*
 * DebugValueInterpreter.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _DEBUGVALUE_INTERPRETER_H_
#define _DEBUGVALUE_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"


#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	template <class EncodingT>
	class DebugValueInterpreter
	: public Base<EncodingT>
	{
	private:

		void tidyValue();

	public:
		DebugValueInterpreter();

		~DebugValueInterpreter();

		virtual typename EncodingT::string_t toString() const;

		virtual shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_INT8() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_INT16() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_INT32() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_INT64() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_FLOAT32() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_FLOAT64() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_FLOAT80() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_FLOAT82() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_FLOAT128() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_VECTOR64() const;

		shared_ptr< Base<EncodingT> > getDEBUG_VALUE_VECTOR128() const;

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( DebugValueInterpreter, C("DebugValue") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_INT8, const_t, C("DebugValue::DEBUG_VALUE_INT8") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_INT16, const_t, C("DebugValue::DEBUG_VALUE_INT16") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_INT32, const_t, C("DebugValue::DEBUG_VALUE_INT32") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_INT64, const_t, C("DebugValue::DEBUG_VALUE_INT64") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_FLOAT32, const_t, C("DebugValue::DEBUG_VALUE_FLOAT32") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_FLOAT64, const_t, C("DebugValue::DEBUG_VALUE_FLOAT64") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_FLOAT80, const_t, C("DebugValue::DEBUG_VALUE_FLOAT80") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_FLOAT82, const_t, C("DebugValue::DEBUG_VALUE_FLOAT82") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_FLOAT128, const_t, C("DebugValue::DEBUG_VALUE_FLOAT128") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_VECTOR64, const_t, C("DebugValue::DEBUG_VALUE_VECTOR64") );
			METHOD_KEY_REGISTER ( DebugValueInterpreter, shared_ptr< Base<EncodingT> >, getDEBUG_VALUE_VECTOR128, const_t, C("DebugValue::DEBUG_VALUE_VECTOR128") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("DebugValue") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_INT8") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_INT16") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_INT32") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_INT64") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_FLOAT32") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_FLOAT64") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_FLOAT80") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_FLOAT82") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_FLOAT128") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_VECTOR64") );
			METHOD_KEY_UNREGISTER ( C("DebugValue::DEBUG_VALUE_VECTOR128") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "DebugValueInterpreter_impl.hpp"

#endif