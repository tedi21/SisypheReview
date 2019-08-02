﻿/*
 * StringListInterpreter_impl.hpp
 *
 *
 * @date 29-05-2015
 * @author Teddy DIDE
 * @version 1.00
 * STL Interpreter generated by gensources.
 */

#include "StringListIteratorInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
StringListInterpreter<EncodingT>::StringListInterpreter()
{}

template <class EncodingT>
StringListInterpreter<EncodingT>::~StringListInterpreter()
{
}

template <class EncodingT>
StringListInterpreter<EncodingT>::StringListInterpreter(const StringList<EncodingT>& object)
: m_object(object)
{}

template <class EncodingT>
const StringList<EncodingT>& StringListInterpreter<EncodingT>::value() const
{
	return m_object;
}

template <class EncodingT>
void StringListInterpreter<EncodingT>::value(StringList<EncodingT> const& object)
{
	m_object = object;
}

template <class EncodingT>
typename EncodingT::string_t StringListInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > StringListInterpreter<EncodingT>::clone() const
{
        return boost::shared_ptr< Base<EncodingT> >(new StringListInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t StringListInterpreter<EncodingT>::getClassName() const
{
        return UCS("StringList");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > StringListInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
                if (tryInvoke(this, UCS("StringList"), method, args, ret) ||
                    tryInvoke(this, UCS("Base"), method, args, ret))
		{
			find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
			for (size_t i = 0; i < params.size(); ++i)
			{
				find_parameter(ret, i, params[i]);
			}
		}
		else
		{
			Category* logger = &Category::getInstance(LOGNAME);
			logger->errorStream() << "Unexpected call in StringList, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Retourne l'itérateur du début
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > StringListInterpreter<EncodingT>::begin() const
{
        boost::shared_ptr< Base<EncodingT> > res(new StringListIteratorInterpreter<EncodingT>());
	res.reset(new StringListIteratorInterpreter<EncodingT>(m_object.begin()));
	return res;
}

// Retourne l'itérateur de fin
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > StringListInterpreter<EncodingT>::end() const
{
        boost::shared_ptr< Base<EncodingT> > res(new StringListIteratorInterpreter<EncodingT>());
	res.reset(new StringListIteratorInterpreter<EncodingT>(m_object.end()));
	return res;
}

template <class EncodingT>
bool check_StringList(boost::shared_ptr< Base<EncodingT> > const& val, StringList<EncodingT>& a)
{
  boost::shared_ptr< StringListInterpreter<EncodingT> > value  = dynamic_pointer_cast< StringListInterpreter<EncodingT> >(val);
  if (value)
  {
    a = value->value();
  }
  else
  {
    Category * logger = &Category::getInstance(LOGNAME);
    logger->errorStream() << "StringList expected, got " << A(val->getClassName());
  }
  return value;
}

template <class EncodingT>
bool reset_StringList(boost::shared_ptr< Base<EncodingT> >& val, StringList<EncodingT> const& a)
{
  boost::shared_ptr< StringListInterpreter<EncodingT> > value  = dynamic_pointer_cast< StringListInterpreter<EncodingT> >(val);
  if (value)
  {
    value->value(a);
  }
  else
  {
    Category* logger = &Category::getInstance(LOGNAME);
    logger->errorStream() << "StringList expected, got " << A(val->getClassName());
  }
  return value;
}

NAMESPACE_END

#undef A
#undef C
