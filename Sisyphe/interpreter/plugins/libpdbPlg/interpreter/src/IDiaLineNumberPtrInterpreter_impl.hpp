/*
 * IDiaLineNumberPtrInterpreter_impl.hpp
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
class IDiaSourceFilePtrInterpreter;

template <class EncodingT>
IDiaLineNumberPtrInterpreter<EncodingT>::IDiaLineNumberPtrInterpreter()
{
}

template <class EncodingT>
void IDiaLineNumberPtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
void IDiaLineNumberPtrInterpreter<EncodingT>::initValue(const IDiaLineNumberPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDiaLineNumberPtr& IDiaLineNumberPtrInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const IDiaLineNumberPtr& IDiaLineNumberPtrInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
IDiaLineNumberPtrInterpreter<EncodingT>::IDiaLineNumberPtrInterpreter(const IDiaLineNumberPtr& object)
{
	initValue(object);
}

template <class EncodingT>
const IDiaLineNumberPtr& IDiaLineNumberPtrInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void IDiaLineNumberPtrInterpreter<EncodingT>::value(IDiaLineNumberPtr const& object)
{
	if (&object != &value()) {
		tidyValue();
		initValue(object);
	}
}

template <class EncodingT>
typename EncodingT::string_t IDiaLineNumberPtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDiaLineNumberPtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDiaLineNumberPtrInterpreter<EncodingT>::getClassName() const
{
	return UCS("IDiaLineNumberPtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("IDiaLineNumberPtr"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in IDiaLineNumberPtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Récupère le numéro de ligne dans le fichier source.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_lineNumber(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaLineNumberPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res->LLvalue(valuePtr->get_lineNumber(&nativePRetVal));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le numéro de ligne source de base 1 où l'instruction ou l'expression se termine.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_lineNumberEnd(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaLineNumberPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res->LLvalue(valuePtr->get_lineNumberEnd(&nativePRetVal));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le numéro de colonne où l'expression ou l'instruction commence.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_columnNumber(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaLineNumberPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res->LLvalue(valuePtr->get_columnNumber(&nativePRetVal));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le numéro de colonne source de base 1 où l'expression ou l'instruction se termine.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_columnNumberEnd(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaLineNumberPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res->LLvalue(valuePtr->get_columnNumberEnd(&nativePRetVal));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le nombre d'octets dans un bloc.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_length(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaLineNumberPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res->LLvalue(valuePtr->get_length(&nativePRetVal));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// extrait une balise indiquant que ces informations de ligne décrivent le début d'une instruction, plutôt qu'une expression, dans la source de programme.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_statement(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaLineNumberPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		int nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res->LLvalue(valuePtr->get_statement(&nativePRetVal));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// extrait une référence au fichier source.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_sourceFile(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaLineNumberPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSourceFilePtr nativePRetVal;
		if (check_IDiaSourceFilePtr(pRetVal, nativePRetVal))
		{
			res->LLvalue(valuePtr->get_sourceFile(&nativePRetVal));
			reset_IDiaSourceFilePtr(pRetVal, nativePRetVal);
		}
	}
	return res;
}


template <class EncodingT>
bool check_IDiaLineNumberPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaLineNumberPtr& a)
{
	boost::shared_ptr< IDiaLineNumberPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaLineNumberPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaLineNumberPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDiaLineNumberPtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaLineNumberPtr const& a)
{
	boost::shared_ptr< IDiaLineNumberPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaLineNumberPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaLineNumberPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C