/*
 * IDiaDataSourcePtrInterpreter_impl.hpp
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
class IDiaSessionPtrInterpreter;

template <class EncodingT>
IDiaDataSourcePtrInterpreter<EncodingT>::IDiaDataSourcePtrInterpreter()
{
}

template <class EncodingT>
void IDiaDataSourcePtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
IDiaDataSourcePtrInterpreter<EncodingT>::~IDiaDataSourcePtrInterpreter()
{
	tidyValue();
}

template <class EncodingT>
void IDiaDataSourcePtrInterpreter<EncodingT>::initValue(const IDiaDataSourcePtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDiaDataSourcePtr& IDiaDataSourcePtrInterpreter<EncodingT>::value()
{
	return m_object;
}

template <class EncodingT>
const IDiaDataSourcePtr& IDiaDataSourcePtrInterpreter<EncodingT>::value() const
{
	return m_object;
}

template <class EncodingT>
IDiaDataSourcePtrInterpreter<EncodingT>::IDiaDataSourcePtrInterpreter(const IDiaDataSourcePtr& object)
{
	initValue(object);
}

template <class EncodingT>
IDiaDataSourcePtrInterpreter<EncodingT>::IDiaDataSourcePtrInterpreter(const IDiaDataSourcePtrInterpreter<EncodingT>& rhs)
{
	initValue(rhs.value());
}

template <class EncodingT>
IDiaDataSourcePtrInterpreter<EncodingT>& IDiaDataSourcePtrInterpreter<EncodingT>::operator=(const IDiaDataSourcePtrInterpreter<EncodingT>& rhs)
{
	setValue(rhs.value());
	return *this;
}

template <class EncodingT>
const IDiaDataSourcePtr& IDiaDataSourcePtrInterpreter<EncodingT>::getValue() const
{
	return value();
}

template <class EncodingT>
void IDiaDataSourcePtrInterpreter<EncodingT>::setValue(IDiaDataSourcePtr const& object)
{
	tidyValue();
	initValue(object);
}

template <class EncodingT>
typename EncodingT::string_t IDiaDataSourcePtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaDataSourcePtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDiaDataSourcePtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDiaDataSourcePtrInterpreter<EncodingT>::getClassName() const
{
	return C("IDiaDataSourcePtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaDataSourcePtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("IDiaDataSourcePtr"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in IDiaDataSourcePtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Ouvre et prépare un fichier de base de données du programme (.pdb) comme source de données de débogage.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaDataSourcePtrInterpreter<EncodingT>::loadDataFromPdb(const boost::shared_ptr< Base<EncodingT> >& pdbPath)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	typename EncodingT::string_t nativePdbPath;
	if (check_string<EncodingT>(pdbPath, nativePdbPath))
	{
		res.reset(new Numeric<EncodingT>(value()->loadDataFromPdb(nativePdbPath.c_str())));
	}
	return res;
}

// Ouvre une session pour obtenir des symboles.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaDataSourcePtrInterpreter<EncodingT>::openSession(boost::shared_ptr< Base<EncodingT> >& ppSession)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr nativePpSession;
	if (check_IDiaSessionPtr(ppSession, nativePpSession))
	{
		res.reset(new Numeric<EncodingT>(value()->openSession(&nativePpSession)));
		reset_IDiaSessionPtr(ppSession, nativePpSession);
	}
	return res;
}


template <class EncodingT>
bool check_IDiaDataSourcePtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaDataSourcePtr& a)
{
	boost::shared_ptr< IDiaDataSourcePtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaDataSourcePtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->getValue();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaDataSourcePtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDiaDataSourcePtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaDataSourcePtr const& a)
{
	boost::shared_ptr< IDiaDataSourcePtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaDataSourcePtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaDataSourcePtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C