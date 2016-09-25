#ifndef _FUNCTION_INTERPRETER_HPP_
#define _FUNCTION_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    // Function term
    template <class EncodingT>
    class Function
    : public Term<EncodingT>
    {
    private:
        typename EncodingT::string_t m_name;
        std::vector<typename EncodingT::string_t> m_params;
        boost::shared_ptr< Term<EncodingT> > m_block;
        typedef typename EncodingT::string_t::const_iterator    char_iterator;

    public:
        Function(typename EncodingT::string_t const& name, std::vector<typename EncodingT::string_t> const& params, boost::shared_ptr< Term<EncodingT> > const& block)
        : m_name(name), m_params(params), m_block(block)
        {}
        typename EncodingT::string_t const& getName() const;
        std::vector<typename EncodingT::string_t> const& getParams() const;
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
        static char_iterator look_for(char_iterator start, char_iterator end);
    };

    // FunctionCall term
    template <class EncodingT>
    class FunctionCall
    : public Term<EncodingT>
    {
    private:
        typename EncodingT::string_t m_name;
        std::vector< boost::shared_ptr< Term<EncodingT> > > m_params;

    public:
        FunctionCall(typename EncodingT::string_t const& name, std::vector< boost::shared_ptr< Term<EncodingT> > > const& params)
        : m_name(name), m_params(params)
        {}
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "FunctionInterpreter_impl.hpp"

#endif
