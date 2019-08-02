#ifndef _FACTORY_EXPORT_H_
#define _FACTORY_EXPORT_H_

#ifdef HAS_FACTORY_DLL
#    ifdef BUILD_FACTORY_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define FACTORY_API __declspec(dllexport)
#               else
#            define FACTORY_API
#               endif 
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define FACTORY_API __declspec(dllimport)
#               else
#            define FACTORY_API
#               endif 
#    endif
#else
#    define FACTORY_API 
#endif

#endif // _FACTORY_EXPORT_H_
