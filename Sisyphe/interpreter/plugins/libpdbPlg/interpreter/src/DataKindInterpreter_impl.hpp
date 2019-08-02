/*
 * DataKindInterpreter_impl.hpp
 *
 *
 * @date 02-08-2019
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
DataKindInterpreter<EncodingT>::DataKindInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t DataKindInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new DataKindInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t DataKindInterpreter<EncodingT>::getClassName() const
{
	return UCS("DataKind");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("DataKind"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in DataKind, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsUnknown() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsUnknown));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsLocal() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsLocal));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsStaticLocal() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsStaticLocal));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsParam() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsParam));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsObjectPtr() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsObjectPtr));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsFileStatic() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsFileStatic));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsGlobal() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsGlobal));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsMember() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsMember));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsStaticMember() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsStaticMember));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataKindInterpreter<EncodingT>::getDataIsConstant() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(DataIsConstant));
}


NAMESPACE_END

#undef A
#undef C