#include "String.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Bool<EncodingT>::Bool()
    {
        m_value = false;
    }

    template <class EncodingT>
    Bool<EncodingT>::Bool(bool value)
    {
        m_value = value;
    }

    template <class EncodingT>
    Bool<EncodingT>::Bool(shared_ptr< Base<EncodingT> > const& value)
    {
        bool boolean;     
        if (check_bool(value, boolean))
        {
            m_value = boolean;
        }
    }

    template <class EncodingT>
    Bool<EncodingT>::~Bool()
    {}

    template <class EncodingT>
    bool Bool<EncodingT>::getValue() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void Bool<EncodingT>::setValue(bool value)
    {
        m_value = value;
    }

    template <class EncodingT>
    typename EncodingT::string_t Bool<EncodingT>::toString() const
    {
        return Convert<typename EncodingT::string_t>::parse(m_value, ios::boolalpha);
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Bool<EncodingT>::clone() const
    {
        return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_value));
    }

    template <class EncodingT>
    typename EncodingT::string_t Bool<EncodingT>::getClassName() const
    {
        return C("Bool");
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Bool<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
    {
        shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("Bool"), method, args, ret) ||
                tryInvoke(this, C("String"), method, args, ret))
            {
                find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
                for (size_t i = 0; i < params.size(); ++i)
                {
                    find_parameter(ret, i, params[i]);
                }
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Unexpected call in Bool, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }
    
    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Bool<EncodingT>::not_() const
    {
        return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!m_value));
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Bool<EncodingT>::and_(shared_ptr< Base<EncodingT> > const& val) const
    {
        shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        bool num;     
        if (check_bool(val, num))
        {
            res.reset(new Bool<EncodingT>(m_value && num));
        }
        return res;
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Bool<EncodingT>::or_(shared_ptr< Base<EncodingT> > const& val) const
    {
        shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        bool num;     
        if (check_bool(val, num))
        {
            res.reset(new Bool<EncodingT>(m_value || num));
        }
        return res;
    }

    template <class EncodingT>
    bool check_bool(shared_ptr< Base<EncodingT> > const& val, bool& n)
    {
        shared_ptr< Bool<EncodingT> > value  = dynamic_pointer_cast< Bool<EncodingT> >(val);        
        if (value)
        {
            n = value->getValue();
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Bool expected, got " << A(val->getClassName());            
        }
        return value;
    }

    template <class EncodingT>
    bool reset_bool(shared_ptr< Base<EncodingT> >& val, bool const& n)
    {
        shared_ptr< Bool<EncodingT> > value  = dynamic_pointer_cast< Bool<EncodingT> >(val);
        if (value)
        {
            value->setValue(n);
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Bool expected, got " << A(val->getClassName());
        }
        return value;
    }

NAMESPACE_END

#undef C
#undef A
