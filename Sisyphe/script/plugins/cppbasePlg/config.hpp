/* 
 * config.hpp
 *
 *
 * @date 01-12-2013
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <log4cpp/Category.hh>

// necessary for use log4cpp with boost
#undef int64_t

static const char* LOGNAME = "cppBase";

#define NAMESPACE_BEGIN(x) namespace x {
#define NAMESPACE_END }

#endif
