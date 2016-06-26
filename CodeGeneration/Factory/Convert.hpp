/**
 * @class Convert
 * @date 20/04/2007
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief Classe permettant de convertir des types vers d'autres types </br> out_type : le type de sortie de la conversion
 */

#ifndef CONVERT_HPP
#define CONVERT_HPP
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

namespace fctr {

// trait pour choisir le type de char
template <class type>
struct convert_traits
{
    typedef char char_type;
    static const char char_default = ' ';
};

#define CHAR_TYPE(type)\
    typename convert_traits<type>::char_type

#define CHAR_DEFAULT(type)\
    convert_traits<type>::char_default

template <bool false_, class type_true, class type_false>
struct char_selection_traits
{
    typedef CHAR_TYPE(type_false) char_type;
    static const char_type char_default = CHAR_DEFAULT(type_false);
};

template <class type_true, class type_false>
struct char_selection_traits<true, type_true, type_false>
{
    typedef CHAR_TYPE(type_true) char_type;
    static const char_type char_default = CHAR_DEFAULT(type_true);
};

template <class type1, class type2>
struct char_decision
{
    enum {value = sizeof(CHAR_TYPE(type1))>sizeof(CHAR_TYPE(type2))};
};

#define CHAR_SELECTION(type1, type2)\
    typename char_selection_traits<char_decision<type1,type2>::value,type1,type2>::char_type


#define CHAR_SELECTION_DEFAULT(type1, type2)\
    char_selection_traits<char_decision<type1,type2>::value,type1,type2>::char_default

template <class CharT>
struct convertstream
: basic_stringstream<CharT, 
            char_traits<CharT>,
            allocator<CharT> >
{};

template <class out_type>
class Convert {
public:
    /** test la conversion des types
    @param t la variable à convertir
    @param fmtfl les flags de format
    @param prec la precision
    @param wide la largeur de completion
    @param fillch le caractere de completion
    @return si le test a réussi
    */
    template <class in_type>
    static bool try_parse(const in_type & t, out_type & r, ios::fmtflags fmtfl = (ios::fmtflags)0,
                          streamsize prec = 6, streamsize wide = 0, CHAR_SELECTION(out_type,in_type) fillch = CHAR_SELECTION_DEFAULT(out_type,in_type))
    {
        typedef CHAR_SELECTION(out_type,in_type) char_type;
        convertstream<char_type> strm;
        strm.flags(fmtfl);
        strm.precision(prec);
        strm.width(wide);
        strm.fill(fillch);
        strm << t;
        strm >> r; 
        return !strm.fail() && strm.peek() == std::char_traits<char_type>::eof();
    }    
    /** réalise la conversion des types
    @param t la variable à convertir
    @param fmtfl les flags de format
    @param prec la precision
    @param wide la largeur de completion
    @param fillch le caractere de completion
    @return la variable convertie
    */
    template <class in_type>
    static out_type parse(const in_type & t, ios::fmtflags fmtfl = (ios::fmtflags)0,
                          streamsize prec = 6, streamsize wide = 0, CHAR_SELECTION(out_type,in_type) fillch = CHAR_SELECTION_DEFAULT(out_type,in_type))
    {
        out_type result;
        try_parse(t, result, fmtfl, prec, wide, fillch); 
        return result;
    }       

/// specialization - no conversion
    /** test la conversion des types
    @param t la variable à convertir
    @param fmtfl les flags de format
    @param prec la precision
    @param wide la largeur de completion
    @param fillch le caractere de completion
    @return si le test a réussi
    */
    static bool try_parse(const out_type & t, out_type & r, ios::fmtflags fmtfl = (ios::fmtflags)0,
                          streamsize prec = 6, streamsize wide = 0, CHAR_TYPE(out_type) fillch = CHAR_DEFAULT(out_type))
    {
        r = t; 
        return true;
    } 
    /** réalise la conversion des types
    @param t la variable à convertir
    @param fmtfl les flags de format
    @param prec la precision
    @param wide la largeur de completion
    @param fillch le caractere de completion
    @return la variable convertie
    */
    static out_type parse(const out_type & t, ios::fmtflags fmtfl = (ios::fmtflags)0,
                          streamsize prec = 6, streamsize wide = 0, CHAR_TYPE(out_type) fillch = CHAR_DEFAULT(out_type))
    {
        return t;
    }     
};

// conversion en string
typedef Convert<string> ToString;
// conversion en int
typedef Convert<int> ToInt;
// conversion en bool
typedef Convert<bool> ToBool;
// conversion en double
typedef Convert<double> ToDouble;
// conversion en char
typedef Convert<char> ToChar;

// traits pour les wstring
template <>
struct convert_traits<wstring>
{
    typedef wchar_t char_type;
    static const wchar_t char_default = L' ';
};

// redefinition des operateurs
inline convertstream<wchar_t>& operator<<(convertstream<wchar_t>& os, const string& str)
{
    wstring tmp(str.begin(), str.end());
    os << tmp;
    return os;
}

inline convertstream<wchar_t>& operator>>(convertstream<wchar_t>& is, string& str)
{
    wstring tmp;
    is >> tmp;
    str.assign(tmp.begin(), tmp.end());
    return is;
}

// conversion en wstring
typedef Convert<wstring> ToWString;

// trait pour les wchar_t
template <>
struct convert_traits<wchar_t>
{
    typedef wchar_t char_type;
    static const wchar_t char_default = L' ';
};
// conversion en wchar_t
typedef Convert<wchar_t> ToWChar;

}

#endif 
