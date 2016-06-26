#ifndef _X_ENCODING_EXPORT_H_
#define _X_ENCODING_EXPORT_H_

#ifdef HAS_XENCODING_DLL
#    ifdef BUILD_XENCODING_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define XENCODING_API __declspec(dllexport)
#               else
#            define XENCODING_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define XENCODING_API __declspec(dllimport)
#               else
#            define XENCODING_API
#               endif 
#    endif
#else
#    define XENCODING_API 
#endif

#endif // _X_ENCODING_EXPORT_H_