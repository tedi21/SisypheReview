/**
 * @class stored_format
 * @date 02/12/2009
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_STORED_FORMAT_HPP
#define GEN_STORED_FORMAT_HPP

#include "format.hpp"
#include "va_arg.hpp"
#include <boost/shared_ptr.hpp>

namespace gen {

    template <typename DataT, bool EmbedByValue = false>
    class stored_format
        : public format_base<
            stored_format<DataT, EmbedByValue>
          , typename boost::mpl::if_c<
                EmbedByValue
                , stored_format<DataT, true>
                , stored_format<DataT> const& >::type 
          , DataT>
    {
    public:
        typedef stored_format<DataT, EmbedByValue>    self_t;
        typedef format_base<
            self_t
          , typename boost::mpl::if_c<
                EmbedByValue
                , stored_format<DataT, true>
                , self_t const& >::type 
          , DataT>                                    base_t;

        typedef abstract_generator<DataT>    abstract_generator_t;

    public:
        stored_format() : ptr() {}
        ~stored_format() {}

        stored_format(stored_format const& f)
        : ptr(f.ptr) {}

        template <typename GeneratorT>
        stored_format(GeneratorT const& g)
        : ptr(new concrete_generator<GeneratorT, DataT>(g)) {}

        template <typename GeneratorT>
        stored_format& operator=(GeneratorT const& g);

        stored_format& operator=(stored_format const& f);

        stored_format<DataT, true> copy() const;

    private:
        friend class format_base_access;
        friend class stored_format<DataT, !EmbedByValue>;

        abstract_generator_t*
        get() const
        {
            return ptr.get();
        }

        stored_format(boost::shared_ptr<abstract_generator_t> const& p)
        : ptr(p) {}

        boost::shared_ptr<abstract_generator_t> ptr;
    };

}

#include "impl/stored_format_impl.hpp"

#endif
