#ifndef _DB_EXPORT_H_
#define _DB_EXPORT_H_

#ifdef HAS_DB_DLL
#    ifdef BUILD_DB_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define DB_API __declspec(dllexport)
#               else
#            define DB_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define DB_API __declspec(dllimport)
#               else
#            define DB_API
#               endif 
#    endif
#else
#    define DB_API
#endif

#endif // _DB_EXPORT_H_
