/*
 * IDiaLineNumberPtrInterpreter_impl.hpp
 *
 *
 * @date 21-06-2016
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
IDiaLineNumberPtrInterpreter<EncodingT>::~IDiaLineNumberPtrInterpreter()
{
	tidyValue();
}

template <class EncodingT>
void IDiaLineNumberPtrInterpreter<EncodingT>::initValue(const IDiaLineNumberPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDiaLineNumberPtr& IDiaLineNumberPtrInterpreter<EncodingT>::value()
{
	return m_object;
}

template <class EncodingT>
const IDiaLineNumberPtr& IDiaLineNumberPtrInterpreter<EncodingT>::value() const
{
	return m_object;
}

template <class EncodingT>
IDiaLineNumberPtrInterpreter<EncodingT>::IDiaLineNumberPtrInterpreter(const IDiaLineNumberPtr& object)
{
	initValue(object);
}

template <class EncodingT>
IDiaLineNumberPtrInterpreter<EncodingT>::IDiaLineNumberPtrInterpreter(const IDiaLineNumberPtrInterpreter<EncodingT>& rhs)
{
	initValue(rhs.value());
}

template <class EncodingT>
IDiaLineNumberPtrInterpreter<EncodingT>& IDiaLineNumberPtrInterpreter<EncodingT>::operator=(const IDiaLineNumberPtrInterpreter<EncodingT>& rhs)
{
	setValue(rhs.value());
	return *this;
}

template <class EncodingT>
const IDiaLineNumberPtr& IDiaLineNumberPtrInterpreter<EncodingT>::getValue() const
{
	return value();
}

template <class EncodingT>
void IDiaLineNumberPtrInterpreter<EncodingT>::setValue(IDiaLineNumberPtr const& object)
{
	tidyValue();
	initValue(object);
}

template <class EncodingT>
typename EncodingT::string_t IDiaLineNumberPtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new IDiaLineNumberPtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDiaLineNumberPtrInterpreter<EncodingT>::getClassName() const
{
	return C("IDiaLineNumberPtr");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("IDiaLineNumberPtr"), method, args, ret))
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
shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_lineNumber(shared_ptr< Base<EncodingT> >& pRetVal)
{
	shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	unsigned long nativePRetVal;
	if (check_numeric(pRetVal, nativePRetVal))
	{
		res.reset(new Numeric<EncodingT>(value()->get_lineNumber(&nativePRetVal)));
		reset_numeric(pRetVal, nativePRetVal);
	}
	return res;
}

// Récupère le numéro de ligne source de base 1 où l'instruction ou l'expression se termine.
template <class EncodingT>
shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_lineNumberEnd(shared_ptr< Base<EncodingT> >& pRetVal)
{
	shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	unsigned long nativePRetVal;
	if (check_numeric(pRetVal, nativePRetVal))
	{
		res.reset(new Numeric<EncodingT>(value()->get_lineNumberEnd(&nativePRetVal)));
		reset_numeric(pRetVal, nativePRetVal);
	}
	return res;
}

// Récupère le numéro de colonne où l'expression ou l'instruction commence.
template <class EncodingT>
shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_columnNumber(shared_ptr< Base<EncodingT> >& pRetVal)
{
	shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	unsigned long nativePRetVal;
	if (check_numeric(pRetVal, nativePRetVal))
	{
		res.reset(new Numeric<EncodingT>(value()->get_columnNumber(&nativePRetVal)));
		reset_numeric(pRetVal, nativePRetVal);
	}
	return res;
}

// Récupère le numéro de colonne source de base 1 où l'expression ou l'instruction se termine.
template <class EncodingT>
shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_columnNumberEnd(shared_ptr< Base<EncodingT> >& pRetVal)
{
	shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	unsigned long nativePRetVal;
	if (check_numeric(pRetVal, nativePRetVal))
	{
		res.reset(new Numeric<EncodingT>(value()->get_columnNumberEnd(&nativePRetVal)));
		reset_numeric(pRetVal, nativePRetVal);
	}
	return res;
}

// Récupère le nombre d'octets dans un bloc.
template <class EncodingT>
shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_length(shared_ptr< Base<EncodingT> >& pRetVal)
{
	shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	unsigned long nativePRetVal;
	if (check_numeric(pRetVal, nativePRetVal))
	{
		res.reset(new Numeric<EncodingT>(value()->get_length(&nativePRetVal)));
		reset_numeric(pRetVal, nativePRetVal);
	}
	return res;
}

// extrait une balise indiquant que ces informations de ligne décrivent le début d'une instruction, plutôt qu'une expression, dans la source de programme.
template <class EncodingT>
shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_statement(shared_ptr< Base<EncodingT> >& pRetVal)
{
	shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	int nativePRetVal;
	if (check_numeric(pRetVal, nativePRetVal))
	{
		res.reset(new Numeric<EncodingT>(value()->get_statement(&nativePRetVal)));
		reset_numeric(pRetVal, nativePRetVal);
	}
	return res;
}

// extrait une référence au fichier source.
template <class EncodingT>
shared_ptr< Base<EncodingT> > IDiaLineNumberPtrInterpreter<EncodingT>::get_sourceFile(shared_ptr< Base<EncodingT> >& pRetVal)
{
	shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSourceFilePtr nativePRetVal;
	if (check_IDiaSourceFilePtr(pRetVal, nativePRetVal))
	{
		res.reset(new Numeric<EncodingT>(value()->get_sourceFile(&nativePRetVal)));
		reset_IDiaSourceFilePtr(pRetVal, nativePRetVal);
	}
	return res;
}


template <class EncodingT>
bool check_IDiaLineNumberPtr(shared_ptr< Base<EncodingT> > const& val, IDiaLineNumberPtr& a)
{
	shared_ptr< IDiaLineNumberPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaLineNumberPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->getValue();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaLineNumberPtr expected, got " << A(val->getClassName());
	}
	return value;
}

template <class EncodingT>
bool reset_IDiaLineNumberPtr(shared_ptr< Base<EncodingT> >& val, IDiaLineNumberPtr const& a)
{
	shared_ptr< IDiaLineNumberPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaLineNumberPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaLineNumberPtr expected, got " << A(val->getClassName());
	}
	return value;
}

NAMESPACE_END

#undef A
#undef C