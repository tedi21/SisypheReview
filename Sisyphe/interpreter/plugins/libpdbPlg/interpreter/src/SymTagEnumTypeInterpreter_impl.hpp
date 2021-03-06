/*
 * SymTagEnumTypeInterpreter_impl.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
SymTagEnumTypeInterpreter<EncodingT>::SymTagEnumTypeInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t SymTagEnumTypeInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new SymTagEnumTypeInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t SymTagEnumTypeInterpreter<EncodingT>::getClassName() const
{
	return UCS("SymTagEnumType");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("SymTagEnumType"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in SymTagEnumType, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagNull() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagNull));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagExe() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagExe));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagCompiland() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagCompiland));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagCompilandDetails() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagCompilandDetails));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagCompilandEnv() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagCompilandEnv));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagFunction() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagFunction));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagBlock() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagBlock));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagData() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagData));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagAnnotation() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagAnnotation));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagLabel() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagLabel));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagPublicSymbol() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagPublicSymbol));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagUDT() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagUDT));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagEnum() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagEnum));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagFunctionType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagFunctionType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagPointerType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagPointerType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagArrayType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagArrayType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagBaseType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagBaseType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagTypedef() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagTypedef));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagBaseClass() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagBaseClass));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagFriend() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagFriend));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagFunctionArgType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagFunctionArgType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagFuncDebugStart() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagFuncDebugStart));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagFuncDebugEnd() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagFuncDebugEnd));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagUsingNamespace() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagUsingNamespace));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagVTableShape() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagVTableShape));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagVTable() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagVTable));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagCustom() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagCustom));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagThunk() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagThunk));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagCustomType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagCustomType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagManagedType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagManagedType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagDimension() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagDimension));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagCallSite() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagCallSite));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagInlineSite() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagInlineSite));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagBaseInterface() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagBaseInterface));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagVectorType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagVectorType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagMatrixType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagMatrixType));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > SymTagEnumTypeInterpreter<EncodingT>::getSymTagHLSLType() const
{
	return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(SymTagHLSLType));
}


NAMESPACE_END

NAMESPACE_BEGIN(interp)

template <class EncodingT>
bool check_SymTagEnumType(boost::shared_ptr< Base<EncodingT> > const& val, SymTagEnumType& s)
{
	boost::shared_ptr< Numeric<EncodingT> > value  = dynamic_pointer_cast< Numeric<EncodingT> >(val);
	if (value)
	{
		s = (SymTagEnumType) value->LLvalue();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "Numeric expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C