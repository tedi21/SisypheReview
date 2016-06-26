/**
 * @class gstring
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief
 */

#ifndef GEN_GSTRING_HPP
#define GEN_GSTRING_HPP

#include "generator.hpp"
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/scoped_array.hpp>

#if defined(_MSC_VER)
#   pragma warning (disable : 4996)
#endif

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  char_generator class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename DerivedT>
    struct char_generator : public generator<DerivedT>
    {
        DECLARE_EMPTY_CONTEXT()
        typedef DerivedT self_t;

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  chlit class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT = char>
    struct chlit : public char_generator<chlit<CharT> >
    {
        chlit(CharT ch_)
        : ch(ch_) {}

        CharT get() const
        {
            return ch;
        }

        CharT   ch;
    };

    template <typename CharT>
    inline chlit<CharT>
    ch_g(CharT ch);

    // This should take care of ch_g("a") "bugs"
    template <typename CharT, std::size_t N>
    inline chlit<CharT>
    ch_g(CharT const (& str)[N]);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  strlit class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharIteratorT = char const*>
    struct strlit : public generator<strlit<CharIteratorT> >
    {
        DECLARE_EMPTY_CONTEXT()

        //char has to be unsigned, else implicit cast is signed (get FF for type superior of 1 byte)
        typedef
            typename boost::make_unsigned<
                typename boost::remove_pointer<CharIteratorT>::type
                                                                >::type char_t;
        typedef char_t *              char_iterator_t;
        typedef strlit<CharIteratorT> self_t;

        // iterators
        char_iterator_t first;
        char_iterator_t last;

        // constructors
        strlit(CharIteratorT first_, CharIteratorT last_)
        : first((char_iterator_t) first_),
          last((char_iterator_t) last_)
        {}

        strlit(CharIteratorT first_)
        : first((char_iterator_t) first_),
          last((char_iterator_t) chr::get_last(first_))
        {}

        strlit()
        : first(0),
          last(0)
        {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };

    // This should take care of string
    template <typename CharIteratorT>
    struct strlit< basic_string<CharIteratorT> > :
    public generator< strlit< basic_string<CharIteratorT> > >
    {
        DECLARE_EMPTY_CONTEXT()
        //char has to be unsigned, else implicit cast is signed (get FF for type superior of 1 byte)
        typedef typename boost::make_unsigned<CharIteratorT>::type  char_t;
        typedef char_t *    char_iterator_t;
        typedef strlit< basic_string<CharIteratorT> > self_t;

        // storage
        boost::scoped_array<char_t> ptr;
        // iterators
        char_iterator_t first;
        char_iterator_t last;

        // constructors
        strlit(basic_string<CharIteratorT> & str)
        : ptr(new char_t[str.length()+1])
        {
            first = (char_iterator_t) memcpy(ptr.get(),str.c_str(),sizeof(char_t)*(str.length()+1));
            last = ptr.get() + str.length();
        }

        strlit()
        : ptr(0),
          first(0),
          last(0)
        {}

        strlit(const strlit< basic_string<CharIteratorT> > & o)
        : ptr(new char_t[chr::get_len(o.ptr.get())+1])
        {
            first = (char_iterator_t) memcpy(ptr.get(),o.ptr.get(),sizeof(char_t)*(chr::get_len(o.ptr.get())+1));
            last = ptr.get() + chr::get_len(o.ptr.get());
        }

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };

    template <typename CharT>
    inline strlit<CharT const*>
    str_g(CharT const* str);

    template <typename CharT>
    inline strlit<CharT *>
    str_g(CharT * str);

    template <typename CharIteratorT>
    inline strlit<CharIteratorT>
    str_g(CharIteratorT first, CharIteratorT last);

    // This should take care of str_g('a') "bugs"
    template <typename CharT>
    inline chlit<CharT>
    str_g(CharT ch);

    // This should take care of string
    template <typename CharT>
    inline strlit< basic_string<CharT> >
    str_g(basic_string<CharT> str);

    template <typename CharT>
    inline strlit<CharT>
    substr_g(CharT const* str, int start, int len = -1);

    // Macro helps string manipulation
    #define STR_G(str) strlit<>(#str)

    ///////////////////////////////////////////////////////////////////////////
    //
    //  upper_ch class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT>
    struct upperch : public char_generator<upperch<CharT> >
    {
        upperch(CharT ch_): ch(ch_) {}

        CharT get() const
        {
            return chr::toupper_(ch);
        }

        typedef upperch self_t;
        CharT ch;
    };

    template <typename CharT>
    inline upperch<CharT>
    upper_str(CharT ch);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  upperlit class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharIteratorT = char const*>
    class upperlit : public generator<upperlit<CharIteratorT> >
    {
    public:
        DECLARE_EMPTY_CONTEXT()

        upperlit(CharIteratorT first, size_t start = 0, size_t length = string::npos)
        : seq(first), m_start(start), m_length(length) {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

    private:
        typedef upperlit<CharIteratorT> self_t;
        strlit<CharIteratorT> seq;
        size_t m_start;
        size_t m_length;
    };

    template <typename CharT>
    inline upperlit<CharT const*>
    upper_str(CharT const* str, size_t start = 0, size_t length = string::npos);

    template <typename CharT>
    inline upperlit<CharT *>
    upper_str(CharT * str, size_t start = 0, size_t length = string::npos);

    // This should take care of string
    template <typename CharT>
    inline upperlit< basic_string<CharT> >
    upper_str(basic_string<CharT> str, size_t start = 0, size_t length = string::npos);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  upper_generator class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename S>
    struct upper_generator
    : public unary<S, generator<upper_generator<S> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(S))

        typedef upper_generator<S>          self_t;
        typedef unary_generator_category    generator_category_t;
        typedef unary<S, generator<self_t> > base_t;

        upper_generator(S const& a, size_t start = 0, size_t length = string::npos)
        : base_t(a), m_start(start), m_length(length)
        {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

        size_t m_start;
        size_t m_length;
    };

    // This should take care of generator
    template <typename S>
    inline upper_generator<S>
    upper_g(generator<S> const& a, size_t start = 0, size_t length = string::npos);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  lower_ch class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT>
    struct lowerch : public char_generator<lowerch<CharT> >
    {
        lowerch(CharT ch_): ch(ch_) {}

        CharT get() const
        {
            return chr::tolower_(ch);
        }

        typedef lowerch self_t;
        CharT ch;
    };

    template <typename CharT>
    inline lowerch<CharT>
    lower_str(CharT ch);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  lowerlit class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharIteratorT = char const*>
    class lowerlit : public generator<lowerlit<CharIteratorT> >
    {
    public:
        DECLARE_EMPTY_CONTEXT()

        lowerlit(CharIteratorT first, size_t start = 0, size_t length = string::npos)
        : seq(first), m_start(start), m_length(length)
        {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

    private:
        typedef lowerlit<CharIteratorT> self_t;
        strlit<CharIteratorT> seq;
        size_t m_start;
        size_t m_length;
    };

    template <typename CharT>
    inline lowerlit<CharT const*>
    lower_str(CharT const* str, size_t start = 0, size_t length = string::npos);

    template <typename CharT>
    inline lowerlit<CharT *>
    lower_str(CharT * str, size_t start = 0, size_t length = string::npos);

    // This should take care of string
    template <typename CharT>
    inline lowerlit< basic_string<CharT> >
    lower_str(basic_string<CharT> str, size_t start = 0, size_t length = string::npos);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  lower_generator class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename S>
    struct lower_generator
    : public unary<S, generator<lower_generator<S> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(S))

        typedef lower_generator<S>          self_t;
        typedef unary_generator_category    generator_category_t;
        typedef unary<S, generator<self_t> > base_t;

        lower_generator(S const& a, size_t start = 0, size_t length = string::npos)
        : base_t(a), m_start(start), m_length(length)
        {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

        size_t m_start;
        size_t m_length;
    };

    // This should take care of generator
    template <typename S>
    inline lower_generator<S>
    lower_g(generator<S> const& a, size_t start = 0, size_t length = string::npos);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  line class
    //
    ///////////////////////////////////////////////////////////////////////////
    class line : public generator<line>
    {
    public:
        DECLARE_EMPTY_CONTEXT()

        line(size_t n = 1)
        : nb(n)
        {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

    private:
        size_t nb;
    };

    inline line
    line_g(size_t n);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  htab class
    //
    ///////////////////////////////////////////////////////////////////////////
    class htab : public generator<htab>
    {
    public:
        DECLARE_EMPTY_CONTEXT()


        htab(size_t n = 1)
        : nb(n)
        {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

    private:
        size_t nb;
    };

    inline htab
    htab_g(size_t n);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  space class
    //
    ///////////////////////////////////////////////////////////////////////////
    class space : public generator<space>
    {
    public:
        DECLARE_EMPTY_CONTEXT()


        space(size_t n = 1)
        : nb(n)
        {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

    private:
        size_t nb;
    };

    inline space
    space_g(size_t n);
}

#include "impl/gstring_impl.hpp"

#endif
