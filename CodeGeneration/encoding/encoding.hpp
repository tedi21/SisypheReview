#ifndef _ENCODING_HPP_
#define _ENCODING_HPP_

#include "primitives_char.hpp"
#include "EncodingExport.hpp"

using namespace std;

namespace enc {

    struct ENCODING_API ansi {
        typedef char    char_t;
        typedef string    string_t;
        static const char * EMPTY;
    };

    struct ENCODING_API ucs {
        typedef wchar_t        char_t;
        typedef wstring        string_t;
        static const wchar_t * EMPTY;
    };

    // generic copy
    template<class EncodingT1, class EncodingT2>
    inline typename EncodingT2::string_t
    encode(const typename EncodingT1::string_t & from)
    {
        return typename EncodingT2::string_t(from.begin(), from.end());
    }

    template<class EncodingT1, class EncodingT2>
    inline typename EncodingT2::string_t
    encode(const typename EncodingT1::char_t * from)
    {
        return typename EncodingT2::string_t(from, chr::get_last(from));
    }

    // same encoding
    template<>
    inline ansi::string_t
    encode<ansi,ansi>(const ansi::string_t & from)
    {
        return from;
    }

    template<>
    inline ansi::string_t
    encode<ansi,ansi>(const ansi::char_t * from)
    {
        return ansi::string_t(from);
    }

    template<>
    inline ucs::string_t
    encode<ucs,ucs>(const ucs::string_t & from)
    {
        return from;
    }

    template<>
    inline ucs::string_t
    encode<ucs,ucs>(const ucs::char_t * from)
    {
        return ucs::string_t(from);
    }

}

#endif
