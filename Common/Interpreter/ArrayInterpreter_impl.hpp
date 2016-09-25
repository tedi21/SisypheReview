#include "Array.hpp"
#include "Null.hpp"
#include <vector>

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > ArrayOperator<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> >  index = m_index->interpret(c);
        boost::shared_ptr< Base<EncodingT> >  var   = m_name->interpret(c);
        std::vector<boost::shared_ptr< Base<EncodingT> > > params;
        params.push_back(index);
        return var->invoke(C("getValue"), params);
    }

    template <class EncodingT>
    void ArrayOperator<EncodingT>::allocate(boost::shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> >  index = m_index->interpret(c);
        boost::shared_ptr< Base<EncodingT> >  var   = m_name->interpret(c);
        std::vector<boost::shared_ptr< Base<EncodingT> > > params;
        params.push_back(index);
        if (dynamic_pointer_cast< Null<EncodingT> >(value))
        {
            var->invoke(C("removeValue"), params);
        }
        else
        {
            params.push_back(value);
            var->invoke(C("insertValue"), params);
        }
    }

    template <class EncodingT>
    bool ArrayOperator<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        boost::shared_ptr< Term<EncodingT> > expr_value;
        boost::shared_ptr< Address<EncodingT> > arr_value;
        typename EncodingT::string_t::const_iterator i = rfind_symbol<EncodingT>(expr.begin(), expr.end(), C("["));
        typename EncodingT::string_t arr((typename EncodingT::string_t::const_iterator) expr.begin(), i);
        typename EncodingT::string_t square(i, (typename EncodingT::string_t::const_iterator) expr.end());
        bool success =  (i != expr.end()) &&
                        Assignable<EncodingT>::parse(arr, arr_value) &&
                        embrace<EncodingT>(square, C("["), C("]"), expr) &&
                        Instruction<EncodingT>::parse(expr, expr_value);
        if (success)
        {
            value.reset(new ArrayOperator<EncodingT>(arr_value, expr_value));
        } 
        return success;  
    }

NAMESPACE_END

#undef C
#undef A
