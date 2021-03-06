/* 
 * cppParameter.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPPARAMETER_HPP_
#define _CPPPARAMETER_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/container/vector.hpp>
#include "copy_ptr.h"
#include "config.hpp"
#include "convert.hpp"
#include "encoding.hpp"

#include "cppBaseExport.hpp"
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

template <class EncodingT>
class _CppParameterAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _CppFunction;

/// cppParameter table represents a parameter.
template <class EncodingT>
class  _CppParameter {
private :
	long long	m_identifier;
	long long	m_paramOrder;
	typename EncodingT::string_t	m_paramType;
	long long	m_isConst;
	typename EncodingT::string_t	m_defaultValue;
	boost::shared_ptr< _CppFunction<EncodingT> >	m_cppFunction;
	typename EncodingT::string_t	m_decName;
	long long	m_decLineNumber;
	long long	m_startDecBlock;
	long long	m_lengthDecBlock;
	typename EncodingT::string_t	m_defName;
	long long	m_defLineNumber;
	long long	m_startDefBlock;
	long long	m_lengthDefBlock;
	Category*	m_logger;

protected :
	friend class data_access::_CppParameterAccess<EncodingT>;

	/** Creates a new element CppParameter.
	@param identifier 
	@param paramOrder 
	@param paramType 
	@param isConst 
	@param defaultValue 
	@param decName 
	@param decLineNumber 
	@param startDecBlock 
	@param lengthDecBlock 
	@param defName 
	@param defLineNumber 
	@param startDefBlock 
	@param lengthDefBlock 
	*/
	_CppParameter(long long identifier,
				long long paramOrder,
				const typename EncodingT::string_t& paramType,
				long long isConst,
				const typename EncodingT::string_t& defaultValue,
				const typename EncodingT::string_t& decName,
				long long decLineNumber,
				long long startDecBlock,
				long long lengthDecBlock,
				const typename EncodingT::string_t& defName,
				long long defLineNumber,
				long long startDefBlock,
				long long lengthDefBlock)
	: m_identifier(identifier),
	  m_paramOrder(paramOrder),
	  m_paramType(paramType),
	  m_isConst(isConst),
	  m_defaultValue(defaultValue),
	  m_decName(decName),
	  m_decLineNumber(decLineNumber),
	  m_startDecBlock(startDecBlock),
	  m_lengthDecBlock(lengthDecBlock),
	  m_defName(defName),
	  m_defLineNumber(defLineNumber),
	  m_startDefBlock(startDefBlock),
	  m_lengthDefBlock(lengthDefBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppParameter "
				<< m_identifier << ' '
				<< m_paramOrder << ' '
				<< A(m_paramType) << ' '
				<< m_isConst << ' '
				<< A(m_defaultValue) << ' '
				<< A(m_decName) << ' '
				<< m_decLineNumber << ' '
				<< m_startDecBlock << ' '
				<< m_lengthDecBlock << ' '
				<< A(m_defName) << ' '
				<< m_defLineNumber << ' '
				<< m_startDefBlock << ' '
				<< m_lengthDefBlock << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppParameter.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element CppParameter.
	*/
	_CppParameter()
	: m_identifier(-1),
	  m_paramOrder(0),
	  m_paramType(EncodingT::EMPTY),
	  m_isConst(0),
	  m_defaultValue(EncodingT::EMPTY),
	  m_decName(EncodingT::EMPTY),
	  m_decLineNumber(0),
	  m_startDecBlock(0),
	  m_lengthDecBlock(0),
	  m_defName(EncodingT::EMPTY),
	  m_defLineNumber(0),
	  m_startDefBlock(0),
	  m_lengthDefBlock(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppParameter ";
	}

	/** Creates a new element CppParameter.
	@param paramOrder 
	@param paramType 
	@param isConst 
	@param defaultValue 
	@param decName 
	@param decLineNumber 
	@param startDecBlock 
	@param lengthDecBlock 
	@param defName 
	@param defLineNumber 
	@param startDefBlock 
	@param lengthDefBlock 
	*/
	_CppParameter(long long paramOrder,
				const typename EncodingT::string_t& paramType,
				long long isConst,
				const typename EncodingT::string_t& defaultValue,
				const typename EncodingT::string_t& decName,
				long long decLineNumber,
				long long startDecBlock,
				long long lengthDecBlock,
				const typename EncodingT::string_t& defName,
				long long defLineNumber,
				long long startDefBlock,
				long long lengthDefBlock)
	: m_identifier(-1),
	  m_paramOrder(paramOrder),
	  m_paramType(paramType),
	  m_isConst(isConst),
	  m_defaultValue(defaultValue),
	  m_decName(decName),
	  m_decLineNumber(decLineNumber),
	  m_startDecBlock(startDecBlock),
	  m_lengthDecBlock(lengthDecBlock),
	  m_defName(defName),
	  m_defLineNumber(defLineNumber),
	  m_startDefBlock(startDefBlock),
	  m_lengthDefBlock(lengthDefBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppParameter "
				<< m_identifier << ' '
				<< m_paramOrder << ' '
				<< A(m_paramType) << ' '
				<< m_isConst << ' '
				<< A(m_defaultValue) << ' '
				<< A(m_decName) << ' '
				<< m_decLineNumber << ' '
				<< m_startDecBlock << ' '
				<< m_lengthDecBlock << ' '
				<< A(m_defName) << ' '
				<< m_defLineNumber << ' '
				<< m_startDefBlock << ' '
				<< m_lengthDefBlock << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in CppParameter.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>paramOrder</i> in CppParameter.
	@return 
	*/
	long long getParamOrder() const 
	{
		return m_paramOrder;
	}

	/** Sets a value of the element <i>paramOrder</i> in CppParameter.
	@param paramOrder 
	*/
	void setParamOrder(long long paramOrder)  
	{
		m_paramOrder = paramOrder;
	}

	/** Returns a const reference to the element <i>paramType</i> in CppParameter.
	@return 
	*/
	const typename EncodingT::string_t& getParamType() const 
	{
		return m_paramType;
	}

	/** Sets a value of the element <i>paramType</i> in CppParameter.
	@param paramType 
	*/
	void setParamType(const typename EncodingT::string_t& paramType)  
	{
		m_paramType = paramType;
	}

	/** Returns a const reference to the element <i>isConst</i> in CppParameter.
	@return 
	*/
	long long getIsConst() const 
	{
		return m_isConst;
	}

	/** Sets a value of the element <i>isConst</i> in CppParameter.
	@param isConst 
	*/
	void setIsConst(long long isConst)  
	{
		m_isConst = isConst;
	}

	/** Returns a const reference to the element <i>defaultValue</i> in CppParameter.
	@return 
	*/
	const typename EncodingT::string_t& getDefaultValue() const 
	{
		return m_defaultValue;
	}

	/** Sets a value of the element <i>defaultValue</i> in CppParameter.
	@param defaultValue 
	*/
	void setDefaultValue(const typename EncodingT::string_t& defaultValue)  
	{
		m_defaultValue = defaultValue;
	}

	/** Returns a const reference to the element <i>cppFunction</i> in CppParameter.
	@return 
	*/
	boost::shared_ptr< _CppFunction<EncodingT> > getCppFunction() const 
	{
		return m_cppFunction;
	}

	/** Sets a value of the element <i>cppFunction</i> in CppParameter.
	@param cppFunction 
	*/
	void setCppFunction(boost::shared_ptr< _CppFunction<EncodingT> > cppFunction)  
	{
		m_cppFunction = cppFunction;
	}

	/** Returns whether the element <i>cppFunction</i> in CppParameter is NULL.
	@return True if the element <i>cppFunction</i> is NULL, false otherwise.
	*/
	bool isNullCppFunction() const 
	{
		return !m_cppFunction;
	}

	/** Removes from CppParameter an element <i>cppFunction</i>.
	*/
	void eraseCppFunction()  
	{
		m_cppFunction.reset();
	}

	/** Returns a const reference to the element <i>decName</i> in CppParameter.
	@return 
	*/
	const typename EncodingT::string_t& getDecName() const 
	{
		return m_decName;
	}

	/** Sets a value of the element <i>decName</i> in CppParameter.
	@param decName 
	*/
	void setDecName(const typename EncodingT::string_t& decName)  
	{
		m_decName = decName;
	}

	/** Returns a const reference to the element <i>decLineNumber</i> in CppParameter.
	@return 
	*/
	long long getDecLineNumber() const 
	{
		return m_decLineNumber;
	}

	/** Sets a value of the element <i>decLineNumber</i> in CppParameter.
	@param decLineNumber 
	*/
	void setDecLineNumber(long long decLineNumber)  
	{
		m_decLineNumber = decLineNumber;
	}

	/** Returns a const reference to the element <i>startDecBlock</i> in CppParameter.
	@return 
	*/
	long long getStartDecBlock() const 
	{
		return m_startDecBlock;
	}

	/** Sets a value of the element <i>startDecBlock</i> in CppParameter.
	@param startDecBlock 
	*/
	void setStartDecBlock(long long startDecBlock)  
	{
		m_startDecBlock = startDecBlock;
	}

	/** Returns a const reference to the element <i>lengthDecBlock</i> in CppParameter.
	@return 
	*/
	long long getLengthDecBlock() const 
	{
		return m_lengthDecBlock;
	}

	/** Sets a value of the element <i>lengthDecBlock</i> in CppParameter.
	@param lengthDecBlock 
	*/
	void setLengthDecBlock(long long lengthDecBlock)  
	{
		m_lengthDecBlock = lengthDecBlock;
	}

	/** Returns a const reference to the element <i>defName</i> in CppParameter.
	@return 
	*/
	const typename EncodingT::string_t& getDefName() const 
	{
		return m_defName;
	}

	/** Sets a value of the element <i>defName</i> in CppParameter.
	@param defName 
	*/
	void setDefName(const typename EncodingT::string_t& defName)  
	{
		m_defName = defName;
	}

	/** Returns a const reference to the element <i>defLineNumber</i> in CppParameter.
	@return 
	*/
	long long getDefLineNumber() const 
	{
		return m_defLineNumber;
	}

	/** Sets a value of the element <i>defLineNumber</i> in CppParameter.
	@param defLineNumber 
	*/
	void setDefLineNumber(long long defLineNumber)  
	{
		m_defLineNumber = defLineNumber;
	}

	/** Returns a const reference to the element <i>startDefBlock</i> in CppParameter.
	@return 
	*/
	long long getStartDefBlock() const 
	{
		return m_startDefBlock;
	}

	/** Sets a value of the element <i>startDefBlock</i> in CppParameter.
	@param startDefBlock 
	*/
	void setStartDefBlock(long long startDefBlock)  
	{
		m_startDefBlock = startDefBlock;
	}

	/** Returns a const reference to the element <i>lengthDefBlock</i> in CppParameter.
	@return 
	*/
	long long getLengthDefBlock() const 
	{
		return m_lengthDefBlock;
	}

	/** Sets a value of the element <i>lengthDefBlock</i> in CppParameter.
	@param lengthDefBlock 
	*/
	void setLengthDefBlock(long long lengthDefBlock)  
	{
		m_lengthDefBlock = lengthDefBlock;
	}

	/** Prints CppParameter object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "CppParameter" << endl
		         << "identifier : " << m_identifier << endl
		         << "paramOrder : " << m_paramOrder << endl
		         << "paramType : " << A(m_paramType) << endl
		         << "isConst : " << m_isConst << endl
		         << "defaultValue : " << A(m_defaultValue) << endl
		         << "decName : " << A(m_decName) << endl
		         << "decLineNumber : " << m_decLineNumber << endl
		         << "startDecBlock : " << m_startDecBlock << endl
		         << "lengthDecBlock : " << m_lengthDecBlock << endl
		         << "defName : " << A(m_defName) << endl
		         << "defLineNumber : " << m_defLineNumber << endl
		         << "startDefBlock : " << m_startDefBlock << endl
		         << "lengthDefBlock : " << m_lengthDefBlock;
	}

	/** Defines <i> operator<< </i> for CppParameter.
	@param o Reference of C++ stream object.
	@param elem Const reference of CppParameter object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _CppParameter<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class CppParameterIDEquality;
	class ParamOrderEquality;
	class ParamOrderInferior;
	class ParamOrderSuperior;
	class ParamTypeEquality;
	class ParamTypeInferior;
	class ParamTypeSuperior;
	class IsConstEquality;
	class IsConstInferior;
	class IsConstSuperior;
	class DefaultValueEquality;
	class DefaultValueInferior;
	class DefaultValueSuperior;
	class DecNameEquality;
	class DecNameInferior;
	class DecNameSuperior;
	class DecLineNumberEquality;
	class DecLineNumberInferior;
	class DecLineNumberSuperior;
	class StartDecBlockEquality;
	class StartDecBlockInferior;
	class StartDecBlockSuperior;
	class LengthDecBlockEquality;
	class LengthDecBlockInferior;
	class LengthDecBlockSuperior;
	class DefNameEquality;
	class DefNameInferior;
	class DefNameSuperior;
	class DefLineNumberEquality;
	class DefLineNumberInferior;
	class DefLineNumberSuperior;
	class StartDefBlockEquality;
	class StartDefBlockInferior;
	class StartDefBlockSuperior;
	class LengthDefBlockEquality;
	class LengthDefBlockInferior;
	class LengthDefBlockSuperior;
};

typedef _CppParameter<ucs> UniCppParameter;
typedef _CppParameter<ansi> CppParameter;

NAMESPACE_END

#undef C
#undef A

#include "cppParameterPredicate.hpp"

#endif
