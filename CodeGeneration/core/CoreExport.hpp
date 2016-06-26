#ifndef _CORE_EXPORT_H_
#define _CORE_EXPORT_H_

#ifdef HAS_CORE_DLL
#    define HAS_FACTORY_DLL
#    ifdef BUILD_CORE_DLL
#        define BUILD_FACTORY_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define CORE_API __declspec(dllexport)
#               else
#            define CORE_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define CORE_API __declspec(dllimport)
#               else
#            define CORE_API
#               endif 
#    endif
#else
#    define CORE_API 
#endif

#endif // _CORE_EXPORT_H_