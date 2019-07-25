namespace gen {

    template <typename DerivedT>
    template <typename DataT>
    void
    report<DerivedT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        typedef typename DerivedT::template etat<DataT> etat_t;
        static etat_t etat(this->derived()); // only one instance
        etat.start().template generate<DataT>(context);
    }

}
