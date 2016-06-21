#ifndef _PROGRAM_INTERPRETER_HPP_
#define _PROGRAM_INTERPRETER_HPP_

#include <map>
#include "Interpreter.hpp"

using namespace boost;
using namespace log4cpp;
using namespace std;

NAMESPACE_BEGIN(interp)

    // program term
    template <class EncodingT>
    class Program
    : public Term<EncodingT>
    {
    private:
        shared_ptr< Term<EncodingT> > m_declaration;
        shared_ptr< Term<EncodingT> > m_block;
    public:
        Program(shared_ptr< Term<EncodingT> > const& declaration, shared_ptr< Term<EncodingT> > const& block)
        : m_declaration(declaration), m_block(block)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
    };

    // declaration term
    template <class EncodingT>
    class Declaration
    : public Term<EncodingT>
    {
    private:
        std::vector< shared_ptr< Term<EncodingT> > > m_constants;
        std::vector< shared_ptr< Term<EncodingT> > > m_functions;
        typedef typename std::vector< shared_ptr< Term<EncodingT> > >::const_iterator iterator;
    public:
        Declaration(std::vector< shared_ptr< Term<EncodingT> > > const& constants, std::vector< shared_ptr< Term<EncodingT> > > const& functions)
        : m_constants(constants), m_functions(functions)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value, typename EncodingT::string_t & instructions);
    };

    // block term
    template <class EncodingT>
    class Block
    : public Term<EncodingT>
    {
    private:
        std::vector< shared_ptr< Term<EncodingT> > > m_instructions;
        typedef typename std::vector< shared_ptr< Term<EncodingT> > >::const_iterator iterator;
    public:
        Block(std::vector< shared_ptr< Term<EncodingT> > > const& instructions)
        : m_instructions(instructions)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value, bool print = false);
    };

    // InstructionsList term
    template <class EncodingT>
    class InstructionsList
    : public Term<EncodingT>
    {
    private:
        shared_ptr< Term<EncodingT> > m_instruction;
        typedef typename EncodingT::string_t::const_iterator    char_iterator;

    public:
        InstructionsList(shared_ptr< Term<EncodingT> > const& instruction)
        : m_instruction(instruction)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
        static char_iterator look_for(char_iterator start, char_iterator end);
    };

    // CommentBlock term
    template <class EncodingT>
    class CommentBlock
    : public Term<EncodingT>
    {
    private:
        typename EncodingT::string_t m_txt;
        typedef typename EncodingT::string_t::const_iterator    char_iterator;

    public:
        CommentBlock(typename EncodingT::string_t const& txt)
        : m_txt(txt)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
        static char_iterator look_for(char_iterator start, char_iterator end);
    };

    // RepetitiveBlock term
    template <class EncodingT>
    class RepetitiveBlock
    : public Term<EncodingT>
    {
    private:
        shared_ptr< Term<EncodingT> > m_condition;
        shared_ptr< Term<EncodingT> > m_instructions;
        typedef typename EncodingT::string_t::const_iterator    char_iterator;

    public:
        RepetitiveBlock(shared_ptr< Term<EncodingT> > const& condition, shared_ptr< Term<EncodingT> > const& instructions)
        : m_condition(condition), m_instructions(instructions)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
        static char_iterator look_for(char_iterator start, char_iterator end);
    };

    // ConditionalBlock term
    template <class EncodingT>
    class ConditionalBlock
    : public Term<EncodingT>
    {
    private:
        shared_ptr< Term<EncodingT> > m_condition;
        shared_ptr< Term<EncodingT> > m_if_instructions;
        shared_ptr< Term<EncodingT> > m_else_instructions;
        typedef typename EncodingT::string_t::const_iterator    char_iterator;

    public:
        ConditionalBlock(shared_ptr< Term<EncodingT> > const& condition, shared_ptr< Term<EncodingT> > const& if_instructions, shared_ptr< Term<EncodingT> > const& else_instructions)
        : m_condition(condition), m_if_instructions(if_instructions), m_else_instructions(else_instructions)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
        static char_iterator look_for(char_iterator start, char_iterator end);
    };

    // ConstantsList term
    template <class EncodingT>
    class ConstantsList
    : public Term<EncodingT>
    {
    private:
        shared_ptr< Term<EncodingT> > m_instruction;
        typedef typename EncodingT::string_t::const_iterator    char_iterator;

    public:
        ConstantsList(shared_ptr< Term<EncodingT> > const& instruction)
        : m_instruction(instruction)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
        static char_iterator look_for(char_iterator start, char_iterator end);
    };

    // Variable term
    template <class EncodingT>
    class Variable
    : public Address<EncodingT>
    {
    private:
        typename EncodingT::string_t m_name;

    public:
        Variable(typename EncodingT::string_t const& name)
        : m_name(name)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        void allocate(shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
    };

    // Assignment term
    template <class EncodingT>
    class Assignment
    : public Term<EncodingT>
    {
    private:
        shared_ptr< Address<EncodingT> > m_object;
        shared_ptr< Term<EncodingT> > m_instruction;

    public:
        Assignment(shared_ptr< Address<EncodingT> > const& object, shared_ptr< Term<EncodingT> > const& instruction)
        : m_object(object), m_instruction(instruction)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
    };

    // Copy term
    template <class EncodingT>
    class Copy
    : public Term<EncodingT>
    {
    private:
        shared_ptr< Address<EncodingT> > m_object;
        shared_ptr< Term<EncodingT> > m_instruction;

    public:
        Copy(shared_ptr< Address<EncodingT> > const& object, shared_ptr< Term<EncodingT> > const& instruction)
        : m_object(object), m_instruction(instruction)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
    };

    // Bracket term
    template <class EncodingT>
    class Bracket
    : public Term<EncodingT>
    {
    private:
        shared_ptr< Term<EncodingT> > m_instruction;
        typedef typename EncodingT::string_t::const_iterator    char_iterator;

    public:
        Bracket(shared_ptr< Term<EncodingT> > const& instruction)
        : m_instruction(instruction)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
        static char_iterator look_for(char_iterator start, char_iterator end);
    };

    template <class EncodingT>
    class MemberAccessOperator
    : public Address<EncodingT>
    {
    private:
        shared_ptr< Term<EncodingT> > m_instruction;
        typename EncodingT::string_t m_methodName;
        std::vector< shared_ptr< Term<EncodingT> > > m_params;

    public:
        MemberAccessOperator(shared_ptr< Term<EncodingT> > const& instruction, typename EncodingT::string_t const& methodName, std::vector< shared_ptr< Term<EncodingT> > > const& params)
        : m_instruction(instruction), m_methodName(methodName), m_params(params)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        void allocate(shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
    };

    // Instruction term
    template <class EncodingT>
    class Instruction
    : public Term<EncodingT>
    {
    private:
        typedef std::map< typename EncodingT::string_t,std::pair< bool,shared_ptr< Term<EncodingT> > > > IntructionsMap;
        static IntructionsMap analyzed;

        shared_ptr< Term<EncodingT> > m_instruction;

    public:
        Instruction(shared_ptr< Term<EncodingT> > const& instruction)
        : m_instruction(instruction)
        {}
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value);
        static void clean();
    };

    template <class EncodingT>
    typename Instruction<EncodingT>::IntructionsMap Instruction<EncodingT>::analyzed;

    // Assignable term
    template <class EncodingT>
    class Assignable
    : public Address<EncodingT>
    {
    private:
        typedef std::map< typename EncodingT::string_t,std::pair< bool,shared_ptr< Term<EncodingT> > > > AssignablesMap;
        static AssignablesMap analyzed;

        shared_ptr< Address<EncodingT> > m_object;

    public:
        Assignable(shared_ptr< Address<EncodingT> > const& object)
        : m_object(object)
        {}
        void allocate(shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c);
        shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, shared_ptr< Address<EncodingT> > & value);
        static void clean();
    };

    template <class EncodingT>
    typename Assignable<EncodingT>::AssignablesMap Assignable<EncodingT>::analyzed;

NAMESPACE_END

#include "ProgramInterpreter_impl.hpp"

#endif
