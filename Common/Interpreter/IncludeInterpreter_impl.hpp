#include "ProgramInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > IncludeInstruction<EncodingT>::interpret(Context<EncodingT> & c)
    {
        typename EncodingT::string_t buf;
        shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>(false));
        shared_ptr< Base<EncodingT> > expr = m_instruction->interpret(c);

        Category * logger = &Category::getInstance(LOGNAME);
        if (!readFile(A(expr->toString()), buf))
        {
            logger->errorStream() << "Cannot open file '" << A(expr->toString()) << "'.";
        }
        else
        {
            typename EncodingT::string_t instructions;
            shared_ptr< Term<EncodingT> > declaration, block;
            if (Declaration<EncodingT>::parse(buf, declaration, instructions) &&
                Block<EncodingT>::parse(instructions, block))
            {
                declaration->interpret(c);
                block->interpret(c);
                res->setValue(true);
            }
            else
            {
                logger->errorStream() << "An error occurred during the file interpretation '" << A(expr->toString()) << "'.";
            }
        }
        return res;
    }

    template <class EncodingT>
    bool IncludeInstruction<EncodingT>::parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr;
        shared_ptr< Term<EncodingT> > expr_value;
        bool success = prefix<EncodingT>(buf, C("include"), expr) &&
                       Bracket<EncodingT>::parse(expr, expr_value);
        if (success)
        {
            value.reset(new IncludeInstruction<EncodingT>(expr_value));
        }
        return success;
    }

NAMESPACE_END

#undef C
#undef A
