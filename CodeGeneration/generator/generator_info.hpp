/**
 * @class generator_info
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief
 */

#ifndef GENERATOR_INFO_HPP
#define GENERATOR_INFO_HPP

#include "primitives_char.hpp"
#include "callback_trait.hpp"
#include <vector>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/uuid/uuid.hpp>

#pragma warning( push )
#pragma warning( disable : 4244)
#include <boost/uuid/uuid_generators.hpp>
#pragma warning( pop ) 

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  generator_string metafunction
    //
    //      Given a type CharT, the generator_string
    //        metafunction provides the actual string used in generator.
    //
    //  Usage:
    //
    //      typename generator_string<CharT>::str_t
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT>
    struct generator_string
    {
        typedef CharT                        character_t;
        typedef basic_string< character_t >  str_t;
        typedef const character_t *          c_str_t;
    };

    template <typename CharT>
    inline size_t
    get_length( const basic_string<CharT>& str )
    {
        return str.length();
    }

    template <typename CharT>
    inline basic_string<CharT>
    get_substring( basic_string<CharT>& str, size_t pos = 0, size_t n = -1, bool erase = false )
    {
        basic_string<CharT> s = str.substr(pos, n);
        if (erase)
        {
            str.erase(pos, n);
        }
        return s;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  domain class
    //
    //    represents generation domain (list of items will be covered for
    //    the generation)
    //
    ///////////////////////////////////////////////////////////////////////////
    template <class IteratorT>
    class domain
    {
    public:
        typedef IteratorT             iterator_t;
        typedef domain<iterator_t>    self_t;
    private:
        iterator_t                    m_first, m_end;
        iterator_t                    m_firstPositive, m_endPositive;
        size_t                        m_size, m_sizePositive;

    public:
        domain(iterator_t const& first, iterator_t const& end)
        : m_first(first), m_end(end),
          m_firstPositive(first), m_endPositive(end),
          m_size(end-first), m_sizePositive(end-first)
        {}
        domain(iterator_t const& first, iterator_t const& end,
               iterator_t const& firstPositive, iterator_t const& endPositive, size_t sizePositive)
        : m_first(first), m_end(end),
          m_firstPositive(firstPositive), m_endPositive(endPositive),
          m_size(end-first), m_sizePositive(sizePositive)
        {}
        iterator_t const& first() const
        {
            return m_first;
        }
        iterator_t const& end() const
        {
            return m_end;
        }
        iterator_t const& firstPositive() const
        {
            return m_firstPositive;
        }
        iterator_t const& endPositive() const
        {
            return m_endPositive;
        }
        size_t size() const
        {
            return m_size;
        }
        size_t sizePositive() const
        {
            return m_sizePositive;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  result_buffer class
    //
    //  represents result buffer
    //
    ///////////////////////////////////////////////////////////////////////////
    template <class CharT>
    class result_buffer
    {
    public:
        typedef typename generator_string<CharT>::character_t    char_t;
        typedef typename generator_string<CharT>::str_t          str_t;
        typedef typename generator_string<CharT>::c_str_t        c_str_t;

    public:
        result_buffer()
        : internalBuffer(new str_t())
        {}
        result_buffer(c_str_t buf)
        : internalBuffer(new str_t(buf))
        {}
        result_buffer(str_t const& buf)
        : internalBuffer(new str_t(buf))
        {}
        const str_t & str() const
        {
            return *internalBuffer;
        }
        size_t length() const
        {
            return get_length(*internalBuffer);
        }
        str_t subtract(size_t pos = 0, size_t n = -1, bool erase = false) 
        {
            return get_substring(*internalBuffer, pos, n, erase);
        }
        void append(c_str_t buf_)
        {
            (*internalBuffer) += buf_;
        }
        void append(const str_t & buf_)
        {
            (*internalBuffer) += buf_;
        }
        void append(char_t c)
        {
            (*internalBuffer) += c;
        }
        void reset(c_str_t buf_)
        {
            internalBuffer.reset(new str_t(buf_));
        }
        void reset(str_t const& buf_)
        {
            internalBuffer.reset(new str_t(buf_));
        }
        void reset()
        {
            internalBuffer.reset(new str_t);
        }
    protected:
        boost::shared_ptr<str_t> internalBuffer;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  context class
    //
    //    represents generation context
    //
    ///////////////////////////////////////////////////////////////////////////
    template <class ContainerT, class ParentT>
    class context
    : public ParentT
    {
    public:
        typedef ContainerT                              container_t;
        typedef typename container_t::const_iterator    iterator_t;
        typedef ParentT                                 parent_t;
        typedef context<container_t, parent_t>          self_t;
        typedef gen::domain<iterator_t>                 domain_t;
        typedef typename parent_t::empty_context_t      empty_context_t;
        typedef typename std::iterator_traits<iterator_t>::value_type    
                                                        value_t;
        enum { base = parent_t::base+1 };
    protected:
        domain_t   m_domain;
        iterator_t m_current;
    public:
        context(iterator_t const& first, iterator_t const& end,
                parent_t const& p = parent_t())
                : parent_t(p),
                  m_domain(first, end),
                  m_current(first)
        {
             parent_t::m_tag = boost::uuids::random_generator()();
        }
        iterator_t const& current() const
        {
            return m_current;
        }
        iterator_t & current()
        {
            return m_current;
        }
        void current(iterator_t const& current)
        {
            m_current = current;
        }
        domain_t & domain()
        {
            return m_domain;
        }
        domain_t const& domain() const
        {
            return m_domain;
        }
        void domain(domain_t const& domain)
        {
            m_domain = domain;
        }
        // virtual functions
        void increment()
        {
            m_current++;
        }
        void decrement()
        {
            m_current--;
        }
        void defineDomain(size_t first, size_t end, size_t size)
        {
            m_domain = domain_t(m_domain.first(), m_domain.end(), 
                                m_domain.first()+first, 
                                m_domain.first()+end,
                                size);
        }
        void position(size_t index)
        {
            m_current = m_domain.first()+index;
        }
        size_t position() const 
        {
            return m_current-m_domain.first();
        };
        size_t endPosition() const 
        {
            return m_domain.endPositive()-m_domain.first();
        };
        size_t firstPosition() const 
        {
            return m_domain.firstPositive()-m_domain.first();
        };
        size_t size() const 
        {
            return m_domain.sizePositive(); 
        }
        size_t max_size() const 
        {
            return m_domain.size(); 
        }
        bool isFirstPosition() const
        {
            return m_domain.firstPositive() == m_current;
        }
        bool isLastPosition() const
        {
            // not empty && end element
            return m_domain.firstPositive() != m_domain.endPositive() && 
                    m_current == m_domain.endPositive()-1; 
        }
        vector<size_t> positions() const 
        { 
            vector<size_t> v = parent_t::positions();
            size_t p = self_t::position();
            v.push_back(p);
            return v;
        }
    };

    template <class CharT>
    class empty_context
    : public result_buffer<CharT>
    {
    protected:
        boost::uuids::uuid m_tag;
    public:
        // Types
        typedef result_buffer<CharT>                parent_t;
        typedef empty_context<CharT>                self_t;
        typedef self_t                              empty_context_t;
        typedef typename parent_t::char_t           char_t;
        typedef typename parent_t::str_t            str_t;
        typedef typename parent_t::c_str_t          c_str_t;
        enum { base = -1 };
        // constructor
        empty_context()
        : parent_t(),
          m_tag(boost::uuids::random_generator()())
        {}
        empty_context(c_str_t buf)
        : parent_t(buf),
          m_tag(boost::uuids::random_generator()())
        {}
        empty_context(str_t const& buf)
        : parent_t(buf),
          m_tag(boost::uuids::random_generator()())
        {}
        boost::uuids::uuid const& tag() const
        {
            return m_tag;
        }
        // polymorphic class
        virtual ~empty_context(){}
        virtual void increment(){}
        virtual void decrement(){}
        virtual void defineDomain(size_t first, size_t end, size_t size){}
        virtual void position(size_t index){}
        virtual size_t position() const { return 0; }
        virtual size_t endPosition() const {return 0; }
        virtual size_t firstPosition() const { return 0; }
        virtual size_t size() const { return 0; }
        virtual size_t max_size() const { return 0; }
        virtual bool isFirstPosition() const { return false; }
        virtual bool isLastPosition() const { return false; }
        virtual bool isValidPosition() const { return false; }
        virtual vector<size_t> positions() const { return vector<size_t>(); }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  generator_type metafunction
    //
    //      Given types CharT and VectorT, the generator_type
    //        metafunction provides the result char type and 
    //        the initial context used in generator.
    //
    //  Usage:
    //
    //      typename generator_type<CharT,VectorT>::initial_list_t
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT = char>
    struct generator_type
    {
        typedef typename generator_string<CharT>::character_t    char_t;
        typedef empty_context<char_t>                            context_t;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  update_context_n metafunction
    //
    //      Given a type ResultT, the generator_type
    //        metafunction provides the actual context types used in generator.
    //
    //  Usage:
    //
    //      typename update_context_n<ResultT, N>::context_t
    //
    ///////////////////////////////////////////////////////////////////////////
    #define DECLARE_CONTEXT(Context)    \
        template <class T__>            \
        struct declare_context          \
        {                               \
            typedef Context context_t;  \
        };

    #define DECLARE_EMPTY_CONTEXT()     \
        template <class T__>            \
        struct declare_context          \
        {                               \
            typedef typename T__::context_t context_t;\
        };

    #define TYPE_CONTEXT(T)\
        typename declare_context<T>::context_t

    #define TYPE_CONTEXT_IMPL(Class,T)\
        typename Class::template declare_context<T>::context_t

    #define TYPE_CONTEXT_IMPL_TPL(Class,C1,T)\
        typename Class<C1>::template declare_context<T>::context_t

    #define TYPE_CONTEXT_IMPL_TPL_2(Class,C1,C2,T)\
        typename Class<C1,C2>::template declare_context<T>::context_t

    #define TYPE_CONTEXT_IMPL_TPL_3(Class,C1,C2,C3,T)\
        typename Class<C1,C2,C3>::template declare_context<T>::context_t

    #define TYPE_GENERATOR_CONTEXT(Generator)\
        typename Generator::template declare_context<T__>::context_t

    #define TYPE_GENERATOR_CONTEXT2(Generator1, Generator2)\
        typename boost::mpl::if_c< (Generator1::template declare_context<T__>::context_t::base > Generator2::template declare_context<T__>::context_t::base),\
                    typename Generator1::template declare_context<T__>::context_t,\
                    typename Generator2::template declare_context<T__>::context_t >::type
}

#endif
