#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <cmath>
#include "String.hpp"

#define A(str) encode<EncodingT,ansi>(str)

using namespace boost::archive::iterators;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Numeric<EncodingT>::Numeric()
    {
        m_value = 0LL;
    }

    template <class EncodingT>
    Numeric<EncodingT>::Numeric(const numeric_variant_t& value)
    {
        m_value = value;
    }

    template <class EncodingT>
    template <class T, class>
    Numeric<EncodingT>::Numeric(T value)
    {
        m_value = static_cast<long long>(value);
    }

    template <class EncodingT>
    template <class T, class, class>
    Numeric<EncodingT>::Numeric(T value)
    {
        m_value = static_cast<double>(value);
    }
    
    template <class EncodingT>
    Numeric<EncodingT>::Numeric(boost::shared_ptr< Base<EncodingT> > const& value)
    {
        numeric_variant_t num;     
        if (check_numeric(value, num))
        {
            m_value = num;
        }
    }

    template <class EncodingT>
    double Numeric<EncodingT>::Dvalue() const
    {
        double res = 0.0;
        if (std::holds_alternative<double>(m_value))
        {
            res = std::get<double>(m_value);
        }
        else
        {
            res = std::visit([](auto&& arg){ return static_cast<double>(arg); }, m_value);
        }
        return res;
    }
	
    template <class EncodingT>
    void Numeric<EncodingT>::Dvalue(double value)
    {
        m_value = value;
    }

    template <class EncodingT>
    long long Numeric<EncodingT>::LLvalue() const
    {
        long long res = 0LL;
        if (std::holds_alternative<long long>(m_value))
        {
            res = std::get<long long>(m_value);
        }
        else
        {
            res = std::visit([](auto&& arg){ return static_cast<long long>(arg); }, m_value);
        }
        return res;
    }
	
    template <class EncodingT>
    void Numeric<EncodingT>::LLvalue(long long value)
    {
        m_value = value;
    }
    
    template <class EncodingT>
    const typename Numeric<EncodingT>::numeric_variant_t& Numeric<EncodingT>::value() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void Numeric<EncodingT>::value(const numeric_variant_t& value)
    {
        m_value = value;
    }

    template <class EncodingT>
    typename EncodingT::string_t Numeric<EncodingT>::toString() const
    {
        return std::visit([](auto&& arg){ return Convert<typename EncodingT::string_t>::parse(arg); }, m_value);
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value));
    }

    template <class EncodingT>
    typename EncodingT::string_t Numeric<EncodingT>::getClassName() const
    {
        return UCS("Numeric");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, UCS("Numeric"), method, args, ret) ||
                tryInvoke(this, UCS("Base"), method, args, ret))
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
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(
          std::visit([](auto&& arg){ return numeric_variant_t(-arg); }, m_value)));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::plus(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Numeric<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return numeric_variant_t(arg1 + arg2); }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::minus(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Numeric<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return numeric_variant_t(arg1 - arg2); }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::multiply(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Numeric<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return numeric_variant_t(arg1 * arg2); }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::divide(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Numeric<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return numeric_variant_t(arg1 / arg2); }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::equals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return arg1 == arg2; }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::notEquals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return arg1 != arg2; }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::inferior(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return arg1 < arg2; }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::inferiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return arg1 <= arg2; }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::superior(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return arg1 > arg2; }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::superiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        numeric_variant_t num;
        if (check_numeric(val, num))
        {
            res.reset(new Bool<EncodingT>(
              std::visit([](auto&& arg1, auto&& arg2){ return arg1 >= arg2; }, m_value, num)));
        }
        return res;
    }

    template <class EncodingT>
    void Numeric<EncodingT>::increment()
    {
        std::visit([](auto&& arg){ ++arg; }, m_value);
    }

    template <class EncodingT>
    void Numeric<EncodingT>::decrement()
    {
        std::visit([](auto&& arg){ --arg; }, m_value);
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::round() const
    {
        numeric_variant_t res = m_value;
        if (std::holds_alternative<double>(m_value))
        {
            res = static_cast<long long>(std::round(std::get<double>(m_value)));
        }
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(res));
    }

    template <class EncodingT>
    void Numeric<EncodingT>::parse(boost::shared_ptr< Base<EncodingT> > const& str)
    {
        typename EncodingT::string_t text = str->toString();
        long long llvalue;
        double dvalue;
        if (Convert<long long>::try_parse(text, llvalue))
        {
            m_value = llvalue;
        }
        else if (Convert<double>::try_parse(text, dvalue))
        {
            m_value = dvalue;
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Cannot convert to numeric \"" << A(text) << "\".";
        }
    }
    
    template <class EncodingT>
    void Numeric<EncodingT>::parseHex(boost::shared_ptr< Base<EncodingT> > const& str)
    {
        m_value = Convert<long long>::parse(str->toString(), std::ios_base::hex);
    }

    template <class EncodingT>
    void Numeric<EncodingT>::parseBase64(boost::shared_ptr< Base<EncodingT> > const& str, boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& size)
    {
        typename EncodingT::string_t text = str->toString();
        unsigned long long natPos, natSize;
        if (check_numeric_i(pos, natPos) &&
            check_numeric_i(size, natSize))
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
            unsigned long long bitPos = natPos;
            unsigned long long bitSize = natSize;
            unsigned long long byteStart = bitPos / 8;
            unsigned long long byteEnd = (bitSize + bitPos) / 8;
            unsigned long long bitStart = bitPos % 8;
            unsigned long long bitEnd = (bitSize + bitPos) % 8;
            unsigned char mask;
            unsigned long long value = 0;
            if (byteEnd < buffer.size())
            {
                while (byteStart != byteEnd)
                {
                    mask = 0xFF;
                    mask = mask >> bitStart;
                    bitSize -= (8 - bitStart);
                    value += ((buffer[byteStart] & mask) << bitSize);
                    bitStart = 0;
                    byteStart++;
                }
                mask = 0xFF;
                mask = mask >> bitStart;
                value += ((buffer[byteEnd] & mask) >> (8 - bitEnd));
            }
            m_value = static_cast<long long>(value);
        }
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Numeric<EncodingT>::convertHex() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(
          Convert<typename EncodingT::string_t>::parse(this->LLvalue(), std::ios_base::hex)));
    }

    template <class EncodingT>
    bool check_numeric(boost::shared_ptr< Base<EncodingT> > const& val, std::variant<long long,double>& n)
    {
        boost::shared_ptr< Numeric<EncodingT> > value  = dynamic_pointer_cast< Numeric<EncodingT> >(val);
        if (value)
        {
            n = value->value();
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Numeric expected, got " << A(val->getClassName());            
        }
        return (value != NULL);
    }

    template <class EncodingT>
    bool reset_numeric(boost::shared_ptr< Base<EncodingT> >& val, std::variant<long long,double> const& n)
    {
        boost::shared_ptr< Numeric<EncodingT> > value  = dynamic_pointer_cast< Numeric<EncodingT> >(val);
        if (value)
        {
            value->value(n);
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Numeric expected, got " << A(val->getClassName());
        }
        return (value != NULL);
    }

    template <class EncodingT, class T, class>
    bool check_numeric_i(boost::shared_ptr< Base<EncodingT> > const& val, T& n)
    {
        boost::shared_ptr< Numeric<EncodingT> > value  = dynamic_pointer_cast< Numeric<EncodingT> >(val);
        if (value)
        {
            n = static_cast<T>(value->LLvalue());
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Numeric expected, got " << A(val->getClassName());            
        }
        return (value != NULL);
    }

    template <class EncodingT, class T, class>
    bool reset_numeric_i(boost::shared_ptr< Base<EncodingT> >& val, T n)
    {
        boost::shared_ptr< Numeric<EncodingT> > value  = dynamic_pointer_cast< Numeric<EncodingT> >(val);
        if (value)
        {
            value->LLvalue(static_cast<long long>(n));
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Numeric expected, got " << A(val->getClassName());
        }
        return (value != NULL);
    }

    template <class EncodingT, class T, class>
    bool check_numeric_d(boost::shared_ptr< Base<EncodingT> > const& val, T& n)
    {
        boost::shared_ptr< Numeric<EncodingT> > value  = dynamic_pointer_cast< Numeric<EncodingT> >(val);
        if (value)
        {
            n = static_cast<T>(value->Dvalue());
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Numeric expected, got " << A(val->getClassName());
        }
        return (value != NULL);
    }
    
    template <class EncodingT, class T, class>
    bool reset_numeric_d(boost::shared_ptr< Base<EncodingT> >& val, T n)
    {
        boost::shared_ptr< Numeric<EncodingT> > value  = dynamic_pointer_cast< Numeric<EncodingT> >(val);
        if (value)
        {
            value->Dvalue(static_cast<double>(n));
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Numeric expected, got " << A(val->getClassName());
        }
        return (value != NULL);
    }
    
    
NAMESPACE_END

#undef A
