/*
 * TimeOutInterpreter_impl.hpp
 *
 *
 * @date 24-09-2016
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
TimeOutInterpreter<EncodingT>::TimeOutInterpreter()
{
}

template <class EncodingT>
void TimeOutInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
TimeOutInterpreter<EncodingT>::~TimeOutInterpreter()
{
	tidyValue();
}

template <class EncodingT>
typename EncodingT::string_t TimeOutInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TimeOutInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new TimeOutInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t TimeOutInterpreter<EncodingT>::getClassName() const
{
	return C("TimeOut");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TimeOutInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("TimeOut"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in TimeOut, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > TimeOutInterpreter<EncodingT>::getINFINITE() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(INFINITE));
}


NAMESPACE_END

#undef A
#undef C