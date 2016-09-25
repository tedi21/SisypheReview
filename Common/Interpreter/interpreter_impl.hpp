#include "convert.hpp"
#include "config.hpp"

using namespace boost;
using namespace std;
using namespace fctr;
using namespace enc;

NAMESPACE_BEGIN(interp)

template <class EncodingT>
Context<EncodingT>::Context()
{}

template <class EncodingT>
Context<EncodingT>::~Context()
{}

template <class EncodingT>
void Context<EncodingT>::add(typename EncodingT::string_t const& var, boost::shared_ptr< Base<EncodingT> > const& object)
{
    iterator_t i = objects.find(var);
    if (i != objects.end() && 
        object->getClassName() != i->second->getClassName())
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->warnStream() << "a previous variable " << A(var) << " [" << A(object->getClassName()) << "] "
                             << " has different type [" << A(i->second->getClassName()) << "]";
    }
    objects[var] = object;
}

template <class EncodingT>
void Context<EncodingT>::remove(typename EncodingT::string_t const& var)
{
    itr_t i = objects.find(var);
    if (i != objects.end())
    {
        objects.erase(i);
    }
}

template <class EncodingT>
void Context<EncodingT>::clear()
{
    objects.clear();
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
Context<EncodingT>::getObject(typename EncodingT::string_t const& var) const
{
    boost::shared_ptr< Base<EncodingT> > val;
    iterator_t i = objects.find(var);
    if (i == objects.end())
    {
        val.reset(new Base<EncodingT>());
        Category * logger = &Category::getInstance(LOGNAME);
        logger->warnStream() << "variable not found : " << A(var);
    }
    else
    {
        val = i->second;
    }
    return val;
}

template <class EncodingT>
typename Context<EncodingT>::iterator_t
Context<EncodingT>::findObject(typename EncodingT::string_t const& var) const
{
    return objects.find(var);
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
Context<EncodingT>::getObject(Context<EncodingT>::iterator_t& i) const
{
    return i->second;
}

template <class EncodingT>
typename EncodingT::string_t 
Context<EncodingT>::getIdentifier(Context<EncodingT>::iterator_t& i) const
{
    return i->first;
}

template <class EncodingT>
size_t
Context<EncodingT>::size() const
{
    return objects.size();
}

template <class EncodingT>
typename Context<EncodingT>::iterator_t
Context<EncodingT>::begin() const
{
    return objects.begin();
}

template <class EncodingT>
typename Context<EncodingT>::iterator_t
Context<EncodingT>::end() const
{
    return objects.end();
}

template <class EncodingT>
void Context<EncodingT>::declare(typename EncodingT::string_t const& name, boost::shared_ptr< Term<EncodingT> > const& function)
{
    itr_fun_t i = functions.find(name);
    if (i != functions.end())
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->warnStream() << "a previous function " << A(name) << " has been declared.";
    }
    functions[name] = function;
}

template <class EncodingT>
boost::shared_ptr< Term<EncodingT> > Context<EncodingT>::getFunction(typename EncodingT::string_t const& name) const
{
    boost::shared_ptr< Term<EncodingT> > val;
    itr_fun_t i = functions.find(name);
    if (i == functions.end())
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->warnStream() << "function not found : " << A(name);
    }
    else
    {
        val = i->second;
    }
    return val;
}

template <class EncodingT>
void Context<EncodingT>::define(typename EncodingT::string_t const& name, boost::shared_ptr< Base<EncodingT> > const& constant)
{
    itr_t i = constants.find(name);
    if (i != constants.end())
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->warnStream() << "a previous constant " << A(name) << " has been declared.";
    }
    constants[name] = constant;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > Context<EncodingT>::getConstant(typename EncodingT::string_t const& name) const
{
    boost::shared_ptr< Base<EncodingT> > val;
    iterator_t i = constants.find(name);
    if (i == constants.end())
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->warnStream() << "constant not found : " << A(name);
    }
    else
    {
        val = i->second;
    }
    return val;
}

NAMESPACE_END

