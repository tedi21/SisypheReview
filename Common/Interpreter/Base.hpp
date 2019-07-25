#ifndef _BASE_HPP_
#define _BASE_HPP_

#include "config.hpp"
#include "macros.hpp"
#include <boost/shared_ptr.hpp>
#include <vector>

#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Bool;

    template <class EncodingT>
    class Base
    {
    public:
        Base() {}

        virtual ~Base() {}
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method);
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);
        
        FACTORY_PROTOTYPE1(isType, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > isType(boost::shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER        (Base)
            METHOD_KEY_REGISTER1  (Base, boost::shared_ptr< Base<EncodingT> >, isType, const_t, C("Base::IsType"))
        FACTORY_END_REGISTER

        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER  (Base)
            METHOD_KEY_UNREGISTER1(C("Base::IsType"))
        FACTORY_END_UNREGISTER
    };

    template <class EncodingT>
    bool check_parameters_array(const std::vector< boost::shared_ptr< Base<EncodingT> > >& params, ParameterArray& out);

    template <class EncodingT>
    bool tryInvoke( Base<EncodingT>* object,
                    const typename EncodingT::string_t& className,
                    const typename EncodingT::string_t& method, 
                    const ParameterArray& params,
                    ParameterArray& out);

    template <class EncodingT2, class EncodingT>
    bool check_string(boost::shared_ptr< Base<EncodingT> > const& val, typename EncodingT2::string_t& n);

NAMESPACE_END

#undef C

#include "base_impl.hpp"

#endif
