#ifndef _STRING_HPP_
#define _STRING_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include "config.hpp"
#include "macros.hpp"
#include "base.hpp"

#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Bool;

    template <class EncodingT>
    class String
    : public Base<EncodingT>
    {
	private:
		typename EncodingT::string_t m_value;
		
    public:
        // Constructor
        String();

        String(typename EncodingT::string_t const& value);

        String(typename EncodingT::char_t const& value);

        FACTORY_PROTOTYPE1(String, In< shared_ptr< Base<EncodingT> > >)
        String(shared_ptr< Base<EncodingT> > const& value);

        // Destructor
        virtual ~String();

        // Accessors
		typename EncodingT::string_t const& getValue() const;
        void setValue(typename EncodingT::string_t const& value);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);
        
        // Dynamic methods
        FACTORY_PROTOTYPE1(concat, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > concat(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(equals, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > equals(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(notEquals, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > notEquals(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(iequals, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > iequals(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(notIEquals, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > notIEquals(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(inferior, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > inferior(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(inferiorOrEqual, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > inferiorOrEqual(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(superior, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > superior(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(superiorOrEqual, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > superiorOrEqual(shared_ptr< Base<EncodingT> > const& val) const;

        shared_ptr< Base<EncodingT> > size() const;

        FACTORY_PROTOTYPE2(match, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > match(shared_ptr< Base<EncodingT> > const& regex, shared_ptr< Base<EncodingT> >& matches) const;

        FACTORY_PROTOTYPE5(search, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > search(shared_ptr< Base<EncodingT> > const& start, shared_ptr< Base<EncodingT> > const& end,
                                             shared_ptr< Base<EncodingT> > const& regex, shared_ptr< Base<EncodingT> >& matches, shared_ptr< Base<EncodingT> >& next) const;

        FACTORY_PROTOTYPE1(split, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > split(shared_ptr< Base<EncodingT> > const& regex) const;

        FACTORY_PROTOTYPE1(append, In< shared_ptr< Base<EncodingT> > >)
        void append(shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE2(insert, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >)
        void insert(shared_ptr< Base<EncodingT> > const& pos, shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE2(remove, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >)
        void remove(shared_ptr< Base<EncodingT> > const& pos, shared_ptr< Base<EncodingT> > const& len);

        FACTORY_PROTOTYPE2(substring, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > substring(shared_ptr< Base<EncodingT> > const& pos, shared_ptr< Base<EncodingT> > const& len) const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER    (String)
            CLASS_REGISTER1   (String)
            METHOD_REGISTER1  (String, shared_ptr< Base<EncodingT> >, concat, const_t)
            METHOD_REGISTER1  (String, shared_ptr< Base<EncodingT> >, inferior, const_t)
            METHOD_REGISTER1  (String, shared_ptr< Base<EncodingT> >, inferiorOrEqual, const_t)
            METHOD_REGISTER1  (String, shared_ptr< Base<EncodingT> >, superior, const_t)
            METHOD_REGISTER1  (String, shared_ptr< Base<EncodingT> >, superiorOrEqual, const_t)
            METHOD_REGISTER1  (String, shared_ptr< Base<EncodingT> >, equals, const_t)
            METHOD_REGISTER1  (String, shared_ptr< Base<EncodingT> >, notEquals, const_t)
            METHOD_REGISTER1  (String, shared_ptr< Base<EncodingT> >, iequals, const_t)
            METHOD_REGISTER1  (String, shared_ptr< Base<EncodingT> >, notIEquals, const_t)
            METHOD_REGISTER   (String, shared_ptr< Base<EncodingT> >, size, const_t)
            METHOD_KEY_REGISTER2  (String, shared_ptr< Base<EncodingT> >, match, const_t, C("String::Match"))
            METHOD_KEY_REGISTER5  (String, shared_ptr< Base<EncodingT> >, search, const_t, C("String::Search"))
            METHOD_KEY_REGISTER1  (String, shared_ptr< Base<EncodingT> >, split, const_t, C("String::Split"))
            METHOD_KEY_REGISTER1  (String, void, append, no_const_t, C("String::Append"))
            METHOD_KEY_REGISTER2  (String, void, insert, no_const_t, C("String::Insert"))
            METHOD_KEY_REGISTER2  (String, void, remove, no_const_t, C("String::Remove"))
            METHOD_KEY_REGISTER2  (String, shared_ptr< Base<EncodingT> >, substring, const_t, C("String::SubString"))
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER  (String)
            CLASS_UNREGISTER1 (String)
            METHOD_UNREGISTER1(String, concat)
            METHOD_UNREGISTER1(String, inferior)
            METHOD_UNREGISTER1(String, inferiorOrEqual)
            METHOD_UNREGISTER1(String, superior)
            METHOD_UNREGISTER1(String, superiorOrEqual)
            METHOD_UNREGISTER1(String, equals)
            METHOD_UNREGISTER1(String, notEquals)
            METHOD_UNREGISTER1(String, iequals)
            METHOD_UNREGISTER1(String, notIEquals)
            METHOD_UNREGISTER (String, size)
            METHOD_KEY_UNREGISTER2(C("String::Match"))
            METHOD_KEY_UNREGISTER5(C("String::Search"))
            METHOD_KEY_UNREGISTER1(C("String::Split"))
            METHOD_KEY_UNREGISTER1(C("String::Append"))
            METHOD_KEY_UNREGISTER2(C("String::Insert"))
            METHOD_KEY_UNREGISTER2(C("String::Remove"))
            METHOD_KEY_UNREGISTER2(C("String::SubString"))
        FACTORY_END_UNREGISTER
    };

    template <class EncodingT2, class EncodingT>
    bool check_string(shared_ptr< Base<EncodingT> > const& val, typename EncodingT2::string_t& n);

    template <class EncodingT2, class EncodingT>
    bool check_char(shared_ptr< Base<EncodingT> > const& val, typename EncodingT2::char_t& n);
        
    template <class EncodingT2, class EncodingT>
    bool reset_string(shared_ptr< Base<EncodingT> >& val, typename EncodingT2::string_t const& n);

NAMESPACE_END

#undef C

#include "string_impl.hpp"

#endif
