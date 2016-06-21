#ifndef _PRINT_INTERPRETER_HPP_
#define _PRINT_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace std;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    // PrintInstruction term
    template <class EncodingT>
    class PrintInstruction
    : public Term<EncodingT>
    {
    private:
        shared_ptr< Term<EncodingT> > m_instruction;

    public:
        PrintInstruction(shared_ptr< Term<EncodingT> > const& instruction)
        : m_instruction(instruction)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "PrintInterpreter_impl.hpp"

#endif
