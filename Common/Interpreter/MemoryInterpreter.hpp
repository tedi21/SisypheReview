#ifndef _MEMORY_INTERPRETER_HPP_
#define _MEMORY_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace std;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    // DeleteOperator term
    template <class EncodingT>
    class DeleteOperator
    : public Term<EncodingT>
    {
    public:
        DeleteOperator()
        {}
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
    };

    template <class EncodingT>
    class NewOperator
    : public Term<EncodingT>
    {
    private:
        typename EncodingT::string_t m_type;
        std::vector< boost::shared_ptr< Term<EncodingT> > > m_params;

    public:
        NewOperator(typename EncodingT::string_t const& type, std::vector< boost::shared_ptr< Term<EncodingT> > > const& params)
        : m_type(type), m_params(params)
        {}
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "MemoryInterpreter_impl.hpp"

#endif
