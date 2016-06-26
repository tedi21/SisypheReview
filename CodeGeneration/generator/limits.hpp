/**
 * @class limits
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef GEN_LIMITS_HPP
#define GEN_LIMITS_HPP

#include "position.hpp"
#include "loop.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //                                                             
    //  limits class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <class MarkerT>
    class limits
    : public collection_expr< limits<MarkerT> >
    {
    public:
        typedef limits<MarkerT>                     self_t;
        typedef MarkerT                             marker_t;
        typedef typename marker_t::context_t        context_t;
        typedef typename marker_t::iterator_t       iterator_t;
        typedef limits<marker_t>                    enumerated_t;

        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(MarkerT))

        limits(marker_expr<marker_t> const& a, marker_expr<marker_t> const& b)
        : m_first(a.derived()), m_end(b.derived())
        {}

        limits(limits const& l)
        : m_first(l.m_first), m_end(l.m_end)
        {}

        limits& operator=(limits const& l);

        template <class DataT>
        enumerated_t
        enumerate(TYPE_CONTEXT(DataT) & context) const;

        iterator_t
        begin() const;

        iterator_t
        end() const;

    private:
        typename marker_t::embed_t m_first;
        typename marker_t::embed_t m_end;
    };

    template <class MarkerT>
    inline limits<MarkerT> 
    operator,( marker_expr<MarkerT> const& b1,
               marker_expr<MarkerT> const& b2);

    template <class MarkerT>
    inline limits<MarkerT>            
    operator,( marker_expr<MarkerT> const& b1, 
			   typename MarkerT::diff_t offset);

    template <class MarkerT>
    inline limits<MarkerT>            
    operator,( typename MarkerT::diff_t offset,
               marker_expr<MarkerT> const& b1);

}

#include "impl/limits_impl.hpp"

#endif
