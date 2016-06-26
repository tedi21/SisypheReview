#include "boost/lexical_cast.hpp"

namespace gen {
 
    inline index::self_t& 
    index::operator+(int n)
    {
        m_offset = n;
        return *this;
    }
    
    inline index::self_t&  
    index::operator-(int n)
    {
        return operator+(-n);
    }

    template <typename DataT>
    void
    index::generate(TYPE_CONTEXT(DataT) & context) const
    { 
        context.append(
            boost::lexical_cast<TYPE_CONTEXT(DataT)::str_t>(
                context.position()+m_offset ));
    }
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  index class implementation
    //
    ///////////////////////////////////////////////////////////////////////////
    inline index
    index_g()
    {
        return index();
    }

}
