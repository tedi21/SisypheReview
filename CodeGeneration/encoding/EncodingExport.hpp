#ifndef _ENCODING_EXPORT_H_
#define _ENCODING_EXPORT_H_

#ifdef HAS_ENCODING_DLL
#    ifdef BUILD_ENCODING_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define ENCODING_API __declspec(dllexport)
#               else
#            define ENCODING_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define ENCODING_API __declspec(dllimport)
#               else
#            define ENCODING_API
#               endif 
#    endif
#else
#    define ENCODING_API 
#endif

#endif // _ENCODING_EXPORT_H_