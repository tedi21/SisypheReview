/* 
 * debugValueInfoPredicate.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGVALUEINFO_PREDICATE_HPP_
#define _DEBUGVALUEINFO_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for DebugValueInfo object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find DebugValueInfo object.
	@param identifier 
	*/
	DebugValueInfoIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	DebugValueInfoIDEquality(const _DebugValueInfo<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _DebugValueInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for DebugValueInfo object.
/// This class is used to find an object with the same element <i>textValue</i>.
template<class EncodingT>
class  _DebugValueInfo<EncodingT>::TextValueEquality {
private :
	typename EncodingT::string_t	m_textValue;
public :
	/** Creates a new functor allowing to find DebugValueInfo object.
	@param textValue 
	*/
	TextValueEquality(const typename EncodingT::string_t& textValue)
	: m_textValue(textValue)
	{
	}

	bool operator()(boost::shared_ptr< _DebugValueInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_textValue==other->getTextValue());
	}

};

/// Represents a comparaison class for DebugValueInfo object.
/// This class is used to sort objects by <i>textValue</i>.
template<class EncodingT>
class  _DebugValueInfo<EncodingT>::TextValueInferior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugValueInfo<EncodingT> > elem1, boost::shared_ptr< _DebugValueInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getTextValue() < elem2->getTextValue());
	}

};

/// Represents a comparaison class for DebugValueInfo object.
/// This class is used to sort objects by <i>textValue</i>.
template<class EncodingT>
class  _DebugValueInfo<EncodingT>::TextValueSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugValueInfo<EncodingT> > elem1, boost::shared_ptr< _DebugValueInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getTextValue() > elem2->getTextValue());
	}

};

NAMESPACE_END

#endif
