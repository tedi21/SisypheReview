/**
 * @class condition
 * @date 15/02/2009
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief
 */

#ifndef GEN_CONDITION_HPP
#define GEN_CONDITION_HPP

#include "if_generator.hpp"
#include <boost/scoped_ptr.hpp>

namespace gen {

    template <
        typename DerivedT       // derived class
      , typename EmbedT         // how derived class is embedded
      , typename DataT
    >
    class condition_base; // forward declaration

    template <typename DataT>
    class condition
    : public condition_base<
            condition<DataT>
          , condition<DataT> const&
          , DataT>
    {
    public:
        typedef condition<DataT>            self_t;
        typedef condition_base<
            self_t
          , self_t const&
          , DataT>                          base_t;

        typedef abstract_condition<DataT> abstract_condition_t;

    public:
        condition() : ptr() {}
        ~condition() {}

        condition(condition const& f)
        : ptr(new concrete_condition<condition, DataT>(f)) {}

        template <typename CondT>
        condition(CondT const& c)
        : ptr(new concrete_condition<CondT, DataT>(c)) {}

        template <typename CondT>
        condition& operator=(CondT const& c);

        condition& operator=(condition const& f);

        self_t copy() const;

    private:
        friend class condition_base_access;

        abstract_condition_t*
        get() const
        {
            return ptr.get();
        }

        condition(abstract_condition_t * p)
        : ptr(p) {}

        boost::scoped_ptr<abstract_condition_t> ptr;
    };

    class condition_base_access
    {
        template <
            typename DerivedT
          , typename EmbedT
          , typename DataT
        >
       friend class condition_base;

       template <typename ConditionT>
       static typename ConditionT::abstract_condition_t*
       get(ConditionT const& r)
       {
           return r.get();
       }
    };


    template <
        typename DerivedT       // derived class
      , typename EmbedT         // how derived class is embedded
      , typename DataT
    >
    class condition_base
    : public cond_expr<DerivedT>
    {
    private:
        string name;

    public:
        DECLARE_EMPTY_CONTEXT()
        typedef EmbedT                    embed_t;

    public:
        template <class>
        bool
        evaluate(TYPE_CONTEXT(DataT) & c) const;

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

#define CONDITION_NAME(var)        \
    var.setName(#var);

#include "impl/condition_impl.hpp"

#endif
