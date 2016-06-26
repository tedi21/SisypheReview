#ifndef _UTF16LE_CODECVT_H_
#define _UTF16LE_CODECVT_H_

#include "utf16_codecvt.hpp"
#include "endianness.hpp"

typedef utf16_codecvt_facet<little_endian> utf16LE_codecvt_facet;

#endif // _UTF16LE_CODECVT_H_