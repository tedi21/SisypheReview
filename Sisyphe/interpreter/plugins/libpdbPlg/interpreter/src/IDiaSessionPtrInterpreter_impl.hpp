/*
 * IDiaSessionPtrInterpreter_impl.hpp
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
class IDiaEnumLineNumbersPtrInterpreter;

template <class EncodingT>
class IDiaEnumSourceFilesPtrInterpreter;

template <class EncodingT>
class IDiaSourceFilePtrInterpreter;

template <class EncodingT>
class IDiaSymbolPtrInterpreter;

template <class EncodingT>
IDiaSessionPtrInterpreter<EncodingT>::IDiaSessionPtrInterpreter()
{
}

template <class EncodingT>
void IDiaSessionPtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
IDiaSessionPtrInterpreter<EncodingT>::~IDiaSessionPtrInterpreter()
{
	tidyValue();
}

template <class EncodingT>
void IDiaSessionPtrInterpreter<EncodingT>::initValue(const IDiaSessionPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDiaSessionPtr& IDiaSessionPtrInterpreter<EncodingT>::value()
{
	return m_object;
}

template <class EncodingT>
const IDiaSessionPtr& IDiaSessionPtrInterpreter<EncodingT>::value() const
{
	return m_object;
}

template <class EncodingT>
IDiaSessionPtrInterpreter<EncodingT>::IDiaSessionPtrInterpreter(const IDiaSessionPtr& object)
{
	initValue(object);
}

template <class EncodingT>
IDiaSessionPtrInterpreter<EncodingT>::IDiaSessionPtrInterpreter(const IDiaSessionPtrInterpreter<EncodingT>& rhs)
{
	initValue(rhs.value());
}

template <class EncodingT>
IDiaSessionPtrInterpreter<EncodingT>& IDiaSessionPtrInterpreter<EncodingT>::operator=(const IDiaSessionPtrInterpreter<EncodingT>& rhs)
{
	setValue(rhs.value());
	return *this;
}

template <class EncodingT>
const IDiaSessionPtr& IDiaSessionPtrInterpreter<EncodingT>::getValue() const
{
	return value();
}

template <class EncodingT>
void IDiaSessionPtrInterpreter<EncodingT>::setValue(IDiaSessionPtr const& object)
{
	tidyValue();
	initValue(object);
}

template <class EncodingT>
typename EncodingT::string_t IDiaSessionPtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDiaSessionPtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDiaSessionPtrInterpreter<EncodingT>::getClassName() const
{
	return C("IDiaSessionPtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("IDiaSessionPtr"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in IDiaSessionPtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Extrait une référence de la portée globale.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::get_globalScope(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr nativePRetVal;
	if (check_IDiaSymbolPtr(pRetVal, nativePRetVal))
	{
		res.reset(new Numeric<EncodingT>(value()->get_globalScope(&nativePRetVal)));
		reset_IDiaSymbolPtr(pRetVal, nativePRetVal);
	}
	return res;
}

// Définit l'adresse de charge du fichier exécutable qui correspond aux symboles dans ce magasin de symboles.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::put_loadAddress(const boost::shared_ptr< Base<EncodingT> >& pNewVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	unsigned long long nativePNewVal;
	if (check_numeric(pNewVal, nativePNewVal))
	{
		res.reset(new Numeric<EncodingT>(value()->put_loadAddress(nativePNewVal)));
	}
	return res;
}

// Récupère les lignes d'un module spécifié qui contient une adresse virtuelle relative spécifiée (RVA).
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findLinesByRVA(const boost::shared_ptr< Base<EncodingT> >& rva, const boost::shared_ptr< Base<EncodingT> >& length, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	unsigned long nativeRva;
	unsigned long nativeLength;
	IDiaEnumLineNumbersPtr nativePpResult;
	if (check_numeric(rva, nativeRva) && 
		check_numeric(length, nativeLength) && 
		check_IDiaEnumLineNumbersPtr(ppResult, nativePpResult))
	{
		res.reset(new Numeric<EncodingT>(value()->findLinesByRVA(nativeRva, nativeLength, &nativePpResult)));
		reset_IDiaEnumLineNumbersPtr(ppResult, nativePpResult);
	}
	return res;
}

// Détermine les numéros de ligne du module (compiland) que le numéro de ligne spécifié dans un fichier source se trouve dans ou approche.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findLinesByLinenum(const boost::shared_ptr< Base<EncodingT> >& compiland, const boost::shared_ptr< Base<EncodingT> >& file, const boost::shared_ptr< Base<EncodingT> >& linenum, const boost::shared_ptr< Base<EncodingT> >& column, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr nativeCompiland;
	IDiaSourceFilePtr nativeFile;
	unsigned long nativeLinenum;
	unsigned long nativeColumn;
	IDiaEnumLineNumbersPtr nativePpResult;
	if (check_IDiaSymbolPtr(compiland, nativeCompiland) && 
		check_IDiaSourceFilePtr(file, nativeFile) && 
		check_numeric(linenum, nativeLinenum) && 
		check_numeric(column, nativeColumn) && 
		check_IDiaEnumLineNumbersPtr(ppResult, nativePpResult))
	{
		res.reset(new Numeric<EncodingT>(value()->findLinesByLinenum(nativeCompiland, nativeFile, nativeLinenum, nativeColumn, &nativePpResult)));
		reset_IDiaEnumLineNumbersPtr(ppResult, nativePpResult);
	}
	return res;
}

// Récupère les numéros de ligne dans les ID spécifiés de module (compiland) et du fichier source.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findLines(const boost::shared_ptr< Base<EncodingT> >& compiland, const boost::shared_ptr< Base<EncodingT> >& file, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr nativeCompiland;
	IDiaSourceFilePtr nativeFile;
	IDiaEnumLineNumbersPtr nativePpResult;
	if (check_IDiaSymbolPtr(compiland, nativeCompiland) && 
		check_IDiaSourceFilePtr(file, nativeFile) && 
		check_IDiaEnumLineNumbersPtr(ppResult, nativePpResult))
	{
		res.reset(new Numeric<EncodingT>(value()->findLines(nativeCompiland, nativeFile, &nativePpResult)));
		reset_IDiaEnumLineNumbersPtr(ppResult, nativePpResult);
	}
	return res;
}

// Récupère les fichiers sources par le module et le nom.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findFile(const boost::shared_ptr< Base<EncodingT> >& pCompiland, const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& option, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr nativePCompiland;
	typename EncodingT::string_t nativeName;
	unsigned long nativeOption;
	IDiaEnumSourceFilesPtr nativePpResult;
	if (check_IDiaSymbolPtr(pCompiland, nativePCompiland) && 
		check_string<EncodingT>(name, nativeName) && 
		check_numeric(option, nativeOption) && 
		check_IDiaEnumSourceFilesPtr(ppResult, nativePpResult))
	{
		res.reset(new Numeric<EncodingT>(value()->findFile(nativePCompiland, nativeName.c_str(), nativeOption, &nativePpResult)));
		reset_IDiaEnumSourceFilesPtr(ppResult, nativePpResult);
	}
	return res;
}

// Récupère les fichiers sources par le module.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findFile(const boost::shared_ptr< Base<EncodingT> >& pCompiland, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDiaSymbolPtr nativePCompiland;
	IDiaEnumSourceFilesPtr nativePpResult;
	if (check_IDiaSymbolPtr(pCompiland, nativePCompiland) &&
      check_IDiaEnumSourceFilesPtr(ppResult, nativePpResult))
	{
		res.reset(new Numeric<EncodingT>(value()->findFile(nativePCompiland, NULL, nsNone, &nativePpResult)));
		reset_IDiaEnumSourceFilesPtr(ppResult, nativePpResult);
	}
	return res;
}

// Récupère les fichiers sources par le nom.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findFile(const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& option, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	typename EncodingT::string_t nativeName;
	unsigned long nativeOption;
	IDiaEnumSourceFilesPtr nativePpResult;
	if (check_string<EncodingT>(name, nativeName) && 
		check_numeric(option, nativeOption) && 
		check_IDiaEnumSourceFilesPtr(ppResult, nativePpResult))
	{
		res.reset(new Numeric<EncodingT>(value()->findFile(NULL, nativeName.c_str(), nativeOption, &nativePpResult)));
		reset_IDiaEnumSourceFilesPtr(ppResult, nativePpResult);
	}
	return res;
}

// Récupère tous les fichiers sources.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findFile(boost::shared_ptr< Base<EncodingT> >& ppResult)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaEnumSourceFilesPtr nativePpResult;
	if (check_IDiaEnumSourceFilesPtr(ppResult, nativePpResult))
	{
		res.reset(new Numeric<EncodingT>(value()->findFile(NULL, NULL, nsNone, &nativePpResult)));
		reset_IDiaEnumSourceFilesPtr(ppResult, nativePpResult);
	}
	return res;
}


template <class EncodingT>
bool check_IDiaSessionPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaSessionPtr& a)
{
	boost::shared_ptr< IDiaSessionPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaSessionPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->getValue();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaSessionPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDiaSessionPtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaSessionPtr const& a)
{
	boost::shared_ptr< IDiaSessionPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaSessionPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->setValue(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaSessionPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C