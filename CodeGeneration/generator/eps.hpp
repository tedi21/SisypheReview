/**
 * @class eps
 * @date 02/10/2016
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_EPS_HPP
#define GEN_EPS_HPP

#include "generator.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  eps class
    //
    //      Handles expressions of the form:
    //
    //          eps_g
    //
    //      where a is a generator. The expression does nothing.
    //
    ///////////////////////////////////////////////////////////////////////////
    class eps
    : public generator< eps >
    {
    public:
        DECLARE_EMPTY_CONTEXT()
        
        eps()
        {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };
    
    //////////////////////////////////
    template <typename T>
    eps
    eps_g(T value);

}

#include "impl/eps_impl.hpp"

#endif
