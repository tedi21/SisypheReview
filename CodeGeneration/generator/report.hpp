
/**
 * @class report
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief The class returns a generator that generate a composite generator.
 */

#ifndef GEN_REPORT_HPP
#define GEN_REPORT_HPP

#include "generator.hpp"

namespace gen {

    template <typename DerivedT>
    struct report
    : public generator<DerivedT>
    {
        DECLARE_EMPTY_CONTEXT()

        typedef report<DerivedT>        self_t;
        typedef DerivedT const&         embed_t;

        /** generate function, call the generator returned by start method.
         * @param info contains information for generation and stores the result.
         */
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };

}

#include "impl/report_impl.hpp"
#endif
