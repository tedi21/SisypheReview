#ifndef UTF16_CODECVT_FACET_HPP
#define UTF16_CODECVT_FACET_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// utf16_codecvt_facet.hpp

#include <locale>
// for mbstate_t
#include <wchar.h>
// for std::size_t
#include <cstddef>
// for symbol export
#include "EncodingExport.hpp"
// for platform_dependent
#include "endianness.hpp"

namespace std {
    #if defined(__LIBCOMO__)
        using ::mbstate_t;
    #elif defined(BOOST_DINKUMWARE_STDLIB) && !defined(__BORLANDC__)
        using ::mbstate_t;
    #elif defined(__SGI_STL_PORT)
    #elif defined(BOOST_NO_STDC_NAMESPACE)
        using ::mbstate_t;
        using ::codecvt;
    #endif
} // namespace std

#if !defined(__MSL_CPP__) && !defined(__LIBCOMO__)
    #define BOOST_CODECVT_DO_LENGTH_CONST const
#else
    #define BOOST_CODECVT_DO_LENGTH_CONST
#endif

template <class ENDIAN=platform_dependent>
struct ENCODING_API utf16_codecvt_facet :
    public std::codecvt<wchar_t, char, std::mbstate_t>
{
public:
    explicit utf16_codecvt_facet(std::size_t no_locale_manage=0)
        : std::codecvt<wchar_t, char, std::mbstate_t>(no_locale_manage)
    {}

    static const wchar_t BOM;
protected:
    virtual std::codecvt_base::result do_in(
        std::mbstate_t& state,
        const char * from,
        const char * from_end,
        const char * & from_next,
        wchar_t * to,
        wchar_t * to_end,
        wchar_t*& to_next
    ) const;

    virtual std::codecvt_base::result do_out(
        std::mbstate_t & state, const wchar_t * from,
        const wchar_t * from_end, const wchar_t*  & from_next,
        char * to, char * to_end, char * & to_next
    ) const;

    bool invalid_continuing_word(unsigned short word_1) const {
        return (word_1 < 0xDC00 || 0xDFFF < word_1);
    }

    bool invalid_leading_word(unsigned short word_1)   const {
        return (word_1 < 0xD800  || 0xDBFF < word_1);
    }

    virtual bool do_always_noconv() const throw() { return false; }

    // UTF-16 isn't really stateful since we rewind on partial conversions
    virtual std::codecvt_base::result do_unshift(
        std::mbstate_t&,
        char * from,
        char * /*to*/,
        char * & next
    ) const
    {
        next = from;
        return ok;
    }

    virtual int do_encoding() const throw() {
        const int variable_word_external_encoding=0;
        return variable_word_external_encoding;
    }

    // How many char objects can I process to get <= max_limit
    // wchar_t objects?
    virtual int do_length(
        BOOST_CODECVT_DO_LENGTH_CONST std::mbstate_t &,
        const char * from,
        const char * from_end,
        std::size_t max_limit
        ) const;

    // Largest possible value do_length(state,from,from_end,1) could return.
    virtual int do_max_length() const throw () {
        return 4; // largest UTF-16 encoding of a UCS-4 character
    }

};

#if !defined(HAS_ENCODING_DLL) || defined(BUILD_ENCODING_DLL)
#    include "impl/utf16_codecvt_impl.hpp"
#endif

#endif // BOOST_UTF16_CODECVT_FACET_HPP
