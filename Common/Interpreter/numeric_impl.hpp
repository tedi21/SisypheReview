#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost::archive::iterators;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Numeric<EncodingT>::Numeric()
    {
        m_value = 0;
    }

    template <class EncodingT>
    Numeric<EncodingT>::Numeric(double value)
    {
        m_value = value;
    }

    template <class EncodingT>
    Numeric<EncodingT>::Numeric(boost::shared_ptr< Base<EncodingT> > const& value)
    {
        double num;     
        if (check_numeric(value, num))
        {
            m_value = num;
        }
    }

    template <class EncodingT>
    Numeric<EncodingT>::~Numeric()
    {}

    template <class EncodingT>
    double Numeric<EncodingT>::getValue() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void Numeric<EncodingT>::setValue(double value)
    {
        m_value = value;
    }

    template <class EncodingT>
    typename EncodingT::string_t Numeric<EncodingT>::toString() const
    {
        return Convert<typename EncodingT::string_t>::parse(m_value);
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value));
    }

    template <class EncodingT>
    typename EncodingT::string_t Numeric<EncodingT>::getClassName() const
    {
        return C("Numeric");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("Numeric"), method, args, ret) ||
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
                logger->errorStream() << "Unexpected call in Numeric, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::minus() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(-m_value));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::plus(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Numeric<EncodingT>(m_value + num));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::minus(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Numeric<EncodingT>(m_value - num));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::multiply(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Numeric<EncodingT>(m_value * num));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::divide(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Numeric<EncodingT>(m_value / num));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::equals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(m_value == num));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::notEquals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(m_value != num));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::inferior(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(m_value < num));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::inferiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(m_value <= num));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::superior(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(m_value > num));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::superiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        double num;     
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(m_value >= num));
        }
        return res;
    }

    template <class EncodingT>
    void Numeric<EncodingT>::increment()
    {
        ++m_value;
    }

    template <class EncodingT>
    void Numeric<EncodingT>::decrement()
    {
        --m_value;
    }

    template <class EncodingT>
    void Numeric<EncodingT>::parse(boost::shared_ptr< Base<EncodingT> > const& str)
    {
        m_value = Convert<double>::parse(str->toString());
    }
    
    template <class EncodingT>
    void Numeric<EncodingT>::parseHex(boost::shared_ptr< Base<EncodingT> > const& str)
    {
        m_value = Convert<int>::parse(str->toString(), std::ios_base::hex);
    }

    template <class EncodingT>
    void Numeric<EncodingT>::parseBase64(boost::shared_ptr< Base<EncodingT> > const& str, boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& size)
    {
        typename EncodingT::string_t text;
        double natPos, natSize;
        if (check_string<EncodingT>(str, text) &&
            check_numeric(pos, natPos) &&
            check_numeric(size, natSize))
        {
            vector<unsigned char> buffer;
            typedef
                transform_width<
                    binary_from_base64<
                        typename EncodingT::string_t::const_iterator
                        >,
                    8,
                    6
                >
                binary_text;
            buffer.assign(binary_text(text.begin()), binary_text(text.end()));
            unsigned int bitPos = natPos;
            unsigned int bitSize = natSize;
            unsigned int byteStart = bitPos / 8;
            unsigned int byteEnd = (bitSize + bitPos) / 8;
            unsigned int bitStart = bitPos % 8;
            unsigned int bitEnd = (bitSize + bitPos) % 8;
            unsigned int mask;
            unsigned long long value = 0;
            if (byteEnd < buffer.size())
            {
                while (byteStart != byteEnd)
                {
                    mask = 0x00FF;
                    mask = mask >> bitStart;
                    bitSize -= (8 - bitStart);
                    value += ((buffer[byteStart] & mask) << bitSize);
                    bitStart = 0;
                    byteStart++;
                }
                mask = 0x00FF;
                mask = mask >> bitStart;
                value += ((buffer[byteEnd] & mask) >> (8 - bitEnd));
            }
            m_value = value;
        }
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::convertHex() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(Convert<typename EncodingT::string_t>::parse((int) m_value, std::ios_base::hex)));
    }

    template <class EncodingT, class T>
    bool check_numeric(boost::shared_ptr< Base<EncodingT> > const& val, T& n)
    {
        boost::shared_ptr< Numeric<EncodingT> > value  = dynamic_pointer_cast< Numeric<EncodingT> >(val);
        if (value)
        {
            n = (T) value->getValue();
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Numeric expected, got " << A(val->getClassName());            
        }
        return (value != NULL);
    }

    template <class EncodingT, class T>
    bool reset_numeric(boost::shared_ptr< Base<EncodingT> >& val, T const& n)
    {
        boost::shared_ptr< Numeric<EncodingT> > value  = dynamic_pointer_cast< Numeric<EncodingT> >(val);
        if (value)
        {
            value->setValue((double) n);
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Numeric expected, got " << A(val->getClassName());
        }
        return (value != NULL);
    }

NAMESPACE_END

#undef C
#undef A
