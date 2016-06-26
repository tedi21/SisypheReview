#ifndef ENDIANNESS_HPP
#define ENDIANNESS_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/detail/endian.hpp>

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// endianness.hpp

struct little_endian
{
    template <class T>
    static void set_bytes_order(char * result, T val)
    {
#ifdef BOOST_LITTLE_ENDIAN
        *((T*)(result)) = val;
#elif BOOST_BIG_ENDIAN
        size_t len = sizeof(T);
        for (size_t i = 0; i < len; i++) {
            result[len-1-i] = (unsigned char) (val >> (i*8));
        }
#else
#     error Unknown machine endianness detected.
#endif
    }

    template <class T>
    static T cast_ordering(const char * buf)
    {
        T result   = static_cast<T>(0);
#ifdef BOOST_LITTLE_ENDIAN
        result = *((T*)(buf));
#elif BOOST_BIG_ENDIAN
        size_t len = sizeof(T);
        for (size_t i = 0; i < len; i++) {
            result |= (static_cast<unsigned char>(buf[len-1-i]) << (i*8));
        }
#else
#     error Unknown machine endianness detected.
#endif
        return result;
    }
};

struct big_endian
{
    template <class T>
    static void set_bytes_order(char * result, T val)
    {
#ifdef BOOST_LITTLE_ENDIAN
        size_t len = sizeof(T);
        for (size_t i = 0; i < len; i++) {
            result[len-1-i] = (unsigned char) (val >> (i*8));
        }
#elif BOOST_BIG_ENDIAN
        *((T*)(result)) = val;
#else
#     error Unknown machine endianness detected.
#endif
    }

    template <class T>
    static T cast_ordering(const char * buf)
    {
        T result   = static_cast<T>(0);
#ifdef BOOST_LITTLE_ENDIAN
        size_t len = sizeof(T);
        for (size_t i = 0; i < len; i++) {
            result |= (static_cast<unsigned char>(buf[len-1-i]) << (i*8));
        }
#elif BOOST_BIG_ENDIAN
        result = *((T*)(buf));
#else
#     error Unknown machine endianness detected.
#endif
        return result;
    }
};

struct platform_dependent
{
    template <class T>
    static void set_bytes_order(char * result, T val)
    {
        *((T*)(result)) = val;
    }

    template <class T>
    static T cast_ordering(const char * buf)
    {
        T result = *((T*)(buf));
        return result;
    }
};

#endif