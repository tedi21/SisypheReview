/*
 * JSONStructureFormatterInterpreter.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _JSON_STRUCTURE_FORMATTER_INTERPRETER_H_
#define _JSON_STRUCTURE_FORMATTER_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "Base.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	template <class EncodingT>
    class JSONStructureFormatterInterpreter
	: public Base<EncodingT>
	{
    private:
        typename EncodingT::string_t m_buffer;

	public:
        JSONStructureFormatterInterpreter();

        JSONStructureFormatterInterpreter(const typename EncodingT::string_t& buffer);

        virtual typename EncodingT::string_t toString() const;

        virtual boost::shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        boost::shared_ptr< Base<EncodingT> > getText() const;

        FACTORY_PROTOTYPE2(append, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void append(const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& val);

        FACTORY_PROTOTYPE2(appendAsText, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void appendAsText(const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& val);

        void clear();

		FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( JSONStructureFormatterInterpreter, C("JSONStructureFormatter") );
            METHOD_KEY_REGISTER ( JSONStructureFormatterInterpreter, boost::shared_ptr< Base<EncodingT> >, getText, const_t, C("JSONStructureFormatter::Text") );
            METHOD_KEY_REGISTER2( JSONStructureFormatterInterpreter, void, append, no_const_t, C("JSONStructureFormatter::Append") );
            METHOD_KEY_REGISTER2( JSONStructureFormatterInterpreter, void, appendAsText, no_const_t, C("JSONStructureFormatter::AppendAsText") );
            METHOD_KEY_REGISTER ( JSONStructureFormatterInterpreter, void, clear, no_const_t, C("JSONStructureFormatter::Clear") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( C("JSONStructureFormatter") );
            METHOD_KEY_UNREGISTER ( C("JSONStructureFormatter::Text") );
            METHOD_KEY_UNREGISTER2( C("JSONStructureFormatter::Append") );
            METHOD_KEY_UNREGISTER2( C("JSONStructureFormatter::AppendAsText") );
            METHOD_KEY_UNREGISTER ( C("JSONStructureFormatter::Clear") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "JSONStructureFormatterInterpreter_impl.hpp"

#endif
