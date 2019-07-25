
namespace gen {
 
    template <typename S>
    template <typename DataT>
    inline void
    not_first<S>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        if (!context.isFirstPosition()) 
        {
            this->subject().template generate<DataT>(context);
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  first class implementation
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename S>
    inline not_first<S> 
    operator~(first<S> const& a)
    {
        // get sub generator, cast to S
        return not_first<S>(a.subject().derived());
    }

}
