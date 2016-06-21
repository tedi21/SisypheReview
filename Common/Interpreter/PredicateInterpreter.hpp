#ifndef _PREDICATE_INTERPRETER_HPP_
#define _PREDICATE_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    // PredicateOperator term
    template <class EncodingT>
    class PredicateOperator
    : public Term<EncodingT>
    {
    private:
        typename EncodingT::string_t m_name;

    public:
        PredicateOperator(typename EncodingT::string_t const& name)
        : m_name(name)
        {}    
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "PredicateInterpreter_impl.hpp"

#endif
