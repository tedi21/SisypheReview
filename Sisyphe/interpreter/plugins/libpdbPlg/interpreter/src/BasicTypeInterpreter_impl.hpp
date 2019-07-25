/*
 * BasicTypeInterpreter_impl.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
BasicTypeInterpreter<EncodingT>::BasicTypeInterpreter()
{
}

template <class EncodingT>
void BasicTypeInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
BasicTypeInterpreter<EncodingT>::~BasicTypeInterpreter()
{
	tidyValue();
}

template <class EncodingT>
typename EncodingT::string_t BasicTypeInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new BasicTypeInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t BasicTypeInterpreter<EncodingT>::getClassName() const
{
	return C("BasicType");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("BasicType"), method, args, ret) ||
			tryInvoke(this, C("Base"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in BasicType, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtNoType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btNoType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtVoid() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btVoid));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtChar() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btChar));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtWChar() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btWChar));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtInt() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btInt));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtUInt() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btUInt));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtFloat() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btFloat));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtBCD() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btBCD));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtBool() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btBool));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtLong() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btLong));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtULong() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btULong));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtCurrency() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btCurrency));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtDate() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btDate));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtVariant() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btVariant));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtComplex() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btComplex));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtBit() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btBit));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtBSTR() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btBSTR));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > BasicTypeInterpreter<EncodingT>::getBtHresult() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(btHresult));
}


NAMESPACE_END

#undef A
#undef C