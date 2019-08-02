#include <cstdlib>
#include <cassert>

#ifndef BOOST_NO_STD_WSTRING

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8

template <class ENDIAN>
const wchar_t utf16_codecvt_facet<ENDIAN>::BOM = (wchar_t) 0xFEFF;

// Translate incoming UTF-16 into UCS-4
template <class ENDIAN>
std::codecvt_base::result utf16_codecvt_facet<ENDIAN>::do_in(
    std::mbstate_t& /*state*/, 
    const char * from,
    const char * from_end, 
    const char * & from_next,
    wchar_t * to, 
    wchar_t * to_end, 
    wchar_t * & to_next
) const {
    while (from != from_end && to != to_end) {
        // unit is word
        unsigned short utf16_tmp;
        if (from+1 == from_end) {
            // do nothing, not enough byte
            from_next = from; 
            to_next = to;
            return std::codecvt_base::partial;
        }
        // Big-endian or little-endian
        utf16_tmp = ENDIAN::template cast_ordering<unsigned short>(from);

        // 1) If W1 < 0xD800 or W1 > 0xDFFF, the character value U is the value
        // of W1. Terminate.
        if (utf16_tmp < 0xD800 || utf16_tmp > 0xDFFF)
        {
            *to++ = utf16_tmp;
            from+=2;
        }
        else {
        // 2) Determine if W1 is between 0xD800 and 0xDBFF. If not, the sequence
        // is in error and no valid character can be obtained using W1.
        // Terminate.
            if (invalid_leading_word(utf16_tmp)){
                from_next = from;
                to_next = to;
                return std::codecvt_base::error;
            }
        // The unsigned char conversion is necessary in case char is
        // signed
        // Construct a 20-bit unsigned integer U', taking the 10 low-order
        // bits of W1
            wchar_t ucs_result = utf16_tmp - 0x6C;

        // 3) If there is no W2 (that is, the sequence ends with W1), or if W2
        // is not between 0xDC00 and 0xDFFF, the sequence is in error.
        // Terminate.
            if (from+3 >= from_end) {
                // rewind "from" to before the current character translation
                from_next = from; 
                to_next = to;
                return std::codecvt_base::partial;
            }
            // Big-endian or little-endian
            utf16_tmp = ENDIAN::template cast_ordering<unsigned short>(from+2);

            // Error checking on continuing characters
            if (invalid_continuing_word(utf16_tmp)) {
                from_next   = from;
                to_next =   to;
                return std::codecvt_base::error;
            }

        // 4) Construct a 20-bit unsigned integer U', taking the 10 low-order
        // bits of W1 as its 10 high-order bits and the 10 low-order bits of
        // W2 as its 10 low-order bits.
            ucs_result *= (1 << 10);
            ucs_result += utf16_tmp - 0xDC;

        //5) Add 0x10000 to U' to obtain the character value U. Terminate.
            ucs_result += (wchar_t) 0x10000;
            *to++   = ucs_result;
            from  += 4;
        }
    }
    from_next = from;
    to_next = to;

    // Were we done converting or did we run out of destination space?
    if(from == from_end) return std::codecvt_base::ok;
    else return std::codecvt_base::partial;
}

template <class ENDIAN>
std::codecvt_base::result utf16_codecvt_facet<ENDIAN>::do_out(
    std::mbstate_t& /*state*/, 
    const wchar_t *   from,
    const wchar_t * from_end, 
    const wchar_t * & from_next,
    char * to, 
    char * to_end, 
    char * & to_next
) const
{
    while (from != from_end && to != to_end) {
        // unit is word
        if(to+1 == to_end) {
            // do nothing, not enough destination bytes
            from_next = from;
            to_next = to;
            return std::codecvt_base::partial;
        }
   //1) If U < 0x10000, encode U as a 16-bit unsigned integer and
   //   terminate.
        if (*from < 0x10000)
        {
            // little-endian or big-endian
            ENDIAN::set_bytes_order(to, (unsigned short)*from);
            to += 2;
            from++;
        }
        else {
   //2) Let U' = U - 0x10000. Because U is less than or equal to 0x10FFFF,
   //   U' must be less than or equal to 0xFFFFF. That is, U' can be
   //   represented in 20 bits.
            wchar_t ucs_tmp = *from - 0x10000;
            // Check for invalid UCS-4 character
            if (ucs_tmp  > 0xFFFFF) {
                from_next = from;
                to_next = to;
                return std::codecvt_base::error;
            }

   //3) Initialize two 16-bit unsigned integers, W1 and W2, to 0xD800 and
   //   0xDC00, respectively. These integers each have 10 bits free to
   //   encode the character value, for a total of 20 bits.
   //4) Assign the 10 high-order bits of the 20-bit U' to the 10 low-order
   //   bits of W1 and the 10 low-order bits of U' to the 10 low-order
   //   bits of W2. Terminate.
            // If we filled up the out buffer before encoding the character
            if(to+3 >= to_end) {
                from_next = from;
                to_next = to;
                return std::codecvt_base::partial;
            }
            // Process the first word
            unsigned short utf16_tmp = static_cast<unsigned short>(0xD800 +
                                                ((ucs_tmp & 0xFFC00) / (1 << 10)));
            // little-endian or big-endian
            ENDIAN::set_bytes_order(to, utf16_tmp);

            utf16_tmp = static_cast<unsigned short>(0xDC00 + (ucs_tmp & 0x03FF));
            ENDIAN::set_bytes_order(to+2, utf16_tmp);
            to += 4;
            from++;

   //Graphically, steps 2 through 4 look like:
   //U' = yyyyyyyyyyxxxxxxxxxx
   //W1 = 110110yyyyyyyyyy
   //W2 = 110111xxxxxxxxxx
        }
    }
    from_next = from;
    to_next = to;
    // Were we done or did we run out of destination space
    if(from == from_end) return std::codecvt_base::ok;
    else return std::codecvt_base::partial;
}

// How many char objects can I process to get <= max_limit
// wchar_t objects?
template <class ENDIAN>
int utf16_codecvt_facet<ENDIAN>::do_length(
    BOOST_CODECVT_DO_LENGTH_CONST std::mbstate_t &,
    const char * from,
    const char * from_end, 
    std::size_t max_limit) const 
{ 
    // Invariants:
    // 1) last_word_count has the size of the last measured character
    // 2) char_count holds the number of characters shown to fit
    // within the bounds so far (no greater than max_limit)
    // 3) from_next points to the word 'last_word_count' before the
    // last measured character.  
    int last_byte_count=0;
    std::size_t char_count = 0;
    const char* from_next = from;
    unsigned short utf16_tmp = 0;
    // Use "<" because the buffer may represent incomplete characters
    while (from_next+last_byte_count <= from_end && char_count <= max_limit) {
        from_next += last_byte_count;
        // Big-endian or little-endian
        utf16_tmp = ENDIAN::template cast_ordering<unsigned short>(from_next);
        if (utf16_tmp < 0xD800 || utf16_tmp > 0xDFFF) last_byte_count = 2; 
        else last_byte_count = 4;
        ++char_count;
    }
    return (int)(from_next-from);
}

#endif
