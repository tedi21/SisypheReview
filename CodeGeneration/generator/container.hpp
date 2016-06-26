/**
 * @class container
 * @date 01/12/2012
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_CONTAINER_HPP
#define GEN_CONTAINER_HPP

#include "callback_trait.hpp"

namespace gen {

    template <class FunctorT>
    struct container_trait
    {
        typedef typename callback_trait<FunctorT>::result_t::context_t context_t;
    };

    template <typename FunctorT, typename RangeT>
    struct container
    {
        container(const FunctorT& f)
        : functor(f)
        {}
        FunctorT functor;
        RangeT   range;
    };

    ///////////////////////////////////////////////////////////////////////////////////////
    //  preimplemented functor
    ///////////////////////////////////////////////////////////////////////////////////////  

    #define DECLARE_NODELIST_ACCESS(ContextT, FunctorName)              \
        struct FunctorName                                              \
        {                                                               \
            range<ContextT> operator()(const ContextT::parent_t& c) const;\
        };

    #define IMPLEMENT_NODELIST_ACCESS(ContextT, FunctorName, Getter)                        \
        range<ContextT> FunctorName::operator()(const ContextT::parent_t& c) const          \
        {                                                                                   \
            return range<ContextT>(c.current()->Getter.begin(),c.current()->Getter.end());  \
        }

    #define DECLARE_NODE_ACCESS(ContextT, FunctorName)                  \
        struct FunctorName                                              \
        {                                                               \
            typedef ContextT::value_t   value_t;                        \
            std::vector<value_t> container;                             \
            range<ContextT> operator()(const ContextT::parent_t& c);    \
        };

    #define IMPLEMENT_NODE_ACCESS(ContextT, FunctorName, Getter)                            \
        range<ContextT> FunctorName::operator()(const ContextT::parent_t& c)                \
        {                                                                                   \
            container.clear();                                                              \
            container.push_back(c.current()->Getter);                                       \
            return range<ContextT>(container.begin(), container.end());                     \
        }
}

#endif