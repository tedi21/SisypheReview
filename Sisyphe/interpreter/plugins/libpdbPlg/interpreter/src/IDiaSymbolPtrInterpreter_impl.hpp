/*
 * IDiaSymbolPtrInterpreter_impl.hpp
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
class SymTagEnumTypeInterpreter;

template <class EncodingT>
IDiaSymbolPtrInterpreter<EncodingT>::IDiaSymbolPtrInterpreter()
{
}

template <class EncodingT>
void IDiaSymbolPtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
IDiaSymbolPtrInterpreter<EncodingT>::~IDiaSymbolPtrInterpreter()
{
	tidyValue();
}

template <class EncodingT>
void IDiaSymbolPtrInterpreter<EncodingT>::initValue(const IDiaSymbolPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDiaSymbolPtr& IDiaSymbolPtrInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const IDiaSymbolPtr& IDiaSymbolPtrInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
IDiaSymbolPtrInterpreter<EncodingT>::IDiaSymbolPtrInterpreter(const IDiaSymbolPtr& object)
{
	initValue(object);
}

template <class EncodingT>
IDiaSymbolPtrInterpreter<EncodingT>::IDiaSymbolPtrInterpreter(const IDiaSymbolPtrInterpreter<EncodingT>& rhs)
{
	initValue(rhs.refValue());
}

template <class EncodingT>
IDiaSymbolPtrInterpreter<EncodingT>& IDiaSymbolPtrInterpreter<EncodingT>::operator=(const IDiaSymbolPtrInterpreter<EncodingT>& rhs)
{
	value(rhs.refValue());
	return *this;
}

template <class EncodingT>
const IDiaSymbolPtr& IDiaSymbolPtrInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void IDiaSymbolPtrInterpreter<EncodingT>::value(IDiaSymbolPtr const& object)
{
	tidyValue();
	initValue(object);
}

template <class EncodingT>
typename EncodingT::string_t IDiaSymbolPtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDiaSymbolPtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDiaSymbolPtrInterpreter<EncodingT>::getClassName() const
{
	return C("IDiaSymbolPtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("IDiaSymbolPtr"), method, args, ret) ||
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
			logger->errorStream() << "Unexpected call in IDiaSymbolPtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Récupère les enfants du symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::findChildren(const boost::shared_ptr< Base<EncodingT> >& symtag, const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& compareFlags, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		SymTagEnumType nativeSymtag;
		typename EncodingT::string_t nativeName;
		long nativeCompareFlags;
		IDiaEnumSymbolsPtr nativePpResult;
		if (check_SymTagEnumType(symtag, nativeSymtag) && 
			check_string<EncodingT>(name, nativeName) && 
			check_numeric_i(compareFlags, nativeCompareFlags) && 
			check_IDiaEnumSymbolsPtr(ppResult, nativePpResult))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->findChildren(nativeSymtag, nativeName.c_str(), nativeCompareFlags, &nativePpResult)));
			reset_IDiaEnumSymbolsPtr(ppResult, nativePpResult);
		}
	}
	return res;
}

// Récupère les enfants du symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::findChildren(const boost::shared_ptr< Base<EncodingT> >& symtag, boost::shared_ptr< Base<EncodingT> >& ppResult)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDiaSymbolPtr valuePtr = value();
  if (valuePtr != NULL)
  {
    SymTagEnumType nativeSymtag;
    IDiaEnumSymbolsPtr nativePpResult;
    if (check_SymTagEnumType(symtag, nativeSymtag) && 
        check_IDiaEnumSymbolsPtr(ppResult, nativePpResult))
    {
      res.reset(new Numeric<EncodingT>(valuePtr->findChildren(nativeSymtag, NULL, nsNone, &nativePpResult)));
      reset_IDiaEnumSymbolsPtr(ppResult, nativePpResult);
    }
  }
	return res;
}

// Extrait le nom du symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_name(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
    IDiaSymbolPtr valuePtr = value();
    if (valuePtr != NULL)
    {
      BSTR nativePRetVal;
      res.reset(new Numeric<EncodingT>(valuePtr->get_name(&nativePRetVal)));
      reset_string<EncodingT>(pRetVal, nativePRetVal);
    }
	  return res;
}

// Extrait le 'undecorated' nom 
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_undecoratedName(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
    IDiaSymbolPtr valuePtr = value();
    if (valuePtr != NULL)
    {
      BSTR nativePRetVal;
      res.reset(new Numeric<EncodingT>(valuePtr->get_undecoratedName(&nativePRetVal)));
      reset_string<EncodingT>(pRetVal, nativePRetVal);
    }
	  return res;
}

// Extrait la partie de section d'un emplacement d'adresse.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_addressSection(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_addressSection(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Extrait la partie d'offset à un emplacement d'adresse.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_addressOffset(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_addressOffset(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Retrieves the location type of a data symbol.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_locationType(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_locationType(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère l'adresse virtuelle relative (RVA) du symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_relativeVirtualAddress(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_relativeVirtualAddress(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le symbole qui représente le type pour ce symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_type(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativePRetVal;
		if (check_IDiaSymbolPtr(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_type(&nativePRetVal)));
			reset_IDiaSymbolPtr(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Extrait une balise qui indique si le type de données défini par l'utilisateur est constante.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_constType(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		int nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_constType(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// extrait la classification variable d'un symbole de données.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_dataKind(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_dataKind(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Extrait une balise qui indique si le type de données défini par l'utilisateur possède un constructeur ou un destructeur.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_constructor(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		int nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_constructor(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le type de base pour ce symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_baseType(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_baseType(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Extrait une balise qui indique si le type de données défini par (UDT) l'utilisateur est volatile.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_volatileType(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		int nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_volatileType(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// extrait une balise qui spécifie si la fonction est virtuelle.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_virtual(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		int nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_virtual(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Extrait une balise qui spécifie si la fonction ou la couche de conversion de code a été marquée comme static.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_isStatic(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		int nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_isStatic(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Spécifie si la variable distribue une valeur de retour.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_isReturnValue(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		int nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_isReturnValue(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le classifieur de type de symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_symTag(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_symTag(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le nombre de bits ou d'octets de mémoire utilisés par l'objet représenté par ce symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_length(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_length(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// extrait une balise qui spécifie si un type pointeur est une référence.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_reference(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		int nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_reference(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le rang (nombre de dimensions) d'un tableau multidimensionnel FORTRAN.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_rank(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_rank(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Extrait la limite inférieure d'une dimension de tableau FORTRAN.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_lowerBound(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativePRetVal;
		if (check_IDiaSymbolPtr(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_lowerBound(&nativePRetVal)));
			reset_IDiaSymbolPtr(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère un symbole représentant la limite supérieure d'une dimension de tableau FORTRAN.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_upperBound(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativePRetVal;
		if (check_IDiaSymbolPtr(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_upperBound(&nativePRetVal)));
			reset_IDiaSymbolPtr(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère la valeur du fabricant d'ordinateurs (OEM) OEM du symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_oemId(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_oemId(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère la valeur (OEM) du symbole de fabricant d'ordinateurs OEM.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_oemSymbolId(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_oemSymbolId(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère un tableau de types de compilateur-détail pour ce symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_types(boost::shared_ptr< Base<EncodingT> >& types)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDiaSymbolPtr valuePtr = value();
  if (valuePtr != NULL)
  {
    std::vector< IDiaSymbolPtr > nativeTypes;
    DWORD count;
    HRESULT hres = valuePtr->get_types(0, &count, NULL);
    if (hres == S_OK) 
    {
      IDiaSymbol** rgpDiaSymbols = (IDiaSymbol**) _alloca(sizeof(IDiaSymbol *) * count);
      hres = valuePtr->get_types(count, &count, rgpDiaSymbols);
      if (hres == S_OK) 
      {
        for (ULONG i = 0; i < count; i++) 
        {
          nativeTypes.push_back(IDiaSymbolPtr(rgpDiaSymbols[i]));
          rgpDiaSymbols[i]->Release();
        }
      }
    }
    res.reset(new Numeric<EncodingT>(hres));
    reset_array(types, nativeTypes, reset_IDiaSymbolPtr<EncodingT>);
  }
	return res;
}

// Récupère les octets de données d'un symbole OEM.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_dataBytes(const boost::shared_ptr< Base<EncodingT> >& cbData, boost::shared_ptr< Base<EncodingT> >& pcbData, boost::shared_ptr< Base<EncodingT> >& data)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeCbData;
		unsigned long nativePcbData;
		std::vector< unsigned char > nativeData;
		if (check_numeric_i(cbData, nativeCbData) && 
			check_numeric_i(pcbData, nativePcbData) && 
			check_array(data, nativeData, check_numeric_i<EncodingT, unsigned char>))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_dataBytes(nativeCbData, &nativePcbData, nativeData.data())));
			reset_numeric_i(pcbData, nativePcbData);
			reset_array(data, nativeData, reset_numeric_i<EncodingT, unsigned char>);
		}
	}
	return res;
}

// Extrait le dossier fichiers divers un type défini par l' (UDT)utilisateur.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_udtKind(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_udtKind(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Retrieves a flag that specifies whether the function has been marked as never returning with the noreturn attribute.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_noReturn(boost::shared_ptr< Base<EncodingT> >& pFlag)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		int nativePFlag;
		if (check_numeric_i(pFlag, nativePFlag))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_noReturn(&nativePFlag)));
			reset_numeric_i(pFlag, nativePFlag);
		}
	}
	return res;
}

// Retrieves the offset of the symbol location. Use when the LocationType is LocIsRegRel or LocIsBitField.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_offset(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_offset(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Extrait une référence au parent lexicale du symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_lexicalParent(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativePRetVal;
		if (check_IDiaSymbolPtr(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_lexicalParent(&nativePRetVal)));
			reset_IDiaSymbolPtr(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Extrait une référence au parent de classe du symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_classParent(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDiaSymbolPtr nativePRetVal;
		if (check_IDiaSymbolPtr(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_classParent(&nativePRetVal)));
			reset_IDiaSymbolPtr(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Extrait l'identificateur unique de symbole.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_symIndexId(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_symIndexId(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}

// Récupère le nombre d'éléments dans une liste ou un tableau.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDiaSymbolPtrInterpreter<EncodingT>::get_count(boost::shared_ptr< Base<EncodingT> >& pRetVal)
{
	boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
	IDiaSymbolPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativePRetVal;
		if (check_numeric_i(pRetVal, nativePRetVal))
		{
			res.reset(new Numeric<EncodingT>(valuePtr->get_count(&nativePRetVal)));
			reset_numeric_i(pRetVal, nativePRetVal);
		}
	}
	return res;
}


template <class EncodingT>
bool check_IDiaSymbolPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaSymbolPtr& a)
{
	boost::shared_ptr< IDiaSymbolPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaSymbolPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaSymbolPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDiaSymbolPtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaSymbolPtr const& a)
{
	boost::shared_ptr< IDiaSymbolPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDiaSymbolPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDiaSymbolPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C