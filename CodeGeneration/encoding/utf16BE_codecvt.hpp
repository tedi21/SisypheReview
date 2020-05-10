#ifndef _UTF16BE_CODECVT_H_
#define _UTF16BE_CODECVT_H_

#include "utf16_codecvt.hpp"
#include "endianness.hpp"

typedef utf16_codecvt_facet<struct big_endian> utf16BE_codecvt_facet;

#endif // _UTF16BE_CODECVT_H_
