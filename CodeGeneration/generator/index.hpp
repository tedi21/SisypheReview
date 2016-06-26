/**
 * @class index
 * @date 16/12/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_INDEX_HPP
#define GEN_INDEX_HPP

#include "generator.hpp"
#include "if_generator.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  index class
    //
    //      Handles expressions of the form:
    //
    //          index_g
    //
    //      where a is a generator. The expression returns an index
    //
    ///////////////////////////////////////////////////////////////////////////
    
    class index
    : public generator< index >
    {
    protected:
        int m_offset;

    public:
        DECLARE_EMPTY_CONTEXT()
        typedef index   self_t;

        index()
        : m_offset(0)
        {}
    
        self_t& operator+(int n);
    
        self_t& operator-(int n);

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };
    
    //////////////////////////////////
    index
    index_g();

}

#include "impl/index_impl.hpp"

#endif
