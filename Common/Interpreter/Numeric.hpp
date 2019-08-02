#ifndef _NUMERIC_HPP_
#define _NUMERIC_HPP_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include <boost/shared_ptr.hpp>
#include <variant>
#include <type_traits>

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Numeric
    : public Base<EncodingT>
    {
    private:
        typedef std::variant<long long,double> numeric_variant_t;
        numeric_variant_t m_value;

    public:
        // Constructor
        Numeric();

        Numeric(const numeric_variant_t& value);
        template <class T, class = typename std::enable_if<std::is_integral<T>::value||std::is_enum<T>::value,T>::type>
        Numeric(T value);
        template <class T, class = void, class = typename std::enable_if<std::is_floating_point<T>::value,T>::type>
        Numeric(T value);
        
        FACTORY_PROTOTYPE1(Numeric, In< boost::shared_ptr< Base<EncodingT> > >)
        Numeric(boost::shared_ptr< Base<EncodingT> > const& value);

        // Accessors
        double Dvalue() const;
        void Dvalue(double value);
        long long LLvalue() const;
        void LLvalue(long long value);
        const numeric_variant_t& value() const;
        void value(const numeric_variant_t& value);
        
        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);
        
        // Dynamic methods
        boost::shared_ptr< Base<EncodingT> > minus() const;

        FACTORY_PROTOTYPE1(plus, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > plus(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(minus, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > minus(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(multiply, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > multiply(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(divide, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > divide(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(equals, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > equals(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(notEquals, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > notEquals(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(inferior, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > inferior(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(inferiorOrEqual, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > inferiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(superior, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > superior(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(superiorOrEqual, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > superiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const;

        void increment();

        void decrement();

        boost::shared_ptr< Base<EncodingT> > round() const;

        FACTORY_PROTOTYPE1(parse, In< boost::shared_ptr< Base<EncodingT> > >)
        void parse(boost::shared_ptr< Base<EncodingT> > const& str);
        
        FACTORY_PROTOTYPE1(parseHex, In< boost::shared_ptr< Base<EncodingT> > >)
        void parseHex(boost::shared_ptr< Base<EncodingT> > const& str);

        FACTORY_PROTOTYPE3(parseBase64, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void parseBase64(boost::shared_ptr< Base<EncodingT> > const& str, boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& size);
        
        boost::shared_ptr< Base<EncodingT> > convertHex() const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER    (Numeric)
            CLASS_REGISTER1   (Numeric)
            METHOD_REGISTER   (Numeric, boost::shared_ptr< Base<EncodingT> >, minus, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, plus, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, minus, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, multiply, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, divide, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, inferior, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, inferiorOrEqual, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, superior, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, superiorOrEqual, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, equals, const_t)
            METHOD_REGISTER1  (Numeric, boost::shared_ptr< Base<EncodingT> >, notEquals, const_t)
            METHOD_KEY_REGISTER  (Numeric, void, increment, no_const_t, UCS("Numeric::Increment"))
            METHOD_KEY_REGISTER  (Numeric, void, decrement, no_const_t, UCS("Numeric::Decrement"))
            METHOD_KEY_REGISTER  (Numeric, boost::shared_ptr< Base<EncodingT> >, round, const_t, UCS("Numeric::Round"))
            METHOD_KEY_REGISTER1 (Numeric, void, parse, no_const_t, UCS("Numeric::Parse"))
            METHOD_KEY_REGISTER1 (Numeric, void, parseHex, no_const_t, UCS("Numeric::ParseHex"))
            METHOD_KEY_REGISTER3 (Numeric, void, parseBase64, no_const_t, UCS("Numeric::ParseBase64"))
            METHOD_KEY_REGISTER  (Numeric, boost::shared_ptr< Base<EncodingT> >, convertHex, const_t, UCS("Numeric::ConvertHex"))
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER  (Numeric)
            CLASS_UNREGISTER1 (Numeric)
            METHOD_UNREGISTER (Numeric, minus)
            METHOD_UNREGISTER1(Numeric, plus)
            METHOD_UNREGISTER1(Numeric, minus)
            METHOD_UNREGISTER1(Numeric, multiply)
            METHOD_UNREGISTER1(Numeric, divide)
            METHOD_UNREGISTER1(Numeric, inferior)
            METHOD_UNREGISTER1(Numeric, inferiorOrEqual)
            METHOD_UNREGISTER1(Numeric, superior)
            METHOD_UNREGISTER1(Numeric, superiorOrEqual)
            METHOD_UNREGISTER1(Numeric, equals)
            METHOD_UNREGISTER1(Numeric, notEquals)
            METHOD_KEY_UNREGISTER (UCS("Numeric::Increment"))
            METHOD_KEY_UNREGISTER (UCS("Numeric::Decrement"))
            METHOD_KEY_UNREGISTER (UCS("Numeric::Round"))
            METHOD_KEY_UNREGISTER1(UCS("Numeric::Parse"))
            METHOD_KEY_UNREGISTER1(UCS("Numeric::ParseHex"))
            METHOD_KEY_UNREGISTER3(UCS("Numeric::ParseBase64"))
            METHOD_KEY_UNREGISTER (UCS("Numeric::ConvertHex"))
        FACTORY_END_UNREGISTER
    };

    template <class EncodingT>
    bool check_numeric(boost::shared_ptr< Base<EncodingT> > const& val, std::variant<long long,double>& n);

    template <class EncodingT>
    bool reset_numeric(boost::shared_ptr< Base<EncodingT> >& val, std::variant<long long,double> const& n);

    template <class EncodingT, class T, class = typename std::enable_if<std::is_integral<T>::value||std::is_enum<T>::value>::type>
    bool check_numeric_i(boost::shared_ptr< Base<EncodingT> > const& val, T& n);

    template <class EncodingT, class T, class = typename std::enable_if<std::is_integral<T>::value||std::is_enum<T>::value>::type>
    bool reset_numeric_i(boost::shared_ptr< Base<EncodingT> >& val, T n);

    template <class EncodingT, class T, class = typename std::enable_if<std::is_floating_point<T>::value>::type>
    bool check_numeric_d(boost::shared_ptr< Base<EncodingT> > const& val, T& n);

    template <class EncodingT, class T, class = typename std::enable_if<std::is_floating_point<T>::value>::type>
    bool reset_numeric_d(boost::shared_ptr< Base<EncodingT> >& val, T n);

    
NAMESPACE_END

#include "Numeric_impl.hpp"

#endif
