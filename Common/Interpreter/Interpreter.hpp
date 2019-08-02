#ifndef _INTERPRETER_HPP_
#define _INTERPRETER_HPP_

#include "config.hpp"
#include "Functions.hpp"
#include "Base.hpp"
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <map>

using namespace boost;
using namespace log4cpp;
using namespace std;

NAMESPACE_BEGIN(interp)

template <class EncodingT>
class Term;

template <class EncodingT>
class Context
{
private:
    std::map< typename EncodingT::string_t,boost::shared_ptr< Base<EncodingT> > >    objects;
    typedef typename std::map< typename EncodingT::string_t,boost::shared_ptr< Base<EncodingT> > >::iterator itr_t;
	
    std::map< typename EncodingT::string_t,boost::shared_ptr< Term<EncodingT> > >    functions;
    typedef typename std::map< typename EncodingT::string_t,boost::shared_ptr< Term<EncodingT> > >::const_iterator itr_fun_t;

    std::map< typename EncodingT::string_t,boost::shared_ptr< Base<EncodingT> > >    constants;

public:
    Context();
    typedef typename std::map< typename EncodingT::string_t,boost::shared_ptr< Base<EncodingT> > >::const_iterator iterator_t;
    void add(typename EncodingT::string_t const& var, boost::shared_ptr< Base<EncodingT> > const& object);
    void remove(typename EncodingT::string_t const& var);
    void clear();
    boost::shared_ptr< Base<EncodingT> > getObject(typename EncodingT::string_t const& var) const;
    iterator_t findObject(typename EncodingT::string_t const& var) const;
    boost::shared_ptr< Base<EncodingT> > getObject(iterator_t& i) const;
    typename EncodingT::string_t getIdentifier(iterator_t& i) const;
    size_t size() const;
    iterator_t begin() const;
    iterator_t end() const;
	 
    void declare(typename EncodingT::string_t const& name, boost::shared_ptr< Term<EncodingT> > const& function);
    boost::shared_ptr< Term<EncodingT> > getFunction(typename EncodingT::string_t const& name) const;

    void define(typename EncodingT::string_t const& name, boost::shared_ptr< Base<EncodingT> > const& constant);
    boost::shared_ptr< Base<EncodingT> > getConstant(typename EncodingT::string_t const& name) const;
};

// Term expression
// abstract term
template <class EncodingT>
class Term
{
public:
    virtual ~Term(){}
    virtual boost::shared_ptr< Base<EncodingT> > interpret(Context<EncodingT> & c) = 0;
};

// Address value
// an expression that can be assigned 
template <class EncodingT>
class Address
: public Term<EncodingT>
{
public:
    virtual void allocate(boost::shared_ptr< Base<EncodingT> > const& value, Context<EncodingT> & c) = 0;
};

NAMESPACE_END

#include "Interpreter_impl.hpp"

#endif
