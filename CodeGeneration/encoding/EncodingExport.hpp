#ifndef _ENCODING_EXPORT_H_
#define _ENCODING_EXPORT_H_

#ifdef HAS_ENCODING_DLL
#    ifdef BUILD_ENCODING_DLL
#        if defined(_WIN32) || defined(__CYGWIN__)
#           ifdef __GNUC__
#               define ENCODING_API __attribute__ ((visibility ("default")))
#           else
#               define ENCODING_API __declspec(dllexport)
#           endif
#        else
#            if __GNUC__ >= 4
#                define ENCODING_API __attribute__ ((visibility ("default")))
#            else
#                define ENCODING_API
#            endif
#        endif
#    else
#        if defined(_WIN32) || defined(__CYGWIN__)
#           ifdef __GNUC__
#               define ENCODING_API __attribute__ ((visibility ("default")))
#           else
#               define ENCODING_API __declspec(dllimport)
#           endif
#        else
#            if __GNUC__ >= 4
#                define ENCODING_API __attribute__ ((visibility ("default")))
#            else
#                define ENCODING_API
#            endif
#        endif
#    endif
#else
#    define ENCODING_API
#endif

#endif // _ENCODING_EXPORT_H_
