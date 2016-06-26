

namespace gen {

    template <typename A, typename B>
    template <typename DataT>
    inline void
    sequence<A,B>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        this->left().generate<DataT>(context);
        this->right().generate<DataT>(context);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  sequence class implementation
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename A, typename B>
    inline sequence<A, B>
    operator<<(generator<A> const& a, generator<B> const& b)
    {
        return sequence<A, B>(a.derived(), b.derived());
    }
    
    template <typename A>
    inline sequence<A, chlit<char> >
    operator<<(generator<A> const& a, char b)
    {
        return sequence<A, chlit<char> >(a.derived(), b);
    }
    
    template <typename B>
    inline sequence<chlit<char>, B>
    operator<<(char a, generator<B> const& b)
    {
        return sequence<chlit<char>, B>(a, b.derived());
    }
    
    template <typename A>
    inline sequence<A, strlit<char const*> >
    operator<<(generator<A> const& a, char const* b)
    {
        return sequence<A, strlit<char const*> >(a.derived(), b);
    }
    
    template <typename B>
    inline sequence<strlit<char const*>, B>
    operator<<(char const* a, generator<B> const& b)
    {
        return sequence<strlit<char const*>, B>(a, b.derived());
    }
    
    template <typename A>
    inline sequence<A, chlit<wchar_t> >
    operator<<(generator<A> const& a, wchar_t b)
    {
        return sequence<A, chlit<wchar_t> >(a.derived(), b);
    }
    
    template <typename B>
    inline sequence<chlit<wchar_t>, B>
    operator<<(wchar_t a, generator<B> const& b)
    {
        return sequence<chlit<wchar_t>, B>(a, b.derived());
    }
    
    template <typename A>
    inline sequence<A, strlit<wchar_t const*> >
    operator<<(generator<A> const& a, wchar_t const* b)
    {
        return sequence<A, strlit<wchar_t const*> >(a.derived(), b);
    }
    
    template <typename B>
    inline sequence<strlit<wchar_t const*>, B>
    operator<<(wchar_t const* a, generator<B> const& b)
    {
        return sequence<strlit<wchar_t const*>, B>(a, b.derived());
    }

}
