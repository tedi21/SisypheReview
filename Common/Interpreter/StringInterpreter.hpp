#ifndef _STRING_INTERPRETER_HPP_
#define _STRING_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class StringConstant
    : public Term<EncodingT>
    {
    private:
        typename EncodingT::string_t m_data;

    public:
        StringConstant(typename EncodingT::string_t const& data)
        : m_data(data)
        {}
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "StringInterpreter_impl.hpp"

#endif
