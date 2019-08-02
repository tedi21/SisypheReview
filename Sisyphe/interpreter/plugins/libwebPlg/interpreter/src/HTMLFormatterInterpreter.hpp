/*
 * HTMLFormatterInterpreter.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _HTML_FORMATTER_INTERPRETER_H_
#define _HTML_FORMATTER_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	template <class EncodingT>
    class HTMLFormatterInterpreter
	: public Base<EncodingT>
	{
    private:
        static const std::set<typename EncodingT::string_t> KEYWORDS;
        static const std::set<typename EncodingT::string_t> TYPES;

        static typename EncodingT::string_t purify(const typename EncodingT::string_t& str);

        static size_t spaceRTL(const typename EncodingT::string_t& str, const size_t right, const size_t left);

        static size_t spaceLTR(const typename EncodingT::string_t& str, const size_t left, const size_t right);

        static typename EncodingT::string_t formatCpp(const typename EncodingT::string_t& content);

	public:
        HTMLFormatterInterpreter();

        virtual typename EncodingT::string_t toString() const;

        virtual boost::shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        FACTORY_PROTOTYPE1(prettyPrint, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > prettyPrint(const boost::shared_ptr< Base<EncodingT> >& source) const;

		FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( HTMLFormatterInterpreter, UCS("HTMLFormatter") );
            METHOD_KEY_REGISTER1( HTMLFormatterInterpreter, boost::shared_ptr< Base<EncodingT> >, prettyPrint, const_t, UCS("HTMLFormatter::PrettyPrint") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( UCS("HTMLFormatter") );
            METHOD_KEY_UNREGISTER1( UCS("HTMLFormatter::PrettyPrint") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "HTMLFormatterInterpreter_impl.hpp"

#endif
