/* 
 * cppVariable.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPVARIABLE_HPP_
#define _CPPVARIABLE_HPP_

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
class _CppVariableAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _CppFunction;

template <class EncodingT>
class _CppFile;

/// cppVariable table represents a variable.
template <class EncodingT>
class  _CppVariable {
private :
	long long	m_identifier;
	typename EncodingT::string_t	m_varType;
	typename EncodingT::string_t	m_name;
	long long	m_isStatic;
	long long	m_isConst;
	long long	m_isConstexpr;
	boost::shared_ptr< _CppFunction<EncodingT> >	m_cppFunction;
	long long	m_lineNumber;
	long long	m_startBlock;
	long long	m_lengthBlock;
	boost::shared_ptr< _CppFile<EncodingT> >	m_cppFile;
	Category*	m_logger;

protected :
	friend class data_access::_CppVariableAccess<EncodingT>;

	/** Creates a new element CppVariable.
	@param identifier 
	@param varType 
	@param name 
	@param isStatic 
	@param isConst 
	@param isConstexpr 
	@param lineNumber 
	@param startBlock 
	@param lengthBlock 
	*/
	_CppVariable(long long identifier,
				const typename EncodingT::string_t& varType,
				const typename EncodingT::string_t& name,
				long long isStatic,
				long long isConst,
				long long isConstexpr,
				long long lineNumber,
				long long startBlock,
				long long lengthBlock)
	: m_identifier(identifier),
	  m_varType(varType),
	  m_name(name),
	  m_isStatic(isStatic),
	  m_isConst(isConst),
	  m_isConstexpr(isConstexpr),
	  m_lineNumber(lineNumber),
	  m_startBlock(startBlock),
	  m_lengthBlock(lengthBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppVariable "
				<< m_identifier << ' '
				<< A(m_varType) << ' '
				<< A(m_name) << ' '
				<< m_isStatic << ' '
				<< m_isConst << ' '
				<< m_isConstexpr << ' '
				<< m_lineNumber << ' '
				<< m_startBlock << ' '
				<< m_lengthBlock << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppVariable.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element CppVariable.
	*/
	_CppVariable()
	: m_identifier(-1),
	  m_varType(EncodingT::EMPTY),
	  m_name(EncodingT::EMPTY),
	  m_isStatic(0),
	  m_isConst(0),
	  m_isConstexpr(0),
	  m_lineNumber(0),
	  m_startBlock(0),
	  m_lengthBlock(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppVariable ";
	}

	/** Creates a new element CppVariable.
	@param varType 
	@param name 
	@param isStatic 
	@param isConst 
	@param isConstexpr 
	@param lineNumber 
	@param startBlock 
	@param lengthBlock 
	*/
	_CppVariable(const typename EncodingT::string_t& varType,
				const typename EncodingT::string_t& name,
				long long isStatic,
				long long isConst,
				long long isConstexpr,
				long long lineNumber,
				long long startBlock,
				long long lengthBlock)
	: m_identifier(-1),
	  m_varType(varType),
	  m_name(name),
	  m_isStatic(isStatic),
	  m_isConst(isConst),
	  m_isConstexpr(isConstexpr),
	  m_lineNumber(lineNumber),
	  m_startBlock(startBlock),
	  m_lengthBlock(lengthBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppVariable "
				<< m_identifier << ' '
				<< A(m_varType) << ' '
				<< A(m_name) << ' '
				<< m_isStatic << ' '
				<< m_isConst << ' '
				<< m_isConstexpr << ' '
				<< m_lineNumber << ' '
				<< m_startBlock << ' '
				<< m_lengthBlock << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in CppVariable.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>varType</i> in CppVariable.
	@return 
	*/
	const typename EncodingT::string_t& getVarType() const 
	{
		return m_varType;
	}

	/** Sets a value of the element <i>varType</i> in CppVariable.
	@param varType 
	*/
	void setVarType(const typename EncodingT::string_t& varType)  
	{
		m_varType = varType;
	}

	/** Returns a const reference to the element <i>name</i> in CppVariable.
	@return 
	*/
	const typename EncodingT::string_t& getName() const 
	{
		return m_name;
	}

	/** Sets a value of the element <i>name</i> in CppVariable.
	@param name 
	*/
	void setName(const typename EncodingT::string_t& name)  
	{
		m_name = name;
	}

	/** Returns a const reference to the element <i>isStatic</i> in CppVariable.
	@return 
	*/
	long long getIsStatic() const 
	{
		return m_isStatic;
	}

	/** Sets a value of the element <i>isStatic</i> in CppVariable.
	@param isStatic 
	*/
	void setIsStatic(long long isStatic)  
	{
		m_isStatic = isStatic;
	}

	/** Returns a const reference to the element <i>isConst</i> in CppVariable.
	@return 
	*/
	long long getIsConst() const 
	{
		return m_isConst;
	}

	/** Sets a value of the element <i>isConst</i> in CppVariable.
	@param isConst 
	*/
	void setIsConst(long long isConst)  
	{
		m_isConst = isConst;
	}

	/** Returns a const reference to the element <i>isConstexpr</i> in CppVariable.
	@return 
	*/
	long long getIsConstexpr() const 
	{
		return m_isConstexpr;
	}

	/** Sets a value of the element <i>isConstexpr</i> in CppVariable.
	@param isConstexpr 
	*/
	void setIsConstexpr(long long isConstexpr)  
	{
		m_isConstexpr = isConstexpr;
	}

	/** Returns a const reference to the element <i>cppFunction</i> in CppVariable.
	@return 
	*/
	boost::shared_ptr< _CppFunction<EncodingT> > getCppFunction() const 
	{
		return m_cppFunction;
	}

	/** Sets a value of the element <i>cppFunction</i> in CppVariable.
	@param cppFunction 
	*/
	void setCppFunction(boost::shared_ptr< _CppFunction<EncodingT> > cppFunction)  
	{
		m_cppFunction = cppFunction;
	}

	/** Returns whether the element <i>cppFunction</i> in CppVariable is NULL.
	@return True if the element <i>cppFunction</i> is NULL, false otherwise.
	*/
	bool isNullCppFunction() const 
	{
		return !m_cppFunction;
	}

	/** Removes from CppVariable an element <i>cppFunction</i>.
	*/
	void eraseCppFunction()  
	{
		m_cppFunction.reset();
	}

	/** Returns a const reference to the element <i>lineNumber</i> in CppVariable.
	@return 
	*/
	long long getLineNumber() const 
	{
		return m_lineNumber;
	}

	/** Sets a value of the element <i>lineNumber</i> in CppVariable.
	@param lineNumber 
	*/
	void setLineNumber(long long lineNumber)  
	{
		m_lineNumber = lineNumber;
	}

	/** Returns a const reference to the element <i>startBlock</i> in CppVariable.
	@return 
	*/
	long long getStartBlock() const 
	{
		return m_startBlock;
	}

	/** Sets a value of the element <i>startBlock</i> in CppVariable.
	@param startBlock 
	*/
	void setStartBlock(long long startBlock)  
	{
		m_startBlock = startBlock;
	}

	/** Returns a const reference to the element <i>lengthBlock</i> in CppVariable.
	@return 
	*/
	long long getLengthBlock() const 
	{
		return m_lengthBlock;
	}

	/** Sets a value of the element <i>lengthBlock</i> in CppVariable.
	@param lengthBlock 
	*/
	void setLengthBlock(long long lengthBlock)  
	{
		m_lengthBlock = lengthBlock;
	}

	/** Returns a const reference to the element <i>cppFile</i> in CppVariable.
	@return 
	*/
	boost::shared_ptr< _CppFile<EncodingT> > getCppFile() const 
	{
		return m_cppFile;
	}

	/** Sets a value of the element <i>cppFile</i> in CppVariable.
	@param cppFile 
	*/
	void setCppFile(boost::shared_ptr< _CppFile<EncodingT> > cppFile)  
	{
		m_cppFile = cppFile;
	}

	/** Returns whether the element <i>cppFile</i> in CppVariable is NULL.
	@return True if the element <i>cppFile</i> is NULL, false otherwise.
	*/
	bool isNullCppFile() const 
	{
		return !m_cppFile;
	}

	/** Removes from CppVariable an element <i>cppFile</i>.
	*/
	void eraseCppFile()  
	{
		m_cppFile.reset();
	}

	/** Prints CppVariable object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "CppVariable" << endl
		         << "identifier : " << m_identifier << endl
		         << "varType : " << A(m_varType) << endl
		         << "name : " << A(m_name) << endl
		         << "isStatic : " << m_isStatic << endl
		         << "isConst : " << m_isConst << endl
		         << "isConstexpr : " << m_isConstexpr << endl
		         << "lineNumber : " << m_lineNumber << endl
		         << "startBlock : " << m_startBlock << endl
		         << "lengthBlock : " << m_lengthBlock;
	}

	/** Defines <i> operator<< </i> for CppVariable.
	@param o Reference of C++ stream object.
	@param elem Const reference of CppVariable object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _CppVariable<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class CppVariableIDEquality;
	class VarTypeEquality;
	class VarTypeInferior;
	class VarTypeSuperior;
	class NameEquality;
	class NameInferior;
	class NameSuperior;
	class IsStaticEquality;
	class IsStaticInferior;
	class IsStaticSuperior;
	class IsConstEquality;
	class IsConstInferior;
	class IsConstSuperior;
	class IsConstexprEquality;
	class IsConstexprInferior;
	class IsConstexprSuperior;
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

typedef _CppVariable<ucs> UniCppVariable;
typedef _CppVariable<ansi> CppVariable;

NAMESPACE_END

#undef C
#undef A

#include "cppVariablePredicate.hpp"

#endif
