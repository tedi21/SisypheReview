/* 
 * cppFunctionPredicate.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPFUNCTION_PREDICATE_HPP_
#define _CPPFUNCTION_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _CppFunction<EncodingT>::CppFunctionIDEquality {
private :
	int	m_identifier;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param identifier 
	*/
	CppFunctionIDEquality(int identifier)
	: m_identifier(identifier)
	{
	}

	CppFunctionIDEquality(const _CppFunction<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>name</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::NameEquality {
private :
	typename EncodingT::string_t	m_name;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param name 
	*/
	NameEquality(const typename EncodingT::string_t& name)
	: m_name(name)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_name==other->getName());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::NameInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() < elem2->getName());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::NameSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() > elem2->getName());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>accessSpecifier</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::AccessSpecifierEquality {
private :
	typename EncodingT::string_t	m_accessSpecifier;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param accessSpecifier 
	*/
	AccessSpecifierEquality(const typename EncodingT::string_t& accessSpecifier)
	: m_accessSpecifier(accessSpecifier)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_accessSpecifier==other->getAccessSpecifier());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>accessSpecifier</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::AccessSpecifierInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getAccessSpecifier() < elem2->getAccessSpecifier());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>accessSpecifier</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::AccessSpecifierSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getAccessSpecifier() > elem2->getAccessSpecifier());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>returnType</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::ReturnTypeEquality {
private :
	typename EncodingT::string_t	m_returnType;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param returnType 
	*/
	ReturnTypeEquality(const typename EncodingT::string_t& returnType)
	: m_returnType(returnType)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_returnType==other->getReturnType());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>returnType</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::ReturnTypeInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getReturnType() < elem2->getReturnType());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>returnType</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::ReturnTypeSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getReturnType() > elem2->getReturnType());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isConst</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstEquality {
private :
	int	m_isConst;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isConst 
	*/
	IsConstEquality(int isConst)
	: m_isConst(isConst)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isConst==other->getIsConst());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isConst</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConst() < elem2->getIsConst());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isConst</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConst() > elem2->getIsConst());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isVirtual</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVirtualEquality {
private :
	int	m_isVirtual;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isVirtual 
	*/
	IsVirtualEquality(int isVirtual)
	: m_isVirtual(isVirtual)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isVirtual==other->getIsVirtual());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isVirtual</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVirtualInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsVirtual() < elem2->getIsVirtual());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isVirtual</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVirtualSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsVirtual() > elem2->getIsVirtual());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isVirtualPure</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVirtualPureEquality {
private :
	int	m_isVirtualPure;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isVirtualPure 
	*/
	IsVirtualPureEquality(int isVirtualPure)
	: m_isVirtualPure(isVirtualPure)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isVirtualPure==other->getIsVirtualPure());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isVirtualPure</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVirtualPureInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsVirtualPure() < elem2->getIsVirtualPure());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isVirtualPure</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVirtualPureSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsVirtualPure() > elem2->getIsVirtualPure());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isStatic</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsStaticEquality {
private :
	int	m_isStatic;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isStatic 
	*/
	IsStaticEquality(int isStatic)
	: m_isStatic(isStatic)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isStatic==other->getIsStatic());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isStatic</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsStaticInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsStatic() < elem2->getIsStatic());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isStatic</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsStaticSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsStatic() > elem2->getIsStatic());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isOperator</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsOperatorEquality {
private :
	int	m_isOperator;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isOperator 
	*/
	IsOperatorEquality(int isOperator)
	: m_isOperator(isOperator)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isOperator==other->getIsOperator());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isOperator</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsOperatorInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsOperator() < elem2->getIsOperator());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isOperator</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsOperatorSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsOperator() > elem2->getIsOperator());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isDestructor</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsDestructorEquality {
private :
	int	m_isDestructor;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isDestructor 
	*/
	IsDestructorEquality(int isDestructor)
	: m_isDestructor(isDestructor)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isDestructor==other->getIsDestructor());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isDestructor</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsDestructorInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsDestructor() < elem2->getIsDestructor());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isDestructor</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsDestructorSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsDestructor() > elem2->getIsDestructor());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isConstructor</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstructorEquality {
private :
	int	m_isConstructor;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isConstructor 
	*/
	IsConstructorEquality(int isConstructor)
	: m_isConstructor(isConstructor)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isConstructor==other->getIsConstructor());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isConstructor</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstructorInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConstructor() < elem2->getIsConstructor());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isConstructor</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstructorSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConstructor() > elem2->getIsConstructor());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isVariadic</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVariadicEquality {
private :
	int	m_isVariadic;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isVariadic 
	*/
	IsVariadicEquality(int isVariadic)
	: m_isVariadic(isVariadic)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isVariadic==other->getIsVariadic());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isVariadic</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVariadicInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsVariadic() < elem2->getIsVariadic());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isVariadic</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVariadicSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsVariadic() > elem2->getIsVariadic());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>signature</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::SignatureEquality {
private :
	typename EncodingT::string_t	m_signature;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param signature 
	*/
	SignatureEquality(const typename EncodingT::string_t& signature)
	: m_signature(signature)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_signature==other->getSignature());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>signature</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::SignatureInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getSignature() < elem2->getSignature());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>signature</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::SignatureSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getSignature() > elem2->getSignature());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>startDecBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::StartDecBlockEquality {
private :
	int	m_startDecBlock;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param startDecBlock 
	*/
	StartDecBlockEquality(int startDecBlock)
	: m_startDecBlock(startDecBlock)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_startDecBlock==other->getStartDecBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>startDecBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::StartDecBlockInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDecBlock() < elem2->getStartDecBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>startDecBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::StartDecBlockSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDecBlock() > elem2->getStartDecBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>lengthDecBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LengthDecBlockEquality {
private :
	int	m_lengthDecBlock;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param lengthDecBlock 
	*/
	LengthDecBlockEquality(int lengthDecBlock)
	: m_lengthDecBlock(lengthDecBlock)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_lengthDecBlock==other->getLengthDecBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>lengthDecBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LengthDecBlockInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDecBlock() < elem2->getLengthDecBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>lengthDecBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LengthDecBlockSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDecBlock() > elem2->getLengthDecBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>decLineNumber</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::DecLineNumberEquality {
private :
	int	m_decLineNumber;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param decLineNumber 
	*/
	DecLineNumberEquality(int decLineNumber)
	: m_decLineNumber(decLineNumber)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_decLineNumber==other->getDecLineNumber());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>decLineNumber</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::DecLineNumberInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDecLineNumber() < elem2->getDecLineNumber());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>decLineNumber</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::DecLineNumberSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDecLineNumber() > elem2->getDecLineNumber());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>linesCount</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LinesCountEquality {
private :
	int	m_linesCount;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param linesCount 
	*/
	LinesCountEquality(int linesCount)
	: m_linesCount(linesCount)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_linesCount==other->getLinesCount());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>linesCount</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LinesCountInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLinesCount() < elem2->getLinesCount());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>linesCount</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LinesCountSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLinesCount() > elem2->getLinesCount());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>complexity</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::ComplexityEquality {
private :
	int	m_complexity;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param complexity 
	*/
	ComplexityEquality(int complexity)
	: m_complexity(complexity)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_complexity==other->getComplexity());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>complexity</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::ComplexityInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getComplexity() < elem2->getComplexity());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>complexity</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::ComplexitySuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getComplexity() > elem2->getComplexity());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>defLineNumber</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::DefLineNumberEquality {
private :
	int	m_defLineNumber;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param defLineNumber 
	*/
	DefLineNumberEquality(int defLineNumber)
	: m_defLineNumber(defLineNumber)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_defLineNumber==other->getDefLineNumber());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>defLineNumber</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::DefLineNumberInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDefLineNumber() < elem2->getDefLineNumber());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>defLineNumber</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::DefLineNumberSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDefLineNumber() > elem2->getDefLineNumber());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>startDefBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::StartDefBlockEquality {
private :
	int	m_startDefBlock;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param startDefBlock 
	*/
	StartDefBlockEquality(int startDefBlock)
	: m_startDefBlock(startDefBlock)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_startDefBlock==other->getStartDefBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>startDefBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::StartDefBlockInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDefBlock() < elem2->getStartDefBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>startDefBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::StartDefBlockSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDefBlock() > elem2->getStartDefBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>lengthDefBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LengthDefBlockEquality {
private :
	int	m_lengthDefBlock;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param lengthDefBlock 
	*/
	LengthDefBlockEquality(int lengthDefBlock)
	: m_lengthDefBlock(lengthDefBlock)
	{
	}

	bool operator()(shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_lengthDefBlock==other->getLengthDefBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>lengthDefBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LengthDefBlockInferior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDefBlock() < elem2->getLengthDefBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>lengthDefBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LengthDefBlockSuperior {
private :
public :
	bool operator()(shared_ptr< _CppFunction<EncodingT> > elem1, shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDefBlock() > elem2->getLengthDefBlock());
	}

};

NAMESPACE_END

#endif
