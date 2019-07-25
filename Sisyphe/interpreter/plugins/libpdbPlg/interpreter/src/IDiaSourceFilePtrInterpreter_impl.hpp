/*
 * IDiaSourceFilePtrInterpreter_impl.hpp
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
class IDiaEnumSymbolsPtrInterpreter;

template <class EncodingT>
IDiaSourceFilePtrInterpreter<EncodingT>::IDiaSourceFilePtrInterpreter()
{
}

template <class EncodingT>
void IDiaSourceFilePtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
IDiaSourceFilePtrInterpreter<EncodingT>::~IDiaSourceFilePtrInterpreter()
{
	tidyValue();
}

template <class EncodingT>
void IDiaSourceFilePtrInterpreter<EncodingT>::initValue(const IDiaSourceFilePtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDiaSourceFilePtr& IDiaSourceFilePtrInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const IDiaSourceFilePtr& IDiaSourceFilePtrInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
IDiaSourceFilePtrInterpreter<EncodingT>::IDiaSourceFilePtrInterpreter(const IDiaSourceFilePtr& object)
{
	initValue(object);
}

template <class EncodingT>
IDiaSourceFilePtrInterpreter<EncodingT>::IDiaSourceFilePtrInterpreter(const IDiaSourceFilePtrInterpreter<EncodingT>& rhs)
{
	initValue(rhs.refValue());
}

template <class EncodingT>
IDiaSourceFilePtrInterpreter<EncodingT>& IDiaSourceFilePtrInterpreter<EncodingT>::operator=(const IDiaSourceFilePtrInterpreter<EncodingT>& rhs)
{
	value(rhs.refValue());
	return *this;
}

template <class EncodingT>
const IDiaSourceFilePtr& IDiaSourceFilePtrInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void IDiaSourceFilePtrInterpreter<EncodingT>::value(IDiaSourceFilePtr const& object)
{
	tidyValue();
	initValue(object);
}

template <class EncodingT>
typename EncodingT::string_t IDiaSourceFilePtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSourceFilePtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDiaSourceFilePtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDiaSourceFilePtrInterpreter<EncodingT>::getClassName() const
{
	return C("IDiaSourceFilePtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSourceFilePtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("IDiaSourceFilePtr"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in IDiaSourceFilePtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Récupère les octets de checksum.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSourceFilePtrInterpreter<EncodingT>::get_checksum(boost::shared_ptr< Base<EncodingT> >& cbData, boost::shared_ptr< Base<EncodingT> >& pcbData, boost::shared_ptr< Base<EncodingT> >& data)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSourceFilePtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeCbData;
		unsigned long nativePcbData;
		std::vector< unsigned char > nativeData;
		if (check_numeric_i(cbData, nativeCbData) && 
			check_numeric_i(pcbData, nativePcbData) && 
			check_array(data, nativeData, check_numeric_i<EncodingT, unsigned char>))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_checksum(nativeCbData, &nativePcbData, nativeData.data())));
			reset_numeric_i(cbData, nativeCbData);
			reset_numeric_i(pcbData, nativePcbData);
			reset_array(data, nativeData, reset_numeric_i<EncodingT, unsigned char>);
		}
	}
	return res;
}

// Extrait le nom du fichier source.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSourceFilePtrInterpreter<EncodingT>::get_fileName(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
    IDiaSourceFilePtr valuePtr = value();
    if (valuePtr != NULL)
    {
      BSTR nativePRetVal;
      res.reset(new Numeric<EncodingT>(valuePtr->get_fileName(&nativePRetVal)));
      reset_string<EncodingT>(pRetVal, nativePRetVal);
    }
    return res;
}

// Récupère un énumérateur des compilands qui ont des numéros de ligne référençant ce fichier.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSourceFilePtrInterpreter<EncodingT>::get_compilands(boost::shared_ptr< Base<EncodingT> >& ppRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSourceFilePtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaEnumSymbolsPtr nativePpRetVal;
		if (check_IDiaEnumSymbolsPtr(ppRetVal, nativePpRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_compilands(&nativePpRetVal)));
			reset_IDiaEnumSymbolsPtr(ppRetVal, nativePpRetVal);
		}
	}
	return res;
}


template <class EncodingT>
bool check_IDiaSourceFilePtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaSourceFilePtr& a)
{
	boost::shared_ptr< IDiaSourceFilePtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaSourceFilePtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaSourceFilePtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDiaSourceFilePtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaSourceFilePtr const& a)
{
	boost::shared_ptr< IDiaSourceFilePtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaSourceFilePtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaSourceFilePtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C