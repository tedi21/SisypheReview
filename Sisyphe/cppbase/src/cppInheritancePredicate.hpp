/* 
 * cppInheritancePredicate.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPINHERITANCE_PREDICATE_HPP_
#define _CPPINHERITANCE_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for CppInheritance object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _CppInheritance<EncodingT>::CppInheritanceIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find CppInheritance object.
	@param identifier 
	*/
	CppInheritanceIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	CppInheritanceIDEquality(const _CppInheritance<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _CppInheritance<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for CppInheritance object.
/// This class is used to find an object with the same element <i>baseClassName</i>.
template<class EncodingT>
class  _CppInheritance<EncodingT>::BaseClassNameEquality {
private :
	typename EncodingT::string_t	m_baseClassName;
public :
	/** Creates a new functor allowing to find CppInheritance object.
	@param baseClassName 
	*/
	BaseClassNameEquality(const typename EncodingT::string_t& baseClassName)
	: m_baseClassName(baseClassName)
	{
	}

	bool operator()(boost::shared_ptr< _CppInheritance<EncodingT> > other) const 
	{
		return (other != NULL && m_baseClassName==other->getBaseClassName());
	}

};

/// Represents a comparaison class for CppInheritance object.
/// This class is used to sort objects by <i>baseClassName</i>.
template<class EncodingT>
class  _CppInheritance<EncodingT>::BaseClassNameInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppInheritance<EncodingT> > elem1, boost::shared_ptr< _CppInheritance<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getBaseClassName() < elem2->getBaseClassName());
	}

};

/// Represents a comparaison class for CppInheritance object.
/// This class is used to sort objects by <i>baseClassName</i>.
template<class EncodingT>
class  _CppInheritance<EncodingT>::BaseClassNameSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppInheritance<EncodingT> > elem1, boost::shared_ptr< _CppInheritance<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getBaseClassName() > elem2->getBaseClassName());
	}

};

/// Represents a comparaison class for CppInheritance object.
/// This class is used to find an object with the same element <i>baseAccess</i>.
template<class EncodingT>
class  _CppInheritance<EncodingT>::BaseAccessEquality {
private :
	typename EncodingT::string_t	m_baseAccess;
public :
	/** Creates a new functor allowing to find CppInheritance object.
	@param baseAccess 
	*/
	BaseAccessEquality(const typename EncodingT::string_t& baseAccess)
	: m_baseAccess(baseAccess)
	{
	}

	bool operator()(boost::shared_ptr< _CppInheritance<EncodingT> > other) const 
	{
		return (other != NULL && m_baseAccess==other->getBaseAccess());
	}

};

/// Represents a comparaison class for CppInheritance object.
/// This class is used to sort objects by <i>baseAccess</i>.
template<class EncodingT>
class  _CppInheritance<EncodingT>::BaseAccessInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppInheritance<EncodingT> > elem1, boost::shared_ptr< _CppInheritance<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getBaseAccess() < elem2->getBaseAccess());
	}

};

/// Represents a comparaison class for CppInheritance object.
/// This class is used to sort objects by <i>baseAccess</i>.
template<class EncodingT>
class  _CppInheritance<EncodingT>::BaseAccessSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppInheritance<EncodingT> > elem1, boost::shared_ptr< _CppInheritance<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getBaseAccess() > elem2->getBaseAccess());
	}

};

NAMESPACE_END

#endif
