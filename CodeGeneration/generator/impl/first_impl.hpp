

namespace gen {
 
    template <typename S>
    template <typename DataT>
    inline void
    first<S>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        if (context.isFirstPosition()) 
        {
            this->subject().generate<DataT>(context);
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  first class implementation
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename S>
    inline first<S>
    operator+(generator<S> const& a)
    {
        return first<S>(a.derived());
    }

}
