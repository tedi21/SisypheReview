#include "else_expr.hpp"

namespace gen {

    template <typename S, typename CondT>
    template <typename DataT>
    void
    if_generator<S,CondT>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        if (this->right().template evaluate<DataT>(context))
        {
            // save domain
            size_t firstSaved    = context.firstPosition(),
                   endSaved      = context.endPosition(),
                   sizeSaved     = context.size(),
                   positionSaved = context.position();    
            // domain information
            size_t first = firstSaved, end = firstSaved, size = 0;
            for (context.position(firstSaved); context.position()<endSaved; context.increment())
            {
                if (this->right().template evaluate<DataT>(context))
                {
                    size++;
                    end = context.position()+1;
                }
                else
                {
                    if (size == 0)
                    {
                        first++;
                    }
                }

            }
            context.defineDomain(first, end, size);
            context.position(positionSaved);
            this->left().template generate<DataT>(context);
            // restore domain
            context.defineDomain(firstSaved, endSaved, sizeSaved);
        }
        // set else condition
        else_expr::declare_context<DataT>::else_condition() = !this->right();
    }

    template <typename DerivedT>
    template <class T>
    inline if_generator< DerivedT, T >
    generator<DerivedT>::operator[](cond_expr<T> const& c) const
    {
        return if_generator< DerivedT, T >(derived(), c.derived());
    }

    template <typename DerivedT>
    inline if_generator< DerivedT, cst_expr >
    generator<DerivedT>::operator[](bool b) const
    {
        return if_generator< DerivedT, cst_expr >(derived(), cst_expr(b));
    }

};
