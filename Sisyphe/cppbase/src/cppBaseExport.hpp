/* 
 * cppBaseExport.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPBASE_EXPORT_HPP_
#define _CPPBASE_EXPORT_HPP_

#ifdef HAS_CPPBASE_DLL
#    define HAS_DB_DLL
#    ifdef BUILD_CPPBASE_DLL
#        define BUILD_DB_DLL
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define CPPBASE_API __declspec(dllexport)
#               else
#            define CPPBASE_API
#      endif
#    else
#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)
#            define CPPBASE_API __declspec(dllimport)
#               else
#            define CPPBASE_API
#      endif
#    endif
#else
#    define CPPBASE_API
#endif

#endif
