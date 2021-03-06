/*
 * DebugValueInterpreter_impl.hpp
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
DebugValueInterpreter<EncodingT>::DebugValueInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t DebugValueInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DebugValueInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t DebugValueInterpreter<EncodingT>::getClassName() const
{
	return UCS("DebugValue");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DebugValue"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DebugValue, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_INT8() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_INT8));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_INT16() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_INT16));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_INT32() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_INT32));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_INT64() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_INT64));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_FLOAT32() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_FLOAT32));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_FLOAT64() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_FLOAT64));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_FLOAT80() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_FLOAT80));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_FLOAT82() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_FLOAT82));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_FLOAT128() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_FLOAT128));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_VECTOR64() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_VECTOR64));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DebugValueInterpreter<EncodingT>::getDEBUG_VALUE_VECTOR128() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DEBUG_VALUE_VECTOR128));
}


NAMESPACE_END

#undef A
#undef C