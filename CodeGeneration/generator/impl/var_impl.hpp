

namespace gen {

    template <typename DataT>
    void
    var::generate(TYPE_CONTEXT(DataT) & context) const
    {
        int level = generator_args<DataT>::level;
        size_t n = generator_args<DataT>::args[level].size()-1;
        if (n >= pos)
        {
            generator_args<DataT>::level--;
            generator_args<DataT>::args[level][n-pos].template generate<DataT>(context);
            generator_args<DataT>::level++;
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  var class implementation
    //
    ///////////////////////////////////////////////////////////////////////////
    inline var
    $(size_t n)
    {
        return var(n);
    }

}
