/**
 * @class glist
 * @date 28/12/2012
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_GLIST_HPP
#define GEN_GLIST_HPP

#include "loop.hpp"
#include "actor.hpp"
#include "container.hpp"

namespace gen {


    ///////////////////////////////////////////////////////////////////////////
    //
    //  glist class
    //
    ///////////////////////////////////////////////////////////////////////////   
    template <typename FunctorT, typename ContextT = no_context>
    class glist 
    : public actor_base<FunctorT,ContextT,
             collection_expr< glist<FunctorT,ContextT> > >
    {
    public:
        typedef typename container_trait<FunctorT>::context_t        context_t;
        typedef range<context_t>                                     range_t;
        typedef glist<FunctorT,ContextT>                             self_t;
        typedef collection_expr<self_t>                              collection_t;  
        typedef actor_base<FunctorT,ContextT,collection_t>           actor_base_t;
        typedef typename range_t::iterator_t                         iterator_t;
        typedef container<FunctorT,range_t>                          container_t;
        typedef typename collection_t::enumerated_t                  enumerated_t;  

    private:
        container_t m_container;

    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(actor_base_t))

        glist(FunctorT const& f)
        : m_container(f)
        {}
   
        template <typename DataT>
        enumerated_t
        enumerate(TYPE_CONTEXT(DataT) & c) const;

        iterator_t
        begin() const;

        iterator_t
        end() const;

    };

    template <class T>
    inline glist<T>
    list_g(const T & f);

    template <class ContextT, class FunctorT>
    inline glist<FunctorT,ContextT>
    listT_g(const FunctorT & f);

}

#include "impl/glist_impl.hpp"

#endif
