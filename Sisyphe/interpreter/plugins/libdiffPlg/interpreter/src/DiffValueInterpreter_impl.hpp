/*
 * DiffValueInterpreter_impl.hpp
 *
 *
 * @date 07-10-2017
 * @author Teddy DIDE
 * @version 1.00
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
DiffValueInterpreter<EncodingT>::DiffValueInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t DiffValueInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffValueInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new DiffValueInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t DiffValueInterpreter<EncodingT>::getClassName() const
{
    return C("DiffValue");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffValueInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
        if (tryInvoke(this, C("DiffValue"), method, args, ret) ||
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
            logger->errorStream() << "Unexpected call in DiffValue, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffValueInterpreter<EncodingT>::getType() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(static_cast<unsigned short>(Type)));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffValueInterpreter<EncodingT>::getIndex1() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(Index1));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffValueInterpreter<EncodingT>::getIndex2() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(Index2));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffValueInterpreter<EncodingT>::getItem1() const
{
    return Item1;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffValueInterpreter<EncodingT>::getItem2() const
{
    return Item2;
}


NAMESPACE_END

#undef A
#undef C
