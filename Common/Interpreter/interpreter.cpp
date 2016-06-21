#include <fstream>
#include <boost/scoped_array.hpp>
#include "utf16LE_codecvt.hpp"
#include "programinterpreter.hpp"
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
    int length;
    scoped_array<wchar_t> buffer;
    std::locale old_locale;
    std::codecvt<wchar_t, char, std::mbstate_t> * codecvt_facet;
    wifstream in_file(filename.c_str(), ios::binary);
    codecvt_facet = new utf16LE_codecvt_facet;
    std::locale new_locale(old_locale,codecvt_facet);
    in_file.imbue(new_locale);

    if (in_file.is_open())
    {
        // get length of file.
        in_file.seekg (0, ios::end);
        length = in_file.tellg();
        in_file.seekg (0, ios::beg);

        // allocate memory: exact(latin-1) or larger than necessary(Unicode).
        buffer.reset( new wchar_t[length+1] );
        memset(buffer.get(), 0, (length+1)*sizeof(wchar_t));

        // read data as a block.
        in_file.read(buffer.get(), length);
        in_file.close();

        buf.assign(buffer.get() + 1);
        success = true;
    }
    return success;
}
