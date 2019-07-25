/*
 * DiffValueInterpreter.hpp
 *
 *
 * @date 07-10-2017
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _DIFFVALUE_INTERPRETER_H_
#define _DIFFVALUE_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "Base.hpp"
#include "Array.hpp"
#include "DiffTypeInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	template <class EncodingT>
    class DiffValueInterpreter
	: public Base<EncodingT>
	{
    public:
        DiffType Type;
        int Index1;
        int Index2;
        boost::shared_ptr< Base<EncodingT> > Item1;
        boost::shared_ptr< Base<EncodingT> > Item2;

	public:
        DiffValueInterpreter();

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        boost::shared_ptr< Base<EncodingT> > getType() const;

        boost::shared_ptr< Base<EncodingT> > getIndex1() const;

        boost::shared_ptr< Base<EncodingT> > getIndex2() const;

        boost::shared_ptr< Base<EncodingT> > getItem1() const;

        boost::shared_ptr< Base<EncodingT> > getItem2() const;

		FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( DiffValueInterpreter, C("DiffValue") );
            METHOD_KEY_REGISTER ( DiffValueInterpreter, boost::shared_ptr< Base<EncodingT> >, getType, const_t, C("DiffValue::Type") );
            METHOD_KEY_REGISTER ( DiffValueInterpreter, boost::shared_ptr< Base<EncodingT> >, getIndex1, const_t, C("DiffValue::Index1") );
            METHOD_KEY_REGISTER ( DiffValueInterpreter, boost::shared_ptr< Base<EncodingT> >, getIndex2, const_t, C("DiffValue::Index2") );
            METHOD_KEY_REGISTER ( DiffValueInterpreter, boost::shared_ptr< Base<EncodingT> >, getItem1, const_t, C("DiffValue::Item1") );
            METHOD_KEY_REGISTER ( DiffValueInterpreter, boost::shared_ptr< Base<EncodingT> >, getItem2, const_t, C("DiffValue::Item2") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( C("DiffValue") );
            METHOD_KEY_UNREGISTER ( C("DiffValue::Type") );
            METHOD_KEY_UNREGISTER ( C("DiffValue::Index1") );
            METHOD_KEY_UNREGISTER ( C("DiffValue::Index2") );
            METHOD_KEY_UNREGISTER ( C("DiffValue::Item1") );
            METHOD_KEY_UNREGISTER ( C("DiffValue::Item2") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "DiffValueInterpreter_impl.hpp"

#endif
