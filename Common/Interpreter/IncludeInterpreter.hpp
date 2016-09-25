#ifndef _INCLUDE_INTERPRETER_HPP_
#define _INCLUDE_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace std;
using namespace log4cpp;

bool readFile(string const& filename, ucs::string_t & buf);

NAMESPACE_BEGIN(interp)

    // IncludeInstruction term
    template <class EncodingT>
    class IncludeInstruction
    : public Term<EncodingT>
    {
    private:
        boost::shared_ptr< Term<EncodingT> > m_instruction;

    public:
        IncludeInstruction(boost::shared_ptr< Term<EncodingT> > const& instruction)
        : m_instruction(instruction)
        {}
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "IncludeInterpreter_impl.hpp"

#endif
