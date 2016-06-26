#ifndef _PACK_EXPORT_H_
#define _PACK_EXPORT_H_

#ifdef HAS_PACK_DLL
#    define HAS_FACTORY_DLL
#    ifdef BUILD_PACK_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACK_API __declspec(dllexport)
#               else
#            define PACK_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define PACK_API __declspec(dllimport)
#               else
#            define PACK_API
#               endif 
#    endif
#else
#    define PACK_API 
#endif

#endif // _PACK_EXPORT_H_
