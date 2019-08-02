/*
 * DiffTypeInterpreter_impl.hpp
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
DiffTypeInterpreter<EncodingT>::DiffTypeInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t DiffTypeInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffTypeInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new DiffTypeInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t DiffTypeInterpreter<EncodingT>::getClassName() const
{
    return UCS("DiffType");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffTypeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
        if (tryInvoke(this, UCS("DiffType"), method, args, ret) ||
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
            logger->errorStream() << "Unexpected call in DiffType, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffTypeInterpreter<EncodingT>::getNONE() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(static_cast<unsigned short>(DIFF_TYPE_NONE)));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffTypeInterpreter<EncodingT>::getADD() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(static_cast<unsigned short>(DIFF_TYPE_ADD)));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffTypeInterpreter<EncodingT>::getDELETE() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(static_cast<unsigned short>(DIFF_TYPE_DELETE)));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffTypeInterpreter<EncodingT>::getMODIFY() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(static_cast<unsigned short>(DIFF_TYPE_MODIFY)));
}

NAMESPACE_END

#undef A
#undef C
