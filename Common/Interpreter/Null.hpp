#ifndef _NULL_HPP_
#define _NULL_HPP_

#include "Base.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Null
    : public Base<EncodingT>
    {
    public:
        Null();
        typename EncodingT::string_t toString() const;
        boost::shared_ptr< Base<EncodingT> > clone() const;
        typename EncodingT::string_t getClassName() const;
    };

NAMESPACE_END

#include "Null_impl.hpp"

#endif
