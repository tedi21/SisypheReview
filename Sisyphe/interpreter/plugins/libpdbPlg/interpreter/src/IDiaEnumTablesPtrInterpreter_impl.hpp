/*
 * IDiaEnumTablesPtrInterpreter_impl.hpp
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
class IDiaTablePtrInterpreter;

template <class EncodingT>
IDiaEnumTablesPtrInterpreter<EncodingT>::IDiaEnumTablesPtrInterpreter()
{
}

template <class EncodingT>
void IDiaEnumTablesPtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
void IDiaEnumTablesPtrInterpreter<EncodingT>::initValue(const IDiaEnumTablesPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDiaEnumTablesPtr& IDiaEnumTablesPtrInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const IDiaEnumTablesPtr& IDiaEnumTablesPtrInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
IDiaEnumTablesPtrInterpreter<EncodingT>::IDiaEnumTablesPtrInterpreter(const IDiaEnumTablesPtr& object)
{
	initValue(object);
}

template <class EncodingT>
const IDiaEnumTablesPtr& IDiaEnumTablesPtrInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void IDiaEnumTablesPtrInterpreter<EncodingT>::value(IDiaEnumTablesPtr const& object)
{
	if (&object != &value()) {
		tidyValue();
		initValue(object);
	}
}

template <class EncodingT>
typename EncodingT::string_t IDiaEnumTablesPtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumTablesPtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDiaEnumTablesPtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDiaEnumTablesPtrInterpreter<EncodingT>::getClassName() const
{
	return UCS("IDiaEnumTablesPtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumTablesPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("IDiaEnumTablesPtr"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in IDiaEnumTablesPtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Récupère le nombre de tables.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumTablesPtrInterpreter<EncodingT>::get_Count(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaEnumTablesPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_Count(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère une table à l'aide d'un index ou d'une étiquette.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumTablesPtrInterpreter<EncodingT>::itemByIndex(const boost::shared_ptr< Base<EncodingT> >& index, boost::shared_ptr< Base<EncodingT> >& table)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaEnumTablesPtr valuePtr = value();
	if (valuePtr != NULL)
	{ 
		IDiaTablePtr nativeTable;
		long nativeIndex;
		if (check_numeric_i(index, nativeIndex) &&
        check_IDiaTablePtr(table, nativeTable))
		{
      VARIANT var;  
      var.vt = VT_I4;  
      var.lVal = nativeIndex; 
			res.reset(new Numeric<EncodingT>(valuePtr->Item(var, &nativeTable)));
			reset_IDiaTablePtr(table, nativeTable);
      VariantClear(&var);
		}
	}
	return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumTablesPtrInterpreter<EncodingT>::itemByName(const boost::shared_ptr< Base<EncodingT> >& label, boost::shared_ptr< Base<EncodingT> >& table)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaEnumTablesPtr valuePtr = value();
	if (valuePtr != NULL)
	{
		IDiaTablePtr nativeTable;
		typename EncodingT::string_t nativeLabel;
		if (check_string<EncodingT>(label, nativeLabel) &&
        check_IDiaTablePtr(table, nativeTable))
		{
      VARIANT var;  
      var.vt = VT_BSTR;  
      var.bstrVal = SysAllocString(nativeLabel.c_str());  
			res.reset(new Numeric<EncodingT>(valuePtr->Item(var, &nativeTable)));
			reset_IDiaTablePtr(table, nativeTable);
      VariantClear(&var);
		}
	}
	return res;
}

// Récupère un nombre spécifié de tables dans la séquence d'énumération.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumTablesPtrInterpreter<EncodingT>::next(const boost::shared_ptr< Base<EncodingT> >& celt, boost::shared_ptr< Base<EncodingT> >& rgelt, boost::shared_ptr< Base<EncodingT> >& pceltFetched)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaEnumTablesPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeCelt;
		IDiaTablePtr nativeRgelt;
		unsigned long nativePceltFetched;
		if (check_numeric_i(celt, nativeCelt) && 
			check_IDiaTablePtr(rgelt, nativeRgelt) && 
			check_numeric_i(pceltFetched, nativePceltFetched))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->Next(nativeCelt, &nativeRgelt, &nativePceltFetched)));
			reset_IDiaTablePtr(rgelt, nativeRgelt);
			reset_numeric_i(pceltFetched, nativePceltFetched);
		}
	}
	return res;
}

// Ignore un nombre spécifié de tables dans une séquence d'énumération.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumTablesPtrInterpreter<EncodingT>::skip(const boost::shared_ptr< Base<EncodingT> >& celt)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaEnumTablesPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeCelt;
		if (check_numeric_i(celt, nativeCelt))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->Skip(nativeCelt)));
		}
	}
	return res;
}

// Réinitialise une séquence d'énumération au début.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaEnumTablesPtrInterpreter<EncodingT>::reset()
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaEnumTablesPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		res.reset(new Numeric<EncodingT>(valuePtr->Reset()));
	}
	return res;
}


template <class EncodingT>
bool check_IDiaEnumTablesPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaEnumTablesPtr& a)
{
	boost::shared_ptr< IDiaEnumTablesPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaEnumTablesPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaEnumTablesPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDiaEnumTablesPtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaEnumTablesPtr const& a)
{
	boost::shared_ptr< IDiaEnumTablesPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaEnumTablesPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaEnumTablesPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C