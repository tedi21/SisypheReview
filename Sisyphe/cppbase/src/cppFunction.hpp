/* 
 * cppFunction.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPFUNCTION_HPP_
#define _CPPFUNCTION_HPP_

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
class _CppFunctionAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _CppParameter;

template <class EncodingT>
class _CppVariable;

template <class EncodingT>
class _CppFile;

template <class EncodingT>
class _CppFile;

template <class EncodingT>
class _CppClass;

/// cppFunction table represents a function.
template <class EncodingT>
class  _CppFunction {
private :
	boost::shared_ptr< _CppFile<EncodingT> >	m_cppDeclarationFile;
	boost::shared_ptr< _CppFile<EncodingT> >	m_cppDefinitionFile;
	long long	m_identifier;
	typename EncodingT::string_t	m_name;
	boost::shared_ptr< _CppClass<EncodingT> >	m_cppClass;
	typename EncodingT::string_t	m_accessSpecifier;
	typename EncodingT::string_t	m_returnType;
	long long	m_isConst;
	long long	m_isVirtual;
	long long	m_isVirtualPure;
	long long	m_isStatic;
	long long	m_isOperator;
	long long	m_isDestructor;
	long long	m_isConstructor;
	long long	m_isVariadic;
	long long	m_isTemplate;
	long long	m_isInline;
	long long	m_isConstexpr;
	long long	m_isOverride;
	long long	m_isFinal;
	long long	m_isNoexcept;
	typename EncodingT::string_t	m_signature;
	long long	m_decLineNumber;
	long long	m_startDecBlock;
	long long	m_lengthDecBlock;
	long long	m_linesCount;
	long long	m_complexity;
	long long	m_defLineNumber;
	long long	m_startDefBlock;
	long long	m_lengthDefBlock;
	typedef std::vector< boost::shared_ptr< _CppParameter<EncodingT> > >	vector_cppParameter;
	vector_cppParameter	m_cppParameters;
	typedef std::vector< boost::shared_ptr< _CppVariable<EncodingT> > >	vector_cppVariable;
	vector_cppVariable	m_cppVariables;
	Category*	m_logger;

protected :
	friend class data_access::_CppFunctionAccess<EncodingT>;

	/** Creates a new element CppFunction.
	@param identifier 
	@param name 
	@param accessSpecifier 
	@param returnType 
	@param isConst 
	@param isVirtual 
	@param isVirtualPure 
	@param isStatic 
	@param isOperator 
	@param isDestructor 
	@param isConstructor 
	@param isVariadic 
	@param isTemplate 
	@param isInline 
	@param isConstexpr 
	@param isOverride 
	@param isFinal 
	@param isNoexcept 
	@param signature 
	@param decLineNumber 
	@param startDecBlock 
	@param lengthDecBlock 
	@param linesCount 
	@param complexity 
	@param defLineNumber 
	@param startDefBlock 
	@param lengthDefBlock 
	*/
	_CppFunction(long long identifier,
				const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& accessSpecifier,
				const typename EncodingT::string_t& returnType,
				long long isConst,
				long long isVirtual,
				long long isVirtualPure,
				long long isStatic,
				long long isOperator,
				long long isDestructor,
				long long isConstructor,
				long long isVariadic,
				long long isTemplate,
				long long isInline,
				long long isConstexpr,
				long long isOverride,
				long long isFinal,
				long long isNoexcept,
				const typename EncodingT::string_t& signature,
				long long decLineNumber,
				long long startDecBlock,
				long long lengthDecBlock,
				long long linesCount,
				long long complexity,
				long long defLineNumber,
				long long startDefBlock,
				long long lengthDefBlock)
	: m_identifier(identifier),
	  m_name(name),
	  m_accessSpecifier(accessSpecifier),
	  m_returnType(returnType),
	  m_isConst(isConst),
	  m_isVirtual(isVirtual),
	  m_isVirtualPure(isVirtualPure),
	  m_isStatic(isStatic),
	  m_isOperator(isOperator),
	  m_isDestructor(isDestructor),
	  m_isConstructor(isConstructor),
	  m_isVariadic(isVariadic),
	  m_isTemplate(isTemplate),
	  m_isInline(isInline),
	  m_isConstexpr(isConstexpr),
	  m_isOverride(isOverride),
	  m_isFinal(isFinal),
	  m_isNoexcept(isNoexcept),
	  m_signature(signature),
	  m_decLineNumber(decLineNumber),
	  m_startDecBlock(startDecBlock),
	  m_lengthDecBlock(lengthDecBlock),
	  m_linesCount(linesCount),
	  m_complexity(complexity),
	  m_defLineNumber(defLineNumber),
	  m_startDefBlock(startDefBlock),
	  m_lengthDefBlock(lengthDefBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppFunction "
				<< m_identifier << ' '
				<< A(m_name) << ' '
				<< A(m_accessSpecifier) << ' '
				<< A(m_returnType) << ' '
				<< m_isConst << ' '
				<< m_isVirtual << ' '
				<< m_isVirtualPure << ' '
				<< m_isStatic << ' '
				<< m_isOperator << ' '
				<< m_isDestructor << ' '
				<< m_isConstructor << ' '
				<< m_isVariadic << ' '
				<< m_isTemplate << ' '
				<< m_isInline << ' '
				<< m_isConstexpr << ' '
				<< m_isOverride << ' '
				<< m_isFinal << ' '
				<< m_isNoexcept << ' '
				<< A(m_signature) << ' '
				<< m_decLineNumber << ' '
				<< m_startDecBlock << ' '
				<< m_lengthDecBlock << ' '
				<< m_linesCount << ' '
				<< m_complexity << ' '
				<< m_defLineNumber << ' '
				<< m_startDefBlock << ' '
				<< m_lengthDefBlock << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppFunction.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element CppFunction.
	*/
	_CppFunction()
	: m_identifier(-1),
	  m_name(EncodingT::EMPTY),
	  m_accessSpecifier(EncodingT::EMPTY),
	  m_returnType(EncodingT::EMPTY),
	  m_isConst(0),
	  m_isVirtual(0),
	  m_isVirtualPure(0),
	  m_isStatic(0),
	  m_isOperator(0),
	  m_isDestructor(0),
	  m_isConstructor(0),
	  m_isVariadic(0),
	  m_isTemplate(0),
	  m_isInline(0),
	  m_isConstexpr(0),
	  m_isOverride(0),
	  m_isFinal(0),
	  m_isNoexcept(0),
	  m_signature(EncodingT::EMPTY),
	  m_decLineNumber(0),
	  m_startDecBlock(0),
	  m_lengthDecBlock(0),
	  m_linesCount(0),
	  m_complexity(0),
	  m_defLineNumber(0),
	  m_startDefBlock(0),
	  m_lengthDefBlock(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppFunction ";
	}

	/** Creates a new element CppFunction.
	@param name 
	@param accessSpecifier 
	@param returnType 
	@param isConst 
	@param isVirtual 
	@param isVirtualPure 
	@param isStatic 
	@param isOperator 
	@param isDestructor 
	@param isConstructor 
	@param isVariadic 
	@param isTemplate 
	@param isInline 
	@param isConstexpr 
	@param isOverride 
	@param isFinal 
	@param isNoexcept 
	@param signature 
	@param decLineNumber 
	@param startDecBlock 
	@param lengthDecBlock 
	@param linesCount 
	@param complexity 
	@param defLineNumber 
	@param startDefBlock 
	@param lengthDefBlock 
	*/
	_CppFunction(const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& accessSpecifier,
				const typename EncodingT::string_t& returnType,
				long long isConst,
				long long isVirtual,
				long long isVirtualPure,
				long long isStatic,
				long long isOperator,
				long long isDestructor,
				long long isConstructor,
				long long isVariadic,
				long long isTemplate,
				long long isInline,
				long long isConstexpr,
				long long isOverride,
				long long isFinal,
				long long isNoexcept,
				const typename EncodingT::string_t& signature,
				long long decLineNumber,
				long long startDecBlock,
				long long lengthDecBlock,
				long long linesCount,
				long long complexity,
				long long defLineNumber,
				long long startDefBlock,
				long long lengthDefBlock)
	: m_identifier(-1),
	  m_name(name),
	  m_accessSpecifier(accessSpecifier),
	  m_returnType(returnType),
	  m_isConst(isConst),
	  m_isVirtual(isVirtual),
	  m_isVirtualPure(isVirtualPure),
	  m_isStatic(isStatic),
	  m_isOperator(isOperator),
	  m_isDestructor(isDestructor),
	  m_isConstructor(isConstructor),
	  m_isVariadic(isVariadic),
	  m_isTemplate(isTemplate),
	  m_isInline(isInline),
	  m_isConstexpr(isConstexpr),
	  m_isOverride(isOverride),
	  m_isFinal(isFinal),
	  m_isNoexcept(isNoexcept),
	  m_signature(signature),
	  m_decLineNumber(decLineNumber),
	  m_startDecBlock(startDecBlock),
	  m_lengthDecBlock(lengthDecBlock),
	  m_linesCount(linesCount),
	  m_complexity(complexity),
	  m_defLineNumber(defLineNumber),
	  m_startDefBlock(startDefBlock),
	  m_lengthDefBlock(lengthDefBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppFunction "
				<< m_identifier << ' '
				<< A(m_name) << ' '
				<< A(m_accessSpecifier) << ' '
				<< A(m_returnType) << ' '
				<< m_isConst << ' '
				<< m_isVirtual << ' '
				<< m_isVirtualPure << ' '
				<< m_isStatic << ' '
				<< m_isOperator << ' '
				<< m_isDestructor << ' '
				<< m_isConstructor << ' '
				<< m_isVariadic << ' '
				<< m_isTemplate << ' '
				<< m_isInline << ' '
				<< m_isConstexpr << ' '
				<< m_isOverride << ' '
				<< m_isFinal << ' '
				<< m_isNoexcept << ' '
				<< A(m_signature) << ' '
				<< m_decLineNumber << ' '
				<< m_startDecBlock << ' '
				<< m_lengthDecBlock << ' '
				<< m_linesCount << ' '
				<< m_complexity << ' '
				<< m_defLineNumber << ' '
				<< m_startDefBlock << ' '
				<< m_lengthDefBlock << ' ';
	}

	/** Returns a const reference to the element <i>cppDeclarationFile</i> in CppFunction.
	@return 
	*/
	boost::shared_ptr< _CppFile<EncodingT> > getCppDeclarationFile() const 
	{
		return m_cppDeclarationFile;
	}

	/** Sets a value of the element <i>cppDeclarationFile</i> in CppFunction.
	@param cppDeclarationFile 
	*/
	void setCppDeclarationFile(boost::shared_ptr< _CppFile<EncodingT> > cppDeclarationFile)  
	{
		m_cppDeclarationFile = cppDeclarationFile;
	}

	/** Returns whether the element <i>cppDeclarationFile</i> in CppFunction is NULL.
	@return True if the element <i>cppDeclarationFile</i> is NULL, false otherwise.
	*/
	bool isNullCppDeclarationFile() const 
	{
		return !m_cppDeclarationFile;
	}

	/** Removes from CppFunction an element <i>cppDeclarationFile</i>.
	*/
	void eraseCppDeclarationFile()  
	{
		m_cppDeclarationFile.reset();
	}

	/** Returns a const reference to the element <i>cppDefinitionFile</i> in CppFunction.
	@return 
	*/
	boost::shared_ptr< _CppFile<EncodingT> > getCppDefinitionFile() const 
	{
		return m_cppDefinitionFile;
	}

	/** Sets a value of the element <i>cppDefinitionFile</i> in CppFunction.
	@param cppDefinitionFile 
	*/
	void setCppDefinitionFile(boost::shared_ptr< _CppFile<EncodingT> > cppDefinitionFile)  
	{
		m_cppDefinitionFile = cppDefinitionFile;
	}

	/** Returns whether the element <i>cppDefinitionFile</i> in CppFunction is NULL.
	@return True if the element <i>cppDefinitionFile</i> is NULL, false otherwise.
	*/
	bool isNullCppDefinitionFile() const 
	{
		return !m_cppDefinitionFile;
	}

	/** Removes from CppFunction an element <i>cppDefinitionFile</i>.
	*/
	void eraseCppDefinitionFile()  
	{
		m_cppDefinitionFile.reset();
	}

	/** Returns a const reference to the element <i>identifier</i> in CppFunction.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>name</i> in CppFunction.
	@return 
	*/
	const typename EncodingT::string_t& getName() const 
	{
		return m_name;
	}

	/** Sets a value of the element <i>name</i> in CppFunction.
	@param name 
	*/
	void setName(const typename EncodingT::string_t& name)  
	{
		m_name = name;
	}

	/** Returns a const reference to the element <i>cppClass</i> in CppFunction.
	@return 
	*/
	boost::shared_ptr< _CppClass<EncodingT> > getCppClass() const 
	{
		return m_cppClass;
	}

	/** Sets a value of the element <i>cppClass</i> in CppFunction.
	@param cppClass 
	*/
	void setCppClass(boost::shared_ptr< _CppClass<EncodingT> > cppClass)  
	{
		m_cppClass = cppClass;
	}

	/** Returns whether the element <i>cppClass</i> in CppFunction is NULL.
	@return True if the element <i>cppClass</i> is NULL, false otherwise.
	*/
	bool isNullCppClass() const 
	{
		return !m_cppClass;
	}

	/** Removes from CppFunction an element <i>cppClass</i>.
	*/
	void eraseCppClass()  
	{
		m_cppClass.reset();
	}

	/** Returns a const reference to the element <i>accessSpecifier</i> in CppFunction.
	@return 
	*/
	const typename EncodingT::string_t& getAccessSpecifier() const 
	{
		return m_accessSpecifier;
	}

	/** Sets a value of the element <i>accessSpecifier</i> in CppFunction.
	@param accessSpecifier 
	*/
	void setAccessSpecifier(const typename EncodingT::string_t& accessSpecifier)  
	{
		m_accessSpecifier = accessSpecifier;
	}

	/** Returns a const reference to the element <i>returnType</i> in CppFunction.
	@return 
	*/
	const typename EncodingT::string_t& getReturnType() const 
	{
		return m_returnType;
	}

	/** Sets a value of the element <i>returnType</i> in CppFunction.
	@param returnType 
	*/
	void setReturnType(const typename EncodingT::string_t& returnType)  
	{
		m_returnType = returnType;
	}

	/** Returns a const reference to the element <i>isConst</i> in CppFunction.
	@return 
	*/
	long long getIsConst() const 
	{
		return m_isConst;
	}

	/** Sets a value of the element <i>isConst</i> in CppFunction.
	@param isConst 
	*/
	void setIsConst(long long isConst)  
	{
		m_isConst = isConst;
	}

	/** Returns a const reference to the element <i>isVirtual</i> in CppFunction.
	@return 
	*/
	long long getIsVirtual() const 
	{
		return m_isVirtual;
	}

	/** Sets a value of the element <i>isVirtual</i> in CppFunction.
	@param isVirtual 
	*/
	void setIsVirtual(long long isVirtual)  
	{
		m_isVirtual = isVirtual;
	}

	/** Returns a const reference to the element <i>isVirtualPure</i> in CppFunction.
	@return 
	*/
	long long getIsVirtualPure() const 
	{
		return m_isVirtualPure;
	}

	/** Sets a value of the element <i>isVirtualPure</i> in CppFunction.
	@param isVirtualPure 
	*/
	void setIsVirtualPure(long long isVirtualPure)  
	{
		m_isVirtualPure = isVirtualPure;
	}

	/** Returns a const reference to the element <i>isStatic</i> in CppFunction.
	@return 
	*/
	long long getIsStatic() const 
	{
		return m_isStatic;
	}

	/** Sets a value of the element <i>isStatic</i> in CppFunction.
	@param isStatic 
	*/
	void setIsStatic(long long isStatic)  
	{
		m_isStatic = isStatic;
	}

	/** Returns a const reference to the element <i>isOperator</i> in CppFunction.
	@return 
	*/
	long long getIsOperator() const 
	{
		return m_isOperator;
	}

	/** Sets a value of the element <i>isOperator</i> in CppFunction.
	@param isOperator 
	*/
	void setIsOperator(long long isOperator)  
	{
		m_isOperator = isOperator;
	}

	/** Returns a const reference to the element <i>isDestructor</i> in CppFunction.
	@return 
	*/
	long long getIsDestructor() const 
	{
		return m_isDestructor;
	}

	/** Sets a value of the element <i>isDestructor</i> in CppFunction.
	@param isDestructor 
	*/
	void setIsDestructor(long long isDestructor)  
	{
		m_isDestructor = isDestructor;
	}

	/** Returns a const reference to the element <i>isConstructor</i> in CppFunction.
	@return 
	*/
	long long getIsConstructor() const 
	{
		return m_isConstructor;
	}

	/** Sets a value of the element <i>isConstructor</i> in CppFunction.
	@param isConstructor 
	*/
	void setIsConstructor(long long isConstructor)  
	{
		m_isConstructor = isConstructor;
	}

	/** Returns a const reference to the element <i>isVariadic</i> in CppFunction.
	@return 
	*/
	long long getIsVariadic() const 
	{
		return m_isVariadic;
	}

	/** Sets a value of the element <i>isVariadic</i> in CppFunction.
	@param isVariadic 
	*/
	void setIsVariadic(long long isVariadic)  
	{
		m_isVariadic = isVariadic;
	}

	/** Returns a const reference to the element <i>isTemplate</i> in CppFunction.
	@return 
	*/
	long long getIsTemplate() const 
	{
		return m_isTemplate;
	}

	/** Sets a value of the element <i>isTemplate</i> in CppFunction.
	@param isTemplate 
	*/
	void setIsTemplate(long long isTemplate)  
	{
		m_isTemplate = isTemplate;
	}

	/** Returns a const reference to the element <i>isInline</i> in CppFunction.
	@return 
	*/
	long long getIsInline() const 
	{
		return m_isInline;
	}

	/** Sets a value of the element <i>isInline</i> in CppFunction.
	@param isInline 
	*/
	void setIsInline(long long isInline)  
	{
		m_isInline = isInline;
	}

	/** Returns a const reference to the element <i>isConstexpr</i> in CppFunction.
	@return 
	*/
	long long getIsConstexpr() const 
	{
		return m_isConstexpr;
	}

	/** Sets a value of the element <i>isConstexpr</i> in CppFunction.
	@param isConstexpr 
	*/
	void setIsConstexpr(long long isConstexpr)  
	{
		m_isConstexpr = isConstexpr;
	}

	/** Returns a const reference to the element <i>isOverride</i> in CppFunction.
	@return 
	*/
	long long getIsOverride() const 
	{
		return m_isOverride;
	}

	/** Sets a value of the element <i>isOverride</i> in CppFunction.
	@param isOverride 
	*/
	void setIsOverride(long long isOverride)  
	{
		m_isOverride = isOverride;
	}

	/** Returns a const reference to the element <i>isFinal</i> in CppFunction.
	@return 
	*/
	long long getIsFinal() const 
	{
		return m_isFinal;
	}

	/** Sets a value of the element <i>isFinal</i> in CppFunction.
	@param isFinal 
	*/
	void setIsFinal(long long isFinal)  
	{
		m_isFinal = isFinal;
	}

	/** Returns a const reference to the element <i>isNoexcept</i> in CppFunction.
	@return 
	*/
	long long getIsNoexcept() const 
	{
		return m_isNoexcept;
	}

	/** Sets a value of the element <i>isNoexcept</i> in CppFunction.
	@param isNoexcept 
	*/
	void setIsNoexcept(long long isNoexcept)  
	{
		m_isNoexcept = isNoexcept;
	}

	/** Returns a const reference to the element <i>signature</i> in CppFunction.
	@return 
	*/
	const typename EncodingT::string_t& getSignature() const 
	{
		return m_signature;
	}

	/** Sets a value of the element <i>signature</i> in CppFunction.
	@param signature 
	*/
	void setSignature(const typename EncodingT::string_t& signature)  
	{
		m_signature = signature;
	}

	/** Returns a const reference to the element <i>decLineNumber</i> in CppFunction.
	@return 
	*/
	long long getDecLineNumber() const 
	{
		return m_decLineNumber;
	}

	/** Sets a value of the element <i>decLineNumber</i> in CppFunction.
	@param decLineNumber 
	*/
	void setDecLineNumber(long long decLineNumber)  
	{
		m_decLineNumber = decLineNumber;
	}

	/** Returns a const reference to the element <i>startDecBlock</i> in CppFunction.
	@return 
	*/
	long long getStartDecBlock() const 
	{
		return m_startDecBlock;
	}

	/** Sets a value of the element <i>startDecBlock</i> in CppFunction.
	@param startDecBlock 
	*/
	void setStartDecBlock(long long startDecBlock)  
	{
		m_startDecBlock = startDecBlock;
	}

	/** Returns a const reference to the element <i>lengthDecBlock</i> in CppFunction.
	@return 
	*/
	long long getLengthDecBlock() const 
	{
		return m_lengthDecBlock;
	}

	/** Sets a value of the element <i>lengthDecBlock</i> in CppFunction.
	@param lengthDecBlock 
	*/
	void setLengthDecBlock(long long lengthDecBlock)  
	{
		m_lengthDecBlock = lengthDecBlock;
	}

	/** Returns a const reference to the element <i>linesCount</i> in CppFunction.
	@return 
	*/
	long long getLinesCount() const 
	{
		return m_linesCount;
	}

	/** Sets a value of the element <i>linesCount</i> in CppFunction.
	@param linesCount 
	*/
	void setLinesCount(long long linesCount)  
	{
		m_linesCount = linesCount;
	}

	/** Returns a const reference to the element <i>complexity</i> in CppFunction.
	@return 
	*/
	long long getComplexity() const 
	{
		return m_complexity;
	}

	/** Sets a value of the element <i>complexity</i> in CppFunction.
	@param complexity 
	*/
	void setComplexity(long long complexity)  
	{
		m_complexity = complexity;
	}

	/** Returns a const reference to the element <i>defLineNumber</i> in CppFunction.
	@return 
	*/
	long long getDefLineNumber() const 
	{
		return m_defLineNumber;
	}

	/** Sets a value of the element <i>defLineNumber</i> in CppFunction.
	@param defLineNumber 
	*/
	void setDefLineNumber(long long defLineNumber)  
	{
		m_defLineNumber = defLineNumber;
	}

	/** Returns a const reference to the element <i>startDefBlock</i> in CppFunction.
	@return 
	*/
	long long getStartDefBlock() const 
	{
		return m_startDefBlock;
	}

	/** Sets a value of the element <i>startDefBlock</i> in CppFunction.
	@param startDefBlock 
	*/
	void setStartDefBlock(long long startDefBlock)  
	{
		m_startDefBlock = startDefBlock;
	}

	/** Returns a const reference to the element <i>lengthDefBlock</i> in CppFunction.
	@return 
	*/
	long long getLengthDefBlock() const 
	{
		return m_lengthDefBlock;
	}

	/** Sets a value of the element <i>lengthDefBlock</i> in CppFunction.
	@param lengthDefBlock 
	*/
	void setLengthDefBlock(long long lengthDefBlock)  
	{
		m_lengthDefBlock = lengthDefBlock;
	}

	/// Random access iterator types for CppParameter vector.
	typedef typename vector_cppParameter::iterator	CppParameterIterator;
	typedef typename vector_cppParameter::const_iterator	CppParameterConstIterator;

	/// Random access iterator types for CppVariable vector.
	typedef typename vector_cppVariable::iterator	CppVariableIterator;
	typedef typename vector_cppVariable::const_iterator	CppVariableConstIterator;

	/** Returns an iterator referring to the first element in the vector container CppParameter.
	@return An iterator to the beginning of the sequence.
	*/
	CppParameterIterator getCppParametersBeginning()  
	{
		return m_cppParameters.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container CppParameter.
	@return An iterator to the element past the end of the sequence.
	*/
	CppParameterIterator getCppParametersEnd()  
	{
		return m_cppParameters.end();
	}

	/** Returns a const iterator referring to the first element in the vector container CppParameter.
	@return A const iterator to the beginning of the sequence.
	*/
	CppParameterConstIterator getCppParametersBeginning() const 
	{
		return m_cppParameters.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container CppParameter.
	@return A const iterator to the element past the end of the sequence.
	*/
	CppParameterConstIterator getCppParametersEnd() const 
	{
		return m_cppParameters.end();
	}

	/** Returns a reference to the element at position n in the vector CppParameter.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppParameter<EncodingT> >& getCppParameterAt(size_t n)  
	{
		return m_cppParameters.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppParameter.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppParameter<EncodingT> > getCppParameterAt(size_t n) const 
	{
		return m_cppParameters.at(n);
	}

	/** Returns the number of elements in the vector container CppParameter.
	@return The number of elements that conform the vector's content.
	*/
	size_t getCppParametersSize() const 
	{
		return m_cppParameters.size();
	}

	/** Returns whether the vector container CppParameter is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isCppParametersEmpty() const 
	{
		return m_cppParameters.empty();
	}

	/** Adds a new element at the end of the vector CppParameter, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addCppParameter(boost::shared_ptr< _CppParameter<EncodingT> > o)  
	{
		m_cppParameters.push_back(copy_ptr(o));
	}

	/** The vector CppParameter is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppParameterIterator insertCppParameter(CppParameterIterator pos, boost::shared_ptr< _CppParameter<EncodingT> > o)  
	{
		return m_cppParameters.insert(pos, copy_ptr(o));
	}

	/** The vector CppParameter is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertCppParameter(CppParameterIterator pos, CppParameterIterator first, CppParameterIterator last)  
	{
		std::transform(first, last, std::inserter(m_cppParameters, pos), static_cast< boost::shared_ptr< _CppParameter<EncodingT> >(*)(boost::shared_ptr< _CppParameter<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container CppParameter a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	CppParameterIterator eraseCppParameter(CppParameterIterator pos)  
	{
		return m_cppParameters.erase(pos);
	}

	/** Removes from the vector container CppParameter a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	CppParameterIterator eraseCppParameter(CppParameterIterator first, CppParameterIterator last)  
	{
		return m_cppParameters.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container CppParameter, leaving the container with a size of 0.
	*/
	void clearCppParameters()  
	{
		m_cppParameters.clear();
	}

	/** Returns an iterator referring to the first element in the vector container CppVariable.
	@return An iterator to the beginning of the sequence.
	*/
	CppVariableIterator getCppVariablesBeginning()  
	{
		return m_cppVariables.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container CppVariable.
	@return An iterator to the element past the end of the sequence.
	*/
	CppVariableIterator getCppVariablesEnd()  
	{
		return m_cppVariables.end();
	}

	/** Returns a const iterator referring to the first element in the vector container CppVariable.
	@return A const iterator to the beginning of the sequence.
	*/
	CppVariableConstIterator getCppVariablesBeginning() const 
	{
		return m_cppVariables.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container CppVariable.
	@return A const iterator to the element past the end of the sequence.
	*/
	CppVariableConstIterator getCppVariablesEnd() const 
	{
		return m_cppVariables.end();
	}

	/** Returns a reference to the element at position n in the vector CppVariable.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppVariable<EncodingT> >& getCppVariableAt(size_t n)  
	{
		return m_cppVariables.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppVariable.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppVariable<EncodingT> > getCppVariableAt(size_t n) const 
	{
		return m_cppVariables.at(n);
	}

	/** Returns the number of elements in the vector container CppVariable.
	@return The number of elements that conform the vector's content.
	*/
	size_t getCppVariablesSize() const 
	{
		return m_cppVariables.size();
	}

	/** Returns whether the vector container CppVariable is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isCppVariablesEmpty() const 
	{
		return m_cppVariables.empty();
	}

	/** Adds a new element at the end of the vector CppVariable, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o)  
	{
		m_cppVariables.push_back(copy_ptr(o));
	}

	/** The vector CppVariable is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppVariableIterator insertCppVariable(CppVariableIterator pos, boost::shared_ptr< _CppVariable<EncodingT> > o)  
	{
		return m_cppVariables.insert(pos, copy_ptr(o));
	}

	/** The vector CppVariable is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertCppVariable(CppVariableIterator pos, CppVariableIterator first, CppVariableIterator last)  
	{
		std::transform(first, last, std::inserter(m_cppVariables, pos), static_cast< boost::shared_ptr< _CppVariable<EncodingT> >(*)(boost::shared_ptr< _CppVariable<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container CppVariable a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	CppVariableIterator eraseCppVariable(CppVariableIterator pos)  
	{
		return m_cppVariables.erase(pos);
	}

	/** Removes from the vector container CppVariable a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	CppVariableIterator eraseCppVariable(CppVariableIterator first, CppVariableIterator last)  
	{
		return m_cppVariables.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container CppVariable, leaving the container with a size of 0.
	*/
	void clearCppVariables()  
	{
		m_cppVariables.clear();
	}

	/** Prints CppFunction object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "CppFunction" << endl
		         << "identifier : " << m_identifier << endl
		         << "name : " << A(m_name) << endl
		         << "accessSpecifier : " << A(m_accessSpecifier) << endl
		         << "returnType : " << A(m_returnType) << endl
		         << "isConst : " << m_isConst << endl
		         << "isVirtual : " << m_isVirtual << endl
		         << "isVirtualPure : " << m_isVirtualPure << endl
		         << "isStatic : " << m_isStatic << endl
		         << "isOperator : " << m_isOperator << endl
		         << "isDestructor : " << m_isDestructor << endl
		         << "isConstructor : " << m_isConstructor << endl
		         << "isVariadic : " << m_isVariadic << endl
		         << "isTemplate : " << m_isTemplate << endl
		         << "isInline : " << m_isInline << endl
		         << "isConstexpr : " << m_isConstexpr << endl
		         << "isOverride : " << m_isOverride << endl
		         << "isFinal : " << m_isFinal << endl
		         << "isNoexcept : " << m_isNoexcept << endl
		         << "signature : " << A(m_signature) << endl
		         << "decLineNumber : " << m_decLineNumber << endl
		         << "startDecBlock : " << m_startDecBlock << endl
		         << "lengthDecBlock : " << m_lengthDecBlock << endl
		         << "linesCount : " << m_linesCount << endl
		         << "complexity : " << m_complexity << endl
		         << "defLineNumber : " << m_defLineNumber << endl
		         << "startDefBlock : " << m_startDefBlock << endl
		         << "lengthDefBlock : " << m_lengthDefBlock;
	}

	/** Defines <i> operator<< </i> for CppFunction.
	@param o Reference of C++ stream object.
	@param elem Const reference of CppFunction object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _CppFunction<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class CppFunctionIDEquality;
	class NameEquality;
	class NameInferior;
	class NameSuperior;
	class AccessSpecifierEquality;
	class AccessSpecifierInferior;
	class AccessSpecifierSuperior;
	class ReturnTypeEquality;
	class ReturnTypeInferior;
	class ReturnTypeSuperior;
	class IsConstEquality;
	class IsConstInferior;
	class IsConstSuperior;
	class IsVirtualEquality;
	class IsVirtualInferior;
	class IsVirtualSuperior;
	class IsVirtualPureEquality;
	class IsVirtualPureInferior;
	class IsVirtualPureSuperior;
	class IsStaticEquality;
	class IsStaticInferior;
	class IsStaticSuperior;
	class IsOperatorEquality;
	class IsOperatorInferior;
	class IsOperatorSuperior;
	class IsDestructorEquality;
	class IsDestructorInferior;
	class IsDestructorSuperior;
	class IsConstructorEquality;
	class IsConstructorInferior;
	class IsConstructorSuperior;
	class IsVariadicEquality;
	class IsVariadicInferior;
	class IsVariadicSuperior;
	class IsTemplateEquality;
	class IsTemplateInferior;
	class IsTemplateSuperior;
	class IsInlineEquality;
	class IsInlineInferior;
	class IsInlineSuperior;
	class IsConstexprEquality;
	class IsConstexprInferior;
	class IsConstexprSuperior;
	class IsOverrideEquality;
	class IsOverrideInferior;
	class IsOverrideSuperior;
	class IsFinalEquality;
	class IsFinalInferior;
	class IsFinalSuperior;
	class IsNoexceptEquality;
	class IsNoexceptInferior;
	class IsNoexceptSuperior;
	class SignatureEquality;
	class SignatureInferior;
	class SignatureSuperior;
	class DecLineNumberEquality;
	class DecLineNumberInferior;
	class DecLineNumberSuperior;
	class StartDecBlockEquality;
	class StartDecBlockInferior;
	class StartDecBlockSuperior;
	class LengthDecBlockEquality;
	class LengthDecBlockInferior;
	class LengthDecBlockSuperior;
	class LinesCountEquality;
	class LinesCountInferior;
	class LinesCountSuperior;
	class ComplexityEquality;
	class ComplexityInferior;
	class ComplexitySuperior;
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

typedef _CppFunction<ucs> UniCppFunction;
typedef _CppFunction<ansi> CppFunction;

NAMESPACE_END

#undef C
#undef A

#include "cppFunctionPredicate.hpp"

#endif
