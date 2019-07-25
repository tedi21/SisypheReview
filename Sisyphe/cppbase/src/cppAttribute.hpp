/* 
 * cppAttribute.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPATTRIBUTE_HPP_
#define _CPPATTRIBUTE_HPP_

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
class _CppAttributeAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _CppClass;

/// cppAttribute table represents an attribute.
template <class EncodingT>
class  _CppAttribute {
private :
	long long	m_identifier;
	typename EncodingT::string_t	m_attrType;
	typename EncodingT::string_t	m_name;
	typename EncodingT::string_t	m_accessSpecifier;
	long long	m_isStatic;
	long long	m_isConst;
	long long	m_isConstexpr;
	typename EncodingT::string_t	m_constValue;
	boost::shared_ptr< _CppClass<EncodingT> >	m_cppClass;
	long long	m_lineNumber;
	long long	m_startBlock;
	long long	m_lengthBlock;
	Category*	m_logger;

protected :
	friend class data_access::_CppAttributeAccess<EncodingT>;

	/** Creates a new element CppAttribute.
	@param identifier 
	@param attrType 
	@param name 
	@param accessSpecifier 
	@param isStatic 
	@param isConst 
	@param isConstexpr 
	@param constValue 
	@param lineNumber 
	@param startBlock 
	@param lengthBlock 
	*/
	_CppAttribute(long long identifier,
				const typename EncodingT::string_t& attrType,
				const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& accessSpecifier,
				long long isStatic,
				long long isConst,
				long long isConstexpr,
				const typename EncodingT::string_t& constValue,
				long long lineNumber,
				long long startBlock,
				long long lengthBlock)
	: m_identifier(identifier),
	  m_attrType(attrType),
	  m_name(name),
	  m_accessSpecifier(accessSpecifier),
	  m_isStatic(isStatic),
	  m_isConst(isConst),
	  m_isConstexpr(isConstexpr),
	  m_constValue(constValue),
	  m_lineNumber(lineNumber),
	  m_startBlock(startBlock),
	  m_lengthBlock(lengthBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppAttribute "
				<< m_identifier << ' '
				<< A(m_attrType) << ' '
				<< A(m_name) << ' '
				<< A(m_accessSpecifier) << ' '
				<< m_isStatic << ' '
				<< m_isConst << ' '
				<< m_isConstexpr << ' '
				<< A(m_constValue) << ' '
				<< m_lineNumber << ' '
				<< m_startBlock << ' '
				<< m_lengthBlock << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppAttribute.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element CppAttribute.
	*/
	_CppAttribute()
	: m_identifier(-1),
	  m_attrType(EncodingT::EMPTY),
	  m_name(EncodingT::EMPTY),
	  m_accessSpecifier(EncodingT::EMPTY),
	  m_isStatic(0),
	  m_isConst(0),
	  m_isConstexpr(0),
	  m_constValue(EncodingT::EMPTY),
	  m_lineNumber(0),
	  m_startBlock(0),
	  m_lengthBlock(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppAttribute ";
	}

	/** Creates a new element CppAttribute.
	@param attrType 
	@param name 
	@param accessSpecifier 
	@param isStatic 
	@param isConst 
	@param isConstexpr 
	@param constValue 
	@param lineNumber 
	@param startBlock 
	@param lengthBlock 
	*/
	_CppAttribute(const typename EncodingT::string_t& attrType,
				const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& accessSpecifier,
				long long isStatic,
				long long isConst,
				long long isConstexpr,
				const typename EncodingT::string_t& constValue,
				long long lineNumber,
				long long startBlock,
				long long lengthBlock)
	: m_identifier(-1),
	  m_attrType(attrType),
	  m_name(name),
	  m_accessSpecifier(accessSpecifier),
	  m_isStatic(isStatic),
	  m_isConst(isConst),
	  m_isConstexpr(isConstexpr),
	  m_constValue(constValue),
	  m_lineNumber(lineNumber),
	  m_startBlock(startBlock),
	  m_lengthBlock(lengthBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppAttribute "
				<< m_identifier << ' '
				<< A(m_attrType) << ' '
				<< A(m_name) << ' '
				<< A(m_accessSpecifier) << ' '
				<< m_isStatic << ' '
				<< m_isConst << ' '
				<< m_isConstexpr << ' '
				<< A(m_constValue) << ' '
				<< m_lineNumber << ' '
				<< m_startBlock << ' '
				<< m_lengthBlock << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in CppAttribute.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>attrType</i> in CppAttribute.
	@return 
	*/
	const typename EncodingT::string_t& getAttrType() const 
	{
		return m_attrType;
	}

	/** Sets a value of the element <i>attrType</i> in CppAttribute.
	@param attrType 
	*/
	void setAttrType(const typename EncodingT::string_t& attrType)  
	{
		m_attrType = attrType;
	}

	/** Returns a const reference to the element <i>name</i> in CppAttribute.
	@return 
	*/
	const typename EncodingT::string_t& getName() const 
	{
		return m_name;
	}

	/** Sets a value of the element <i>name</i> in CppAttribute.
	@param name 
	*/
	void setName(const typename EncodingT::string_t& name)  
	{
		m_name = name;
	}

	/** Returns a const reference to the element <i>accessSpecifier</i> in CppAttribute.
	@return 
	*/
	const typename EncodingT::string_t& getAccessSpecifier() const 
	{
		return m_accessSpecifier;
	}

	/** Sets a value of the element <i>accessSpecifier</i> in CppAttribute.
	@param accessSpecifier 
	*/
	void setAccessSpecifier(const typename EncodingT::string_t& accessSpecifier)  
	{
		m_accessSpecifier = accessSpecifier;
	}

	/** Returns a const reference to the element <i>isStatic</i> in CppAttribute.
	@return 
	*/
	long long getIsStatic() const 
	{
		return m_isStatic;
	}

	/** Sets a value of the element <i>isStatic</i> in CppAttribute.
	@param isStatic 
	*/
	void setIsStatic(long long isStatic)  
	{
		m_isStatic = isStatic;
	}

	/** Returns a const reference to the element <i>isConst</i> in CppAttribute.
	@return 
	*/
	long long getIsConst() const 
	{
		return m_isConst;
	}

	/** Sets a value of the element <i>isConst</i> in CppAttribute.
	@param isConst 
	*/
	void setIsConst(long long isConst)  
	{
		m_isConst = isConst;
	}

	/** Returns a const reference to the element <i>isConstexpr</i> in CppAttribute.
	@return 
	*/
	long long getIsConstexpr() const 
	{
		return m_isConstexpr;
	}

	/** Sets a value of the element <i>isConstexpr</i> in CppAttribute.
	@param isConstexpr 
	*/
	void setIsConstexpr(long long isConstexpr)  
	{
		m_isConstexpr = isConstexpr;
	}

	/** Returns a const reference to the element <i>constValue</i> in CppAttribute.
	@return 
	*/
	const typename EncodingT::string_t& getConstValue() const 
	{
		return m_constValue;
	}

	/** Sets a value of the element <i>constValue</i> in CppAttribute.
	@param constValue 
	*/
	void setConstValue(const typename EncodingT::string_t& constValue)  
	{
		m_constValue = constValue;
	}

	/** Returns a const reference to the element <i>cppClass</i> in CppAttribute.
	@return 
	*/
	boost::shared_ptr< _CppClass<EncodingT> > getCppClass() const 
	{
		return m_cppClass;
	}

	/** Sets a value of the element <i>cppClass</i> in CppAttribute.
	@param cppClass 
	*/
	void setCppClass(boost::shared_ptr< _CppClass<EncodingT> > cppClass)  
	{
		m_cppClass = cppClass;
	}

	/** Returns whether the element <i>cppClass</i> in CppAttribute is NULL.
	@return True if the element <i>cppClass</i> is NULL, false otherwise.
	*/
	bool isNullCppClass() const 
	{
		return !m_cppClass;
	}

	/** Removes from CppAttribute an element <i>cppClass</i>.
	*/
	void eraseCppClass()  
	{
		m_cppClass.reset();
	}

	/** Returns a const reference to the element <i>lineNumber</i> in CppAttribute.
	@return 
	*/
	long long getLineNumber() const 
	{
		return m_lineNumber;
	}

	/** Sets a value of the element <i>lineNumber</i> in CppAttribute.
	@param lineNumber 
	*/
	void setLineNumber(long long lineNumber)  
	{
		m_lineNumber = lineNumber;
	}

	/** Returns a const reference to the element <i>startBlock</i> in CppAttribute.
	@return 
	*/
	long long getStartBlock() const 
	{
		return m_startBlock;
	}

	/** Sets a value of the element <i>startBlock</i> in CppAttribute.
	@param startBlock 
	*/
	void setStartBlock(long long startBlock)  
	{
		m_startBlock = startBlock;
	}

	/** Returns a const reference to the element <i>lengthBlock</i> in CppAttribute.
	@return 
	*/
	long long getLengthBlock() const 
	{
		return m_lengthBlock;
	}

	/** Sets a value of the element <i>lengthBlock</i> in CppAttribute.
	@param lengthBlock 
	*/
	void setLengthBlock(long long lengthBlock)  
	{
		m_lengthBlock = lengthBlock;
	}

	/** Prints CppAttribute object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "CppAttribute" << endl
		         << "identifier : " << m_identifier << endl
		         << "attrType : " << A(m_attrType) << endl
		         << "name : " << A(m_name) << endl
		         << "accessSpecifier : " << A(m_accessSpecifier) << endl
		         << "isStatic : " << m_isStatic << endl
		         << "isConst : " << m_isConst << endl
		         << "isConstexpr : " << m_isConstexpr << endl
		         << "constValue : " << A(m_constValue) << endl
		         << "lineNumber : " << m_lineNumber << endl
		         << "startBlock : " << m_startBlock << endl
		         << "lengthBlock : " << m_lengthBlock;
	}

	/** Defines <i> operator<< </i> for CppAttribute.
	@param o Reference of C++ stream object.
	@param elem Const reference of CppAttribute object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _CppAttribute<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class CppAttributeIDEquality;
	class AttrTypeEquality;
	class AttrTypeInferior;
	class AttrTypeSuperior;
	class NameEquality;
	class NameInferior;
	class NameSuperior;
	class AccessSpecifierEquality;
	class AccessSpecifierInferior;
	class AccessSpecifierSuperior;
	class IsStaticEquality;
	class IsStaticInferior;
	class IsStaticSuperior;
	class IsConstEquality;
	class IsConstInferior;
	class IsConstSuperior;
	class IsConstexprEquality;
	class IsConstexprInferior;
	class IsConstexprSuperior;
	class ConstValueEquality;
	class ConstValueInferior;
	class ConstValueSuperior;
	class LineNumberEquality;
	class LineNumberInferior;
	class LineNumberSuperior;
	class StartBlockEquality;
	class StartBlockInferior;
	class StartBlockSuperior;
	class LengthBlockEquality;
	class LengthBlockInferior;
	class LengthBlockSuperior;
};

typedef _CppAttribute<ucs> UniCppAttribute;
typedef _CppAttribute<ansi> CppAttribute;

NAMESPACE_END

#undef C
#undef A

#include "cppAttributePredicate.hpp"

#endif
