

namespace gen {
 
    template <typename S>
    template <typename DataT>
    inline void
    last<S>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        if (context.isLastPosition()) 
        {
            this->subject().template generate<DataT>(context);
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  last class implementation
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename S>
    inline last<S>
    operator-(generator<S> const& a)
    {
        return last<S>(a.derived());
    }

}
