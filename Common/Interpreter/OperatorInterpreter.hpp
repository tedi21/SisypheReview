#ifndef _OPERATOR_INTERPRETER_HPP_
#define _OPERATOR_INTERPRETER_HPP_

#include "Interpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

#define    BINARY_OP_CLASS( Name )                                                                      \
template <class EncodingT>                                                                              \
class Name                                                                                              \
: public Term<EncodingT>                                                                                \
{                                                                                                       \
private:                                                                                                \
    boost::shared_ptr< Term<EncodingT> > m_left;                                                               \
    boost::shared_ptr< Term<EncodingT> > m_right;                                                              \
public:                                                                                                 \
    Name(boost::shared_ptr< Term<EncodingT> > const& left, boost::shared_ptr< Term<EncodingT> > const& right)         \
    : m_left(left), m_right(right)                                                                      \
    {}                                                                                                  \
    boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);                                    \
    static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);  \
};

#define    BINARY_OP_INTERPRET( Name, MethodName )                                                      \
template <class EncodingT>                                                                              \
boost::shared_ptr< Base<EncodingT> > Name<EncodingT>::interpret(Context<EncodingT> & c)                        \
{                                                                                                       \
    boost::shared_ptr< Base<EncodingT> > var = m_left->interpret(c);                                           \
    boost::shared_ptr< Base<EncodingT> > rhs = m_right->interpret(c);                                          \
    vector<boost::shared_ptr< Base<EncodingT> > > params;                                                      \
    params.push_back(rhs);                                                                              \
    return var->invoke(C( #MethodName ), params);                                                       \
}

#define    BINARY_OP_PARSE( Name, Op )                                                                  \
template <class EncodingT>                                                                              \
bool Name<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)\
{                                                                                                       \
    typename EncodingT::string_t left, right;                                                           \
    boost::shared_ptr< Term<EncodingT> > left_value, right_value;                                              \
    size_t i = buf.length();                                                                            \
    bool success = false;                                                                               \
    while ( i != EncodingT::string_t::npos && !success)                                                 \
    {                                                                                                   \
        success = rbinary_op<EncodingT>(buf, C( #Op ), left, right, i) &&                               \
                  Instruction<EncodingT>::parse(left, left_value) &&                                    \
                  Instruction<EncodingT>::parse(right, right_value);                                    \
    }                                                                                                   \
    if (success)                                                                                        \
    {                                                                                                   \
        value.reset( new Name<EncodingT>(left_value, right_value) );                                    \
    }                                                                                                   \
    return success;                                                                                     \
}

#define    BINARY_OP_IMPL( Name, MethodName, Op )                                                       \
    BINARY_OP_PARSE( Name, Op )                                                                         \
    BINARY_OP_INTERPRET( Name, MethodName )

#define    BINARY_OP_INTERPRET_REF( Name, MethodName )                                                  \
template <class EncodingT>                                                                              \
boost::shared_ptr< Base<EncodingT> > Name<EncodingT>::interpret(Context<EncodingT> & c)                        \
{                                                                                                       \
    boost::shared_ptr< Base<EncodingT> > var = m_left->interpret(c);                                           \
    boost::shared_ptr< Base<EncodingT> > rhs = m_right->interpret(c);                                          \
    vector<boost::shared_ptr< Base<EncodingT> > > params;                                                      \
    params.push_back(rhs);                                                                              \
    boost::shared_ptr< Base<EncodingT> >    ret = var->invoke(C( #MethodName ), params);                       \
    boost::shared_ptr< Address<EncodingT> > ref = dynamic_pointer_cast< Address<EncodingT> >(m_right);         \
    if (ref)                                                                                            \
    {                                                                                                   \
        ref->allocate(params[0], c);                                                                    \
    }                                                                                                   \
    return ret;                                                                                         \
}

#define    BINARY_OP_PARSE_REF( Name, Op )                                                              \
template <class EncodingT>                                                                              \
bool Name<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)\
{                                                                                                       \
    typename EncodingT::string_t left, right;                                                           \
    boost::shared_ptr< Term<EncodingT> > left_value;                                                           \
    boost::shared_ptr< Address<EncodingT> > ref_right_value;                                                   \
    size_t i = buf.length();                                                                            \
    bool success = false;                                                                               \
    while ( i != EncodingT::string_t::npos && !success)                                                 \
    {                                                                                                   \
        success = rbinary_op<EncodingT>(buf, C( #Op ), left, right, i) &&                               \
                  Instruction<EncodingT>::parse(left, left_value) &&                                    \
                  Assignable<EncodingT>::parse(right, ref_right_value);                                 \
    }                                                                                                   \
    if (success)                                                                                        \
    {                                                                                                   \
        value.reset( new Name<EncodingT>(left_value, ref_right_value) );                                \
    }                                                                                                   \
    return success;                                                                                     \
}

#define    BINARY_OP_IMPL_REF( Name, MethodName, Op )                                                   \
    BINARY_OP_PARSE_REF( Name, Op )                                                                     \
    BINARY_OP_INTERPRET_REF( Name, MethodName )

#define    UNARY_OP_CLASS( Name )                                                                       \
template <class EncodingT>                                                                              \
class Name                                                                                              \
: public Term<EncodingT>                                                                                \
{                                                                                                       \
private:                                                                                                \
    boost::shared_ptr< Term<EncodingT> > m_right;                                                              \
public:                                                                                                 \
    Name(boost::shared_ptr< Term<EncodingT> > const& right)                                                    \
    : m_right(right)                                                                                    \
    {}                                                                                                  \
    boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c);                                    \
    static bool parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value);  \
};

#define    UNARY_OP_INTERPRET( Name, MethodName )                                                       \
template <class EncodingT>                                                                              \
boost::shared_ptr< Base<EncodingT> > Name<EncodingT>::interpret(Context<EncodingT> & c)                        \
{                                                                                                       \
    boost::shared_ptr< Base<EncodingT> >  var   = m_right->interpret(c);                                       \
    return var->invoke(C( #MethodName ));                                                               \
}

#define    UNARY_OP_PARSE( Name, Op )                                                                   \
template <class EncodingT>                                                                              \
bool Name<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)\
{                                                                                                       \
    typename EncodingT::string_t right;                                                                 \
    boost::shared_ptr< Term<EncodingT> > right_value;                                                          \
    bool success = unary_op<EncodingT>(buf, C( #Op ), right) &&                                         \
                   Instruction<EncodingT>::parse(right, right_value);                                   \
    if (success)                                                                                        \
    {                                                                                                   \
        value.reset(new Name<EncodingT>(right_value));                                                  \
    }                                                                                                   \
    return success;                                                                                     \
}

#define    UNARY_OP_IMPL( Name, MethodName, Op )                                                        \
    UNARY_OP_PARSE( Name, Op )                                                                          \
    UNARY_OP_INTERPRET( Name, MethodName )

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    UNARY_OP_CLASS(  SizeOperator )
    UNARY_OP_CLASS(  UnaryMinusOperator )
    UNARY_OP_CLASS(  NotOperator )

    BINARY_OP_CLASS( ConcatOperator )
    BINARY_OP_CLASS( PlusOperator )
    BINARY_OP_CLASS( MinusOperator )
    BINARY_OP_CLASS( MultiplyOperator )
    BINARY_OP_CLASS( DivideOperator )
    BINARY_OP_CLASS( EqualOperator )
    BINARY_OP_CLASS( NotEqualOperator )
    BINARY_OP_CLASS( IEqualOperator )
    BINARY_OP_CLASS( NotIEqualOperator )
    BINARY_OP_CLASS( InferiorOperator )
    BINARY_OP_CLASS( InferiorOrEqualOperator )
    BINARY_OP_CLASS( SuperiorOperator )
    BINARY_OP_CLASS( SuperiorOrEqualOperator )
    BINARY_OP_CLASS( AndOperator )
    BINARY_OP_CLASS( OrOperator )
    BINARY_OP_CLASS( LoadOperator )
    BINARY_OP_CLASS( SaveOperator )

NAMESPACE_END

#include "OperatorInterpreter_impl.hpp"

#undef C
#undef A

#endif
