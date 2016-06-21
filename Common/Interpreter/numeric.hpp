#ifndef _NUMERIC_HPP_
#define _NUMERIC_HPP_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include <boost/shared_ptr.hpp>

#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Numeric
    : public String<EncodingT>
    {
	private:
		double m_value;
		
    public:
        // Constructor
        Numeric();

        Numeric(double value);

        FACTORY_PROTOTYPE1(Numeric, In< shared_ptr< Base<EncodingT> > >)
        Numeric(shared_ptr< Base<EncodingT> > const& value);

        // Destructor
        ~Numeric();

        // Accessors
		double getValue() const;
        void setValue(double value);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual shared_ptr< Base<EncodingT> > clone() const;    
        virtual typename EncodingT::string_t getClassName() const;
        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);
        
        // Dynamic methods
        shared_ptr< Base<EncodingT> > minus() const;

        FACTORY_PROTOTYPE1(plus, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > plus(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(minus, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > minus(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(multiply, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > multiply(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(divide, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > divide(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(equals, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > equals(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(notEquals, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > notEquals(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(inferior, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > inferior(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(inferiorOrEqual, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > inferiorOrEqual(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(superior, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > superior(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(superiorOrEqual, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > superiorOrEqual(shared_ptr< Base<EncodingT> > const& val) const;

        void increment();

        void decrement();

        FACTORY_PROTOTYPE1(parse, In< shared_ptr< Base<EncodingT> > >)
        void parse(shared_ptr< Base<EncodingT> > const& str);
        
        FACTORY_PROTOTYPE1(parseHex, In< shared_ptr< Base<EncodingT> > >)
        void parseHex(shared_ptr< Base<EncodingT> > const& str);

        FACTORY_PROTOTYPE3(parseBase64, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >)
        void parseBase64(shared_ptr< Base<EncodingT> > const& str, shared_ptr< Base<EncodingT> > const& pos, shared_ptr< Base<EncodingT> > const& size);
        
        shared_ptr< Base<EncodingT> > convertHex() const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER    (Numeric)
            CLASS_REGISTER1   (Numeric)
            METHOD_REGISTER   (Numeric, shared_ptr< Base<EncodingT> >, minus, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, plus, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, minus, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, multiply, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, divide, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, inferior, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, inferiorOrEqual, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, superior, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, superiorOrEqual, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, equals, const_t)
            METHOD_REGISTER1  (Numeric, shared_ptr< Base<EncodingT> >, notEquals, const_t)
            METHOD_KEY_REGISTER  (Numeric, void, increment, no_const_t, C("Numeric::Increment"))
            METHOD_KEY_REGISTER  (Numeric, void, decrement, no_const_t, C("Numeric::Decrement"))
            METHOD_KEY_REGISTER1 (Numeric, void, parse, no_const_t, C("Numeric::Parse"))
            METHOD_KEY_REGISTER1 (Numeric, void, parseHex, no_const_t, C("Numeric::ParseHex"))
            METHOD_KEY_REGISTER3 (Numeric, void, parseBase64, no_const_t, C("Numeric::ParseBase64"))
            METHOD_KEY_REGISTER  (Numeric, shared_ptr< Base<EncodingT> >, convertHex, const_t, C("Numeric::ConvertHex"))
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
            METHOD_KEY_UNREGISTER (C("Numeric::Increment"))
            METHOD_KEY_UNREGISTER (C("Numeric::Decrement"))
            METHOD_KEY_UNREGISTER1(C("Numeric::Parse"))
            METHOD_KEY_UNREGISTER1(C("Numeric::ParseHex"))
            METHOD_KEY_UNREGISTER3(C("Numeric::ParseBase64"))
            METHOD_KEY_UNREGISTER (C("Numeric::ConvertHex"))
        FACTORY_END_UNREGISTER
    };

    template <class EncodingT, class T>
    bool check_numeric(shared_ptr< Base<EncodingT> > const& val, T& n);

    template <class EncodingT, class T>
    bool reset_numeric(shared_ptr< Base<EncodingT> >& val, T const& n);

NAMESPACE_END

#undef C

#include "numeric_impl.hpp"

#endif
