/**
 * @class collection
 * @date 27/12/2012
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief
 */

#ifndef GEN_COLLECTION_HPP
#define GEN_COLLECTION_HPP

#include "loop.hpp"
#include <boost/scoped_ptr.hpp>

namespace gen {

    template <
        typename DerivedT       // derived class
      , typename EmbedT         // how derived class is embedded
      , typename ContextT
    >
    class collection_base; // forward declaration

    template <typename ContextT>
    class enumerated_collection;

    template <typename ContextT>
    class collection
    : public collection_base<
            collection<ContextT>
          , collection<ContextT> const&
          , ContextT>
    {
    public:
        typedef collection<ContextT>     self_t;
        typedef collection_base<
            self_t
          , self_t const&
          , ContextT>                    base_t;
        typedef ContextT                 context_t;
        typedef typename context_t::char_t char_t;
        typedef generator_type<char_t>   data_t;
        typedef range<context_t>         range_t; 

        typedef abstract_collection<range_t,data_t> abstract_collection_t;

    public:
        collection() 
        : ptr() {}

        ~collection() {}

        collection(collection const& l)
        : ptr(new concrete_collection<collection,range_t,data_t>(l)) {}

        template <typename CollectionT>
        collection(CollectionT const& l)
        : ptr(new concrete_collection<CollectionT,range_t,data_t>(l)) {}

        template <typename CollectionT>
        collection& operator=(CollectionT const& l);

        collection& operator=(collection const& f);

        self_t copy() const;

        operator enumerated_collection<context_t>() const;

    private:
        friend class collection_access;

        abstract_collection_t*
        get() const
        {
            return ptr.get();
        }

        collection(abstract_collection_t * p)
        : ptr(p) 
        {}

        boost::shared_ptr<abstract_collection_t> ptr;
    };

    template <typename ContextT>
    class enumerated_collection
    : public collection_base<
            enumerated_collection<ContextT>
          , enumerated_collection<ContextT>
          , ContextT>
    {
    public:
        typedef enumerated_collection<ContextT>     self_t;
        typedef collection_base<
            self_t
          , self_t
          , ContextT>                               base_t;
        typedef ContextT                            context_t;
        typedef typename context_t::char_t          char_t;
        typedef generator_type<char_t>              data_t;
        typedef range<context_t>                    range_t; 

        typedef abstract_collection<range_t,data_t> abstract_collection_t;

    public:
        enumerated_collection(boost::shared_ptr<abstract_collection_t> p, const char* nm)
        {
            base_t::name = nm;
            ptr = p;
        }

        enumerated_collection(enumerated_collection const& l)
        {
            base_t::name = l.getName();
            ptr = l.ptr;
        }

        enumerated_collection& operator=(enumerated_collection const& l);

    protected:
        friend class collection_access;

        abstract_collection_t*
        get() const
        {
            return ptr.get();
        }

        boost::shared_ptr<abstract_collection_t> ptr;
    };

    class collection_access
    {
        template <
            typename DerivedT
          , typename EmbedT
          , typename ContextT
        >
       friend class collection_base;

       template <typename CollectionT>
       static typename CollectionT::abstract_collection_t*
       get(CollectionT const& r)
       {
           return r.get();
       }
    };

    template <
        typename DerivedT       // derived class
      , typename EmbedT         // how derived class is embedded
      , typename ContextT
    >
    class collection_base
    : public collection_expr<DerivedT>
    {
    protected:
        string name;

    public:
        DECLARE_CONTEXT(typename ContextT::parent_t)
        typedef EmbedT                          embed_t;
        typedef ContextT                        context_t;
        typedef range<context_t>                range_t;
        typedef typename range_t::iterator_t    iterator_t;
        typedef enumerated_collection<ContextT> enumerated_t;
        typedef typename context_t::char_t      char_t;
        typedef generator_type<char_t>          data_t;

        typedef abstract_collection<range_t,data_t> abstract_collection_t;

        template <class DataT>
        enumerated_t
        enumerate(TYPE_CONTEXT(DataT) & c) const;

        iterator_t
        begin() const;

        iterator_t
        end() const;

        void setName(const char* n)
        {
            name = n;
        }
        const char* getName() const
        {
            return name.c_str();
        }
    };

}

#define COLLECTION_NAME(var)        \
    var.setName(#var);

#include "impl/collection_impl.hpp"

#endif
