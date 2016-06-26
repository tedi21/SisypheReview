#ifndef ISO_8859_15_CODECVT_FACET_HPP
#define ISO_8859_15_CODECVT_FACET_HPP

#include <locale>
// for mbstate_t
#include <wchar.h>
// for std::size_t
#include <cstddef>
#include <algorithm>
// for symbol export
#include "EncodingExport.hpp"

namespace std {
    #if defined(__LIBCOMO__)
        using ::mbstate_t;
    #elif defined(BOOST_DINKUMWARE_STDLIB) && !defined(__BORLANDC__)
        using ::mbstate_t;
    #elif defined(__SGI_STL_PORT)
    #elif defined(BOOST_NO_STDC_NAMESPACE)
        using ::mbstate_t;
        using ::codecvt;
        using ::min;
    #endif
} // namespace std

#if !defined(__MSL_CPP__) && !defined(__LIBCOMO__)
    #define BOOST_CODECVT_DO_LENGTH_CONST const
#else
    #define BOOST_CODECVT_DO_LENGTH_CONST
#endif

struct ENCODING_API iso_8859_15_codecvt_facet :
    public std::codecvt<wchar_t, char, std::mbstate_t>  
{
private:
    static const int iso_8859_15_SIZE = 256;        
    static wchar_t table[iso_8859_15_SIZE][2]; 
public:
    explicit iso_8859_15_codecvt_facet(std::size_t no_locale_manage=0)
        : std::codecvt<wchar_t, char, std::mbstate_t>(no_locale_manage) 
    {}
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

    virtual bool do_always_noconv() const throw() { return false; }

    virtual int do_encoding() const throw() {
        return 1;
    }

    // How many char objects can I process to get <= max_limit
    // wchar_t objects?
    virtual int do_length(
        BOOST_CODECVT_DO_LENGTH_CONST std::mbstate_t &,
        const char * from,
        const char * from_end, 
        std::size_t max_limit) const
    { return std::min<int>((int) (from_end - from), (int) max_limit); }

    // Largest possible value do_length(state,from,from_end,1) could return.
    virtual int do_max_length() const throw () {
        return 1; // largest iso_8859_15 encoding of a UCS-4 character
    }
};

#endif