/*
 * JSONConverterInterpreter.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _JSON_CONVERTER_INTERPRETER_H_
#define _JSON_CONVERTER_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "Base.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	template <class EncodingT>
    class JSONConverterInterpreter
	: public Base<EncodingT>
	{
    private:
        static typename EncodingT::string_t escapeChar(const typename EncodingT::string_t& str);

        static typename EncodingT::string_t unEscapeChar(const typename EncodingT::string_t& str);

        static typename EncodingT::string_t shrinkText(const typename EncodingT::string_t& str);

        static size_t findChar(const typename EncodingT::string_t& str, const typename EncodingT::char_t& ch, size_t start);

	public:
        JSONConverterInterpreter();

        virtual typename EncodingT::string_t toString() const;

        virtual boost::shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        static typename EncodingT::string_t toNativeText(const boost::shared_ptr< Base<EncodingT> >& object);

        static boost::shared_ptr< Base<EncodingT> > fromNativeText(const typename EncodingT::string_t& nativeText);

        FACTORY_PROTOTYPE1(toText, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > toText(const boost::shared_ptr< Base<EncodingT> >& object) const;

        FACTORY_PROTOTYPE1(fromText, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > fromText(const boost::shared_ptr< Base<EncodingT> >& text) const;

		FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( JSONConverterInterpreter, C("JSONConverter") );
            METHOD_KEY_REGISTER1( JSONConverterInterpreter, boost::shared_ptr< Base<EncodingT> >, toText, const_t, C("JSONConverter::ToText") );
            METHOD_KEY_REGISTER1( JSONConverterInterpreter, boost::shared_ptr< Base<EncodingT> >, fromText, const_t, C("JSONConverter::FromText") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( C("JSONConverter") );
            METHOD_KEY_UNREGISTER1( C("JSONConverter::ToText") );
            METHOD_KEY_UNREGISTER1( C("JSONConverter::FromText") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "JSONConverterInterpreter_impl.hpp"

#endif
