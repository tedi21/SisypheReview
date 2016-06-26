#ifndef _LOCALE_HPP_
#define _LOCALE_HPP_

#include "CoreExport.hpp"
#include <sstream>

namespace dsg {

    // Unicode Enum
    enum file_encoding_t 
    {
        FILE_ANSI = 0,
        FILE_UTF_8,
        FILE_UTF_16LE,
        FILE_UTF_16BE,
        FILE_ISO_8859_15,
    };

    CORE_API void
    set_locale(std::basic_ios<wchar_t, std::char_traits<wchar_t> > & stream, file_encoding_t enc);

    CORE_API bool 
    read_file(const char* filename, file_encoding_t enc, std::wstring& in);

    CORE_API bool 
    write_file(const char* filename, file_encoding_t enc, const std::wstring& out);

}

#endif // _LOCALE_HPP_