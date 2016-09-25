#include "StringInterpreter.hpp"
#include "BoolInterpreter.hpp"
#include "NumericInterpreter.hpp"
#include "ArrayInterpreter.hpp"
#include "OperatorInterpreter.hpp"
#include "MemoryInterpreter.hpp"
#include "IncludeInterpreter.hpp"
#include "PrintInterpreter.hpp"
#include "SystemInterpreter.hpp"
#include "FunctionInterpreter.hpp"
#include "PredicateInterpreter.hpp"
#include "ConstantInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Program<EncodingT>::interpret(Context<EncodingT> & c)
    {
        m_declaration->interpret(c);
        return m_block->interpret(c);
    }

    template <class EncodingT>
    bool Program<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        bool success = false;
        typename EncodingT::string_t instructions;
        boost::shared_ptr< Term<EncodingT> > block;
        boost::shared_ptr< Term<EncodingT> > declaration;
        success = Declaration<EncodingT>::parse(buf, declaration, instructions) &&
                  Block<EncodingT>::parse(instructions, block, true);
        // clean program analysis
        Instruction<EncodingT>::clean();
        Assignable<EncodingT>::clean();
        if (success)
        {
            value.reset(new Program<EncodingT>(declaration, block));
        }
        return success;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Declaration<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > ret(new Base<EncodingT>());
        // Définit les constantes
        for (iterator i = m_constants.begin(); i < m_constants.end(); ++i)
        {
            (*i)->interpret(c);
        }
        // Declare les fonctions
        for (iterator i = m_functions.begin(); i < m_functions.end(); ++i)
        {
            boost::shared_ptr< Function<EncodingT> > function = dynamic_pointer_cast< Function<EncodingT> >(*i);
            if (function)
            {
                c.declare(function->getName(), function);
            }
        }
        return ret;
    }

    template <class EncodingT>
    bool Declaration<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value, typename EncodingT::string_t & instructions)
    {
        vector< boost::shared_ptr< Term<EncodingT> > > constantsList;
        vector< boost::shared_ptr< Term<EncodingT> > > functionsList;
        boost::shared_ptr< Term<EncodingT> > declaration;
        typename EncodingT::string_t sequence;
        Category * logger = &Category::getInstance(LOGNAME);
        typename EncodingT::string_t::const_iterator i = buf.begin();
        typename EncodingT::string_t::const_iterator j = buf.begin();
        typename EncodingT::string_t::const_iterator end = buf.end();

        bool success = true;
        bool parsing = true;
        // Declaration has two blocks : constants list followed by functions
        // we start by the constants list
        bool insideConstantList = true;
        while (i!=end && success && parsing)
        {
            // advance to first no space character
            i = next_word<EncodingT>(i, end);

            if (i != end)
            {
                if ((j = CommentBlock<EncodingT>::look_for(i, buf.end())) != i)
                {
                    sequence.assign(i, j);
                    declaration.reset();
                    success = CommentBlock<EncodingT>::parse(sequence, declaration);
                    if (success)
                    {
                        // advance index
                        i = j;
                    }
                }
                // constant list
                else if (insideConstantList &&
                         (j = ConstantsList<EncodingT>::look_for(i, buf.end())) != i)
                {
                    sequence.assign(i, j);
                    declaration.reset();
                    success = ConstantsList<EncodingT>::parse(sequence, declaration);
                    if (success)
                    {
                        // add instruction
                        constantsList.push_back(declaration);
                        // advance index
                        i = j;
                    }
                }
                // function block
                else if ((j = Function<EncodingT>::look_for(i, buf.end())) != i)
                {
                    // the constants list is ended, we read the functions block
                    insideConstantList = false;
                    sequence.assign(i, j);
                    declaration.reset();
                    success = Function<EncodingT>::parse(sequence, declaration);
                    if (success)
                    {
                        // add function
                        functionsList.push_back(declaration);
                        // advance index
                        i = j;
                    }
                }
                else
                {
                    parsing = false;
                }
            }
        }
        if (success)
        {
            value.reset(new Declaration<EncodingT>(constantsList, functionsList));
            instructions.assign(i, end);
        }
        else
        {
            typename EncodingT::string_t stopped(i, buf.end());
            logger->errorStream() << "instruction is invalid : " << A(stopped);
        }
        return success;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Block<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > ret(new Base<EncodingT>());
        for (iterator i = m_instructions.begin(); i < m_instructions.end(); ++i)
        {
            ret = (*i)->interpret(c);
        }
        return ret;
    }

    template <class EncodingT>
    bool Block<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value, bool print)
    {
        vector< boost::shared_ptr< Term<EncodingT> > > blockList;
        boost::shared_ptr< Term<EncodingT> > block;
        typename EncodingT::string_t sequence;
        Category * logger = &Category::getInstance(LOGNAME);
        typename EncodingT::string_t::const_iterator i = buf.begin();
        typename EncodingT::string_t::const_iterator j = buf.begin();
        typename EncodingT::string_t::const_iterator end = buf.end();

        bool success = true;
        while (i!=end && success)
        {
            // advance to first no space character
            i = next_word<EncodingT>(i, end);

            if (i != end)
            {
                // comment block
                if ((j = CommentBlock<EncodingT>::look_for(i, buf.end())) != i)
                {
                    sequence.assign(i, j);
                    block.reset();
                    success = CommentBlock<EncodingT>::parse(sequence, block);
                    if (success)
                    {
                        // advance index
                        i = j;
                    }
                }
                // conditional block
                else if ((j = ConditionalBlock<EncodingT>::look_for(i, buf.end())) != i)
                {
                    sequence.assign(i, j);
                    block.reset();
                    success = ConditionalBlock<EncodingT>::parse(sequence, block);
                    if (success)
                    {
                        // add instruction
                        blockList.push_back(block);
                        // advance index
                        i = j;
                    }
                }
                // repetitive block
                else if ((j = RepetitiveBlock<EncodingT>::look_for(i, buf.end())) != i)
                {
                    sequence.assign(i, j);
                    block.reset();
                    success = RepetitiveBlock<EncodingT>::parse(sequence, block);
                    if (success)
                    {
                        // add instruction
                        blockList.push_back(block);
                        // advance index
                        i = j;
                    }
                }
                // instructions list
                else if ((j = InstructionsList<EncodingT>::look_for(i, buf.end())) != i)
                {
                    sequence.assign(i, j);
                    block.reset();
                    success = InstructionsList<EncodingT>::parse(sequence, block);
                    if (success)
                    {
                        // add instruction
                        blockList.push_back(block);
                        // advance index
                        i = j;
                    }
                }
                else
                {
                    success = false;
                }
            }
        }
        if (success)
        {
            value.reset(new Block<EncodingT>(blockList));
        }
        else if (print)
        {
            typename EncodingT::string_t stopped(i, buf.end());
            logger->errorStream() << "instruction is invalid : " << A(stopped);
        }
        return success;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > InstructionsList<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return m_instruction->interpret(c);
    }

    template <class EncodingT>
    bool InstructionsList<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        boost::shared_ptr< Term<EncodingT> > instruction;
        typename EncodingT::string_t expr;
        bool success =  suffix<EncodingT>(buf, C(";"), expr) &&
                        Instruction<EncodingT>::parse(expr, instruction);
        if (success)
        {
            value.reset(new InstructionsList<EncodingT>(instruction));
        }
        return success;
    }

    template <class EncodingT>
    typename InstructionsList<EncodingT>::char_iterator
    InstructionsList<EncodingT>::look_for(typename InstructionsList<EncodingT>::char_iterator start, typename InstructionsList<EncodingT>::char_iterator end)
    {
        typename EncodingT::string_t::const_iterator i = start, j;
        while ( (j = find_symbol<EncodingT>(start, end, C(";"))) != end &&
                (std::count(i, j, '"')%2) != 0 )
        {
            start = j + 1;
        }
        if (j != end)
        {
            i = j + 1;
        }
        return i;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > CommentBlock<EncodingT>::interpret(Context<EncodingT>&)
    {
        return boost::shared_ptr< Base<EncodingT> >(new Base<EncodingT>());
    }

    template <class EncodingT>
    bool CommentBlock<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        boost::shared_ptr< Term<EncodingT> > instruction;
        typename EncodingT::string_t expr;
        bool success =  embrace<EncodingT>(buf, C("/*"), C("*/"), expr);
        if (success)
        {
            value.reset(new CommentBlock<EncodingT>(expr));
        }
        return success;
    }

    template <class EncodingT>
    typename CommentBlock<EncodingT>::char_iterator
    CommentBlock<EncodingT>::look_for(typename CommentBlock<EncodingT>::char_iterator start, typename CommentBlock<EncodingT>::char_iterator end)
    {
        typename EncodingT::string_t::const_iterator i = start, j;
        if ( end-start > 2 &&
             equal_symbol<EncodingT>(start, start+2, C("/*")) &&
            (j = find_symbol<EncodingT>(start+2, end, C("*/")))!=end)
        {
            i = j + 2;
        }
        return i;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > RepetitiveBlock<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
        bool bool_value = false;
        do
        {
            boost::shared_ptr< Base<EncodingT> > baseexpr = m_condition->interpret(c);
            boost::shared_ptr< Bool<EncodingT> > boolexpr = dynamic_pointer_cast< Bool<EncodingT> >(baseexpr);
            if (boolexpr)
            {
                bool_value = boolexpr->getValue();
                if (bool_value)
                {
                    m_instructions->interpret(c);
                }
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "invalid object, required : " << A(res->getClassName())
                                      << ", got " << A(baseexpr->getClassName());
            }
        } while (bool_value);
        return res;
    }

    template <class EncodingT>
    bool RepetitiveBlock<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        typename EncodingT::string_t condition, instructions;
        boost::shared_ptr< Term<EncodingT> > condition_value;
        boost::shared_ptr< Term<EncodingT> > instructions_value;
        bool success =  prefix<EncodingT>(expr, C("while"), expr, true) &&
                        suffix<EncodingT>(expr, C("endwhile"), expr, true) &&
                        hyphenation<EncodingT>(expr, C("do"), condition, instructions, true) &&
                        /*Bool*/Instruction<EncodingT>::parse(condition, condition_value) &&
                        Block<EncodingT>::parse(instructions, instructions_value);
        if (success)
        {
            value.reset(new RepetitiveBlock<EncodingT>(condition_value, instructions_value));
        }
        return success;
    }

    template <class EncodingT>
    typename RepetitiveBlock<EncodingT>::char_iterator
    RepetitiveBlock<EncodingT>::look_for(typename RepetitiveBlock<EncodingT>::char_iterator start, typename RepetitiveBlock<EncodingT>::char_iterator end)
    {
        typename EncodingT::string_t::const_iterator i = start, j = start, k = start;
        k = next_space<EncodingT>(j, end);
        if (equal_symbol<EncodingT>(j, k, C("while")))
        {
            j = k;
            int ignore = 0;
            size_t cpt = 1;
            while (cpt != 0 && j != end)
            {
                if ((ignore == 0) && j+2 < end && equal_symbol<EncodingT>(j, j+2, C("/*")))
                {
                    ignore = 1;
                    j += 1;
                }
                else if ((ignore == 0 || ignore == 2) && j+1 < end && equal_symbol<EncodingT>(j, j+1, C("\"")))
                {
                    ignore ^= 2;
                }
                else if ((ignore == 1) && j+2 < end && equal_symbol<EncodingT>(j, j+2, C("*/")))
                {
                    ignore = 0;
                    j += 1;
                }
                else if ((ignore == 0) && j+5 < end && isspace_(*(j-1)) && isspace_(*(j+5)) && equal_symbol<EncodingT>(j, j+5, C("while")))
                {
                    ++cpt;
                    j += 4;
                }
                else if ((ignore == 0) && ((j+8 < end && isspace_(*(j+8))) || (j+8 == end)) && isspace_(*(j-1)) && equal_symbol<EncodingT>(j, j+8, C("endwhile")))
                {
                    --cpt;
                    j += 7;
                }
                j++;
            }
            // found
            if (cpt == 0)
            {
                i = j;
            }
        }
        return i;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > ConditionalBlock<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>());
        boost::shared_ptr< Base<EncodingT> > baseexpr = m_condition->interpret(c);
        boost::shared_ptr< Bool<EncodingT> > boolexpr = dynamic_pointer_cast< Bool<EncodingT> >(baseexpr);
        if (boolexpr)
        {
            res = boolexpr;
            if (boolexpr->getValue())
            {
                m_if_instructions->interpret(c);
            }
            else if (m_else_instructions)
            {
                m_else_instructions->interpret(c);
            }
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "invalid object, required : " << A(res->getClassName())
                                  << ", got " << A(baseexpr->getClassName());
        }
        return res;
    }

    template <class EncodingT>
    bool ConditionalBlock<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        typename EncodingT::string_t condition, instructions, if_instructions, else_instructions;
        boost::shared_ptr< Term<EncodingT> > condition_value;
        boost::shared_ptr< Term<EncodingT> > if_instructions_value, else_instructions_value;
        bool success =  prefix<EncodingT>(expr, C("if"), expr, true) &&
                        suffix<EncodingT>(expr, C("endif"), expr, true) &&
                        hyphenation<EncodingT>(expr, C("then"), condition, instructions, true) &&
                        /*Bool*/Instruction<EncodingT>::parse(condition, condition_value);
        if (success)
        {
            success = false;
            size_t i = 0;
            while (i != EncodingT::string_t::npos && !success)
            {
                success = ((hyphenation<EncodingT>(instructions, C("else"), if_instructions, else_instructions, i, true) &&
                            Block<EncodingT>::parse(if_instructions, if_instructions_value) &&
                            Block<EncodingT>::parse(else_instructions, else_instructions_value)) ||
                            Block<EncodingT>::parse(instructions, if_instructions_value));
            }
            if (success)
            {
                value.reset(new ConditionalBlock<EncodingT>(condition_value, if_instructions_value, else_instructions_value));
            }
        }
        return success;
    }

    template <class EncodingT>
    typename ConditionalBlock<EncodingT>::char_iterator
    ConditionalBlock<EncodingT>::look_for(typename ConditionalBlock<EncodingT>::char_iterator start, typename ConditionalBlock<EncodingT>::char_iterator end)
    {
        typename EncodingT::string_t::const_iterator i = start, j = start, k = start;
        k = next_space<EncodingT>(j, end);
        if (equal_symbol<EncodingT>(j, k, C("if")))
        {
            j = k;
            int ignore = 0;
            size_t cpt = 1;
            while (cpt != 0 && j != end)
            {
                if ((ignore == 0) && j+2 < end && equal_symbol<EncodingT>(j, j+2, C("/*")))
                {
                    ignore = 1;
                    j += 1;
                }
                else if ((ignore == 0 || ignore == 2) && j+1 < end && equal_symbol<EncodingT>(j, j+1, C("\"")))
                {
                    ignore ^= 2;
                }
                else if ((ignore == 1) && j+2 < end && equal_symbol<EncodingT>(j, j+2, C("*/")))
                {
                    ignore = 0;
                    j += 1;
                }
                else if ((ignore == 0) && j+2 < end && isspace_(*(j-1)) && isspace_(*(j+2)) && equal_symbol<EncodingT>(j, j+2, C("if")))
                {
                    ++cpt;
                    j += 1;
                }
                else if ((ignore == 0) && ((j+5 < end && isspace_(*(j+5))) || (j+5 == end)) && isspace_(*(j-1)) && equal_symbol<EncodingT>(j, j+5, C("endif")))
                {
                    --cpt;
                    j += 4;
                }
                j++;
            }
            // found
            if (cpt == 0)
            {
                i = j;
            }
        }
        return i;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > ConstantsList<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return m_instruction->interpret(c);
    }

    template <class EncodingT>
    bool ConstantsList<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        boost::shared_ptr< Term<EncodingT> > instruction;
        typename EncodingT::string_t expr;
        bool success =  suffix<EncodingT>(buf, C(";"), expr) &&
                        ConstantAssignment<EncodingT>::parse(expr, instruction);
        if (success)
        {
            value.reset(new ConstantsList<EncodingT>(instruction));
        }
        return success;
    }

    template <class EncodingT>
    typename ConstantsList<EncodingT>::char_iterator
    ConstantsList<EncodingT>::look_for(typename ConstantsList<EncodingT>::char_iterator start, typename ConstantsList<EncodingT>::char_iterator end)
    {
        typename EncodingT::string_t::const_iterator i = start, j;
        if (end-start > 13 && equal_symbol<EncodingT>(start, start+8, C("constant")))
        {
            while ( (j = find_symbol<EncodingT>(start, end, C(";"))) != end &&
                    (std::count(i, j, '"')%2) != 0 )
            {
                start = j + 1;
            }
            if (j != end)
            {
                i = j + 1;
            }
        }
        return i;
    }

    template <class EncodingT>
    void Variable<EncodingT>::allocate(boost::shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c)
    {
        if (dynamic_pointer_cast< Null<EncodingT> >(value))
        {
            c.remove(m_name);
        }
        else
        {
            c.add(m_name, value);
        }
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Variable<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return c.getObject(m_name);
    }

    template <class EncodingT>
    bool Variable<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t identifier = eat_space<EncodingT>(buf);
        bool success = is_identifier<EncodingT>(identifier);
        if (success)
        {
            value.reset(new Variable<EncodingT>(identifier));
        }
        return success;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Assignment<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > val = m_instruction->interpret(c);
        m_object->allocate(val, c);
        return val;
    }

    template <class EncodingT>
    bool Assignment<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t left, right;
        boost::shared_ptr< Term<EncodingT> > right_value;
        boost::shared_ptr< Address<EncodingT> > left_value;
        bool success = binary_op<EncodingT>(buf, C("="), left, right) &&
                       Assignable<EncodingT>::parse(left, left_value) &&
                       Instruction<EncodingT>::parse(right, right_value);
        if (success)
        {
            value.reset(new Assignment<EncodingT>(left_value, right_value));
        }
        return success;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Copy<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > val = m_instruction->interpret(c)->clone();
        m_object->allocate(val, c);
        return val;
    }

    template <class EncodingT>
    bool Copy<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t left, right;
        boost::shared_ptr< Term<EncodingT> > right_value;
        boost::shared_ptr< Address<EncodingT> > left_value;
        bool success = binary_op<EncodingT>(buf, C(":="), left, right) &&
                       Assignable<EncodingT>::parse(left, left_value) &&
                       Instruction<EncodingT>::parse(right, right_value);
        if (success)
        {
            value.reset(new Copy<EncodingT>(left_value, right_value));
        }
        return success;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Bracket<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return m_instruction->interpret(c);
    }

    template <class EncodingT>
    bool Bracket<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr;
        boost::shared_ptr< Term<EncodingT> > expr_value;
        bool success = embrace<EncodingT>(buf, C("("), C(")"), expr) &&
                       Instruction<EncodingT>::parse(expr, expr_value);
        if (success)
        {
            value.reset(new Bracket<EncodingT>(expr_value));
        }
        return success;
    }

    template <class EncodingT>
    typename Bracket<EncodingT>::char_iterator
    Bracket<EncodingT>::look_for(typename Bracket<EncodingT>::char_iterator start, typename Bracket<EncodingT>::char_iterator end)
    {
        typename EncodingT::string_t::const_iterator i = start;
        if (start!=end && equal_symbol<EncodingT>(start, start+1, C("(")))
        {
            typename EncodingT::string_t::const_iterator j = start+1;
            int ignore = 0;
            size_t cpt = 1;
            while (cpt != 0 && j != end)
            {
                if ((ignore == 0) && j+2 < end && equal_symbol<EncodingT>(j, j+2, C("/*")))
                {
                    ignore = 1;
                    j += 1;
                }
                else if ((ignore == 0 || ignore == 2) && j+1 < end && equal_symbol<EncodingT>(j, j+1, C("\"")))
                {
                    ignore ^= 2;
                }
                else if ((ignore == 1) && j+2 < end && equal_symbol<EncodingT>(j, j+2, C("*/")))
                {
                    ignore = 0;
                    j += 1;
                }
                else if ((ignore == 0) && j+1 < end && equal_symbol<EncodingT>(j, j+1, C("(")))
                {
                    ++cpt;
                }
                else if ((ignore == 0) && j+1 <= end && equal_symbol<EncodingT>(j, j+1, C(")")))
                {
                    --cpt;
                }
                j++;
            }
            // found
            if (cpt == 0)
            {
                i = j;
            }
        }
        return i;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > MemberAccessOperator<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > obj = m_instruction->interpret(c);
        vector< boost::shared_ptr< Base<EncodingT> > > inparameters, outparameters;
        for (size_t i = 0; i<m_params.size(); ++i)
        {
            inparameters.push_back(m_params[i]->interpret(c));
        }
        outparameters = inparameters;
        boost::shared_ptr< Base<EncodingT> > ret =  obj->invoke( m_methodName, outparameters );
        for (size_t i = 0; i<m_params.size(); ++i)
        {
            boost::shared_ptr< Address<EncodingT> > ref = dynamic_pointer_cast< Address<EncodingT> >(m_params[i]);
            if (ref)
            {
                if (outparameters[i] != inparameters[i])
                {
                    ref->allocate(outparameters[i], c);
                }
            }
        }
        return ret;
    }

    template <class EncodingT>
    void MemberAccessOperator<EncodingT>::allocate(boost::shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > obj = m_instruction->interpret(c);
        vector< boost::shared_ptr< Base<EncodingT> > > parameters;
        for (size_t i = 0; i<m_params.size(); ++i)
        {
            parameters.push_back(m_params[i]->interpret(c));
        }
        if (dynamic_pointer_cast< Null<EncodingT> >(value))
        {
            obj->invoke(C("remove") + m_methodName, parameters);
        }
        else
        {
            parameters.push_back(value);
            obj->invoke( m_methodName, parameters );
        }
    }

    template <class EncodingT>
    bool MemberAccessOperator<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t left, right, method;
        boost::shared_ptr< Term<EncodingT> > left_value;
        vector< boost::shared_ptr< Term<EncodingT> > > params_values;
        bool success = false;
        size_t i = buf.length();
        while (i != EncodingT::string_t::npos && !success)
        {
            if (rbinary_op<EncodingT>(buf, C("."), left, right, i) &&
                Instruction<EncodingT>::parse(left, left_value))
            {
                typename EncodingT::string_t::const_iterator i = find_symbol<EncodingT>(right.begin(), right.end(), C("("));
                typename EncodingT::string_t parameters(i, (typename EncodingT::string_t::const_iterator) right.end());
                method = eat_space<EncodingT>(typename EncodingT::string_t(
                         (typename EncodingT::string_t::const_iterator) right.begin(), i));

                success = is_identifier<EncodingT>(method);
                embrace<EncodingT>(parameters, C("("), C(")"), parameters);

                if (!parameters.empty())
                {
                    vector<typename EncodingT::string_t> params;
                    size_t j = 0;
                    ignore_literal_comment<EncodingT> predicat;
                    tuple_op_if<EncodingT>(parameters, C(","), params, predicat);
                    params_values.clear();
                    while (success && j<params.size())
                    {
                        boost::shared_ptr< Address<EncodingT> > ref_value;
                        boost::shared_ptr< Term<EncodingT> >    expr_value;
                        success = Assignable<EncodingT>::parse(params[j], ref_value) ||
                                  Instruction<EncodingT>::parse(params[j], expr_value);
                        if (ref_value)
                        {
                            params_values.push_back(ref_value);
                        }
                        else if (expr_value)
                        {
                            params_values.push_back(expr_value);
                        }
                        ++j;
                    }
                }
            }
        }
        if (success)
        {
            value.reset(new MemberAccessOperator<EncodingT>(left_value, method, params_values));
        }
        return success;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Instruction<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return m_instruction->interpret(c);
    }

    template <class EncodingT>
    bool Instruction<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
       boost::shared_ptr< Term<EncodingT> > instruction;
       bool success = false;
       typename IntructionsMap::const_iterator i = analyzed.find(buf);
       if (i == analyzed.end())
       {
           success =
               IncludeInstruction<EncodingT>::parse(buf, instruction)       ||
               PrintInstruction<EncodingT>::parse(buf, instruction)         ||
               SystemInstruction<EncodingT>::parse(buf, instruction)        ||
               Copy<EncodingT>::parse(buf, instruction)               		  ||
               Assignment<EncodingT>::parse(buf, instruction)               ||
               SaveOperator<EncodingT>::parse(buf, instruction)             ||
               LoadOperator<EncodingT>::parse(buf, instruction)             ||
               OrOperator<EncodingT>::parse(buf, instruction)               ||
               AndOperator<EncodingT>::parse(buf, instruction)              ||
               NotEqualOperator<EncodingT>::parse(buf, instruction)         ||
               EqualOperator<EncodingT>::parse(buf, instruction)            ||
               NotIEqualOperator<EncodingT>::parse(buf, instruction)        ||
               IEqualOperator<EncodingT>::parse(buf, instruction)           ||
               InferiorOrEqualOperator<EncodingT>::parse(buf, instruction)  ||
               SuperiorOrEqualOperator<EncodingT>::parse(buf, instruction)  ||
               InferiorOperator<EncodingT>::parse(buf, instruction)         ||
               SuperiorOperator<EncodingT>::parse(buf, instruction)         ||
               PlusOperator<EncodingT>::parse(buf, instruction)             ||
               MinusOperator<EncodingT>::parse(buf, instruction)            ||
               MultiplyOperator<EncodingT>::parse(buf, instruction)         ||
               DivideOperator<EncodingT>::parse(buf, instruction)           ||
               ConcatOperator<EncodingT>::parse(buf, instruction)           ||
               UnaryMinusOperator<EncodingT>::parse(buf, instruction)       ||
               NotOperator<EncodingT>::parse(buf, instruction)              ||
               SizeOperator<EncodingT>::parse(buf, instruction)             ||
               MemberAccessOperator<EncodingT>::parse(buf, instruction)     ||
               ArrayOperator<EncodingT>::parse(buf, instruction)            ||
               Bracket<EncodingT>::parse(buf, instruction)                  ||
               BoolConstant<EncodingT>::parse(buf, instruction)             ||
               NumericConstant<EncodingT>::parse(buf, instruction)          ||
               StringConstant<EncodingT>::parse(buf, instruction)           ||
               NewOperator<EncodingT>::parse(buf, instruction)              ||
               DeleteOperator<EncodingT>::parse(buf, instruction)           ||
               FunctionCall<EncodingT>::parse(buf, instruction)             ||
               ConstantOperator<EncodingT>::parse(buf, instruction)         ||
               PredicateOperator<EncodingT>::parse(buf, instruction)        ||
               Variable<EncodingT>::parse(buf, instruction);
           // memo
           analyzed.insert(std::make_pair(buf, std::make_pair(success, instruction)));
       }
       else
       {
           success = i->second.first;
           instruction = i->second.second;
       }
       if (success)
       {
           value.reset(new Instruction<EncodingT>(instruction));
       }
       return success;
    }

    template <class EncodingT>
    void Instruction<EncodingT>::clean()
    {
        analyzed.clear();
    }

    template <class EncodingT>
    void Assignable<EncodingT>::allocate(boost::shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c)
    {
        m_object->allocate(value, c);
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Assignable<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return m_object->interpret(c);
    }

    template <class EncodingT>
    bool Assignable<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Address<EncodingT> > & value)
    {
       boost::shared_ptr< Term<EncodingT> > instruction;
       bool success = false;
       typename AssignablesMap::const_iterator i = analyzed.find(buf);
       if (i == analyzed.end())
       {
           success =
                ArrayOperator<EncodingT>::parse(buf, instruction)        ||
                MemberAccessOperator<EncodingT>::parse(buf, instruction) ||
                Variable<EncodingT>::parse(buf, instruction);
           // memo
           analyzed.insert(std::make_pair(buf, std::make_pair(success, instruction)));
       }
       else
       {
           success = i->second.first;
           instruction = i->second.second;
       }
        if (success)
        {
            boost::shared_ptr< Address<EncodingT> > object = dynamic_pointer_cast< Address<EncodingT> >(instruction);
            if (object)
            {
                value.reset(new Assignable<EncodingT>(object));
            }
            else
            {
                success = false;
            }
        }
        return success;
    }

    template <class EncodingT>
    void Assignable<EncodingT>::clean()
    {
        analyzed.clear();
    }

    template <class EncodingT>
    void ignore_literal_comment<EncodingT>::parse(typename EncodingT::string_t const& buffer)
    {
        typename EncodingT::string_t::const_iterator i1 = buffer.begin();
        typename EncodingT::string_t::const_iterator i2 = buffer.begin();
        typename EncodingT::string_t::const_iterator j = buffer.begin();
        typename EncodingT::string_t::const_iterator end = buffer.end();

        while (j != end)
        {
            if (i1 <= j)
            {
                // Search first comment
                i1 = find_symbol<EncodingT>(j, end, L"/*");
            }
            if (i2 <= j)
            {
                // Search first quote
                i2 = find_symbol<EncodingT>(j, end, L"\"");
            }
            if ((i1 != end) || (i2 != end))
            {
                if (i1 < i2)
                {
                    // comment is before quote
                    j = find_symbol<EncodingT>(i1 + 2, end, L"*/");
                    if (j != end)
                    {
                        j += 2;
                        m_indices.push_back(pair_indices(i1 - buffer.begin(), j - buffer.begin()));
                    }
                }
                else
                {
                    // quote is before comment
                    j = find_symbol<EncodingT>(i2 + 1, end, L"\"");
                    if (j != end)
                    {
                        j += 1;
                        m_indices.push_back(pair_indices(i2 - buffer.begin(), j - buffer.begin()));
                    }
                }
            }
            else
            {
                j = end;
            }
        }
    }

    template <class EncodingT>
    bool ignore_literal_comment<EncodingT>::operator()(typename EncodingT::string_t const& buffer, size_t index)
    {
        bool valid = true;
        if (index == (size_t)-1)
        {
            parse(buffer);
        }
        else
        {
            typename std::list<pair_indices>::const_iterator i = m_indices.begin();
            while (valid && (i != m_indices.end()) && (index > i->first))
            {
                valid = !((i->first < index) && (index < i->second));
                ++i;
            }
        }
        return valid;
    }

NAMESPACE_END

#undef C
#undef A

