/**
 * @class count
 * @date 20/08/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief
 */

#ifndef COUNT_HPP
#define COUNT_HPP

#include "if_expr.hpp"

namespace gen {

    struct eq_g
    {
        bool
        operator()(int value1, int value2) const
        {
            return value1==value2;
        }
    };

    struct neq_g
    {
        bool
        operator()(int value1, int value2) const
        {
            return value1!=value2;
        }
    };

    struct lt_g
    {
        bool
        operator()(int value1, int value2) const
        {
            return value1<value2;
        }
    };

    struct gt_g
    {
        bool
        operator()(int value1, int value2) const
        {
            return value1>value2;
        }
    };

    struct leq_g
    {
        bool
        operator()(int value1, int value2) const
        {
            return value1<=value2;
        }
    };

    struct geq_g
    {
        bool
        operator()(int value1, int value2) const
        {
            return value1>=value2;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  count class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <class CollectionT, class OperatorT = eq_g>
    class count
    : public cond_expr< count<CollectionT,OperatorT> >
    {
    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(CollectionT))

        count(size_t value,
              collection_expr<CollectionT> const& collection,
              OperatorT const& op = eq_g())
        : m_value(value), m_op(op), m_collection(collection.derived())
        {}

        template <typename DataT>
        bool
        evaluate(TYPE_CONTEXT(DataT) & c) const;

    private:
        size_t        m_value;
        OperatorT     m_op;
        typename CollectionT::embed_t m_collection;
    };

    template <typename CollectionT, typename OperatorT>
    inline count<CollectionT, OperatorT>
    has_g(size_t value, 
          collection_expr<CollectionT> const& collection, 
          OperatorT const& op);

}

#include "impl/count_impl.hpp"

#endif

