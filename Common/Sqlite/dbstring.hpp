#ifndef _DB_STRING_HPP_
#define _DB_STRING_HPP_

#include "encoding.hpp"
#include <codecvt>
#include <locale>

namespace enc {

    struct dbs {
        typedef char         char_t;
        typedef std::string  string_t;
    };

    // convert
    template<>
    inline typename dbs::string_t
    encode<ucs,dbs>(const typename ucs::char_t * from)
    {
        std::wstring_convert<std::codecvt_utf8<typename ucs::char_t, 0x10ffff, std::little_endian>, typename ucs::char_t> conv;
        return conv.to_bytes(from);
    }
    
    template<>
    inline typename dbs::string_t
    encode<ucs,dbs>(const typename ucs::string_t & from)
    {
        std::wstring_convert<std::codecvt_utf8<typename ucs::char_t, 0x10ffff, std::little_endian>, typename ucs::char_t> conv;
        return conv.to_bytes(from);
    }

    template<>
    inline typename ucs::string_t
    encode<dbs,ucs>(const typename dbs::char_t * from)
    {
        std::wstring_convert<std::codecvt_utf8<typename ucs::char_t, 0x10ffff, std::little_endian>, typename ucs::char_t> conv;
        return conv.from_bytes(from);
    }
    

    template<>
    inline typename ucs::string_t
    encode<dbs,ucs>(const typename dbs::string_t & from)
    {
        std::wstring_convert<std::codecvt_utf8<typename ucs::char_t, 0x10ffff, std::little_endian>, typename ucs::char_t> conv;
        return conv.from_bytes(from);
    }

    // same encoding
    template<>
    inline dbs::string_t
    encode<dbs,dbs>(const dbs::string_t & from)
    {
        return from;
    }

    template<>
    inline dbs::string_t
    encode<dbs,dbs>(const dbs::char_t * from)
    {
        return dbs::string_t(from);
    }

}

#endif

