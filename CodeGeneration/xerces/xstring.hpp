#pragma once

#include <string>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/TranscodingException.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include "primitives_char.hpp"
#include "encoding.hpp"
#include "XEncodingExport.hpp"

using namespace chr;
using namespace xercesc;
using namespace std;

typedef std::basic_string<XMLCh> xstring;

namespace enc {

    #define XML(s) u ## s
    struct XENCODING_API xml {
        typedef XMLCh        char_t;
        typedef xstring      string_t;
        static const XMLCh * EMPTY;
    };

    // conversion ansi <-> xml
    template<>
    inline xml::string_t
    encode<ansi,xml>(const ansi::char_t * from)
    {
        xml::string_t result;
        xml::char_t * enc_value = XMLString::transcode(from);
        result = enc_value;
        XMLString::release(&enc_value);
        return result;
    }

    template<>
    inline xml::string_t
    encode<ansi,xml>(const ansi::string_t & from)
    {
        return encode<ansi,xml>(from.c_str());
    }

    template<>
    inline ansi::string_t
    encode<xml,ansi>(const xml::char_t * from)
    {
        ansi::string_t result;
        ansi::char_t * enc_value = XMLString::transcode(from);
        result = enc_value;
        XMLString::release(&enc_value);
        return result;
    }

    template<>
    inline ansi::string_t
    encode<xml,ansi>(const xml::string_t & from)
    {
        return encode<xml,ansi>(from.c_str());
    }

    // conversion ucs <-> xml
    XENCODING_API xml::string_t
    transcodeFrom(const ucs::char_t * from);

    template<>
    inline xml::string_t
    encode<ucs,xml>(const ucs::char_t * from)
    {
        return transcodeFrom(from);
    }

    XENCODING_API ucs::string_t
    transcodeTo(const xml::char_t * from);

    template<>
    inline ucs::string_t
    encode<xml,ucs>(const xml::char_t * from)
    {
        return transcodeTo(from);
    }

    template<>
    inline xml::string_t
    encode<ucs,xml>(const ucs::string_t & from)
    {
        return encode<ucs,xml>(from.c_str());
    }

    template<>
    inline ucs::string_t
    encode<xml,ucs>(const xml::string_t & from)
    {
        return encode<xml,ucs>(from.c_str());
    }

    // same encoding : no conversion
    template<>
    inline xml::string_t
    encode<xml,xml>(const xml::string_t & from)
    {
        return from;
    }

    template<>
    inline xml::string_t
    encode<xml,xml>(const xml::char_t * from)
    {
        return xml::string_t(from);
    }
}
