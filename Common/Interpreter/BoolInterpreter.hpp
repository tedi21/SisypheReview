#ifndef _BOOL_INTERPRETER_HPP_
#define _BOOL_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class BoolConstant
    : public Term<EncodingT>
    {
    private:
        bool m_data;
    public:
        BoolConstant(bool data)
        : m_data(data)
        {}
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "BoolInterpreter_impl.hpp"

#endif
