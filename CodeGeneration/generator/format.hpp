/**
 * @class format
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_FORMAT_HPP
#define GEN_FORMAT_HPP

#include <map>
#include <boost/uuid/uuid.hpp>
#include <boost/scoped_ptr.hpp>
#include "generator.hpp"

namespace gen {

    template <
        typename DerivedT       // derived class
      , typename EmbedT         // how derived class is embedded
      , typename DataT
    >
    class format_base; // forward declaration

    template <typename BaseT, typename DataT>
    class generate_policy;

    template <typename DataT, template <typename,typename> class PolicyT = generate_policy>
    class format
        : public PolicyT < 
            format_base<
                  format<DataT, PolicyT>
                , format<DataT, PolicyT> const&
                , DataT>
            , DataT>
    {
    public:
        typedef format<DataT, PolicyT>        self_t;
        typedef format_base<
                       self_t
                      , self_t const &
                      , DataT>                base_t;

        typedef abstract_generator<DataT>     abstract_generator_t;

    public:
        format() : ptr() {}
        ~format() {}

        format(format const& f)
        : ptr(new concrete_generator<format, DataT>(f)) {}

        template <typename GeneratorT>
        format(GeneratorT const& g)
        : ptr(new concrete_generator<GeneratorT, DataT>(g)) {}

        template <typename GeneratorT>
        format& operator=(GeneratorT const& g);

        format& operator=(format const& f);

        self_t copy() const;

    private:
        friend class format_base_access;

        abstract_generator_t*
        get() const
        {
            return ptr.get();
        }

        format(abstract_generator_t * p)
        : ptr(p) {}

        boost::scoped_ptr<abstract_generator_t> ptr;
    };

    class format_base_access
    {
        template <
            typename DerivedT
          , typename EmbedT
          , typename DataT
        >
       friend class format_base;

       template <typename FormatT>
       static typename FormatT::abstract_generator_t*
       get(FormatT const& r)
       {
           return r.get();
       }
    };

    template <
        typename DerivedT       // derived class
      , typename EmbedT         // how derived class is embedded
      , typename DataT
    >
    class format_base
    : public generator<DerivedT>
    {
    private:
        string name;

    public:
        DECLARE_EMPTY_CONTEXT()
        typedef EmbedT                    embed_t;

    public:
        template <class>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

        void setName(const char* n)
        {
            name = n;
        }
        const char* getName() const
        {
            return name.c_str();
        }

    };

    template <class BaseT, class DataT>
    class generate_policy
    : public BaseT
    {
    public:
        DECLARE_EMPTY_CONTEXT()

        template <class>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };


    template <class BaseT, class DataT>
    class const_policy
    : public BaseT
    {
    private:
        typedef typename generator_string<typename DataT::char_t>::str_t    result_t;
        typedef typename std::map<size_t,result_t>::iterator iterator_t;
        boost::uuids::uuid tag;

    public:
        DECLARE_EMPTY_CONTEXT()

        const_policy()
        : tag(boost::uuids::random_generator()())
        {}

        template <class>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };

    template <class BaseT, class DataT>
    class memo_policy
    : public BaseT
    {
    private:
        typedef typename generator_string<typename DataT::char_t>::str_t    result_t;
        typedef typename std::map<size_t,result_t>::iterator iterator_t;
        boost::uuids::uuid tag;

    public:
        DECLARE_EMPTY_CONTEXT()

        memo_policy()
        : tag(boost::uuids::random_generator()())
        {}

        template <class>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };
}

#define FORMAT_NAME(var)        \
    var.setName(#var);

#include "impl/format_impl.hpp"

#endif
