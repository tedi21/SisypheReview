#if !defined(PRIMITIVES_CHAR_HPP)
#define PRIMITIVES_CHAR_HPP

// This should eventually go to a config file.
#if defined(__GNUC__) && (__GNUC__ < 3) && !defined(_STLPORT_VERSION)
#  ifndef NO_CHAR_TRAITS
#    define NO_CHAR_TRAITS
#  endif
#endif

#include <cctype>
#if !defined(BOOST_NO_CWCTYPE)
#include <cwctype>
#endif

#ifndef NO_CHAR_TRAITS
#  include <string> // char_traits
#endif

#if defined(BOOST_MSVC)
#  pragma warning(disable:4800)
#endif

//#include <boost/ref.hpp>

namespace chr {
    ///////////////////////////////////////////////////////////////////////////
    //
    // Character type of string type
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharIteratorT>
    inline CharIteratorT get_last(CharIteratorT first)
    {
        while (*first)
            first++;
        return first;
    }

    template <typename CharIteratorT>
    inline size_t get_len(CharIteratorT first)
    { 
        return chr::get_last(first)-first;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    // Conversion from char_type to int_type
    //
    ///////////////////////////////////////////////////////////////////////////

#ifndef NO_CHAR_TRAITS
#  define CHAR_TRAITS_NAMESPACE std
#else

    template <typename CharT>
    struct char_traits
    {
        typedef CharT int_type;
        typedef CharT char_type;
    };

    template<>
    struct char_traits<char>
    {
        typedef int int_type;
        typedef char char_type;

        static char_type 
        to_char_type(int_type c)
        { 
            return static_cast<char_type>(c); 
        }

        static int 
        to_int_type(char c)
        { 
            return static_cast<unsigned char>(c); 
        }
    };

    template<>
    struct char_traits<unsigned char>
    {
        typedef int int_type;
        typedef unsigned char char_type;

        static char_type 
        to_char_type(int_type c)
        { 
            return static_cast<char_type>(c); 
        }

        static int 
        to_int_type(unsigned char c)
        { 
            return c; 
        }
    };

#  define CHAR_TRAITS_NAMESPACE impl
#  ifndef BOOST_NO_CWCTYPE

    template<>
    struct char_traits<wchar_t>
    {
        typedef wint_t int_type;
        typedef wchar_t char_type;
        
        static char_type 
        to_char_type(int_type c)
        { 
            return static_cast<char_type>(c); 
        }

        static wint_t 
        to_int_type(wchar_t c)
        { 
            return c; 
        }
    };

#  endif
#endif // NO_CHAR_TRAITS

    //  Use char_traits for char and wchar_t only, as these are the only
    //  specializations provided in the standard. Other types are on their
    //  own.
    //
    //  For UDT, one may override:
    //
    //      isalnum
    //      isalpha
    //      iscntrl
    //      isdigit
    //      isgraph
    //      islower
    //      isprint
    //      ispunct
    //      isspace
    //      isupper
    //      isxdigit
    //      isblank
    //      isupper
    //      tolower
    //      toupper
    //
    //  in a namespace suitable for Argument Dependent lookup or in
    //  namespace std (disallowed by the standard).
    
    template <typename CharT>
    struct char_type_char_traits_helper
    {
        typedef CharT char_type;
        typedef typename CHAR_TRAITS_NAMESPACE
            ::char_traits<CharT>::int_type int_type;

        static int_type to_int_type(CharT c)
        {
            return CHAR_TRAITS_NAMESPACE
                ::char_traits<CharT>::to_int_type(c);
        }

        static char_type to_char_type(int_type i)
        {
            return CHAR_TRAITS_NAMESPACE
                ::char_traits<CharT>::to_char_type(i);
        }
    };

    template <typename CharT>
    struct char_traits_helper
    {
        typedef CharT char_type;
        typedef CharT int_type;

        static CharT & to_int_type(CharT & c)
        {
            return c;
        }

        static CharT & to_char_type(CharT & c)
        {
            return c;
        }
    };

    template <>
    struct char_traits_helper<char>
        : char_type_char_traits_helper<char>
    {
    };

#if !defined(BOOST_NO_CWCTYPE)

    template <>
    struct char_traits_helper<wchar_t>
        : char_type_char_traits_helper<wchar_t>
    {
    };

#endif

    template <typename CharT>
    inline typename char_traits_helper<CharT>::int_type
    to_int_type(CharT c)
    {
        return char_traits_helper<CharT>::to_int_type(c);
    }

    template <typename CharT>
    inline CharT
    to_char_type(typename char_traits_helper<CharT>::int_type c)
    {
        return char_traits_helper<CharT>::to_char_type(c);
    }

    ///////////////////////////////////////////////////////////////////////
    //
    //  Convenience functions
    //
    ///////////////////////////////////////////////////////////////////////

    template <typename CharT>
    inline bool 
    isalnum_(CharT c)
    { 
        using namespace std; 
        return isalnum(to_int_type(c)) ? true : false; 
    }

    template <typename CharT>
    inline bool 
    isalpha_(CharT c)
    { 
        using namespace std; 
        return isalpha(to_int_type(c)) ? true : false; 
    }

    template <typename CharT>
    inline bool 
    iscntrl_(CharT c)
    { 
        using namespace std; 
        return iscntrl(to_int_type(c)) ? true : false; 
    }

    template <typename CharT>
    inline bool 
    isdigit_(CharT c)
    { 
        using namespace std; 
        return isdigit(to_int_type(c)) ? true : false; 
    }

    template <typename CharT>
    inline bool 
    isgraph_(CharT c)
    { 
        using namespace std; 
        return isgraph(to_int_type(c)) ? true : false; 
    }

    template <typename CharT>
    inline bool 
    islower_(CharT c)
    { 
        using namespace std; 
        return islower(to_int_type(c)) ? true : false; 
    }

    template <typename CharT>
    inline bool 
    isprint_(CharT c)
    { 
        using namespace std; 
        return isprint(to_int_type(c)) ? true : false; 
    }

    template <typename CharT>
    inline bool 
    ispunct_(CharT c)
    { 
        using namespace std; 
        return ispunct(to_int_type(c)) ? true : false; 
    }

    template <typename CharT>
    inline bool 
    isspace_(CharT c)
    { 
        using namespace std; 
        return isspace(to_int_type(c)) ? true : false; 
    }

    template <typename CharT>
    inline bool 
    isupper_(CharT c)
    { 
        using namespace std; 
        return isupper(to_int_type(c)) ? true : false;  
    }

    template <typename CharT>
    inline bool 
    isxdigit_(CharT c)
    { 
        using namespace std; 
        return isxdigit(to_int_type(c)) ? true : false;  
    }

    template <typename CharT>
    inline bool 
    isblank_(CharT c)
    { 
        return (c == ' ' || c == '\t'); 
    }
    
    template <typename CharT>
    inline CharT 
    tolower_(CharT c)
    { 
        using namespace std; 
        return to_char_type<CharT>(tolower(to_int_type(c))); 
    }

    template <typename CharT>
    inline CharT 
    toupper_(CharT c)
    { 
        using namespace std; 
        return to_char_type<CharT>(toupper(to_int_type(c))); 
    }

#if !defined(BOOST_NO_CWCTYPE)

    inline bool 
    isalnum_(wchar_t c)
    { 
        using namespace std; 
        return iswalnum(to_int_type(c)) ? true : false;  
    }

    inline bool 
    isalpha_(wchar_t c)
    { 
        using namespace std; 
        return iswalpha(to_int_type(c)) ? true : false;  
    }

    inline bool 
    iscntrl_(wchar_t c)
    { 
        using namespace std; 
        return iswcntrl(to_int_type(c)) ? true : false;  
    }

    inline bool 
    isdigit_(wchar_t c)
    { 
        using namespace std; 
        return iswdigit(to_int_type(c)) ? true : false;  
    }

    inline bool 
    isgraph_(wchar_t c)
    { 
        using namespace std; 
        return iswgraph(to_int_type(c)) ? true : false;  
    }

    inline bool 
    islower_(wchar_t c)
    { 
        using namespace std; 
        return iswlower(to_int_type(c)) ? true : false;  
    }

    inline bool 
    isprint_(wchar_t c)
    { 
        using namespace std; 
        return iswprint(to_int_type(c)) ? true : false;  
    }

    inline bool 
    ispunct_(wchar_t c)
    { 
        using namespace std; 
        return iswpunct(to_int_type(c)) ? true : false;  
    }

    inline bool 
    isspace_(wchar_t c)
    { 
        using namespace std; 
        return iswspace(to_int_type(c)) ? true : false;  
    }

    inline bool 
    isupper_(wchar_t c)
    { 
        using namespace std; 
        return iswupper(to_int_type(c)) ? true : false;  
    }

    inline bool 
    isxdigit_(wchar_t c)
    { 
        using namespace std; 
        return iswxdigit(to_int_type(c)) ? true : false;  
    }

    inline bool 
    isblank_(wchar_t c)
    { 
        return (c == L' ' || c == L'\t'); 
    } 

    inline wchar_t 
    tolower_(wchar_t c)
    { 
        using namespace std; 
        return to_char_type<wchar_t>(towlower(to_int_type(c))); 
    }

    inline wchar_t 
    toupper_(wchar_t c)
    { 
        using namespace std; 
        return to_char_type<wchar_t>(towupper(to_int_type(c))); 
    }

#endif // !defined(BOOST_NO_CWCTYPE)

} // namespace chr

#endif
