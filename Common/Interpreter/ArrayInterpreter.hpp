#ifndef _ARRAY_INTERPRETER_HPP_
#define _ARRAY_INTERPRETER_HPP_

#include "Interpreter.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Instruction;

    // ArrayOperator term
    template <class EncodingT>
    class ArrayOperator
    : public Address<EncodingT>
    {
    private:
        boost::shared_ptr< Address<EncodingT> > m_name;
        boost::shared_ptr< Term<EncodingT> > m_index1;
        boost::shared_ptr< Term<EncodingT> > m_index2;
        bool m_listIndex;

    public:
        ArrayOperator(boost::shared_ptr< Address<EncodingT> > const& name, 
                      boost::shared_ptr< Term<EncodingT> > const& index1,
                      boost::shared_ptr< Term<EncodingT> > const& index2,
                      bool listIndex)
        : m_name(name), m_index1(index1), m_index2(index2), m_listIndex(listIndex)
        {}    
        boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);
        void allocate(boost::shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c);
        static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);
    };

NAMESPACE_END

#include "ArrayInterpreter_impl.hpp"

#endif
