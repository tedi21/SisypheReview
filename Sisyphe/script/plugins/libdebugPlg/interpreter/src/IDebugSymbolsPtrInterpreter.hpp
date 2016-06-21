/*
 * IDebugSymbolsPtrInterpreter.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _IDEBUGSYMBOLSPTR_INTERPRETER_H_
#define _IDEBUGSYMBOLSPTR_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "DebugPtr.h"
typedef CDebugPtr<IDebugSymbols> IDebugSymbolsPtr;

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe permettant d'accéder aux informations de symboles de débogage.
	template <class EncodingT>
	class IDebugSymbolsPtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDebugSymbolsPtr m_object;

		void initValue(const IDebugSymbolsPtr& object);

		IDebugSymbolsPtr& value();

		const IDebugSymbolsPtr& value() const;

		void tidyValue();

	public:
		IDebugSymbolsPtrInterpreter();

		~IDebugSymbolsPtrInterpreter();

		IDebugSymbolsPtrInterpreter(const IDebugSymbolsPtr& object);

		IDebugSymbolsPtrInterpreter(const IDebugSymbolsPtrInterpreter<EncodingT>& rhs);

		IDebugSymbolsPtrInterpreter<EncodingT>& operator=(const IDebugSymbolsPtrInterpreter<EncodingT>& rhs);

		const IDebugSymbolsPtr& getValue() const;

		void setValue(IDebugSymbolsPtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

		FACTORY_PROTOTYPE1(appendSymbolPath, In< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > appendSymbolPath(const shared_ptr< Base<EncodingT> >& addition);

		FACTORY_PROTOTYPE2(getSymbolModule, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
		shared_ptr< Base<EncodingT> > getSymbolModule(const shared_ptr< Base<EncodingT> >& symbol, shared_ptr< Base<EncodingT> >& base);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDebugSymbolsPtrInterpreter, C("IDebugSymbolsPtr") );
			METHOD_KEY_REGISTER1( IDebugSymbolsPtrInterpreter, shared_ptr< Base<EncodingT> >, appendSymbolPath, no_const_t, C("IDebugSymbolsPtr::AppendSymbolPath") );
			METHOD_KEY_REGISTER2( IDebugSymbolsPtrInterpreter, shared_ptr< Base<EncodingT> >, getSymbolModule, no_const_t, C("IDebugSymbolsPtr::GetSymbolModule") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("IDebugSymbolsPtr") );
			METHOD_KEY_UNREGISTER1( C("IDebugSymbolsPtr::AppendSymbolPath") );
			METHOD_KEY_UNREGISTER2( C("IDebugSymbolsPtr::GetSymbolModule") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDebugSymbolsPtr(shared_ptr< Base<EncodingT> > const& val, IDebugSymbolsPtr& a);

	template <class EncodingT>
	bool reset_IDebugSymbolsPtr(shared_ptr< Base<EncodingT> >& val, IDebugSymbolsPtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDebugSymbolsPtrInterpreter_impl.hpp"

#endif