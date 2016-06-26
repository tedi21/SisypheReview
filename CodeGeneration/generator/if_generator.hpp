/**
 * @class if_generator
 * @date 10/04/2008
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef IF_GENERATOR_HPP
#define IF_GENERATOR_HPP

#include "generator.hpp"
#include "primitives.hpp"
#include <map>

using namespace std;

namespace gen {

    template <class CompositionT>
    class neg_expr;
    template <class CompositionT1, class CompositionT2>
    class and_expr;
    template <class CompositionT1, class CompositionT2>
    class or_expr;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  cond_expr class
    //
    //      Handles expressions of the form:
    //
    //          a[!c && (d || f)]
    //
    //      where c, d and f are conditional expressions. 
    //
    ///////////////////////////////////////////////////////////////////////////

    template <class DerivedT>
    struct cond_expr
    {

        typedef cond_expr<DerivedT> self_t;
        typedef DerivedT            derived_t;
        typedef DerivedT            embed_t;

        cond_expr()
        {}

        DerivedT& derived()
        {
            return *static_cast<DerivedT*>(this);
        }

        DerivedT const& derived() const
        {
            return *static_cast<DerivedT const*>(this);
        }

        neg_expr< DerivedT >
        operator!() const
        {
            return neg_expr< DerivedT >(*this);
        }

        template <class DerivedT2>
        and_expr< DerivedT, DerivedT2 >
        operator&&(const cond_expr<DerivedT2> & other) const
        {
            return and_expr< DerivedT, DerivedT2 >(*this, other);
        }

        template <class DerivedT2>
        or_expr< DerivedT, DerivedT2 >
        operator||(const cond_expr<DerivedT2> & other) const
        {
            return or_expr< DerivedT, DerivedT2 >(*this, other);
        }

        and_expr< DerivedT, cst_expr >
        operator&&(bool value) const
        {
            return and_expr< DerivedT, cst_expr >(*this, cst_expr(value));
        }

        or_expr< DerivedT, cst_expr >
        operator||(bool value) const
        {
            return or_expr< DerivedT, cst_expr >(*this, cst_expr(value));
        }

        
        // to be implemented by derived class
        //template <typename IteratorT>
        //bool
        //evaluate(IteratorT const& i) const;

    };

    ///////////////////////////////////////////////////////////////////////
    //
    //  abstract_condition class
    //
    ///////////////////////////////////////////////////////////////////////
    template <typename DataT>
    struct abstract_condition
    {
        DECLARE_EMPTY_CONTEXT()

        abstract_condition() {}
        virtual ~abstract_condition() {}

        virtual bool
        do_evaluate_virtual(TYPE_CONTEXT(DataT) & c) const /*throw(std::bad_cast)*/ = 0;

        virtual abstract_condition*
        clone() const = 0;
    };
    
    template <typename DataT>
    inline abstract_condition<DataT>*
    new_clone( const abstract_condition<DataT>& a )
    {
        return a.clone();
    }    

    ///////////////////////////////////////////////////////////////////////
    //
    //  concrete_condition class
    //
    ///////////////////////////////////////////////////////////////////////
    template <typename CondT, typename DataT>
    struct concrete_condition : abstract_condition<DataT>
    {
        DECLARE_EMPTY_CONTEXT()
        
        typedef typename CondT::template declare_context<DataT>::context_t    required_context_t;

        concrete_condition(CondT const& c) : cond(c) {}
        virtual ~concrete_condition() {}

        virtual bool
        do_evaluate_virtual(TYPE_CONTEXT(DataT) & c) const /*throw(std::bad_cast)*/
        {
            bool valid;
            try 
            {
                required_context_t & required_context = dynamic_cast<required_context_t &>(c);
                valid = cond.template evaluate<DataT>(required_context);
            }
            catch (std::bad_cast &)
            {
                throw generator_exception<typename DataT::char_t>(c.str());
            }
            return valid;
        }

        virtual abstract_condition<DataT>*
        clone() const
        {
            return new concrete_condition(cond);
        }

        typename CondT::embed_t cond;
    };

    ///////////////////////////////////////////////////////////////////////////
    //                       
    //  if_generator class
    //
    //      Handles expressions of the form:
    //
    //          a[c]
    //
    //      where a is a generator. The expression returns a composite
    //      generator that generate its subject from c.
    //
    ///////////////////////////////////////////////////////////////////////////
    
    template <typename S, typename CondT>
    struct if_generator
    : public binary<S, CondT, generator< if_generator<S,CondT> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT2(S, CondT))

        typedef if_generator<S,CondT>            self_t;
        typedef unary_generator_category         generator_category_t;
        typedef binary<S, CondT, generator<self_t> > base_t;

        if_generator(S const& a, CondT const& c)
        : base_t(a,c)
        {}
    
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };

}

#include "impl/if_generator_impl.hpp"

#endif
