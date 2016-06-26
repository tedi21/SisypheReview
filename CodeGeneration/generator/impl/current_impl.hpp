namespace gen {

    template <class ContextT> 
    range<ContextT> current_range<ContextT>::operator()
            (ContextT const& c)
    {
        return gen::range<ContextT>(c.current(), c.domain().end());
    }
	
    template <class ContextT> 
    range<ContextT> first_range<ContextT>::operator()
            (ContextT const& c)
    {
        return gen::range<ContextT>(c.domain().first(), c.current()+1);
    }
	
    template <class ContextT> 
    range<ContextT> last_range<ContextT>::operator()
            (ContextT const& c)
    {
        return gen::range<ContextT>(c.domain().end()-1, c.domain().end());
    }

    template <class ContextT>
    inline marker<current_range<ContextT>,ContextT> 
    current_g()
    {
        return begT_g<ContextT>(current_range<ContextT>());
    }
	
    template <class ContextT>
    inline marker<first_range<ContextT>,ContextT> 
    first_g()
    {
        return begT_g<ContextT>(first_range<ContextT>());
    }
	
    template <class ContextT>
    inline marker<last_range<ContextT>,ContextT> 
    last_g()
    {
        return begT_g<ContextT>(last_range<ContextT>());
    }

    template <class ContextT>
    inline glist<first_range<ContextT>,ContextT>
    leading_g()
    {
        return listT_g<ContextT>(first_range<ContextT>());
    }

    template <class ContextT>
    inline glist<current_range<ContextT>,ContextT>
    trailing_g()
    {
        return listT_g<ContextT>(current_range<ContextT>());
    }
}