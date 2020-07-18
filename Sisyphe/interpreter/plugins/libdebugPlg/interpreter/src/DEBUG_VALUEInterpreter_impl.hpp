/*
 * DEBUG_VALUEInterpreter_impl.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
DEBUG_VALUEInterpreter<EncodingT>::DEBUG_VALUEInterpreter()
{
}

template <class EncodingT>
void DEBUG_VALUEInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
void DEBUG_VALUEInterpreter<EncodingT>::initValue(const DEBUG_VALUE& object)
{
	m_object = object;
}

template <class EncodingT>
DEBUG_VALUE& DEBUG_VALUEInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const DEBUG_VALUE& DEBUG_VALUEInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
DEBUG_VALUEInterpreter<EncodingT>::DEBUG_VALUEInterpreter(const DEBUG_VALUE& object)
{
	initValue(object);
}

template <class EncodingT>
const DEBUG_VALUE& DEBUG_VALUEInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void DEBUG_VALUEInterpreter<EncodingT>::value(DEBUG_VALUE const& object)
{
	if (&object != &value()) {
		tidyValue();
		initValue(object);
	}
}

template <class EncodingT>
typename EncodingT::string_t DEBUG_VALUEInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DEBUG_VALUEInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t DEBUG_VALUEInterpreter<EncodingT>::getClassName() const
{
	return UCS("DEBUG_VALUE");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DEBUG_VALUE"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DEBUG_VALUE, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::geti8() const
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>((char) value().I8));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::geti16() const
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>((short) value().I16));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::geti32() const
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>((int) value().I32));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::geti64() const
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>((long long) value().I64));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::getuI8() const
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>((unsigned char) value().I8));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::getuI16() const
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>((unsigned short) value().I16));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::getuI32() const
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>((unsigned int) value().I32));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::getuI64() const
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>((unsigned long long) value().I64));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::getf32() const
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>(refValue().F32));
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::getf64() const
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>(refValue().F64));
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::getc8() const
{
boost::shared_ptr< Base<EncodingT> > res(new String<EncodingT>((char) value().I8));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::getc16() const
{
boost::shared_ptr< Base<EncodingT> > res(new String<EncodingT>((wchar_t) value().I16));
  return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::gettype() const
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>(refValue().Type));
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DEBUG_VALUEInterpreter<EncodingT>::gettailOfRawBytes() const
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>(refValue().TailOfRawBytes));
	return res;
}


template <class EncodingT>
bool check_DEBUG_VALUE(boost::shared_ptr< Base<EncodingT> > const& val, DEBUG_VALUE& a)
{
	boost::shared_ptr< DEBUG_VALUEInterpreter<EncodingT> > value  = dynamic_pointer_cast< DEBUG_VALUEInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DEBUG_VALUE expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_DEBUG_VALUE(boost::shared_ptr< Base<EncodingT> >& val, DEBUG_VALUE const& a)
{
	boost::shared_ptr< DEBUG_VALUEInterpreter<EncodingT> > value  = dynamic_pointer_cast< DEBUG_VALUEInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "DEBUG_VALUE expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C