#ifndef _STRING_HPP_
#define _STRING_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <functional>
#include <string>
#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Indexable.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Bool;

    template <class EncodingT>
    class String
    : public Base<EncodingT>,
      public Indexable<EncodingT>
    {
    private:
        typename EncodingT::string_t m_value;

    public:
        // Constructor
        String();

        String(typename EncodingT::string_t const& value);

        String(typename EncodingT::char_t const& value);

        FACTORY_PROTOTYPE1(String, In< boost::shared_ptr< Base<EncodingT> > >)
        String(boost::shared_ptr< Base<EncodingT> > const& value);

        // Accessors
        typename EncodingT::string_t const& value() const;
        void value(typename EncodingT::string_t const& value);
        virtual boost::shared_ptr< Base<EncodingT> > valueAt(size_t i) const;
        virtual size_t length() const;

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);
        
        // Dynamic methods
        FACTORY_PROTOTYPE1(concat, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > concat(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(equals, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > equals(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(notEquals, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > notEquals(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(iequals, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > iequals(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(notIEquals, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > notIEquals(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(inferior, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > inferior(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(inferiorOrEqual, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > inferiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(superior, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > superior(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(superiorOrEqual, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > superiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const;

        boost::shared_ptr< Base<EncodingT> > size() const;
        
        FACTORY_PROTOTYPE1(addValue, In< boost::shared_ptr< Base<EncodingT> > >)
        void addValue(boost::shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE2(insertValue, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void insertValue(boost::shared_ptr< Base<EncodingT> > const& i, boost::shared_ptr< Base<EncodingT> > const& val);
        
        FACTORY_PROTOTYPE3(insertList, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void insertList(boost::shared_ptr< Base<EncodingT> > const& i1, boost::shared_ptr< Base<EncodingT> > const& i2, boost::shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE1(removeValue, In< boost::shared_ptr< Base<EncodingT> > >)
        void removeValue(boost::shared_ptr< Base<EncodingT> > const& i);
        
        FACTORY_PROTOTYPE2(removeList, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void removeList(boost::shared_ptr< Base<EncodingT> > const& i1, boost::shared_ptr< Base<EncodingT> > const& i2);
        
        FACTORY_PROTOTYPE1(getValue, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > getValue(boost::shared_ptr< Base<EncodingT> > const& i) const;
        
        FACTORY_PROTOTYPE2(getList, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > getList(boost::shared_ptr< Base<EncodingT> > const& i1, boost::shared_ptr< Base<EncodingT> > const& i2) const;

        FACTORY_PROTOTYPE2(match, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > match(boost::shared_ptr< Base<EncodingT> > const& regex, boost::shared_ptr< Base<EncodingT> >& matches) const;

        FACTORY_PROTOTYPE5(search, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > search(boost::shared_ptr< Base<EncodingT> > const& start, boost::shared_ptr< Base<EncodingT> > const& end,
                                             boost::shared_ptr< Base<EncodingT> > const& regex, boost::shared_ptr< Base<EncodingT> >& matches, boost::shared_ptr< Base<EncodingT> >& next) const;

        FACTORY_PROTOTYPE1(split, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > split(boost::shared_ptr< Base<EncodingT> > const& regex) const;
        
        FACTORY_PROTOTYPE2(replaceAll, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void replaceAll(boost::shared_ptr< Base<EncodingT> > const& search, boost::shared_ptr< Base<EncodingT> > const& replace);
        
        FACTORY_PROTOTYPE4(replaceRegex, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void replaceRegex(boost::shared_ptr< Base<EncodingT> > const& start, boost::shared_ptr< Base<EncodingT> > const& end,
                          boost::shared_ptr< Base<EncodingT> > const& regex, boost::shared_ptr< Base<EncodingT> > const& replace);

        FACTORY_PROTOTYPE1(append, In< boost::shared_ptr< Base<EncodingT> > >)
        void append(boost::shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE2(insert, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void insert(boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE2(remove, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void remove(boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& len);

        FACTORY_PROTOTYPE2(substring, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > substring(boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& len) const;
        
        boost::shared_ptr< Base<EncodingT> > hash() const;
        
        void trim();

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER    (String)
            CLASS_REGISTER1   (String)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, concat, const_t)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, inferior, const_t)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, inferiorOrEqual, const_t)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, superior, const_t)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, superiorOrEqual, const_t)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, equals, const_t)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, notEquals, const_t)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, iequals, const_t)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, notIEquals, const_t)
            METHOD_REGISTER   (String, boost::shared_ptr< Base<EncodingT> >, size, const_t)
            METHOD_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, getValue, const_t)
            METHOD_REGISTER2  (String, boost::shared_ptr< Base<EncodingT> >, getList, const_t)
            METHOD_REGISTER1  (String, void, addValue, no_const_t)
            METHOD_REGISTER2  (String, void, insertValue, no_const_t)
            METHOD_REGISTER3  (String, void, insertList, no_const_t)
            METHOD_REGISTER1  (String, void, removeValue, no_const_t)
            METHOD_REGISTER2  (String, void, removeList, no_const_t)
            METHOD_KEY_REGISTER2  (String, boost::shared_ptr< Base<EncodingT> >, match, const_t, UCS("String::Match"))
            METHOD_KEY_REGISTER5  (String, boost::shared_ptr< Base<EncodingT> >, search, const_t, UCS("String::Search"))
            METHOD_KEY_REGISTER1  (String, boost::shared_ptr< Base<EncodingT> >, split, const_t, UCS("String::Split"))
            METHOD_KEY_REGISTER2  (String, void, replaceAll, no_const_t, UCS("String::ReplaceAll"))
            METHOD_KEY_REGISTER4  (String, void, replaceRegex, no_const_t, UCS("String::ReplaceRegex"))
            METHOD_KEY_REGISTER1  (String, void, append, no_const_t, UCS("String::Append"))
            METHOD_KEY_REGISTER2  (String, void, insert, no_const_t, UCS("String::Insert"))
            METHOD_KEY_REGISTER2  (String, void, remove, no_const_t, UCS("String::Remove"))
            METHOD_KEY_REGISTER2  (String, boost::shared_ptr< Base<EncodingT> >, substring, const_t, UCS("String::SubString"))
            METHOD_KEY_REGISTER   (String, boost::shared_ptr< Base<EncodingT> >, hash, const_t, UCS("String::Hash"))
            METHOD_KEY_REGISTER   (String, void, trim, no_const_t, UCS("String::Trim"))
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
            METHOD_UNREGISTER1(String, getValue)
            METHOD_UNREGISTER2(String, getList)
            METHOD_UNREGISTER1(String, addValue)
            METHOD_UNREGISTER2(String, insertValue)
            METHOD_UNREGISTER3(String, insertList)
            METHOD_UNREGISTER1(String, removeValue)
            METHOD_UNREGISTER2(String, removeList)
            METHOD_KEY_UNREGISTER2(UCS("String::Match"))
            METHOD_KEY_UNREGISTER5(UCS("String::Search"))
            METHOD_KEY_UNREGISTER1(UCS("String::Split"))
            METHOD_KEY_UNREGISTER2(UCS("String::ReplaceAll"))
            METHOD_KEY_UNREGISTER4(UCS("String::ReplaceRegex"))
            METHOD_KEY_UNREGISTER1(UCS("String::Append"))
            METHOD_KEY_UNREGISTER2(UCS("String::Insert"))
            METHOD_KEY_UNREGISTER2(UCS("String::Remove"))
            METHOD_KEY_UNREGISTER2(UCS("String::SubString"))
            METHOD_KEY_UNREGISTER (UCS("String::Hash"))
            METHOD_KEY_UNREGISTER (UCS("String::Trim"))
        FACTORY_END_UNREGISTER
    };

    template <class EncodingT2, class EncodingT>
    bool check_string(boost::shared_ptr< Base<EncodingT> > const& val, typename EncodingT2::string_t& n);

    template <class EncodingT2, class EncodingT>
    bool check_char(boost::shared_ptr< Base<EncodingT> > const& val, typename EncodingT2::char_t& n);
        
    template <class EncodingT2, class EncodingT>
    bool reset_string(boost::shared_ptr< Base<EncodingT> >& val, typename EncodingT2::string_t const& n);

NAMESPACE_END

#include "String_impl.hpp"

#endif
