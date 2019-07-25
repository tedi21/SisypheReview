#ifndef _INDEXABLE_HPP_
#define _INDEXABLE_HPP_

#include "config.hpp"
#include "Base.hpp"
#include <boost/shared_ptr.hpp>


NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Indexable
    {
    public:   
        virtual ~Indexable()
        {}
        
        virtual boost::shared_ptr< Base<EncodingT> > valueAt(size_t i) const = 0;
        
        virtual size_t length() const = 0;
    };


NAMESPACE_END

#endif
