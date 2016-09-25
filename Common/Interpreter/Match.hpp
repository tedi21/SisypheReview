#ifndef _MATCH_HPP_
#define _MATCH_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/regex.hpp>
#include "config.hpp"
#include "macros.hpp"
#include "base.hpp"

#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Match
    : public Base<EncodingT>
    {
    public:
        typedef boost::match_results<typename EncodingT::string_t::const_iterator> match_t;

	private:
        match_t m_value;
        size_t  m_start;

		
    public:
        // Constructor
        Match();

        Match(match_t const& value, size_t start = 0);

        // Destructor
        virtual ~Match();

        // Accessors
        match_t const& getValue() const;
        void setValue(match_t const& value, size_t start = 0);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);
        
        // Dynamic methods
        boost::shared_ptr< Base<EncodingT> > getString() const;

        boost::shared_ptr< Base<EncodingT> > getStringPos() const;

        boost::shared_ptr< Base<EncodingT> > getSubStrings() const;

        boost::shared_ptr< Base<EncodingT> > getSubStringsPos() const;

        boost::shared_ptr< Base<EncodingT> > getPrefix() const;

        boost::shared_ptr< Base<EncodingT> > getSuffix() const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER    (Match)
            METHOD_KEY_REGISTER   (Match, boost::shared_ptr< Base<EncodingT> >, getString, const_t, C("Match::String"))
            METHOD_KEY_REGISTER   (Match, boost::shared_ptr< Base<EncodingT> >, getSubStrings, const_t, C("Match::SubStrings"))
            METHOD_KEY_REGISTER   (Match, boost::shared_ptr< Base<EncodingT> >, getStringPos, const_t, C("Match::StringPos"))
            METHOD_KEY_REGISTER   (Match, boost::shared_ptr< Base<EncodingT> >, getSubStringsPos, const_t, C("Match::SubStringsPos"))
            METHOD_KEY_REGISTER   (Match, boost::shared_ptr< Base<EncodingT> >, getPrefix, const_t, C("Match::Prefix"))
            METHOD_KEY_REGISTER   (Match, boost::shared_ptr< Base<EncodingT> >, getSuffix, const_t, C("Match::Suffix"))
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER  (Match)
            METHOD_KEY_UNREGISTER (C("Match::String"))
            METHOD_KEY_UNREGISTER (C("Match::SubStrings"))
            METHOD_KEY_UNREGISTER (C("Match::StringPos"))
            METHOD_KEY_UNREGISTER (C("Match::SubStringsPos"))
            METHOD_KEY_UNREGISTER (C("Match::Prefix"))
            METHOD_KEY_UNREGISTER (C("Match::Suffix"))
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#undef C

#include "match_impl.hpp"

#endif
