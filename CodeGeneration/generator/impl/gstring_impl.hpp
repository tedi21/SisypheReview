#include <boost/lexical_cast.hpp>
    
namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  char_generator class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename DerivedT>
    template <typename DataT>
    inline void
    char_generator<DerivedT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        context.append(this->derived().get());
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  chlit class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT>
    inline chlit<CharT>
    ch_g(CharT ch)
    { 
        return chlit<CharT>(ch); 
    }

    // This should take care of ch_g("a") "bugs"
    template <typename CharT, std::size_t N>
    inline chlit<CharT>
    ch_g(CharT const (& str)[N])
    {
        //  ch_p's argument should be a single character or a null-terminated
        //  string with a single character
        BOOST_STATIC_ASSERT(N < 3);
        return chlit<CharT>(str[0]);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  strlit class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharIteratorT>
    template <typename DataT>
    inline void
    strlit<CharIteratorT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        typedef typename generator_string<typename DataT::char_t>::str_t    result_t;
        context.append(result_t(first, last));
    }

    template <typename CharT>
    inline strlit<CharT const*>
    str_g(CharT const* str)
    { 
        return strlit<CharT const*>(str); 
    }

    template <typename CharT>
    inline strlit<CharT *>
    str_g(CharT * str)
    { 
        return strlit<CharT *>(str); 
    }

    template <typename CharIteratorT>
    inline strlit<CharIteratorT>
    str_g(CharIteratorT first, CharIteratorT last)
    { 
        return strlit<CharIteratorT>(first, last); 
    }

    // This should take care of string
    template <typename CharIteratorT>
    template <typename DataT>
    inline void
    strlit< basic_string<CharIteratorT> >::generate(TYPE_CONTEXT(DataT) & context) const
    {
        typedef typename generator_string<typename DataT::char_t>::str_t    result_t;
        context.append(result_t(ptr.get(), last));
    }

    template <typename CharT>
    inline strlit< basic_string<CharT> >
    str_g(basic_string<CharT> str)
    {
        return strlit< basic_string<CharT> >(str);
    }

    // This should take care of str_g('a') "bugs"
    template <typename CharT>
    inline chlit<CharT>
    str_g(CharT ch)
    {
        return chlit<CharT>(ch);
    }

    template <typename CharT>
    inline strlit<CharT>
    substr_g(CharT const* str, int start, int len)
    {
        return str_g(str+start, str+len+1);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  upper class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharIteratorT>
    template <typename DataT>
    inline void
    upperlit<CharIteratorT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        typename strlit<CharIteratorT>::char_iterator_t i;    
        for (i = seq.first; i<seq.last; ++i)                
        {                                                    
            if (i >= seq.first+m_start && 
               (m_length == string::npos || i<seq.first+m_start+m_length))
            {                                                
                context.append(chr::toupper_(*i));            
            }                                                
            else context.append(*i);                        
        }
    }

    template <typename CharT>
    inline upperlit<CharT const*>
    upper_str(CharT const* str, size_t start, size_t length)
    { 
        return upperlit<CharT const*>(str, start, length); 
    }

    template <typename CharT>
    inline upperlit<CharT *>
    upper_str(CharT * str, size_t start, size_t length)
    { 
        return upperlit<CharT *>(str, start, length); 
    }

    // This should take care of string
    template <typename CharT>
    inline upperlit< basic_string<CharT> >
    upper_str(basic_string<CharT> str, size_t start, size_t length)
    { 
        return upperlit< basic_string<CharT> >(str, start, length); 
    }

    template <typename CharT>
    inline upperch<CharT>
    upper_str(CharT ch)
    { 
        return upperch<CharT>(ch); 
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  upper_generator class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename S>
    template <typename DataT>
    inline void
    upper_generator<S>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        size_t l = context.length();                        
        this->subject().template generate<DataT>(context);
        upper_str(context.subtract(l, -1, true), m_start, m_length).template generate<DataT>(context);
    }

    // This should take care of generator
    template <typename S>
    inline upper_generator<S>
    upper_g(generator<S> const& a, size_t start, size_t length)
    {
        return upper_generator<S>(a.derived(), start, length);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  lower class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharIteratorT>
    template <typename DataT>
    inline void
    lowerlit<CharIteratorT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        typename strlit<CharIteratorT>::char_iterator_t i;    
        for (i = seq.first; i<seq.last; ++i)                
        {                                                    
            if (i >= seq.first+m_start &&
               (m_length == string::npos || i<seq.first+m_start+m_length))
            {                                                
                context.append(chr::tolower_(*i));            
            }                                                
            else context.append(*i);                        
        }
    }

    template <typename CharT>
    inline lowerlit<CharT const*>
    lower_str(CharT const* str, size_t start, size_t length)
    { 
        return lowerlit<CharT const*>(str, start, length); 
    }

    template <typename CharT>
    inline lowerlit<CharT *>
    lower_str(CharT * str, size_t start, size_t length)
    { 
        return lowerlit<CharT *>(str, start, length); 
    }

    // This should take care of string
    template <typename CharT>
    inline lowerlit< basic_string<CharT> >
    lower_str(basic_string<CharT> str, size_t start, size_t length)
    { 
        return lowerlit< basic_string<CharT> >(str, start, length); 
    }

    template <typename CharT>
    inline lowerch<CharT>
    lower_str(CharT ch)
    { 
        return lowerch<CharT>(ch); 
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  lower_generator class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename S>
    template <typename DataT>
    inline void
    lower_generator<S>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        size_t l = context.length();                        
        this->subject().template generate<DataT>(context);
        lower_str(context.subtract(l, -1, true), m_start, m_length).template generate<DataT>(context);
    }

    // This should take care of generator
    template <typename S>
    inline lower_generator<S>
    lower_g(generator<S> const& a, size_t start, size_t length)
    {
        return lower_generator<S>(a.derived(), start, length);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  line generator
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename DataT>
    inline void
    line::generate(TYPE_CONTEXT(DataT) & context) const
    {
        for (size_t i=nb; i>0; i--)        
        {                                
            context.append('\r');        
            context.append('\n');        
        }
    }

    // This should take care of generator
    inline line
    line_g(size_t n)
    {
        return line(n);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  htab generator
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename DataT>
    inline void
    htab::generate(TYPE_CONTEXT(DataT) & context) const
    {
        for (size_t i=nb; i>0; i--)        
        {                                
            context.append('\t');        
        }
    }

    // This should take care of generator
    inline htab
    htab_g(size_t n)
    {
        return htab(n);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  space generator
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename DataT>
    inline void
    space::generate(TYPE_CONTEXT(DataT) & context) const
    {
        for (int i=nb; i>0; i--)        
        {                                
            context.append(' ');        
        }
    }

    // This should take care of generator
    inline space
    space_g(size_t n)
    {
        return space(n);
    }

}
