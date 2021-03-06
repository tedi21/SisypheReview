#ifndef _NUMERIC_INTERPRETER_HPP_
#define _NUMERIC_INTERPRETER_HPP_

#include "Interpreter.hpp"
#include <variant>

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class NumericConstant
    : public Term<EncodingT>
    {
    private:
        std::variant<long long,double> m_data;
    public:
        NumericConstant(const std::variant<long long,double>& data)
        : m_data(data)
        {}
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "NumericInterpreter_impl.hpp"

#endif
