/*
 * IDiaEnumLineNumbersPtrInterpreter_impl.hpp
 *
 *
 * @date 03-09-2016
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
class IDiaLineNumberPtrInterpreter;

template <class EncodingT>
IDiaEnumLineNumbersPtrInterpreter<EncodingT>::IDiaEnumLineNumbersPtrInterpreter()
{
}

template <class EncodingT>
void IDiaEnumLineNumbersPtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
IDiaEnumLineNumbersPtrInterpreter<EncodingT>::~IDiaEnumLineNumbersPtrInterpreter()
{
	tidyValue();
}

template <class EncodingT>
void IDiaEnumLineNumbersPtrInterpreter<EncodingT>::initValue(const IDiaEnumLineNumbersPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDiaEnumLineNumbersPtr& IDiaEnumLineNumbersPtrInterpreter<EncodingT>::value()
{
	return m_object;
}

template <class EncodingT>
const IDiaEnumLineNumbersPtr& IDiaEnumLineNumbersPtrInterpreter<EncodingT>::value() const
{
	return m_object;
}

template <class EncodingT>
IDiaEnumLineNumbersPtrInterpreter<EncodingT>::IDiaEnumLineNumbersPtrInterpreter(const IDiaEnumLineNumbersPtr& object)
{
	initValue(object);
}

template <class EncodingT>
IDiaEnumLineNumbersPtrInterpreter<EncodingT>::IDiaEnumLineNumbersPtrInterpreter(const IDiaEnumLineNumbersPtrInterpreter<EncodingT>& rhs)
{
	initValue(rhs.value());
}

template <class EncodingT>
IDiaEnumLineNumbersPtrInterpreter<EncodingT>& IDiaEnumLineNumbersPtrInterpreter<EncodingT>::operator=(const IDiaEnumLineNumbersPtrInterpreter<EncodingT>& rhs)
{
	setValue(rhs.value());
	return *this;
}

template <class EncodingT>
const IDiaEnumLineNumbersPtr& IDiaEnumLineNumbersPtrInterpreter<EncodingT>::getValue() const
{
	return value();
}

template <class EncodingT>
void IDiaEnumLineNumbersPtrInterpreter<EncodingT>::setValue(IDiaEnumLineNumbersPtr const& object)
{
	tidyValue();
	initValue(object);
}

template <class EncodingT>
typename EncodingT::string_t IDiaEnumLineNumbersPtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumLineNumbersPtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDiaEnumLineNumbersPtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDiaEnumLineNumbersPtrInterpreter<EncodingT>::getClassName() const
{
	return C("IDiaEnumLineNumbersPtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumLineNumbersPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("IDiaEnumLineNumbersPtr"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in IDiaEnumLineNumbersPtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Récupère le nombre de symboles.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumLineNumbersPtrInterpreter<EncodingT>::get_Count(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	long nativePRetVal;
	if (check_numeric(pRetVal, nativePRetVal))
	{
		res.reset(new Numeric<EncodingT>(value()->get_Count(&nativePRetVal)));
		reset_numeric(pRetVal, nativePRetVal);
	}
	return res;
}

// Récupère un symbole au moyen d'un index.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumLineNumbersPtrInterpreter<EncodingT>::item(const boost::shared_ptr< Base<EncodingT> >& index, boost::shared_ptr< Base<EncodingT> >& symbol)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	long nativeIndex;
	IDiaLineNumberPtr nativeSymbol;
	if (check_numeric(index, nativeIndex) && 
		check_IDiaLineNumberPtr(symbol, nativeSymbol))
	{
		res.reset(new Numeric<EncodingT>(value()->Item(nativeIndex, &nativeSymbol)));
		reset_IDiaLineNumberPtr(symbol, nativeSymbol);
	}
	return res;
}

// Récupère un nombre spécifié de symboles dans la séquence d'énumération.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumLineNumbersPtrInterpreter<EncodingT>::next(const boost::shared_ptr< Base<EncodingT> >& celt, boost::shared_ptr< Base<EncodingT> >& rgelt, boost::shared_ptr< Base<EncodingT> >& pceltFetched)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	unsigned long nativeCelt;
	IDiaLineNumberPtr nativeRgelt;
	unsigned long nativePceltFetched;
	if (check_numeric(celt, nativeCelt) && 
		check_IDiaLineNumberPtr(rgelt, nativeRgelt) && 
		check_numeric(pceltFetched, nativePceltFetched))
	{
		res.reset(new Numeric<EncodingT>(value()->Next(nativeCelt, &nativeRgelt, &nativePceltFetched)));
		reset_IDiaLineNumberPtr(rgelt, nativeRgelt);
		reset_numeric(pceltFetched, nativePceltFetched);
	}
	return res;
}

// Ignore un nombre spécifié de symboles dans une séquence d'énumération.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumLineNumbersPtrInterpreter<EncodingT>::skip(const boost::shared_ptr< Base<EncodingT> >& celt)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	unsigned long nativeCelt;
	if (check_numeric(celt, nativeCelt))
	{
		res.reset(new Numeric<EncodingT>(value()->Skip(nativeCelt)));
	}
	return res;
}

// Réinitialise une séquence d'énumération au début.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumLineNumbersPtrInterpreter<EncodingT>::reset()
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	res.reset(new Numeric<EncodingT>(value()->Reset()));
	return res;
}


template <class EncodingT>
bool check_IDiaEnumLineNumbersPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaEnumLineNumbersPtr& a)
{
	boost::shared_ptr< IDiaEnumLineNumbersPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaEnumLineNumbersPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->getValue();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaEnumLineNumbersPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDiaEnumLineNumbersPtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaEnumLineNumbersPtr const& a)
{
	boost::shared_ptr< IDiaEnumLineNumbersPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaEnumLineNumbersPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaEnumLineNumbersPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C