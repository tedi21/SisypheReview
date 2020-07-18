/* 
 * debugFunctionInfoPredicate.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGFUNCTIONINFO_PREDICATE_HPP_
#define _DEBUGFUNCTIONINFO_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find DebugFunctionInfo object.
	@param identifier 
	*/
	DebugFunctionInfoIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	DebugFunctionInfoIDEquality(const _DebugFunctionInfo<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to find an object with the same element <i>name</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::NameEquality {
private :
	typename EncodingT::string_t	m_name;
public :
	/** Creates a new functor allowing to find DebugFunctionInfo object.
	@param name 
	*/
	NameEquality(const typename EncodingT::string_t& name)
	: m_name(name)
	{
	}

	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_name==other->getName());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::NameInferior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() < elem2->getName());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::NameSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() > elem2->getName());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to find an object with the same element <i>firstLineNumber</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::FirstLineNumberEquality {
private :
	long long	m_firstLineNumber;
public :
	/** Creates a new functor allowing to find DebugFunctionInfo object.
	@param firstLineNumber 
	*/
	FirstLineNumberEquality(long long firstLineNumber)
	: m_firstLineNumber(firstLineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_firstLineNumber==other->getFirstLineNumber());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to sort objects by <i>firstLineNumber</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::FirstLineNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getFirstLineNumber() < elem2->getFirstLineNumber());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to sort objects by <i>firstLineNumber</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::FirstLineNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getFirstLineNumber() > elem2->getFirstLineNumber());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to find an object with the same element <i>lastLineNumber</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::LastLineNumberEquality {
private :
	long long	m_lastLineNumber;
public :
	/** Creates a new functor allowing to find DebugFunctionInfo object.
	@param lastLineNumber 
	*/
	LastLineNumberEquality(long long lastLineNumber)
	: m_lastLineNumber(lastLineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_lastLineNumber==other->getLastLineNumber());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to sort objects by <i>lastLineNumber</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::LastLineNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLastLineNumber() < elem2->getLastLineNumber());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to sort objects by <i>lastLineNumber</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::LastLineNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLastLineNumber() > elem2->getLastLineNumber());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to find an object with the same element <i>address</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::AddressEquality {
private :
	long long	m_address;
public :
	/** Creates a new functor allowing to find DebugFunctionInfo object.
	@param address 
	*/
	AddressEquality(long long address)
	: m_address(address)
	{
	}

	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_address==other->getAddress());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to sort objects by <i>address</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::AddressInferior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getAddress() < elem2->getAddress());
	}

};

/// Represents a comparaison class for DebugFunctionInfo object.
/// This class is used to sort objects by <i>address</i>.
template<class EncodingT>
class  _DebugFunctionInfo<EncodingT>::AddressSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getAddress() > elem2->getAddress());
	}

};

NAMESPACE_END

#endif
