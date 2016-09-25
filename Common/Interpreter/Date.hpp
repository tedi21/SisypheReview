#ifndef _DATE_HPP_
#define _DATE_HPP_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace boost;
using namespace log4cpp;
namespace dates = boost::gregorian;

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Date
    : public String<EncodingT>
    {
    private:
        dates::date  m_date;

    public:
        // Constructor
        Date();

        Date(const dates::date& d);

        FACTORY_PROTOTYPE3(Date, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        Date(boost::shared_ptr< Base<EncodingT> > const& year, boost::shared_ptr< Base<EncodingT> > const& month, boost::shared_ptr< Base<EncodingT> > const& day);

        // Destructor
        ~Date();

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        // Dynamic methods
        boost::shared_ptr< Base<EncodingT> > getCurrentDate() const;

        boost::shared_ptr< Base<EncodingT> > getDay() const;

        boost::shared_ptr< Base<EncodingT> > getMonth() const;

        boost::shared_ptr< Base<EncodingT> > getYear() const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER      (Date)
            CLASS_REGISTER3     (Date)
            METHOD_KEY_REGISTER (Date, boost::shared_ptr< Base<EncodingT> >, getCurrentDate, const_t, C("Date::CurrentDate") )
            METHOD_KEY_REGISTER (Date, boost::shared_ptr< Base<EncodingT> >, getDay, const_t, C("Date::Day") )
            METHOD_KEY_REGISTER (Date, boost::shared_ptr< Base<EncodingT> >, getMonth, const_t, C("Date::Month") )
            METHOD_KEY_REGISTER (Date, boost::shared_ptr< Base<EncodingT> >, getYear, const_t, C("Date::Year") )
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER      (Date)
            CLASS_UNREGISTER3     (Date)
            METHOD_KEY_UNREGISTER (C("Date::CurrentDate"))
            METHOD_KEY_UNREGISTER (C("Date::Day"))
            METHOD_KEY_UNREGISTER (C("Date::Month"))
            METHOD_KEY_UNREGISTER (C("Date::Year"))
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#undef C
#undef A

#include "date_impl.hpp"

#endif
