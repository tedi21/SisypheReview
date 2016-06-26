/**
 * @class marker
 * @date 01/12/2012
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_MARKER_HPP
#define GEN_MARKER_HPP

#include "position.hpp"
#include "actor.hpp"
#include "container.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  marker class
    //
    ///////////////////////////////////////////////////////////////////////////
    enum marker_cur_t { beg = 0, end };

    template <typename FunctorT, typename ContextT>
    class marker_factory;
    
    template <typename FunctorT, typename ContextT = no_context>
    class marker 
    : public actor_base<FunctorT,ContextT,
             marker_expr< marker<FunctorT,ContextT> > >
    {
    public:
        typedef marker<FunctorT,ContextT>                            self_t;
        typedef typename container_trait<FunctorT>::context_t        context_t;
        typedef range<context_t>                                     range_t;
        typedef marker_factory<FunctorT,ContextT>                    factory_t;
        typedef marker_expr<self_t>                                  base_t;
        typedef actor_base<FunctorT,ContextT,base_t>                 actor_base_t;
        typedef typename range_t::iterator_t                         iterator_t;
        typedef typename iterator_t::difference_type                 diff_t;
        typedef container<FunctorT,range_t>                          container_t;

        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(actor_base_t))

        marker()
        : m_base_cur(beg),
          m_offset(0)
        {}

        marker(FunctorT const& f, marker_cur_t cur, diff_t offset = 0)
        : m_container(new container_t(f)),
          m_base_cur(cur),
          m_offset(offset)
        {}
   
        template <typename DataT>
        void
        enumerate(TYPE_CONTEXT(DataT) & c) const;

        iterator_t reach() const;

        // operators
        self_t operator+(diff_t offset) const;

        self_t operator-(diff_t offset) const;
        
        template<class MarkerT2>
        friend inline MarkerT2 operator+(typename MarkerT2::diff_t offset, const MarkerT2& b);

        marker_cur_t get_cursor() const;

        diff_t       get_offset() const;

    private:
        friend class marker_factory<FunctorT,ContextT>;

        marker(boost::shared_ptr<container_t> const& c, marker_cur_t cur, diff_t offset)
        : m_container(c),
          m_base_cur(cur),
          m_offset(offset)
        {}

        boost::shared_ptr<container_t>  m_container;
        marker_cur_t                    m_base_cur;
        diff_t                          m_offset;
    };

    template<class MarkerT>
    inline MarkerT
    operator+(typename MarkerT::diff_t offset, const MarkerT& m);

    template <class T>
    inline marker<T>
    beg_g(const T & f);

    template <class T>
    inline marker<T>
    end_g(const T & f);

    template <class ContextT, class FunctorT>
    inline marker<FunctorT,ContextT>
    begT_g(const FunctorT & f);

    template <class ContextT, class FunctorT>
    inline marker<FunctorT,ContextT>
    endT_g(const FunctorT & f);

    template <typename FunctorT, typename ContextT = no_context>
    class marker_factory
    {
    private:
        typedef marker<FunctorT,ContextT>                       marker_t;
        typedef typename container_trait<FunctorT>::context_t   context_t;
        typedef range<context_t>                                range_t;
        typedef typename range_t::iterator_t                    iterator_t;
        typedef typename iterator_t::difference_type            diff_t;
        typedef container<FunctorT,range_t>                     container_t;

        boost::shared_ptr<container_t>  m_container;
        marker_cur_t                    m_base_cur;
        diff_t                          m_offset;

    public:
        explicit marker_factory(FunctorT const& f = FunctorT())
        : m_container(new container_t(f)),
          m_base_cur(beg),
          m_offset(0)
        {}

        marker_factory(marker_t const& m)
        {
            m_base_cur = m.m_base_cur;
            m_offset   = m.get_offset();
            m_container.reset(new container_t(*m.m_container));
        }

        marker_t make(marker_cur_t base_cur, diff_t offset = 0) const;

        marker_t make(diff_t offset = 0) const;
    };

}

#include "impl/marker_impl.hpp"

#endif
