#ifndef _SYSTEM_INTERPRETER_HPP_
#define _SYSTEM_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace std;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    // SystemInstruction term
    template <class EncodingT>
    class SystemInstruction
    : public Term<EncodingT>
    {
    private:
        boost::shared_ptr< Term<EncodingT> > m_instruction;

    public:
        SystemInstruction(boost::shared_ptr< Term<EncodingT> > const& instruction)
        : m_instruction(instruction)
        {}
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "SystemInterpreter_impl.hpp"

#endif
