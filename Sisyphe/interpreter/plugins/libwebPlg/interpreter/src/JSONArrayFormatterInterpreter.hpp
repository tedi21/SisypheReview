/*
 * JSONArrayFormatterInterpreter.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _JSON_ARRAY_FORMATTER_INTERPRETER_H_
#define _JSON_ARRAY_FORMATTER_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	template <class EncodingT>
    class JSONArrayFormatterInterpreter
	: public Base<EncodingT>
	{
    private:
        typename EncodingT::string_t m_buffer;

	public:
        JSONArrayFormatterInterpreter();

        JSONArrayFormatterInterpreter(const typename EncodingT::string_t& buffer);

        virtual typename EncodingT::string_t toString() const;

        virtual boost::shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        boost::shared_ptr< Base<EncodingT> > getText() const;

        FACTORY_PROTOTYPE1(append, In< boost::shared_ptr< Base<EncodingT> > >)
        void append(const boost::shared_ptr< Base<EncodingT> >& val);

        FACTORY_PROTOTYPE1(appendAsText, In< boost::shared_ptr< Base<EncodingT> > >)
        void appendAsText(const boost::shared_ptr< Base<EncodingT> >& val);

        void clear();

		FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( JSONArrayFormatterInterpreter, UCS("JSONArrayFormatter") );
            METHOD_KEY_REGISTER ( JSONArrayFormatterInterpreter, boost::shared_ptr< Base<EncodingT> >, getText, const_t, UCS("JSONArrayFormatter::Text") );
            METHOD_KEY_REGISTER1( JSONArrayFormatterInterpreter, void, append, no_const_t, UCS("JSONArrayFormatter::Append") );
            METHOD_KEY_REGISTER1( JSONArrayFormatterInterpreter, void, appendAsText, no_const_t, UCS("JSONArrayFormatter::AppendAsText") );
            METHOD_KEY_REGISTER ( JSONArrayFormatterInterpreter, void, clear, no_const_t, UCS("JSONArrayFormatter::Clear") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( UCS("JSONArrayFormatter") );
            METHOD_KEY_UNREGISTER ( UCS("JSONArrayFormatter::Text") );
            METHOD_KEY_UNREGISTER1( UCS("JSONArrayFormatter::Append") );
            METHOD_KEY_UNREGISTER1( UCS("JSONArrayFormatter::AppendAsText") );
            METHOD_KEY_UNREGISTER ( UCS("JSONArrayFormatter::Clear") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "JSONArrayFormatterInterpreter_impl.hpp"

#endif
