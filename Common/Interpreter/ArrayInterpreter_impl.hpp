#include "Array.hpp"
#include "Null.hpp"
#include <vector>

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > ArrayOperator<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> >  index1 = m_index1->interpret(c);
        boost::shared_ptr< Base<EncodingT> >  var   = m_name->interpret(c);
        std::vector<boost::shared_ptr< Base<EncodingT> > > params;
        params.push_back(index1);
        boost::shared_ptr< Base<EncodingT> > res(new Base<EncodingT>());
        if (m_listIndex)
        {
            boost::shared_ptr< Base<EncodingT> > index2 = m_index2->interpret(c);
            params.push_back(index2);
            res = var->invoke(C("getList"), params);
        }
        else
        {
            res = var->invoke(C("getValue"), params);
        }
        return res;
    }

    template <class EncodingT>
    void ArrayOperator<EncodingT>::allocate(boost::shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > index1 = m_index1->interpret(c);
        boost::shared_ptr< Base<EncodingT> > var   = m_name->interpret(c);
        std::vector<boost::shared_ptr< Base<EncodingT> > > params;
        params.push_back(index1);
        if (dynamic_pointer_cast< Null<EncodingT> >(value))
        {
            if (m_listIndex)
            {
                boost::shared_ptr< Base<EncodingT> > index2 = m_index2->interpret(c);
                params.push_back(index2);
                var->invoke(C("removeList"), params);
            }
            else
            {
                var->invoke(C("removeValue"), params);
            }
        }
        else
        {
            if (m_listIndex)
            {
                boost::shared_ptr< Base<EncodingT> > index2 = m_index2->interpret(c);
                params.push_back(index2);
                params.push_back(value);
                var->invoke(C("insertList"), params);
            }
            else
            {
                params.push_back(value);
                var->invoke(C("insertValue"), params);
            }
        }
    }

    template <class EncodingT>
    bool ArrayOperator<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        boost::shared_ptr< Term<EncodingT> > expr_value, right_value;
        boost::shared_ptr< Address<EncodingT> > arr_value;
        bool listIndex = false;
        typename EncodingT::string_t::const_iterator i = rfind_symbol<EncodingT>(expr.begin(), expr.end(), C("["));
        typename EncodingT::string_t arr((typename EncodingT::string_t::const_iterator) expr.begin(), i);
        typename EncodingT::string_t square(i, (typename EncodingT::string_t::const_iterator) expr.end());
        bool success =  (i != expr.end()) &&
                        Assignable<EncodingT>::parse(arr, arr_value) &&
                        embrace<EncodingT>(square, C("["), C("]"), expr);
        typename EncodingT::string_t left, right;
        if (success && hyphenation<EncodingT>(expr, C("_"), left, right, true))
        {
            listIndex = true;
            success = success &&
                      Instruction<EncodingT>::parse(left,  expr_value) &&
                      Instruction<EncodingT>::parse(right, right_value);
        }
        else 
        {
            success = success && Instruction<EncodingT>::parse(expr, expr_value);
        }
        if (success)
        {
            value.reset(new ArrayOperator<EncodingT>(arr_value, expr_value, right_value, listIndex));
        } 
        return success;  
    }

NAMESPACE_END

#undef C
#undef A
