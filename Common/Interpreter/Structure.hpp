#ifndef _STRUCTURE_HPP_
#define _STRUCTURE_HPP_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "numeric.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/container/vector.hpp>

#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;
namespace bc = boost::container;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Structure
    : public String<EncodingT>
    {
    private:
        typedef typename std::map< typename EncodingT::string_t, shared_ptr< Base<EncodingT> > >::iterator itr_t;
        typedef typename std::map< typename EncodingT::string_t, shared_ptr< Base<EncodingT> > >::const_iterator iterator_t;
        std::map< typename EncodingT::string_t, shared_ptr< Base<EncodingT> > > m_container;

    public:
        // Constructor
        Structure();

        // Destructor
        ~Structure();

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual shared_ptr< Base<EncodingT> > clone() const;    
        virtual typename EncodingT::string_t getClassName() const;
        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);
        
        // Dynamic methods
        void removeField(typename EncodingT::string_t const& name);

        void insertField(typename EncodingT::string_t const& name, shared_ptr< Base<EncodingT> > const& value);

        size_t getFieldsCount() const;

        bool findField(typename EncodingT::string_t const& name, shared_ptr< Base<EncodingT> >& value) const;

        iterator_t getField(size_t index) const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER    (Structure)
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER  (Structure)
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#undef C

#include "structure_impl.hpp"

#endif
