#ifndef _BASE_HPP_
#define _BASE_HPP_

#include "config.hpp"
#include "macros.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Base
    {
    public:
        Base() {}

        virtual ~Base() {}
        virtual typename EncodingT::string_t toString() const;
        virtual shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method);
        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER    (Base)
        FACTORY_END_REGISTER

        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER  (Base)
        FACTORY_END_UNREGISTER
    };

    template <class EncodingT>
    bool check_parameters_array(const std::vector< shared_ptr< Base<EncodingT> > >& params, ParameterArray& out);

    template <class EncodingT>
    bool tryInvoke( Base<EncodingT>* object,
                    const typename EncodingT::string_t& className,
                    const typename EncodingT::string_t& method, 
                    const ParameterArray& params,
                    ParameterArray& out);

NAMESPACE_END

#include "base_impl.hpp"

#endif
