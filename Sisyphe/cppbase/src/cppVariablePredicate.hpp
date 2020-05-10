/* 
 * cppVariablePredicate.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPVARIABLE_PREDICATE_HPP_
#define _CPPVARIABLE_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for CppVariable object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _CppVariable<EncodingT>::CppVariableIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find CppVariable object.
	@param identifier 
	*/
	CppVariableIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	CppVariableIDEquality(const _CppVariable<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to find an object with the same element <i>varType</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::VarTypeEquality {
private :
	typename EncodingT::string_t	m_varType;
public :
	/** Creates a new functor allowing to find CppVariable object.
	@param varType 
	*/
	VarTypeEquality(const typename EncodingT::string_t& varType)
	: m_varType(varType)
	{
	}

	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > other) const 
	{
		return (other != NULL && m_varType==other->getVarType());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>varType</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::VarTypeInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getVarType() < elem2->getVarType());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>varType</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::VarTypeSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getVarType() > elem2->getVarType());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to find an object with the same element <i>name</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::NameEquality {
private :
	typename EncodingT::string_t	m_name;
public :
	/** Creates a new functor allowing to find CppVariable object.
	@param name 
	*/
	NameEquality(const typename EncodingT::string_t& name)
	: m_name(name)
	{
	}

	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > other) const 
	{
		return (other != NULL && m_name==other->getName());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::NameInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() < elem2->getName());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::NameSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() > elem2->getName());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to find an object with the same element <i>isStatic</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::IsStaticEquality {
private :
	long long	m_isStatic;
public :
	/** Creates a new functor allowing to find CppVariable object.
	@param isStatic 
	*/
	IsStaticEquality(long long isStatic)
	: m_isStatic(isStatic)
	{
	}

	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > other) const 
	{
		return (other != NULL && m_isStatic==other->getIsStatic());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>isStatic</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::IsStaticInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsStatic() < elem2->getIsStatic());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>isStatic</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::IsStaticSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsStatic() > elem2->getIsStatic());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to find an object with the same element <i>isConst</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::IsConstEquality {
private :
	long long	m_isConst;
public :
	/** Creates a new functor allowing to find CppVariable object.
	@param isConst 
	*/
	IsConstEquality(long long isConst)
	: m_isConst(isConst)
	{
	}

	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > other) const 
	{
		return (other != NULL && m_isConst==other->getIsConst());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>isConst</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::IsConstInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConst() < elem2->getIsConst());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>isConst</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::IsConstSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConst() > elem2->getIsConst());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to find an object with the same element <i>isConstexpr</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::IsConstexprEquality {
private :
	long long	m_isConstexpr;
public :
	/** Creates a new functor allowing to find CppVariable object.
	@param isConstexpr 
	*/
	IsConstexprEquality(long long isConstexpr)
	: m_isConstexpr(isConstexpr)
	{
	}

	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > other) const 
	{
		return (other != NULL && m_isConstexpr==other->getIsConstexpr());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>isConstexpr</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::IsConstexprInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConstexpr() < elem2->getIsConstexpr());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>isConstexpr</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::IsConstexprSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConstexpr() > elem2->getIsConstexpr());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to find an object with the same element <i>lineNumber</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::LineNumberEquality {
private :
	long long	m_lineNumber;
public :
	/** Creates a new functor allowing to find CppVariable object.
	@param lineNumber 
	*/
	LineNumberEquality(long long lineNumber)
	: m_lineNumber(lineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > other) const 
	{
		return (other != NULL && m_lineNumber==other->getLineNumber());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::LineNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() < elem2->getLineNumber());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::LineNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() > elem2->getLineNumber());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to find an object with the same element <i>startBlock</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::StartBlockEquality {
private :
	long long	m_startBlock;
public :
	/** Creates a new functor allowing to find CppVariable object.
	@param startBlock 
	*/
	StartBlockEquality(long long startBlock)
	: m_startBlock(startBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > other) const 
	{
		return (other != NULL && m_startBlock==other->getStartBlock());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>startBlock</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::StartBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartBlock() < elem2->getStartBlock());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>startBlock</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::StartBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartBlock() > elem2->getStartBlock());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to find an object with the same element <i>lengthBlock</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::LengthBlockEquality {
private :
	long long	m_lengthBlock;
public :
	/** Creates a new functor allowing to find CppVariable object.
	@param lengthBlock 
	*/
	LengthBlockEquality(long long lengthBlock)
	: m_lengthBlock(lengthBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > other) const 
	{
		return (other != NULL && m_lengthBlock==other->getLengthBlock());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>lengthBlock</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::LengthBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthBlock() < elem2->getLengthBlock());
	}

};

/// Represents a comparaison class for CppVariable object.
/// This class is used to sort objects by <i>lengthBlock</i>.
template<class EncodingT>
class  _CppVariable<EncodingT>::LengthBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppVariable<EncodingT> > elem1, boost::shared_ptr< _CppVariable<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthBlock() > elem2->getLengthBlock());
	}

};

NAMESPACE_END

#endif
