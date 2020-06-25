/* 
 * cppFunctionPredicate.hpp
 *
 *
 * @date 25-06-2020
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
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param identifier 
	*/
	CppFunctionIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	CppFunctionIDEquality(const _CppFunction<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getReturnType() > elem2->getReturnType());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isConst</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstEquality {
private :
	long long	m_isConst;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isConst 
	*/
	IsConstEquality(long long isConst)
	: m_isConst(isConst)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConst() > elem2->getIsConst());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isVirtual</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVirtualEquality {
private :
	long long	m_isVirtual;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isVirtual 
	*/
	IsVirtualEquality(long long isVirtual)
	: m_isVirtual(isVirtual)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsVirtual() > elem2->getIsVirtual());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isVirtualPure</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVirtualPureEquality {
private :
	long long	m_isVirtualPure;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isVirtualPure 
	*/
	IsVirtualPureEquality(long long isVirtualPure)
	: m_isVirtualPure(isVirtualPure)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsVirtualPure() > elem2->getIsVirtualPure());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isStatic</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsStaticEquality {
private :
	long long	m_isStatic;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isStatic 
	*/
	IsStaticEquality(long long isStatic)
	: m_isStatic(isStatic)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsStatic() > elem2->getIsStatic());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isOperator</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsOperatorEquality {
private :
	long long	m_isOperator;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isOperator 
	*/
	IsOperatorEquality(long long isOperator)
	: m_isOperator(isOperator)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsOperator() > elem2->getIsOperator());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isDestructor</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsDestructorEquality {
private :
	long long	m_isDestructor;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isDestructor 
	*/
	IsDestructorEquality(long long isDestructor)
	: m_isDestructor(isDestructor)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsDestructor() > elem2->getIsDestructor());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isConstructor</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstructorEquality {
private :
	long long	m_isConstructor;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isConstructor 
	*/
	IsConstructorEquality(long long isConstructor)
	: m_isConstructor(isConstructor)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConstructor() > elem2->getIsConstructor());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isVariadic</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsVariadicEquality {
private :
	long long	m_isVariadic;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isVariadic 
	*/
	IsVariadicEquality(long long isVariadic)
	: m_isVariadic(isVariadic)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsVariadic() > elem2->getIsVariadic());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isTemplate</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsTemplateEquality {
private :
	long long	m_isTemplate;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isTemplate 
	*/
	IsTemplateEquality(long long isTemplate)
	: m_isTemplate(isTemplate)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isTemplate==other->getIsTemplate());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isTemplate</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsTemplateInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsTemplate() < elem2->getIsTemplate());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isTemplate</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsTemplateSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsTemplate() > elem2->getIsTemplate());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isInline</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsInlineEquality {
private :
	long long	m_isInline;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isInline 
	*/
	IsInlineEquality(long long isInline)
	: m_isInline(isInline)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isInline==other->getIsInline());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isInline</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsInlineInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsInline() < elem2->getIsInline());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isInline</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsInlineSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsInline() > elem2->getIsInline());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isConstexpr</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstexprEquality {
private :
	long long	m_isConstexpr;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isConstexpr 
	*/
	IsConstexprEquality(long long isConstexpr)
	: m_isConstexpr(isConstexpr)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isConstexpr==other->getIsConstexpr());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isConstexpr</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstexprInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConstexpr() < elem2->getIsConstexpr());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isConstexpr</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsConstexprSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConstexpr() > elem2->getIsConstexpr());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isOverride</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsOverrideEquality {
private :
	long long	m_isOverride;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isOverride 
	*/
	IsOverrideEquality(long long isOverride)
	: m_isOverride(isOverride)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isOverride==other->getIsOverride());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isOverride</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsOverrideInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsOverride() < elem2->getIsOverride());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isOverride</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsOverrideSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsOverride() > elem2->getIsOverride());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isFinal</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsFinalEquality {
private :
	long long	m_isFinal;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isFinal 
	*/
	IsFinalEquality(long long isFinal)
	: m_isFinal(isFinal)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isFinal==other->getIsFinal());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isFinal</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsFinalInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsFinal() < elem2->getIsFinal());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isFinal</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsFinalSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsFinal() > elem2->getIsFinal());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>isNoexcept</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsNoexceptEquality {
private :
	long long	m_isNoexcept;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param isNoexcept 
	*/
	IsNoexceptEquality(long long isNoexcept)
	: m_isNoexcept(isNoexcept)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
	{
		return (other != NULL && m_isNoexcept==other->getIsNoexcept());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isNoexcept</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsNoexceptInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsNoexcept() < elem2->getIsNoexcept());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to sort objects by <i>isNoexcept</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::IsNoexceptSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsNoexcept() > elem2->getIsNoexcept());
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

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getSignature() > elem2->getSignature());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>decLineNumber</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::DecLineNumberEquality {
private :
	long long	m_decLineNumber;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param decLineNumber 
	*/
	DecLineNumberEquality(long long decLineNumber)
	: m_decLineNumber(decLineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDecLineNumber() > elem2->getDecLineNumber());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>startDecBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::StartDecBlockEquality {
private :
	long long	m_startDecBlock;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param startDecBlock 
	*/
	StartDecBlockEquality(long long startDecBlock)
	: m_startDecBlock(startDecBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDecBlock() > elem2->getStartDecBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>lengthDecBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LengthDecBlockEquality {
private :
	long long	m_lengthDecBlock;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param lengthDecBlock 
	*/
	LengthDecBlockEquality(long long lengthDecBlock)
	: m_lengthDecBlock(lengthDecBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDecBlock() > elem2->getLengthDecBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>linesCount</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LinesCountEquality {
private :
	long long	m_linesCount;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param linesCount 
	*/
	LinesCountEquality(long long linesCount)
	: m_linesCount(linesCount)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLinesCount() > elem2->getLinesCount());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>complexity</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::ComplexityEquality {
private :
	long long	m_complexity;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param complexity 
	*/
	ComplexityEquality(long long complexity)
	: m_complexity(complexity)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getComplexity() > elem2->getComplexity());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>defLineNumber</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::DefLineNumberEquality {
private :
	long long	m_defLineNumber;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param defLineNumber 
	*/
	DefLineNumberEquality(long long defLineNumber)
	: m_defLineNumber(defLineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDefLineNumber() > elem2->getDefLineNumber());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>startDefBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::StartDefBlockEquality {
private :
	long long	m_startDefBlock;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param startDefBlock 
	*/
	StartDefBlockEquality(long long startDefBlock)
	: m_startDefBlock(startDefBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDefBlock() > elem2->getStartDefBlock());
	}

};

/// Represents a comparaison class for CppFunction object.
/// This class is used to find an object with the same element <i>lengthDefBlock</i>.
template<class EncodingT>
class  _CppFunction<EncodingT>::LengthDefBlockEquality {
private :
	long long	m_lengthDefBlock;
public :
	/** Creates a new functor allowing to find CppFunction object.
	@param lengthDefBlock 
	*/
	LengthDefBlockEquality(long long lengthDefBlock)
	: m_lengthDefBlock(lengthDefBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > other) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
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
	bool operator()(boost::shared_ptr< _CppFunction<EncodingT> > elem1, boost::shared_ptr< _CppFunction<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDefBlock() > elem2->getLengthDefBlock());
	}

};

NAMESPACE_END

#endif
