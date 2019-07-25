
namespace gen {
 
    template <typename S>
    template <typename DataT>
    inline void
    not_last<S>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        if (!context.isLastPosition()) 
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
    inline not_last<S> 
    operator~(last<S> const& a)
    {
        // get sub generator, cast to S
        return not_last<S>(a.subject().derived());
    }

}
