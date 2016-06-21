/*
 * config.hpp
 *
 *
 * @date 24-11-2013
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <log4cpp/Category.hh>

// necessary for use log4cpp with boost
#undef int64_t

static const char* LOGNAME = "libWord";

// Avoid putting "libword::" in front of everything in Doxygen output
#ifdef LIBWORD_DOXYGEN_PROCESSING
#    define libword
#    define NAMESPACE_BEGIN(x)
#    define NAMESPACE_END
#else
#    define NAMESPACE_BEGIN(x) namespace x {
#    define NAMESPACE_END }
#endif

#endif // _CONFIG_HPP_

