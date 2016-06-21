#ifndef _BOOL_HPP_
#define _BOOL_HPP_

#include <boost/shared_ptr.hpp>
#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Bool
    : public String<EncodingT>
    {
	private:
		bool m_value;
		
    public:
        // Constructor
        Bool();

        Bool(bool value);

        FACTORY_PROTOTYPE1(Bool, In< shared_ptr< Base<EncodingT> > >)
        Bool(shared_ptr< Base<EncodingT> > const& value);

        // Destructor
        ~Bool();

        // Accessors
		bool getValue() const;
        void setValue(bool value);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual shared_ptr< Base<EncodingT> > clone() const;    
        virtual typename EncodingT::string_t getClassName() const;
        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);
        
        // Dynamic methods
        shared_ptr< Base<EncodingT> > not_() const;

        FACTORY_PROTOTYPE1(and_, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > and_(shared_ptr< Base<EncodingT> > const& val) const;

        FACTORY_PROTOTYPE1(or_, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > or_(shared_ptr< Base<EncodingT> > const& val) const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER    (Bool)
            CLASS_REGISTER1   (Bool)
            METHOD_REGISTER   (Bool, shared_ptr< Base<EncodingT> >, not_, const_t)
            METHOD_REGISTER1  (Bool, shared_ptr< Base<EncodingT> >, and_, const_t)
            METHOD_REGISTER1  (Bool, shared_ptr< Base<EncodingT> >, or_, const_t)
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER  (Bool)
            CLASS_UNREGISTER1 (Bool)
            METHOD_UNREGISTER (Bool, not_)
            METHOD_UNREGISTER1(Bool, and_)
            METHOD_UNREGISTER1(Bool, or_)
        FACTORY_END_UNREGISTER
    };

    template <class EncodingT>
    bool check_bool(shared_ptr< Base<EncodingT> > const& val, bool& n);

NAMESPACE_END

#include "bool_impl.hpp"

#endif
