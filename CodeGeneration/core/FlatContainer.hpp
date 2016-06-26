#ifndef FLAT_CONTAINER_HPP_
#define FLAT_CONTAINER_HPP_

#include "FlatIterator.hpp"

namespace dsg {

    #define callMethod(object,ptrToMember)  ((object).*(ptrToMember))()

    template <class ContainerItr, class Container, class ItemItr, class Item>
    class FlatContainer
    {
    private:
        typedef ItemItr (Container::*callback_t)();
    public:
        typedef FlatIterator<ContainerItr,Container,ItemItr,Item>    iterator;
    protected:
        FlatContainer()
        {}
        
        void define( ContainerItr first,
                     ContainerItr last,    
                     callback_t begin,
                     callback_t end)
        {
            m_end = last;
            m_begin = first;
            m_methodBegin = begin;
            m_methodEnd = end;
        }
    public:
        iterator begin()
        {
            ContainerItr first = m_begin;
            // search first element
            while (callMethod(*first, m_methodBegin) == callMethod(*first, m_methodEnd)
                   && first != m_end-1) first++;
            // construct first element
            return iterator(first, m_end,    // entity range
                            callMethod(*first, m_methodBegin),// current element
                            m_methodBegin, m_methodEnd); // range method
        }

        iterator end()
        {
            ContainerItr last = m_end-1;
            // construct last attribute
            return iterator(last, m_end,
                            callMethod(*last, m_methodEnd),
                            m_methodBegin, m_methodEnd);
        }
    private:
        ContainerItr        m_end;
        ContainerItr        m_begin;
        callback_t          m_methodBegin;
        callback_t          m_methodEnd;
    };

    // # CONST specialization
    template <class ContainerItr, class Container, class ItemItr, class Item>
    class FlatContainer <ContainerItr, Container, ItemItr, Item const>
    {
    private:
        typedef ItemItr (Container::*callback_t)() const;
    public:
        typedef FlatIterator<ContainerItr,Container,ItemItr,Item const>    const_iterator;
    protected:
        FlatContainer()
        {}
        
        void define( ContainerItr first,
                     ContainerItr last,    
                     callback_t begin,
                     callback_t end)
        {
            m_end = last;
            m_begin = first;
            m_methodBegin = begin;
            m_methodEnd = end;
        }
    public:
        const_iterator begin() const
        {
            assert(m_begin != m_end);
            ContainerItr first = m_begin;
            // search first element
            while (callMethod(*first, m_methodBegin) == callMethod(*first, m_methodEnd)
                   && first != m_end-1) first++;
            // construct first element
            return const_iterator(first, m_end,    // entity range
                                  callMethod(*first, m_methodBegin),// current element
                                  m_methodBegin, m_methodEnd); // range method
        }

        const_iterator end() const
        {
            assert(m_begin != m_end);
            ContainerItr last = m_end-1;
            // construct last attribute
            return const_iterator(last, m_end,
                                  callMethod(*last, m_methodEnd),
                                  m_methodBegin, m_methodEnd);
        }
    private:
        ContainerItr        m_end;
        ContainerItr        m_begin;
        callback_t          m_methodBegin;
        callback_t          m_methodEnd;
    };
    // # END CONST specialization

    #undef callMethod

}

#endif