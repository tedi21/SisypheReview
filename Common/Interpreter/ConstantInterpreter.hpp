#ifndef _CONSTANT_INTERPRETER_HPP_
#define _CONSTANT_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    // Constant term
    template <class EncodingT>
    class ConstantAssignment
    : public Term<EncodingT>
    {
    private:
         typename EncodingT::string_t  m_name;
         shared_ptr< Term<EncodingT> > m_instruction;

    public:
        ConstantAssignment(typename EncodingT::string_t const& name, shared_ptr< Term<EncodingT> > const& instruction)
        : m_name(name), m_instruction(instruction)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
    };

    // ConstantOperator term
    template <class EncodingT>
    class ConstantOperator
    : public Term<EncodingT>
    {
    private:
        typename EncodingT::string_t m_name;

    public:
        ConstantOperator(typename EncodingT::string_t const& name)
        : m_name(name)
        {}    
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "ConstantInterpreter_impl.hpp"

#endif
