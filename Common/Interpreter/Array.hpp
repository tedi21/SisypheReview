#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_

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
    class Array
    : public String<EncodingT>
    {
    private:
        std::vector< shared_ptr< Base<EncodingT> > > m_container;

    public:
        // Constructor
        Array();

        // Destructor
        ~Array();

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual shared_ptr< Base<EncodingT> > clone() const;    
        virtual typename EncodingT::string_t getClassName() const;
        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);
        
        // Dynamic methods
        FACTORY_PROTOTYPE1(addValue, In< shared_ptr< Base<EncodingT> > >)
        void addValue(shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE2(insertValue, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >)
        void insertValue(shared_ptr< Base<EncodingT> > const& i, shared_ptr< Base<EncodingT> > const& val);

        FACTORY_PROTOTYPE1(removeValue, In< shared_ptr< Base<EncodingT> > >)
        void removeValue(shared_ptr< Base<EncodingT> > const& i);
        
        void clear();

        FACTORY_PROTOTYPE1(getValue, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > getValue(shared_ptr< Base<EncodingT> > const& i) const;

        shared_ptr< Base<EncodingT> > size() const;

        FACTORY_PROTOTYPE1(sort, In< shared_ptr< Base<EncodingT> > >)
        void sort(shared_ptr< Base<EncodingT> > const& function);
        void sort();

        FACTORY_PROTOTYPE1(find, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > find(shared_ptr< Base<EncodingT> > const& function) const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            CLASS_REGISTER    (Array)
            METHOD_REGISTER1  (Array, void, addValue, no_const_t)
            METHOD_REGISTER2  (Array, void, insertValue, no_const_t)
            METHOD_REGISTER1  (Array, void, removeValue, no_const_t)
            METHOD_REGISTER1  (Array, shared_ptr< Base<EncodingT> >, getValue, const_t)
            METHOD_REGISTER   (Array, shared_ptr< Base<EncodingT> >, size, const_t)
            METHOD_KEY_REGISTER   (Array, void, clear, no_const_t, C("Array::Clear"))
            METHOD_KEY_REGISTER   (Array, void, sort, no_const_t, C("Array::Sort"))
            METHOD_KEY_REGISTER1  (Array, void, sort, no_const_t, C("Array::Sort"))
            METHOD_KEY_REGISTER1  (Array, shared_ptr< Base<EncodingT> >, find, const_t, C("Array::Find"))
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            CLASS_UNREGISTER  (Array)
            METHOD_UNREGISTER1(Array, addValue)
            METHOD_UNREGISTER2(Array, insertValue)
            METHOD_UNREGISTER1(Array, removeValue)
            METHOD_UNREGISTER1(Array, getValue)
            METHOD_UNREGISTER (Array, size)
            METHOD_KEY_UNREGISTER (C("Array::Clear"))
            METHOD_KEY_UNREGISTER (C("Array::Sort"))
            METHOD_KEY_UNREGISTER1(C("Array::Sort"))
            METHOD_KEY_UNREGISTER1(C("Array::Find"))
        FACTORY_END_UNREGISTER
    };

    inline bool check_index(double value, size_t size, size_t& index);
	
    template <class EncodingT, class T>
    shared_ptr< Base<EncodingT> > convert_numeric_array(const bc::vector<T>& value);

    template <class EncodingT, class T>
    bool check_numeric_array(shared_ptr< Base<EncodingT> > const& val, bc::vector<T>& v);

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > convert_string_array(const std::vector<typename EncodingT::string_t>& value);

    template <class EncodingT>
    bool check_string_array(shared_ptr< Base<EncodingT> > const& val, std::vector<typename EncodingT::string_t>& v);
    
    template <class EncodingT, class T, class Fct>
    bool check_array(shared_ptr< Base<EncodingT> > const& val, std::vector<T>& v, Fct check_fct);
    
    template <class EncodingT, class T, class Fct>
    bool reset_array(shared_ptr< Base<EncodingT> >& val, std::vector<T> const& v, Fct reset_fct);

NAMESPACE_END

#undef C

#include "array_impl.hpp"

#endif
