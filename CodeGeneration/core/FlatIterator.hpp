#ifndef FLAT_ITERATOR_HPP_
#define FLAT_ITERATOR_HPP_

#include <boost/iterator/iterator_facade.hpp>
#include <boost/call_traits.hpp>

#define callMethod(object,ptrToMember)  ((object).*(ptrToMember))()

namespace dsg {

    #define FLAT_ITERATOR_MEMBERS                                   \
    public:                                                         \
        FlatIterator()                                              \
        {}                                                          \
                                                                    \
        explicit FlatIterator(  ContainerItr first,                 \
                                ContainerItr last,                  \
                                ItemItr item,                       \
                                callback_t begin,                   \
                                callback_t end)                     \
        : m_end(last),                                              \
          m_container(first),                                       \
          m_item(item),                                             \
          m_methodBegin(begin),                                     \
          m_methodEnd(end)                                          \
        {}                                                          \
                                                                    \
    private:                                                        \
        friend class boost::iterator_core_access;                   \
                                                                    \
        void increment() {                                          \
            m_item++;                                               \
            while (m_item == callMethod(*m_container, m_methodEnd) && m_container+1 != m_end) {\
                /* at the end, stay to the end position*/           \
                if (m_container+1 != m_end) {                       \
                    m_container++;                                  \
                    m_item = callMethod(*m_container, m_methodBegin);\
                }                                                   \
            }                                                       \
        }                                                           \
                                                                    \
        void advance(typename ParentType::difference_type n) {      \
            int i = 0;                                              \
            if (n>0)        while ( i++ < n ) increment();          \
            else if (n<0)   while ( i-- > n ) decrement();          \
        }                                                           \
                                                                    \
        typename ParentType::difference_type                        \
        distance_to(FlatIterator const& other) const {              \
            typename ParentType::difference_type n = 0, direction;  \
            ContainerItr minContainer, maxContainer;                \
            ItemItr minItem, maxItem;                               \
            /* get direction */                                     \
            if (m_container < other.m_container ||                  \
                (m_container == other.m_container && m_item < other.m_item))\
            {                                                       \
                minContainer = m_container; minItem = m_item;       \
                maxContainer = other.m_container; maxItem = other.m_item;\
                direction = 1;                                      \
            }                                                       \
            else                                                    \
            {                                                       \
                maxContainer = m_container; maxItem = m_item;       \
                minContainer = other.m_container; minItem = other.m_item;\
                direction = -1;                                     \
            }                                                       \
            /* compute distance    */                               \
            while (minContainer!=maxContainer || minItem!=maxItem)  \
            {                                                       \
                if (minContainer!=maxContainer)                     \
                {                                                   \
                    n += callMethod(*minContainer, m_methodEnd) - minItem;\
                    minContainer += 1;                              \
                    minItem = callMethod(*minContainer, m_methodBegin);\
                }                                                   \
                else /* minItem!=maxItem */                         \
                {                                                   \
                    n += maxItem - minItem;                         \
                    maxItem = minItem;                              \
                }                                                   \
            }                                                       \
            return n*direction;                                     \
        }                                                           \
                                                                    \
        void decrement() {                                          \
            if (m_item == callMethod(*m_container, m_methodBegin)) {\
                while (callMethod(*(m_container-1), m_methodBegin) == callMethod(*(m_container-1), m_methodEnd)) m_container--;\
                m_item = callMethod(*(--m_container), m_methodEnd)-1;\
            }                                                       \
            else {                                                  \
                m_item--;                                           \
            }                                                       \
        }                                                           \
                                                                    \
        bool equal(FlatIterator const& other) const {               \
            return (this->m_container == other.m_container && this->m_item == other.m_item);\
        }                                                           \
                                                                    \
        ItemReference dereference() const {                         \
            return *m_item;                                         \
        }                                                           \
                                                                    \
    private:                                                        \
        ContainerItr        m_end;                                  \
        ContainerItr        m_container;                            \
        ItemItr             m_item;                                 \
        callback_t          m_methodBegin;                          \
        callback_t          m_methodEnd;


    template <class ContainerItr, class Container, class ItemItr, class Item>
    class FlatIterator
    : public boost::iterator_facade< FlatIterator<ContainerItr,Container,ItemItr,Item>,
                                     Item,
                                     boost::random_access_traversal_tag> {
    private:
        typedef ItemItr (Container::*callback_t)();
        typedef typename boost::call_traits<Item>::reference  ItemReference;
        typedef boost::iterator_facade<
                    FlatIterator< ContainerItr,Container,ItemItr,Item >,
                    Item,
                    boost::random_access_traversal_tag>         ParentType;

        FLAT_ITERATOR_MEMBERS
    };

    // # CONST specialization
    template <class ContainerItr, class Container, class ItemItr, class Item>
    class FlatIterator <ContainerItr, Container, ItemItr, Item const>
    : public boost::iterator_facade< FlatIterator<ContainerItr,Container,ItemItr,Item const>,
                                     Item const,
                                     boost::random_access_traversal_tag> {
    private:
        typedef ItemItr (Container::*callback_t)() const;
        typedef typename boost::call_traits<Item>::const_reference ItemReference;
        typedef boost::iterator_facade<
                    FlatIterator<ContainerItr,Container,ItemItr,Item const>,
                    Item const,
                    boost::random_access_traversal_tag>         ParentType;

        FLAT_ITERATOR_MEMBERS
    };
    // # END CONST specialization

    #undef FLAT_ITERATOR_MEMBERS
}

#undef callMethod

#endif