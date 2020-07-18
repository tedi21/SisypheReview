/*
 * IDiaSessionPtrInterpreter_impl.hpp
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
class IDiaEnumLineNumbersPtrInterpreter;

template <class EncodingT>
class IDiaEnumSourceFilesPtrInterpreter;

template <class EncodingT>
class IDiaEnumSymbolsByAddrPtrInterpreter;

template <class EncodingT>
class IDiaEnumSymbolsPtrInterpreter;

template <class EncodingT>
class IDiaEnumTablesPtrInterpreter;

template <class EncodingT>
class IDiaSourceFilePtrInterpreter;

template <class EncodingT>
class IDiaSymbolPtrInterpreter;

template <class EncodingT>
class SymTagEnumTypeInterpreter;

template <class EncodingT>
IDiaSessionPtrInterpreter<EncodingT>::IDiaSessionPtrInterpreter()
{
}

template <class EncodingT>
void IDiaSessionPtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
void IDiaSessionPtrInterpreter<EncodingT>::initValue(const IDiaSessionPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDiaSessionPtr& IDiaSessionPtrInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const IDiaSessionPtr& IDiaSessionPtrInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
IDiaSessionPtrInterpreter<EncodingT>::IDiaSessionPtrInterpreter(const IDiaSessionPtr& object)
{
	initValue(object);
}

template <class EncodingT>
const IDiaSessionPtr& IDiaSessionPtrInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void IDiaSessionPtrInterpreter<EncodingT>::value(IDiaSessionPtr const& object)
{
	if (&object != &value()) {
		tidyValue();
		initValue(object);
	}
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
	return UCS("IDiaSessionPtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("IDiaSessionPtr"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in IDiaSessionPtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Extrait une référence de la portée globale.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::get_globalScope(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativePRetVal;
		if (check_IDiaSymbolPtr(pRetVal, nativePRetVal))
		{
			res->LLvalue(valuePtr->get_globalScope(&nativePRetVal));
			reset_IDiaSymbolPtr(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Définit l'adresse de charge du fichier exécutable qui correspond aux symboles dans ce magasin de symboles.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::put_loadAddress(const boost::shared_ptr< Base<EncodingT> >& pNewVal)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long long nativePNewVal;
		if (check_numeric_i(pNewVal, nativePNewVal))
		{
			res->LLvalue(valuePtr->put_loadAddress(nativePNewVal));
		}
	}
	return res;
}

// Extrait un énumérateur qui recherche des symboles dans l'ordre de leurs adresses.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::getSymbolsByAddr(boost::shared_ptr< Base<EncodingT> >& ppEnumbyAddr)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaEnumSymbolsByAddrPtr nativePpEnumbyAddr;
		if (check_IDiaEnumSymbolsByAddrPtr(ppEnumbyAddr, nativePpEnumbyAddr))
		{
			res->LLvalue(valuePtr->getSymbolsByAddr(&nativePpEnumbyAddr));
			reset_IDiaEnumSymbolsByAddrPtr(ppEnumbyAddr, nativePpEnumbyAddr);
		}
	}
	return res;
}

// Récupère un énumérateur pour tous les tables contenues dans le magasin de symboles.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::getEnumTables(boost::shared_ptr< Base<EncodingT> >& ppEnumTables)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaEnumTablesPtr nativePpEnumTables;
		if (check_IDiaEnumTablesPtr(ppEnumTables, nativePpEnumTables))
		{
			res->LLvalue(valuePtr->getEnumTables(&nativePpEnumTables));
			reset_IDiaEnumTablesPtr(ppEnumTables, nativePpEnumTables);
		}
	}
	return res;
}

// Récupère un type spécifié de symboles qui contient, ou est le plus proche de, une adresse spécifiée.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findSymbolByAddr(const boost::shared_ptr< Base<EncodingT> >& isect, const boost::shared_ptr< Base<EncodingT> >& offset, const boost::shared_ptr< Base<EncodingT> >& symtag, boost::shared_ptr< Base<EncodingT> >& ppSymbol)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeIsect;
		unsigned long nativeOffset;
		SymTagEnumType nativeSymtag;
		IDiaSymbolPtr nativePpSymbol;
		if (check_numeric_i(isect, nativeIsect) && 
			check_numeric_i(offset, nativeOffset) && 
			check_SymTagEnumType(symtag, nativeSymtag) && 
			check_IDiaSymbolPtr(ppSymbol, nativePpSymbol))
		{
			res->LLvalue(valuePtr->findSymbolByAddr(nativeIsect, nativeOffset, nativeSymtag, &nativePpSymbol));
			reset_IDiaSymbolPtr(ppSymbol, nativePpSymbol);
		}
	}
	return res;
}

// Récupère un type spécifié de symboles qui contient, ou est le plus proche de, une adresse virtuelle relative spécifiée (RVA).
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findSymbolByRVA(const boost::shared_ptr< Base<EncodingT> >& rva, const boost::shared_ptr< Base<EncodingT> >& symtag, boost::shared_ptr< Base<EncodingT> >& ppSymbol)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeRva;
		SymTagEnumType nativeSymtag;
		IDiaSymbolPtr nativePpSymbol;
		if (check_numeric_i(rva, nativeRva) && 
			check_SymTagEnumType(symtag, nativeSymtag) && 
			check_IDiaSymbolPtr(ppSymbol, nativePpSymbol))
		{
			res->LLvalue(valuePtr->findSymbolByRVA(nativeRva, nativeSymtag, &nativePpSymbol));
			reset_IDiaSymbolPtr(ppSymbol, nativePpSymbol);
		}
	}
	return res;
}

// Récupère un symbole par son identificateur unique.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::symbolById(const boost::shared_ptr< Base<EncodingT> >& identifier, boost::shared_ptr< Base<EncodingT> >& ppSymbol)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeIdentifier;
		IDiaSymbolPtr nativePpSymbol;
		if (check_numeric_i(identifier, nativeIdentifier) && 
			check_IDiaSymbolPtr(ppSymbol, nativePpSymbol))
		{
			res->LLvalue(valuePtr->symbolById(nativeIdentifier, &nativePpSymbol));
			reset_IDiaSymbolPtr(ppSymbol, nativePpSymbol);
		}
	}
	return res;
}

// Vérifie si deux symboles sont équivalents.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::symsAreEquiv(const boost::shared_ptr< Base<EncodingT> >& symbolA, const boost::shared_ptr< Base<EncodingT> >& symbolB)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativeSymbolA;
		IDiaSymbolPtr nativeSymbolB;
		if (check_IDiaSymbolPtr(symbolA, nativeSymbolA) && 
			check_IDiaSymbolPtr(symbolB, nativeSymbolB))
		{
			res->LLvalue(valuePtr->symsAreEquiv(nativeSymbolA, nativeSymbolB));
		}
	}
	return res;
}

// Récupère les lignes d'un module spécifié qui contient une adresse virtuelle relative spécifiée (RVA).
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findLinesByRVA(const boost::shared_ptr< Base<EncodingT> >& rva, const boost::shared_ptr< Base<EncodingT> >& length, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeRva;
		unsigned long nativeLength;
		IDiaEnumLineNumbersPtr nativePpResult;
		if (check_numeric_i(rva, nativeRva) && 
			check_numeric_i(length, nativeLength) && 
			check_IDiaEnumLineNumbersPtr(ppResult, nativePpResult))
		{
			res->LLvalue(valuePtr->findLinesByRVA(nativeRva, nativeLength, &nativePpResult));
			reset_IDiaEnumLineNumbersPtr(ppResult, nativePpResult);
		}
	}
	return res;
}

// Retrieves the lines in a specified compiland that contain a specified address.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findLinesByAddr(const boost::shared_ptr< Base<EncodingT> >& seg, const boost::shared_ptr< Base<EncodingT> >& offset, const boost::shared_ptr< Base<EncodingT> >& length, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeSeg;
		unsigned long nativeOffset;
		unsigned long nativeLength;
		IDiaEnumLineNumbersPtr nativePpResult;
		if (check_numeric_i(seg, nativeSeg) && 
			check_numeric_i(offset, nativeOffset) && 
			check_numeric_i(length, nativeLength) && 
			check_IDiaEnumLineNumbersPtr(ppResult, nativePpResult))
		{
			res->LLvalue(valuePtr->findLinesByAddr(nativeSeg, nativeOffset, nativeLength, &nativePpResult));
			reset_IDiaEnumLineNumbersPtr(ppResult, nativePpResult);
		}
	}
	return res;
}

// Détermine les numéros de ligne du module (compiland) que le numéro de ligne spécifié dans un fichier source se trouve dans ou approche.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findLinesByLinenum(const boost::shared_ptr< Base<EncodingT> >& compiland, const boost::shared_ptr< Base<EncodingT> >& file, const boost::shared_ptr< Base<EncodingT> >& linenum, const boost::shared_ptr< Base<EncodingT> >& column, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativeCompiland;
		IDiaSourceFilePtr nativeFile;
		unsigned long nativeLinenum;
		unsigned long nativeColumn;
		IDiaEnumLineNumbersPtr nativePpResult;
		if (check_IDiaSymbolPtr(compiland, nativeCompiland) && 
			check_IDiaSourceFilePtr(file, nativeFile) && 
			check_numeric_i(linenum, nativeLinenum) && 
			check_numeric_i(column, nativeColumn) && 
			check_IDiaEnumLineNumbersPtr(ppResult, nativePpResult))
		{
			res->LLvalue(valuePtr->findLinesByLinenum(nativeCompiland, nativeFile, nativeLinenum, nativeColumn, &nativePpResult));
			reset_IDiaEnumLineNumbersPtr(ppResult, nativePpResult);
		}
	}
	return res;
}

// Récupère les numéros de ligne dans les ID spécifiés de module (compiland) et du fichier source.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findLines(const boost::shared_ptr< Base<EncodingT> >& compiland, const boost::shared_ptr< Base<EncodingT> >& file, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativeCompiland;
		IDiaSourceFilePtr nativeFile;
		IDiaEnumLineNumbersPtr nativePpResult;
		if (check_IDiaSymbolPtr(compiland, nativeCompiland) && 
			check_IDiaSourceFilePtr(file, nativeFile) && 
			check_IDiaEnumLineNumbersPtr(ppResult, nativePpResult))
		{
			res->LLvalue(valuePtr->findLines(nativeCompiland, nativeFile, &nativePpResult));
			reset_IDiaEnumLineNumbersPtr(ppResult, nativePpResult);
		}
	}
	return res;
}

// Récupère les fichiers sources par le module et le nom.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findFile(const boost::shared_ptr< Base<EncodingT> >& pCompiland, const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& option, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativePCompiland;
		typename EncodingT::string_t nativeName;
		unsigned long nativeOption;
		IDiaEnumSourceFilesPtr nativePpResult;
		if (check_IDiaSymbolPtr(pCompiland, nativePCompiland) && 
			check_string<EncodingT>(name, nativeName) && 
			check_numeric_i(option, nativeOption) && 
			check_IDiaEnumSourceFilesPtr(ppResult, nativePpResult))
		{
			res->LLvalue(valuePtr->findFile(nativePCompiland, nativeName.c_str(), nativeOption, &nativePpResult));
			reset_IDiaEnumSourceFilesPtr(ppResult, nativePpResult);
		}
	}
	return res;
}

// Récupère les fichiers sources par le module.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findFile(const boost::shared_ptr< Base<EncodingT> >& pCompiland, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDiaSessionPtr valuePtr = value();
	if (valuePtr != NULL)
	{
    IDiaSymbolPtr nativePCompiland;
    IDiaEnumSourceFilesPtr nativePpResult;
    if (check_IDiaSymbolPtr(pCompiland, nativePCompiland) &&
        check_IDiaEnumSourceFilesPtr(ppResult, nativePpResult))
    {
      res.reset(new Numeric<EncodingT>(valuePtr->findFile(nativePCompiland, NULL, nsNone, &nativePpResult)));
      reset_IDiaEnumSourceFilesPtr(ppResult, nativePpResult);
    }
  }
	return res;
}

// Récupère les fichiers sources par le nom.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findFile(const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& option, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDiaSessionPtr valuePtr = value();
  if (valuePtr != NULL)
	{
    typename EncodingT::string_t nativeName;
    unsigned long nativeOption;
    IDiaEnumSourceFilesPtr nativePpResult;
    if (check_string<EncodingT>(name, nativeName) && 
      check_numeric_i(option, nativeOption) && 
      check_IDiaEnumSourceFilesPtr(ppResult, nativePpResult))
    {
      res.reset(new Numeric<EncodingT>(valuePtr->findFile(NULL, nativeName.c_str(), nativeOption, &nativePpResult)));
      reset_IDiaEnumSourceFilesPtr(ppResult, nativePpResult);
    }
  }
	return res;
}

// Récupère tous les fichiers sources.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findFile(boost::shared_ptr< Base<EncodingT> >& ppResult)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDiaSessionPtr valuePtr = value();
  if (valuePtr != NULL)
	{
    IDiaEnumSourceFilesPtr nativePpResult;
    if (check_IDiaEnumSourceFilesPtr(ppResult, nativePpResult))
    {
      res.reset(new Numeric<EncodingT>(valuePtr->findFile(NULL, NULL, nsNone, &nativePpResult)));
      reset_IDiaEnumSourceFilesPtr(ppResult, nativePpResult);
    }
  }
	return res;
}

// Récupère tous les enfants d'un identificateur parent spécifié qui correspondent au nom et le type de symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findChildren(const boost::shared_ptr< Base<EncodingT> >& parent, const boost::shared_ptr< Base<EncodingT> >& symtag, const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& compareFlags, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSessionPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativeParent;
		SymTagEnumType nativeSymtag;
		typename EncodingT::string_t nativeName;
		long nativeCompareFlags;
		IDiaEnumSymbolsPtr nativePpResult;
		if (check_IDiaSymbolPtr(parent, nativeParent) && 
			check_SymTagEnumType(symtag, nativeSymtag) && 
			check_string<EncodingT>(name, nativeName) && 
			check_numeric_i(compareFlags, nativeCompareFlags) && 
			check_IDiaEnumSymbolsPtr(ppResult, nativePpResult))
		{
			res->LLvalue(valuePtr->findChildren(nativeParent, nativeSymtag, nativeName.c_str(), nativeCompareFlags, &nativePpResult));
			reset_IDiaEnumSymbolsPtr(ppResult, nativePpResult);
		}
	}
	return res;
}

// Récupère tous les enfants d'un identificateur parent spécifié qui correspondent au nom et le type de symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSessionPtrInterpreter<EncodingT>::findChildren(const boost::shared_ptr< Base<EncodingT> >& parent, const boost::shared_ptr< Base<EncodingT> >& symtag, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDiaSessionPtr valuePtr = value();
  if (valuePtr != NULL)
  {
    IDiaSymbolPtr nativeParent;
    SymTagEnumType nativeSymtag;
    IDiaEnumSymbolsPtr nativePpResult;
    if (check_IDiaSymbolPtr(parent, nativeParent) &&
        check_SymTagEnumType(symtag, nativeSymtag) && 
        check_IDiaEnumSymbolsPtr(ppResult, nativePpResult))
    {
      res.reset(new Numeric<EncodingT>(valuePtr->findChildren(nativeParent, nativeSymtag, NULL, nsNone, &nativePpResult)));
      reset_IDiaEnumSymbolsPtr(ppResult, nativePpResult);
    }
  }
	return res;
}


template <class EncodingT>
bool check_IDiaSessionPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaSessionPtr& a)
{
	boost::shared_ptr< IDiaSessionPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaSessionPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
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
		value->value(a);
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