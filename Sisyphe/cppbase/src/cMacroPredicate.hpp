/* 
 * cMacroPredicate.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CMACRO_PREDICATE_HPP_
#define _CMACRO_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for CMacro object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _CMacro<EncodingT>::CMacroIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find CMacro object.
	@param identifier 
	*/
	CMacroIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	CMacroIDEquality(const _CMacro<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to find an object with the same element <i>name</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::NameEquality {
private :
	typename EncodingT::string_t	m_name;
public :
	/** Creates a new functor allowing to find CMacro object.
	@param name 
	*/
	NameEquality(const typename EncodingT::string_t& name)
	: m_name(name)
	{
	}

	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > other) const 
	{
		return (other != NULL && m_name==other->getName());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::NameInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() < elem2->getName());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::NameSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() > elem2->getName());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to find an object with the same element <i>isConst</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::IsConstEquality {
private :
	long long	m_isConst;
public :
	/** Creates a new functor allowing to find CMacro object.
	@param isConst 
	*/
	IsConstEquality(long long isConst)
	: m_isConst(isConst)
	{
	}

	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > other) const 
	{
		return (other != NULL && m_isConst==other->getIsConst());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>isConst</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::IsConstInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConst() < elem2->getIsConst());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>isConst</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::IsConstSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConst() > elem2->getIsConst());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to find an object with the same element <i>constValue</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::ConstValueEquality {
private :
	typename EncodingT::string_t	m_constValue;
public :
	/** Creates a new functor allowing to find CMacro object.
	@param constValue 
	*/
	ConstValueEquality(const typename EncodingT::string_t& constValue)
	: m_constValue(constValue)
	{
	}

	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > other) const 
	{
		return (other != NULL && m_constValue==other->getConstValue());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>constValue</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::ConstValueInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getConstValue() < elem2->getConstValue());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>constValue</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::ConstValueSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getConstValue() > elem2->getConstValue());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to find an object with the same element <i>lineNumber</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::LineNumberEquality {
private :
	long long	m_lineNumber;
public :
	/** Creates a new functor allowing to find CMacro object.
	@param lineNumber 
	*/
	LineNumberEquality(long long lineNumber)
	: m_lineNumber(lineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > other) const 
	{
		return (other != NULL && m_lineNumber==other->getLineNumber());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::LineNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() < elem2->getLineNumber());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::LineNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() > elem2->getLineNumber());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to find an object with the same element <i>startBlock</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::StartBlockEquality {
private :
	long long	m_startBlock;
public :
	/** Creates a new functor allowing to find CMacro object.
	@param startBlock 
	*/
	StartBlockEquality(long long startBlock)
	: m_startBlock(startBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > other) const 
	{
		return (other != NULL && m_startBlock==other->getStartBlock());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>startBlock</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::StartBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartBlock() < elem2->getStartBlock());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>startBlock</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::StartBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartBlock() > elem2->getStartBlock());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to find an object with the same element <i>lengthBlock</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::LengthBlockEquality {
private :
	long long	m_lengthBlock;
public :
	/** Creates a new functor allowing to find CMacro object.
	@param lengthBlock 
	*/
	LengthBlockEquality(long long lengthBlock)
	: m_lengthBlock(lengthBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > other) const 
	{
		return (other != NULL && m_lengthBlock==other->getLengthBlock());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>lengthBlock</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::LengthBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthBlock() < elem2->getLengthBlock());
	}

};

/// Represents a comparaison class for CMacro object.
/// This class is used to sort objects by <i>lengthBlock</i>.
template<class EncodingT>
class  _CMacro<EncodingT>::LengthBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CMacro<EncodingT> > elem1, boost::shared_ptr< _CMacro<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthBlock() > elem2->getLengthBlock());
	}

};

NAMESPACE_END

#endif
