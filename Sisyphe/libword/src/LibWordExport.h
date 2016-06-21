#ifndef _LIBWORD_EXPORT_HPP_
#define _LIBWORD_EXPORT_HPP_

#ifdef HAS_LIBWORD_DLL
#    ifdef BUILD_LIBWORD_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBWORD_API __declspec(dllexport)
#               else
#            define LIBWORD_API
#      endif
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define LIBWORD_API __declspec(dllimport)
#               else
#            define LIBWORD_API
#      endif
#    endif
#else
#    define LIBWORD_API
#endif

#endif // _LIBWORD_EXPORT_HPP_
