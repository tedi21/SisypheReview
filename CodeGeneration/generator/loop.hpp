/**
 * @class loop
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  2.0
 * @brief 
 */

#ifndef GEN_LOOP_HPP
#define GEN_LOOP_HPP

#include "position.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //                                                             
    //  collection_expr class
    //
    ///////////////////////////////////////////////////////////////////////////

    /// collection_expr : facade definition for a collection
    template <class DerivedT>
    struct collection_expr
    {
        // base class
        typedef collection_expr<DerivedT>            self_t;
        typedef DerivedT                             embed_t;
        typedef DerivedT                             derived_t;
        typedef DerivedT                             enumerated_t;

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
    //  abstract_collection class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename RangeT, typename DataT>
    struct abstract_collection
    {
        DECLARE_CONTEXT(typename RangeT::context_t::parent_t)

        abstract_collection() {}
        virtual ~abstract_collection() {}

        virtual abstract_collection*
        do_enumerate_virtual(TYPE_CONTEXT(DataT) & c) const /*throw(std::bad_cast)*/ = 0;

        virtual typename RangeT::iterator_t
        do_begin_virtual() const = 0;

        virtual typename RangeT::iterator_t
        do_end_virtual() const = 0;

        virtual abstract_collection*
        clone() const = 0;
    };

    template <typename RangeT, typename DataT>
    inline abstract_collection<RangeT,DataT>*
    new_clone( const abstract_collection<RangeT,DataT>& a )
    {
        return a.clone();
    } 

    ///////////////////////////////////////////////////////////////////////
    //
    //  concrete_collection class
    //
    ///////////////////////////////////////////////////////////////////////

    template <typename CollectionT, typename RangeT, typename DataT>
    struct concrete_collection : abstract_collection<RangeT,DataT>
    {
        DECLARE_CONTEXT(typename RangeT::context_t::parent_t)
        typedef typename CollectionT::template declare_context<DataT>::context_t    required_context_t;

        typedef abstract_collection<RangeT,DataT> abstract_collection_t;

        concrete_collection(CollectionT const& l) 
        : collection(l)
        {}
        
        virtual ~concrete_collection() {}

        virtual abstract_collection_t*
        do_enumerate_virtual(TYPE_CONTEXT(DataT) & context) const /*throw(std::bad_cast)*/
        {
            abstract_collection_t* ret = NULL;
            try 
            {
                required_context_t& required_context = dynamic_cast<required_context_t&>(context);
                typename CollectionT::enumerated_t copy = collection.template enumerate<DataT>(required_context);
                ret = new concrete_collection<typename CollectionT::enumerated_t,RangeT,DataT>(copy);
            }
            catch (std::bad_cast &)
            {
                throw generator_exception<typename DataT::char_t>(context.str());
            }
            return ret;
        }

        virtual typename RangeT::iterator_t
        do_begin_virtual() const
        {
            return collection.begin();
        }

        virtual typename RangeT::iterator_t
        do_end_virtual() const
        {
            return collection.end();
        }

        virtual abstract_collection<RangeT,DataT>*
        clone() const
        {
            return new concrete_collection(collection);
        }

        typename CollectionT::embed_t collection;
    };

    ///////////////////////////////////////////////////////////////////////////
    //                       
    //  loop class
    //
    //      Handles expressions of the form:
    //
    //          a[b1, b2]
    //
    //      where a is a generator. The expression returns a composite
    //      generator that generate its subject from b1 to b2.
    //
    ///////////////////////////////////////////////////////////////////////////
    
    template <typename S, typename CollectionT>
    class loop
    : public binary<S, CollectionT, generator< loop<S,CollectionT> > >
    {
    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(CollectionT))

        typedef loop<S,CollectionT>             self_t;
        typedef unary_generator_category        generator_category_t;
        typedef binary<S, CollectionT, generator<self_t> > base_t;

    public:
        loop(S const& a, CollectionT const& b)
        : base_t(a,b) {}
    
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };
}

#include "impl/loop_impl.hpp"

#endif
