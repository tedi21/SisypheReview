/**
 * @class position
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef GEN_POSITION_HPP
#define GEN_POSITION_HPP

#include "generator.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  marker_expr class
    //
    //      Handles expressions of the form:
    //
    //          a[b1, b2]
    //
    //      where a is a generator. The expression returns a composite
    //      generator that generate its subject from b1 to b2. b1 and b2
    //        are bounds.
    //
    ///////////////////////////////////////////////////////////////////////////

    // marker_expr : facade definition for a limit
    template <class DerivedT>
    struct marker_expr
    {
    public:
        // base class
        typedef marker_expr<DerivedT>           self_t;
        typedef DerivedT                        embed_t;
        typedef DerivedT                        derived_t;

        DerivedT& derived()
        {
            return *static_cast<DerivedT*>(this);
        }

        DerivedT const& derived() const
        {
            return *static_cast<DerivedT const*>(this);
        }
    };


    ///////////////////////////////////////////////////////////////////////////
    //
    //  range class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename ContextT>
    class range 
    {
    public :
        typedef range<ContextT>         range_t;
        typedef ContextT                context_t;
        typedef typename context_t::iterator_t iterator_t;

    public :
        range()
        {}

        range(iterator_t const& first, iterator_t const& end)
        :m_first(first), m_end(end)
        {}

        iterator_t const& begin() const
        {
            return m_first;
        }

        iterator_t const& end() const
        {
            return m_end;
        }

    private:
        iterator_t m_first;
        iterator_t m_end;
    };
}

#include "impl/position_impl.hpp"

#endif

