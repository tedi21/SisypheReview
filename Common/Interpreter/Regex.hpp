#ifndef _REGEX_HPP_
#define _REGEX_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/regex.hpp>
#include "config.hpp"
#include "macros.hpp"
#include "Base.hpp"

#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Regex
    : public Base<EncodingT>
    {
    public:
        typedef boost::basic_regex<typename EncodingT::char_t> regex_t;

    private:
        regex_t m_value;

		
    public:
        // Constructor
        Regex();

        Regex(regex_t const& value);
        
        FACTORY_PROTOTYPE1(Regex, In< boost::shared_ptr< Base<EncodingT> > >)
        Regex(boost::shared_ptr< Base<EncodingT> > const& val);

        // Accessors
        regex_t const& value() const;
        void value(regex_t const& value);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);
        
        // Dynamic methods
        FACTORY_PROTOTYPE1(setICase, In< boost::shared_ptr< Base<EncodingT> > >)
        void setICase(boost::shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE1(setNoSubs, In< boost::shared_ptr< Base<EncodingT> > >)
        void setNoSubs(boost::shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE1(setCollate, In< boost::shared_ptr< Base<EncodingT> > >)
        void setCollate(boost::shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE1(setOptimize, In< boost::shared_ptr< Base<EncodingT> > >)
        void setOptimize(boost::shared_ptr< Base<EncodingT> > const& val);

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER       (Regex)
            CLASS_REGISTER1      (Regex)
            METHOD_KEY_REGISTER1 (Regex, void, setICase, no_const_t, C("Regex::ICase"))
            METHOD_KEY_REGISTER1 (Regex, void, setNoSubs, no_const_t, C("Regex::NoSubs"))
            METHOD_KEY_REGISTER1 (Regex, void, setCollate, no_const_t, C("Regex::Collate"))
            METHOD_KEY_REGISTER1 (Regex, void, setOptimize, no_const_t, C("Regex::Optimize"))
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER      (Regex)
            CLASS_UNREGISTER1     (Regex)
            METHOD_KEY_UNREGISTER1(C("Regex::ICase"))
            METHOD_KEY_UNREGISTER1(C("Regex::NoSubs"))
            METHOD_KEY_UNREGISTER1(C("Regex::Collate"))
            METHOD_KEY_UNREGISTER1(C("Regex::Optimize"))
        FACTORY_END_UNREGISTER
    };
    
    template <class EncodingT>
    bool check_regex(boost::shared_ptr< Base<EncodingT> > const& val, boost::basic_regex<typename EncodingT::char_t>& r);

    template <class EncodingT>
    bool reset_regex(boost::shared_ptr< Base<EncodingT> >& val, boost::basic_regex<typename EncodingT::char_t> const& r);

NAMESPACE_END

#undef C

#include "regex_impl.hpp"

#endif
