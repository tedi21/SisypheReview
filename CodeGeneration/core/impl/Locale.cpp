#include "Locale.hpp"
#include "encoding.hpp"
#include "utf8_codecvt.hpp"
#include "utf16BE_codecvt.hpp"
#include "utf16LE_codecvt.hpp"
#include "iso_8859_15_codecvt.hpp"
#include "Logger.hpp"
#include <fstream>
#include <boost/scoped_array.hpp>

using namespace std;
using namespace log4cpp;
using namespace boost;
using namespace enc;

namespace dsg {

    CORE_API void
    set_locale(std::basic_ios<wchar_t, std::char_traits<wchar_t> > & stream, file_encoding_t enc)
    {
        // set encoding
        std::locale old_locale;
        std::codecvt<wchar_t, char, std::mbstate_t> * codecvt_facet;

        switch (enc)
        {
        case FILE_UTF_8:
            codecvt_facet = new utf8_codecvt_facet;
            break;
        case FILE_UTF_16LE:
            codecvt_facet = new utf16LE_codecvt_facet;
            break;
        case FILE_UTF_16BE:
            codecvt_facet = new utf16BE_codecvt_facet;
            break;
        case FILE_ISO_8859_15:
            codecvt_facet = new iso_8859_15_codecvt_facet;
            break;
        case FILE_ANSI:
        default:
            return;
        }
        std::locale new_locale(old_locale,codecvt_facet);
        // Set a New global locale
        //std::locale::global(new_locale);
        stream.imbue(new_locale);
    }

    CORE_API bool 
    read_file(const char* filename, file_encoding_t enc, std::wstring& in)
    {
        bool result = false;
        Category* logger = &Category::getInstance(LOGNAME);

        wifstream in_file(filename, ios::binary);
        set_locale(in_file, enc);

        if (in_file.is_open())
        {
            scoped_array<wchar_t> buffer;
            int start = 0, length = 0;
            // get length of file:
            in_file.seekg (0, ios::end);
            length = in_file.tellg();
            in_file.seekg (0, ios::beg);
            logger->debugStream() << "length of file :" << length;

            // allocate memory: exact(latin-1) or larger than necessary(Unicode)
            buffer.reset( new wchar_t[length+1] );
            memset(buffer.get(), 0, (length+1)*sizeof(wchar_t));

            // read data as a block:
            in_file.read(buffer.get(), length);
            in_file.close();
            if (enc == FILE_UTF_16LE ||
				enc == FILE_UTF_16BE) 
			    start = 1; // without 0xFEFF
            logger->debugStream() << encode<ucs,ansi>(buffer.get());
            in = buffer.get()+ start;
            result = true;
        }
        else
        {
            logger->errorStream() << "Unable to open the file :" << filename;
        }
        return result;
    }

    CORE_API bool 
    write_file(const char* filename, file_encoding_t enc, const std::wstring& out)
    {
        Category* logger = &Category::getInstance(LOGNAME);

        wofstream out_file;
        set_locale(out_file, enc);

        bool result = out.empty();
        if (!result)
        {
            out_file.open(filename, ios::binary);
            if (out_file.is_open())
            {
                if (enc == FILE_UTF_16LE || 
					enc == FILE_UTF_16BE)
                    out_file << utf16_codecvt_facet<>::BOM;
                out_file.write(out.c_str(), (streamsize) out.size());
                out_file.close();
                result = true;
            }
            else 
            {
                logger->errorStream() << "Unable to open the file :" << filename;
            }
        }
        else
        {
            logger->noticeStream() << "No file " << filename << " generated";
        }
        return result;
    }

}
