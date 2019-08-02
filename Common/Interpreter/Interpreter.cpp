#include <fstream>
#include <boost/scoped_array.hpp>
#include "utf16LE_codecvt.hpp"
#include "ProgramInterpreter.hpp"
#include "File.hpp"
#include "Folder.hpp"
#include "Date.hpp"

using namespace interp;
template class fctr::ClassManager< Base<ucs>, typename ucs::string_t >;

//////////////////////////////////////////
// Exportation des classes
//////////////////////////////////////////

FACTORY_EXPORT_FILE(Base<ucs>, Interp)
FACTORY_EXPORT_FILE(Array<ucs>, Interp)
FACTORY_EXPORT_FILE(Match<ucs>, Interp)
FACTORY_EXPORT_FILE(Regex<ucs>, Interp)
FACTORY_EXPORT_FILE(String<ucs>, Interp)
FACTORY_EXPORT_FILE(Numeric<ucs>, Interp)
FACTORY_EXPORT_FILE(Bool<ucs>, Interp)
FACTORY_EXPORT_FILE(File<ucs>, Interp)
FACTORY_EXPORT_FILE(Folder<ucs>, Interp)
FACTORY_EXPORT_FILE(Date<ucs>, Interp)
FACTORY_EXPORT_FILE(Predicate<ucs>, Interp)
FACTORY_EXPORT_FILE(Structure<ucs>, Interp)

//////////////////////////////////////////
// Fonction de lecture
//////////////////////////////////////////

bool readFile(string const& filename, ucs::string_t & buf)
{
    bool success = false;
    // open UTF-16 file
    ifstream in_file(filename.c_str(), ios_base::binary);
    if (in_file.is_open())
    {
        // read BOM
        unsigned char a = static_cast<unsigned char>(in_file.get());
        unsigned char b = static_cast<unsigned char>(in_file.get());
        ucs::char_t c = static_cast<ucs::char_t>(b << 8) | a;
        in_file.close();

        std::codecvt<ucs::char_t, char, std::mbstate_t> * codecvt_facet = nullptr;
        size_t offset_bom = 0U;
        if (c == utf16LE_codecvt_facet::BOM)
        {
          codecvt_facet = new utf16LE_codecvt_facet;
          offset_bom = 2U;
        }
        else
        {
          codecvt_facet = new iso_8859_15_codecvt_facet;
        }

        basic_ifstream<ucs::char_t> file(filename.c_str());
        if (file.is_open())
        {
            std::locale old_locale;
            std::locale new_locale(old_locale,codecvt_facet);
            file.imbue(new_locale);

            // get length of file:
            file.seekg (0, ios::end);
            size_t length = file.tellg() - offset_bom;
            file.clear();
            file.seekg(0, ios::beg);
            file.seekg(offset_bom);

            // allocate memory
            buf.resize(length);
            // read data as a block:
            file.read(&buf[0], length);
            buf.erase(std::find(buf.begin(), buf.end(), '\0'), buf.end());
            buf.shrink_to_fit();
            success = true;
        }
    }
    return success;
}
