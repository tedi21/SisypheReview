

namespace gen {

    template <typename A, typename B>
    template <typename DataT>
    inline void
    sentence<A,B>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        this->left().template generate<DataT>(context);
        context.append(' ');
        this->right().template generate<DataT>(context);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  sentence class implementation
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename A, typename B>
    inline sentence<A, B>
    operator<(generator<A> const& a, generator<B> const& b)
    {
        return sentence<A, B>(a.derived(), b.derived());
    }

    template <typename A>
    inline sentence<A, chlit<char> >
    operator<(generator<A> const& a, char b)
    {
        return sentence<A, chlit<char> >(a.derived(), b);
    }
    
    template <typename B>
    inline sentence<chlit<char>, B>
    operator<(char a, generator<B> const& b)
    {
        return sentence<chlit<char>, B>(a, b.derived());
    }
    
    template <typename A>
    inline sentence<A, strlit<char const*> >
    operator<(generator<A> const& a, char const* b)
    {
        return sentence<A, strlit<char const*> >(a.derived(), b);
    }
    
    template <typename B>
    inline sentence<strlit<char const*>, B>
    operator<(char const* a, generator<B> const& b)
    {
        return sentence<strlit<char const*>, B>(a, b.derived());
    }
    
    template <typename A>
    inline sentence<A, chlit<wchar_t> >
    operator<(generator<A> const& a, wchar_t b)
    {
        return sentence<A, chlit<wchar_t> >(a.derived(), b);
    }
    
    template <typename B>
    inline sentence<chlit<wchar_t>, B>
    operator<(wchar_t a, generator<B> const& b)
    {
        return sentence<chlit<wchar_t>, B>(a, b.derived());
    }
    
    template <typename A>
    inline sentence<A, strlit<wchar_t const*> >
    operator<(generator<A> const& a, wchar_t const* b)
    {
        return sentence<A, strlit<wchar_t const*> >(a.derived(), b);
    }
    
    template <typename B>
    inline sentence<strlit<wchar_t const*>, B>
    operator<(wchar_t const* a, generator<B> const& b)
    {
        return sentence<strlit<wchar_t const*>, B>(a, b.derived());
    }

}
