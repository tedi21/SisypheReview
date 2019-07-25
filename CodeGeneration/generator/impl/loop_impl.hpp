
namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  loop class implementation
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename S, typename CollectionT>
    template <typename DataT>
    inline void
    loop<S,CollectionT>::generate(TYPE_CONTEXT(DataT) & context) const
    {       
        // Enumerates 
        typename CollectionT::enumerated_t copy = 
            this->right().template enumerate<DataT>(context);
        
        // generates
        typename CollectionT::context_t c(copy.begin(), copy.end(), context);                                                         
        for (; c.current() != copy.end(); c.increment())                    
        {                                                            
            this->left().template generate<DataT>(c);
        }
    }

    template <typename DerivedT>
    template <class T>
    inline loop< DerivedT, limits<T> >
    generator<DerivedT>::operator[](marker_expr<T> const& m) const
    {
        return loop<DerivedT, limits<T> >(derived(), (m.derived(),1));
    }

    template <typename DerivedT>
    template <class T>
    inline loop< DerivedT, T >
    generator<DerivedT>::operator[](collection_expr<T> const& l) const
    {
        return loop<DerivedT, T>(derived(), l.derived());
    }

}
