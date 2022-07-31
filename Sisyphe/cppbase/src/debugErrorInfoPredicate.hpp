/* 
 * debugErrorInfoPredicate.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGERRORINFO_PREDICATE_HPP_
#define _DEBUGERRORINFO_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for DebugErrorInfo object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _DebugErrorInfo<EncodingT>::DebugErrorInfoIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find DebugErrorInfo object.
	@param identifier 
	*/
	DebugErrorInfoIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	DebugErrorInfoIDEquality(const _DebugErrorInfo<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(const boost::shared_ptr< _DebugErrorInfo<EncodingT> >& other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for DebugErrorInfo object.
/// This class is used to sort objects by ID.
template<class EncodingT>
class  _DebugErrorInfo<EncodingT>::DebugErrorInfoIDInferior {
private :
public :
	bool operator()(const boost::shared_ptr< _DebugErrorInfo<EncodingT> >& elem1, const boost::shared_ptr< _DebugErrorInfo<EncodingT> >& elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIdentifier() < elem2->getIdentifier());
	}

};

/// Represents a comparaison class for DebugErrorInfo object.
/// This class is used to find an object with the same element <i>callStack</i>.
template<class EncodingT>
class  _DebugErrorInfo<EncodingT>::CallStackEquality {
private :
	typename EncodingT::string_t	m_callStack;
public :
	/** Creates a new functor allowing to find DebugErrorInfo object.
	@param callStack 
	*/
	CallStackEquality(const typename EncodingT::string_t& callStack)
	: m_callStack(callStack)
	{
	}

	bool operator()(const boost::shared_ptr< _DebugErrorInfo<EncodingT> >& other) const 
	{
		return (other != NULL && m_callStack==other->getCallStack());
	}

};

/// Represents a comparaison class for DebugErrorInfo object.
/// This class is used to sort objects by <i>callStack</i>.
template<class EncodingT>
class  _DebugErrorInfo<EncodingT>::CallStackInferior {
private :
public :
	bool operator()(const boost::shared_ptr< _DebugErrorInfo<EncodingT> >& elem1, const boost::shared_ptr< _DebugErrorInfo<EncodingT> >& elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCallStack() < elem2->getCallStack());
	}

};

/// Represents a comparaison class for DebugErrorInfo object.
/// This class is used to sort objects by <i>callStack</i>.
template<class EncodingT>
class  _DebugErrorInfo<EncodingT>::CallStackSuperior {
private :
public :
	bool operator()(const boost::shared_ptr< _DebugErrorInfo<EncodingT> >& elem1, const boost::shared_ptr< _DebugErrorInfo<EncodingT> >& elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCallStack() > elem2->getCallStack());
	}

};

NAMESPACE_END

#endif
