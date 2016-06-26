/**
 * @class current
 * @date 03/11/2012
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_CURRENT_HPP
#define GEN_CURRENT_HPP

#include "marker.hpp"
#include "glist.hpp"

namespace gen {

    template <class ContextT>
    struct current_range 
    {    
        range<ContextT> operator()
            (ContextT const& c);
    };
	
    template <class ContextT>
    struct first_range 
    {    
        range<ContextT> operator()
            (ContextT const& c);
    };
	
    template <class ContextT>
    struct last_range 
    {    
        range<ContextT> operator()
            (ContextT const& c);
    };
    
    
    //////////////////////////////////
    template <class ContextT>
    inline marker<current_range<ContextT>,ContextT>
    current_g();
	
    template <class ContextT>
    inline marker<first_range<ContextT>,ContextT>
    first_g();
	
    template <class ContextT>
    inline marker<last_range<ContextT>,ContextT>
    last_g();

    template <class ContextT>
    inline glist<first_range<ContextT>,ContextT>
    leading_g();

    template <class ContextT>
    inline glist<current_range<ContextT>,ContextT>
    trailing_g();
}

#include "impl/current_impl.hpp"

#endif
