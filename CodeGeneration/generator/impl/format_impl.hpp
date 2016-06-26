

namespace gen {

    template <typename DataT, template <typename,typename> class PolicyT>
    template <typename GeneratorT>
    inline format<DataT, PolicyT> & 
    format<DataT, PolicyT>::operator=(GeneratorT const& g)
    {
        ptr.reset(new concrete_generator<GeneratorT, DataT>(g));
        return *this;
    }

    template <typename DataT, template <typename,typename> class PolicyT>
    inline format<DataT, PolicyT>& 
    format<DataT, PolicyT>::operator=(format const& f)
    {
        ptr.reset(new concrete_generator<format, DataT>(f));
        return *this;
    }

    template <typename DataT, template <typename,typename> class PolicyT>
    inline format<DataT, PolicyT>
    format<DataT, PolicyT>::copy() const
    {
        return self_t(ptr.get() ? ptr->clone() : 0);
    }
 
    template <
        typename DerivedT,       // derived class
        typename EmbedT,         // how derived class is embedded
        typename DataT
    >
    template <class>
    inline void
    format_base<DerivedT,EmbedT,DataT>::generate(TYPE_CONTEXT(DataT) & context) const
    {     
        DerivedT const* derived_this = static_cast<DerivedT const*>(this);
        if (format_base_access::get(*derived_this))                    
        {                                                            
            format_base_access::get(*derived_this)                    
                    ->do_generate_virtual(context);                    
        }                                                            
    }

    template <class BaseT, class DataT>
    template <class>
    inline void 
    generate_policy<BaseT,DataT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        BaseT::template generate<DataT>(context);
    }
    
    template <class BaseT, class DataT>
    template <class>
    inline void 
    const_policy<BaseT,DataT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        static std::map<size_t,result_t> results;
        std::size_t seed = hash_value(tag);
        iterator_t i = results.find(seed);
        if (i == results.end())    
        {
            size_t len = context.length();
            BaseT::template generate<DataT>(context);
            results.insert(make_pair(seed, context.subtract(len)));
        }
        else
        {
            context.append(i->second);
        }
    }
    
    template <class BaseT, class DataT>
    template <class>
    inline void 
    memo_policy<BaseT,DataT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        static std::map<size_t,result_t> results;
        vector<size_t> v = context.positions();
        std::size_t seed = hash_value(tag);    
        std::size_t hash = boost::hash_range(v.begin(), v.end());
        boost::hash_combine(seed, hash);
        boost::hash_combine(seed, context.tag());
        iterator_t i = results.find(seed);                                   
        if (i == results.end())                                         
        {                                                            
            size_t len = context.length();                            
            BaseT::template generate<DataT>(context);                                            
            results.insert(make_pair(seed, context.subtract(len)));    
        }                                                            
        else                                                        
        {                                                            
            context.append(i->second);                                
        }
    }

}
