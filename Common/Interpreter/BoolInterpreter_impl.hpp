#include "Bool.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > BoolConstant<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_data));
    }

    template <class EncodingT>
    bool BoolConstant<EncodingT>::parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value)
    {  
        typename EncodingT::string_t str = eat_space<EncodingT>(buf);
        bool success = (str==C("true") || str==C("false"));
        if (success)
        {
            value.reset(new BoolConstant<EncodingT>((str==C("true"))?true:false));
        }
        return success; 
    }

NAMESPACE_END

#undef C
#undef A
