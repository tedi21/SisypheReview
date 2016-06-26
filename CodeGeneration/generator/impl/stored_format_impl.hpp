

namespace gen {

    template <typename DataT, bool EmbedByValue>
    template <typename GeneratorT>
    inline stored_format<DataT,EmbedByValue> & 
    stored_format<DataT,EmbedByValue>::operator=(GeneratorT const& g)
    {
        ptr.reset(new concrete_generator<GeneratorT, DataT>(g));
        return *this;
    }

    template <typename DataT, bool EmbedByValue>
    inline stored_format<DataT,EmbedByValue>& 
    stored_format<DataT,EmbedByValue>::operator=(stored_format const& f)
    {
        ptr = f.ptr;
        return *this;
    }

    template <typename DataT, bool EmbedByValue>
    inline stored_format<DataT,true>
    stored_format<DataT,EmbedByValue>::copy() const
    {
        return stored_format<DataT, true>(ptr);
    }
 
}
