/* 
 * cppParameterPredicate.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPPARAMETER_PREDICATE_HPP_
#define _CPPPARAMETER_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _CppParameter<EncodingT>::CppParameterIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param identifier 
	*/
	CppParameterIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	CppParameterIDEquality(const _CppParameter<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>paramOrder</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::ParamOrderEquality {
private :
	long long	m_paramOrder;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param paramOrder 
	*/
	ParamOrderEquality(long long paramOrder)
	: m_paramOrder(paramOrder)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_paramOrder==other->getParamOrder());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>paramOrder</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::ParamOrderInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getParamOrder() < elem2->getParamOrder());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>paramOrder</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::ParamOrderSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getParamOrder() > elem2->getParamOrder());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>paramType</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::ParamTypeEquality {
private :
	typename EncodingT::string_t	m_paramType;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param paramType 
	*/
	ParamTypeEquality(const typename EncodingT::string_t& paramType)
	: m_paramType(paramType)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_paramType==other->getParamType());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>paramType</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::ParamTypeInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getParamType() < elem2->getParamType());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>paramType</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::ParamTypeSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getParamType() > elem2->getParamType());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>isConst</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::IsConstEquality {
private :
	long long	m_isConst;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param isConst 
	*/
	IsConstEquality(long long isConst)
	: m_isConst(isConst)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_isConst==other->getIsConst());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>isConst</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::IsConstInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConst() < elem2->getIsConst());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>isConst</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::IsConstSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsConst() > elem2->getIsConst());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>defaultValue</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DefaultValueEquality {
private :
	typename EncodingT::string_t	m_defaultValue;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param defaultValue 
	*/
	DefaultValueEquality(const typename EncodingT::string_t& defaultValue)
	: m_defaultValue(defaultValue)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_defaultValue==other->getDefaultValue());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>defaultValue</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DefaultValueInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDefaultValue() < elem2->getDefaultValue());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>defaultValue</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DefaultValueSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDefaultValue() > elem2->getDefaultValue());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>decName</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DecNameEquality {
private :
	typename EncodingT::string_t	m_decName;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param decName 
	*/
	DecNameEquality(const typename EncodingT::string_t& decName)
	: m_decName(decName)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_decName==other->getDecName());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>decName</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DecNameInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDecName() < elem2->getDecName());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>decName</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DecNameSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDecName() > elem2->getDecName());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>decLineNumber</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DecLineNumberEquality {
private :
	long long	m_decLineNumber;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param decLineNumber 
	*/
	DecLineNumberEquality(long long decLineNumber)
	: m_decLineNumber(decLineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_decLineNumber==other->getDecLineNumber());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>decLineNumber</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DecLineNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDecLineNumber() < elem2->getDecLineNumber());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>decLineNumber</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DecLineNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDecLineNumber() > elem2->getDecLineNumber());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>startDecBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::StartDecBlockEquality {
private :
	long long	m_startDecBlock;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param startDecBlock 
	*/
	StartDecBlockEquality(long long startDecBlock)
	: m_startDecBlock(startDecBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_startDecBlock==other->getStartDecBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>startDecBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::StartDecBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDecBlock() < elem2->getStartDecBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>startDecBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::StartDecBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDecBlock() > elem2->getStartDecBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>lengthDecBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::LengthDecBlockEquality {
private :
	long long	m_lengthDecBlock;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param lengthDecBlock 
	*/
	LengthDecBlockEquality(long long lengthDecBlock)
	: m_lengthDecBlock(lengthDecBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_lengthDecBlock==other->getLengthDecBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>lengthDecBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::LengthDecBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDecBlock() < elem2->getLengthDecBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>lengthDecBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::LengthDecBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDecBlock() > elem2->getLengthDecBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>defName</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DefNameEquality {
private :
	typename EncodingT::string_t	m_defName;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param defName 
	*/
	DefNameEquality(const typename EncodingT::string_t& defName)
	: m_defName(defName)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_defName==other->getDefName());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>defName</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DefNameInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDefName() < elem2->getDefName());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>defName</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DefNameSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDefName() > elem2->getDefName());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>defLineNumber</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DefLineNumberEquality {
private :
	long long	m_defLineNumber;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param defLineNumber 
	*/
	DefLineNumberEquality(long long defLineNumber)
	: m_defLineNumber(defLineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_defLineNumber==other->getDefLineNumber());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>defLineNumber</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DefLineNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDefLineNumber() < elem2->getDefLineNumber());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>defLineNumber</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::DefLineNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDefLineNumber() > elem2->getDefLineNumber());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>startDefBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::StartDefBlockEquality {
private :
	long long	m_startDefBlock;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param startDefBlock 
	*/
	StartDefBlockEquality(long long startDefBlock)
	: m_startDefBlock(startDefBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_startDefBlock==other->getStartDefBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>startDefBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::StartDefBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDefBlock() < elem2->getStartDefBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>startDefBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::StartDefBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartDefBlock() > elem2->getStartDefBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to find an object with the same element <i>lengthDefBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::LengthDefBlockEquality {
private :
	long long	m_lengthDefBlock;
public :
	/** Creates a new functor allowing to find CppParameter object.
	@param lengthDefBlock 
	*/
	LengthDefBlockEquality(long long lengthDefBlock)
	: m_lengthDefBlock(lengthDefBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > other) const 
	{
		return (other != NULL && m_lengthDefBlock==other->getLengthDefBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>lengthDefBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::LengthDefBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDefBlock() < elem2->getLengthDefBlock());
	}

};

/// Represents a comparaison class for CppParameter object.
/// This class is used to sort objects by <i>lengthDefBlock</i>.
template<class EncodingT>
class  _CppParameter<EncodingT>::LengthDefBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppParameter<EncodingT> > elem1, boost::shared_ptr< _CppParameter<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthDefBlock() > elem2->getLengthDefBlock());
	}

};

NAMESPACE_END

#endif
