/* 
 * cppEnumPredicate.hpp
 *
 *
 * @date 28-08-2016
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPENUM_PREDICATE_HPP_
#define _CPPENUM_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for CppEnum object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _CppEnum<EncodingT>::CppEnumIDEquality {
private :
	int	m_identifier;
public :
	/** Creates a new functor allowing to find CppEnum object.
	@param identifier 
	*/
	CppEnumIDEquality(int identifier)
	: m_identifier(identifier)
	{
	}

	CppEnumIDEquality(const _CppEnum<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to find an object with the same element <i>name</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::NameEquality {
private :
	typename EncodingT::string_t	m_name;
public :
	/** Creates a new functor allowing to find CppEnum object.
	@param name 
	*/
	NameEquality(const typename EncodingT::string_t& name)
	: m_name(name)
	{
	}

	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > other) const 
	{
		return (other != NULL && m_name==other->getName());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::NameInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > elem1, boost::shared_ptr< _CppEnum<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() < elem2->getName());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::NameSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > elem1, boost::shared_ptr< _CppEnum<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() > elem2->getName());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to find an object with the same element <i>lineNumber</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::LineNumberEquality {
private :
	int	m_lineNumber;
public :
	/** Creates a new functor allowing to find CppEnum object.
	@param lineNumber 
	*/
	LineNumberEquality(int lineNumber)
	: m_lineNumber(lineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > other) const 
	{
		return (other != NULL && m_lineNumber==other->getLineNumber());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::LineNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > elem1, boost::shared_ptr< _CppEnum<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() < elem2->getLineNumber());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::LineNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > elem1, boost::shared_ptr< _CppEnum<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() > elem2->getLineNumber());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to find an object with the same element <i>startBlock</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::StartBlockEquality {
private :
	int	m_startBlock;
public :
	/** Creates a new functor allowing to find CppEnum object.
	@param startBlock 
	*/
	StartBlockEquality(int startBlock)
	: m_startBlock(startBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > other) const 
	{
		return (other != NULL && m_startBlock==other->getStartBlock());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to sort objects by <i>startBlock</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::StartBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > elem1, boost::shared_ptr< _CppEnum<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartBlock() < elem2->getStartBlock());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to sort objects by <i>startBlock</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::StartBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > elem1, boost::shared_ptr< _CppEnum<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartBlock() > elem2->getStartBlock());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to find an object with the same element <i>lengthBlock</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::LengthBlockEquality {
private :
	int	m_lengthBlock;
public :
	/** Creates a new functor allowing to find CppEnum object.
	@param lengthBlock 
	*/
	LengthBlockEquality(int lengthBlock)
	: m_lengthBlock(lengthBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > other) const 
	{
		return (other != NULL && m_lengthBlock==other->getLengthBlock());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to sort objects by <i>lengthBlock</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::LengthBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > elem1, boost::shared_ptr< _CppEnum<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthBlock() < elem2->getLengthBlock());
	}

};

/// Represents a comparaison class for CppEnum object.
/// This class is used to sort objects by <i>lengthBlock</i>.
template<class EncodingT>
class  _CppEnum<EncodingT>::LengthBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppEnum<EncodingT> > elem1, boost::shared_ptr< _CppEnum<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthBlock() > elem2->getLengthBlock());
	}

};

NAMESPACE_END

#endif
