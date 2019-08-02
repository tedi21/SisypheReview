/*
 * DiffTypeInterpreter.hpp
 *
 *
 * @date 07-10-2017
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _DIFFTYPE_INTERPRETER_H_
#define _DIFFTYPE_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"


#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

    enum DiffType : unsigned short
    {
        DIFF_TYPE_NONE = 0,
        DIFF_TYPE_ADD,
        DIFF_TYPE_DELETE,
        DIFF_TYPE_MODIFY
    };

	template <class EncodingT>
    class DiffTypeInterpreter
	: public Base<EncodingT>
	{        
	public:
        DiffTypeInterpreter();

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        boost::shared_ptr< Base<EncodingT> > getNONE() const;

        boost::shared_ptr< Base<EncodingT> > getADD() const;

        boost::shared_ptr< Base<EncodingT> > getDELETE() const;

        boost::shared_ptr< Base<EncodingT> > getMODIFY() const;

		FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( DiffTypeInterpreter, UCS("DiffType") );
            METHOD_KEY_REGISTER ( DiffTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getNONE, const_t, UCS("DiffType::NONE") );
            METHOD_KEY_REGISTER ( DiffTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getADD, const_t, UCS("DiffType::ADD") );
            METHOD_KEY_REGISTER ( DiffTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getDELETE, const_t, UCS("DiffType::DELETE") );
            METHOD_KEY_REGISTER ( DiffTypeInterpreter, boost::shared_ptr< Base<EncodingT> >, getMODIFY, const_t, UCS("DiffType::MODIFY") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( UCS("DiffType") );
            METHOD_KEY_UNREGISTER ( UCS("DiffType::NONE") );
            METHOD_KEY_UNREGISTER ( UCS("DiffType::ADD") );
            METHOD_KEY_UNREGISTER ( UCS("DiffType::DELETE") );
            METHOD_KEY_UNREGISTER ( UCS("DiffType::MODIFY") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "DiffTypeInterpreter_impl.hpp"

#endif
