/* 
 * cppFunction.hpp
 *
 *
 * @date 21-06-2016
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
class _DebugFunctionInfo;

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
	shared_ptr< _CppFile<EncodingT> >	m_cppDeclarationFile;
	shared_ptr< _CppFile<EncodingT> >	m_cppDefinitionFile;
	int	m_identifier;
	typename EncodingT::string_t	m_name;
	shared_ptr< _CppClass<EncodingT> >	m_cppClass;
	typename EncodingT::string_t	m_accessSpecifier;
	typename EncodingT::string_t	m_returnType;
	int	m_isConst;
	int	m_isVirtual;
	int	m_isVirtualPure;
	int	m_isStatic;
	int	m_isOperator;
	int	m_isDestructor;
	int	m_isConstructor;
	int	m_isVariadic;
	typename EncodingT::string_t	m_signature;
	int	m_startDecBlock;
	int	m_lengthDecBlock;
	int	m_decLineNumber;
	int	m_linesCount;
	int	m_complexity;
	int	m_defLineNumber;
	int	m_startDefBlock;
	int	m_lengthDefBlock;
	typedef std::vector< shared_ptr< _CppParameter<EncodingT> > >	vector_cppParameter;
	vector_cppParameter	m_cppParameters;
	typedef std::vector< shared_ptr< _CppVariable<EncodingT> > >	vector_cppVariable;
	vector_cppVariable	m_cppVariables;
	typedef std::vector< shared_ptr< _DebugFunctionInfo<EncodingT> > >	vector_debugFunctionInfo;
	vector_debugFunctionInfo	m_debugFunctionInfos;
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
	@param signature 
	@param startDecBlock 
	@param lengthDecBlock 
	@param decLineNumber 
	@param linesCount 
	@param complexity 
	@param defLineNumber 
	@param startDefBlock 
	@param lengthDefBlock 
	*/
	_CppFunction(int identifier,
				const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& accessSpecifier,
				const typename EncodingT::string_t& returnType,
				int isConst,
				int isVirtual,
				int isVirtualPure,
				int isStatic,
				int isOperator,
				int isDestructor,
				int isConstructor,
				int isVariadic,
				const typename EncodingT::string_t& signature,
				int startDecBlock,
				int lengthDecBlock,
				int decLineNumber,
				int linesCount,
				int complexity,
				int defLineNumber,
				int startDefBlock,
				int lengthDefBlock)
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
	  m_signature(signature),
	  m_startDecBlock(startDecBlock),
	  m_lengthDecBlock(lengthDecBlock),
	  m_decLineNumber(decLineNumber),
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
				<< A(m_signature) << ' '
				<< m_startDecBlock << ' '
				<< m_lengthDecBlock << ' '
				<< m_decLineNumber << ' '
				<< m_linesCount << ' '
				<< m_complexity << ' '
				<< m_defLineNumber << ' '
				<< m_startDefBlock << ' '
				<< m_lengthDefBlock << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppFunction.
	@param identifier 
	*/
	void setIdentifier(int identifier)  
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
	  m_signature(EncodingT::EMPTY),
	  m_startDecBlock(0),
	  m_lengthDecBlock(0),
	  m_decLineNumber(0),
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
	@param signature 
	@param startDecBlock 
	@param lengthDecBlock 
	@param decLineNumber 
	@param linesCount 
	@param complexity 
	@param defLineNumber 
	@param startDefBlock 
	@param lengthDefBlock 
	*/
	_CppFunction(const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& accessSpecifier,
				const typename EncodingT::string_t& returnType,
				int isConst,
				int isVirtual,
				int isVirtualPure,
				int isStatic,
				int isOperator,
				int isDestructor,
				int isConstructor,
				int isVariadic,
				const typename EncodingT::string_t& signature,
				int startDecBlock,
				int lengthDecBlock,
				int decLineNumber,
				int linesCount,
				int complexity,
				int defLineNumber,
				int startDefBlock,
				int lengthDefBlock)
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
	  m_signature(signature),
	  m_startDecBlock(startDecBlock),
	  m_lengthDecBlock(lengthDecBlock),
	  m_decLineNumber(decLineNumber),
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
				<< A(m_signature) << ' '
				<< m_startDecBlock << ' '
				<< m_lengthDecBlock << ' '
				<< m_decLineNumber << ' '
				<< m_linesCount << ' '
				<< m_complexity << ' '
				<< m_defLineNumber << ' '
				<< m_startDefBlock << ' '
				<< m_lengthDefBlock << ' ';
	}

	/** Creates a copy of elem as the content for the CppFunction object.
	@param elem A CppFunction object containing elements of the same type.
	*/
	_CppFunction(const _CppFunction<EncodingT>& elem)
	: m_cppDeclarationFile(elem.m_cppDeclarationFile),
	  m_cppDefinitionFile(elem.m_cppDefinitionFile),
	  m_identifier(elem.m_identifier),
	  m_name(elem.m_name),
	  m_cppClass(elem.m_cppClass),
	  m_accessSpecifier(elem.m_accessSpecifier),
	  m_returnType(elem.m_returnType),
	  m_isConst(elem.m_isConst),
	  m_isVirtual(elem.m_isVirtual),
	  m_isVirtualPure(elem.m_isVirtualPure),
	  m_isStatic(elem.m_isStatic),
	  m_isOperator(elem.m_isOperator),
	  m_isDestructor(elem.m_isDestructor),
	  m_isConstructor(elem.m_isConstructor),
	  m_isVariadic(elem.m_isVariadic),
	  m_signature(elem.m_signature),
	  m_startDecBlock(elem.m_startDecBlock),
	  m_lengthDecBlock(elem.m_lengthDecBlock),
	  m_decLineNumber(elem.m_decLineNumber),
	  m_linesCount(elem.m_linesCount),
	  m_complexity(elem.m_complexity),
	  m_defLineNumber(elem.m_defLineNumber),
	  m_startDefBlock(elem.m_startDefBlock),
	  m_lengthDefBlock(elem.m_lengthDefBlock),
	  m_cppParameters(copy_ptr(elem.m_cppParameters)),
	  m_cppVariables(copy_ptr(elem.m_cppVariables)),
	  m_debugFunctionInfos(copy_ptr(elem.m_debugFunctionInfos))
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppFunction " << ": copy";
	}

	/** Assigns a copy of elem as the new content for the CppFunction object.
	@param elem A CppFunction object containing elements of the same type.
	@return *this
	*/
	_CppFunction<EncodingT>& operator=(const _CppFunction<EncodingT>& elem)  
	{
		m_cppDeclarationFile = elem.m_cppDeclarationFile;
		m_cppDefinitionFile = elem.m_cppDefinitionFile;
		m_identifier = elem.m_identifier;
		m_name = elem.m_name;
		m_cppClass = elem.m_cppClass;
		m_accessSpecifier = elem.m_accessSpecifier;
		m_returnType = elem.m_returnType;
		m_isConst = elem.m_isConst;
		m_isVirtual = elem.m_isVirtual;
		m_isVirtualPure = elem.m_isVirtualPure;
		m_isStatic = elem.m_isStatic;
		m_isOperator = elem.m_isOperator;
		m_isDestructor = elem.m_isDestructor;
		m_isConstructor = elem.m_isConstructor;
		m_isVariadic = elem.m_isVariadic;
		m_signature = elem.m_signature;
		m_startDecBlock = elem.m_startDecBlock;
		m_lengthDecBlock = elem.m_lengthDecBlock;
		m_decLineNumber = elem.m_decLineNumber;
		m_linesCount = elem.m_linesCount;
		m_complexity = elem.m_complexity;
		m_defLineNumber = elem.m_defLineNumber;
		m_startDefBlock = elem.m_startDefBlock;
		m_lengthDefBlock = elem.m_lengthDefBlock;
		m_cppParameters = copy_ptr(elem.m_cppParameters);
		m_cppVariables = copy_ptr(elem.m_cppVariables);
		m_debugFunctionInfos = copy_ptr(elem.m_debugFunctionInfos);
		return *this;
	}

	/** Returns a const reference to the element <i>cppDeclarationFile</i> in CppFunction.
	@return 
	*/
	shared_ptr< _CppFile<EncodingT> > getCppDeclarationFile() const 
	{
		return m_cppDeclarationFile;
	}

	/** Sets a value of the element <i>cppDeclarationFile</i> in CppFunction.
	@param cppDeclarationFile 
	*/
	void setCppDeclarationFile(shared_ptr< _CppFile<EncodingT> > cppDeclarationFile)  
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
	shared_ptr< _CppFile<EncodingT> > getCppDefinitionFile() const 
	{
		return m_cppDefinitionFile;
	}

	/** Sets a value of the element <i>cppDefinitionFile</i> in CppFunction.
	@param cppDefinitionFile 
	*/
	void setCppDefinitionFile(shared_ptr< _CppFile<EncodingT> > cppDefinitionFile)  
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
	int getIdentifier() const 
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
	shared_ptr< _CppClass<EncodingT> > getCppClass() const 
	{
		return m_cppClass;
	}

	/** Sets a value of the element <i>cppClass</i> in CppFunction.
	@param cppClass 
	*/
	void setCppClass(shared_ptr< _CppClass<EncodingT> > cppClass)  
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
	int getIsConst() const 
	{
		return m_isConst;
	}

	/** Sets a value of the element <i>isConst</i> in CppFunction.
	@param isConst 
	*/
	void setIsConst(int isConst)  
	{
		m_isConst = isConst;
	}

	/** Returns a const reference to the element <i>isVirtual</i> in CppFunction.
	@return 
	*/
	int getIsVirtual() const 
	{
		return m_isVirtual;
	}

	/** Sets a value of the element <i>isVirtual</i> in CppFunction.
	@param isVirtual 
	*/
	void setIsVirtual(int isVirtual)  
	{
		m_isVirtual = isVirtual;
	}

	/** Returns a const reference to the element <i>isVirtualPure</i> in CppFunction.
	@return 
	*/
	int getIsVirtualPure() const 
	{
		return m_isVirtualPure;
	}

	/** Sets a value of the element <i>isVirtualPure</i> in CppFunction.
	@param isVirtualPure 
	*/
	void setIsVirtualPure(int isVirtualPure)  
	{
		m_isVirtualPure = isVirtualPure;
	}

	/** Returns a const reference to the element <i>isStatic</i> in CppFunction.
	@return 
	*/
	int getIsStatic() const 
	{
		return m_isStatic;
	}

	/** Sets a value of the element <i>isStatic</i> in CppFunction.
	@param isStatic 
	*/
	void setIsStatic(int isStatic)  
	{
		m_isStatic = isStatic;
	}

	/** Returns a const reference to the element <i>isOperator</i> in CppFunction.
	@return 
	*/
	int getIsOperator() const 
	{
		return m_isOperator;
	}

	/** Sets a value of the element <i>isOperator</i> in CppFunction.
	@param isOperator 
	*/
	void setIsOperator(int isOperator)  
	{
		m_isOperator = isOperator;
	}

	/** Returns a const reference to the element <i>isDestructor</i> in CppFunction.
	@return 
	*/
	int getIsDestructor() const 
	{
		return m_isDestructor;
	}

	/** Sets a value of the element <i>isDestructor</i> in CppFunction.
	@param isDestructor 
	*/
	void setIsDestructor(int isDestructor)  
	{
		m_isDestructor = isDestructor;
	}

	/** Returns a const reference to the element <i>isConstructor</i> in CppFunction.
	@return 
	*/
	int getIsConstructor() const 
	{
		return m_isConstructor;
	}

	/** Sets a value of the element <i>isConstructor</i> in CppFunction.
	@param isConstructor 
	*/
	void setIsConstructor(int isConstructor)  
	{
		m_isConstructor = isConstructor;
	}

	/** Returns a const reference to the element <i>isVariadic</i> in CppFunction.
	@return 
	*/
	int getIsVariadic() const 
	{
		return m_isVariadic;
	}

	/** Sets a value of the element <i>isVariadic</i> in CppFunction.
	@param isVariadic 
	*/
	void setIsVariadic(int isVariadic)  
	{
		m_isVariadic = isVariadic;
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

	/** Returns a const reference to the element <i>startDecBlock</i> in CppFunction.
	@return 
	*/
	int getStartDecBlock() const 
	{
		return m_startDecBlock;
	}

	/** Sets a value of the element <i>startDecBlock</i> in CppFunction.
	@param startDecBlock 
	*/
	void setStartDecBlock(int startDecBlock)  
	{
		m_startDecBlock = startDecBlock;
	}

	/** Returns a const reference to the element <i>lengthDecBlock</i> in CppFunction.
	@return 
	*/
	int getLengthDecBlock() const 
	{
		return m_lengthDecBlock;
	}

	/** Sets a value of the element <i>lengthDecBlock</i> in CppFunction.
	@param lengthDecBlock 
	*/
	void setLengthDecBlock(int lengthDecBlock)  
	{
		m_lengthDecBlock = lengthDecBlock;
	}

	/** Returns a const reference to the element <i>decLineNumber</i> in CppFunction.
	@return 
	*/
	int getDecLineNumber() const 
	{
		return m_decLineNumber;
	}

	/** Sets a value of the element <i>decLineNumber</i> in CppFunction.
	@param decLineNumber 
	*/
	void setDecLineNumber(int decLineNumber)  
	{
		m_decLineNumber = decLineNumber;
	}

	/** Returns a const reference to the element <i>linesCount</i> in CppFunction.
	@return 
	*/
	int getLinesCount() const 
	{
		return m_linesCount;
	}

	/** Sets a value of the element <i>linesCount</i> in CppFunction.
	@param linesCount 
	*/
	void setLinesCount(int linesCount)  
	{
		m_linesCount = linesCount;
	}

	/** Returns a const reference to the element <i>complexity</i> in CppFunction.
	@return 
	*/
	int getComplexity() const 
	{
		return m_complexity;
	}

	/** Sets a value of the element <i>complexity</i> in CppFunction.
	@param complexity 
	*/
	void setComplexity(int complexity)  
	{
		m_complexity = complexity;
	}

	/** Returns a const reference to the element <i>defLineNumber</i> in CppFunction.
	@return 
	*/
	int getDefLineNumber() const 
	{
		return m_defLineNumber;
	}

	/** Sets a value of the element <i>defLineNumber</i> in CppFunction.
	@param defLineNumber 
	*/
	void setDefLineNumber(int defLineNumber)  
	{
		m_defLineNumber = defLineNumber;
	}

	/** Returns a const reference to the element <i>startDefBlock</i> in CppFunction.
	@return 
	*/
	int getStartDefBlock() const 
	{
		return m_startDefBlock;
	}

	/** Sets a value of the element <i>startDefBlock</i> in CppFunction.
	@param startDefBlock 
	*/
	void setStartDefBlock(int startDefBlock)  
	{
		m_startDefBlock = startDefBlock;
	}

	/** Returns a const reference to the element <i>lengthDefBlock</i> in CppFunction.
	@return 
	*/
	int getLengthDefBlock() const 
	{
		return m_lengthDefBlock;
	}

	/** Sets a value of the element <i>lengthDefBlock</i> in CppFunction.
	@param lengthDefBlock 
	*/
	void setLengthDefBlock(int lengthDefBlock)  
	{
		m_lengthDefBlock = lengthDefBlock;
	}

	/// Random access iterator types for CppParameter vector.
	typedef typename vector_cppParameter::iterator	CppParameterIterator;
	typedef typename vector_cppParameter::const_iterator	CppParameterConstIterator;

	/// Random access iterator types for CppVariable vector.
	typedef typename vector_cppVariable::iterator	CppVariableIterator;
	typedef typename vector_cppVariable::const_iterator	CppVariableConstIterator;

	/// Random access iterator types for DebugFunctionInfo vector.
	typedef typename vector_debugFunctionInfo::iterator	DebugFunctionInfoIterator;
	typedef typename vector_debugFunctionInfo::const_iterator	DebugFunctionInfoConstIterator;

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
	shared_ptr< _CppParameter<EncodingT> >& getCppParameterAt(size_t n)  
	{
		return m_cppParameters.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppParameter.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	shared_ptr< _CppParameter<EncodingT> > getCppParameterAt(size_t n) const 
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
	void addCppParameter(shared_ptr< _CppParameter<EncodingT> > o)  
	{
		m_cppParameters.push_back(copy_ptr(o));
	}

	/** The vector CppParameter is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppParameterIterator insertCppParameter(CppParameterIterator pos, shared_ptr< _CppParameter<EncodingT> > o)  
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
		std::transform(first, last, std::inserter(m_cppParameters, pos), static_cast< shared_ptr< _CppParameter<EncodingT> >(*)(shared_ptr< _CppParameter<EncodingT> >) >(copy_ptr));
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
	shared_ptr< _CppVariable<EncodingT> >& getCppVariableAt(size_t n)  
	{
		return m_cppVariables.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppVariable.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	shared_ptr< _CppVariable<EncodingT> > getCppVariableAt(size_t n) const 
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
	void addCppVariable(shared_ptr< _CppVariable<EncodingT> > o)  
	{
		m_cppVariables.push_back(copy_ptr(o));
	}

	/** The vector CppVariable is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppVariableIterator insertCppVariable(CppVariableIterator pos, shared_ptr< _CppVariable<EncodingT> > o)  
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
		std::transform(first, last, std::inserter(m_cppVariables, pos), static_cast< shared_ptr< _CppVariable<EncodingT> >(*)(shared_ptr< _CppVariable<EncodingT> >) >(copy_ptr));
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

	/** Returns an iterator referring to the first element in the vector container DebugFunctionInfo.
	@return An iterator to the beginning of the sequence.
	*/
	DebugFunctionInfoIterator getDebugFunctionInfosBeginning()  
	{
		return m_debugFunctionInfos.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container DebugFunctionInfo.
	@return An iterator to the element past the end of the sequence.
	*/
	DebugFunctionInfoIterator getDebugFunctionInfosEnd()  
	{
		return m_debugFunctionInfos.end();
	}

	/** Returns a const iterator referring to the first element in the vector container DebugFunctionInfo.
	@return A const iterator to the beginning of the sequence.
	*/
	DebugFunctionInfoConstIterator getDebugFunctionInfosBeginning() const 
	{
		return m_debugFunctionInfos.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container DebugFunctionInfo.
	@return A const iterator to the element past the end of the sequence.
	*/
	DebugFunctionInfoConstIterator getDebugFunctionInfosEnd() const 
	{
		return m_debugFunctionInfos.end();
	}

	/** Returns a reference to the element at position n in the vector DebugFunctionInfo.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	shared_ptr< _DebugFunctionInfo<EncodingT> >& getDebugFunctionInfoAt(size_t n)  
	{
		return m_debugFunctionInfos.at(n);
	}

	/** Returns a const reference to the element at position n in the vector DebugFunctionInfo.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	shared_ptr< _DebugFunctionInfo<EncodingT> > getDebugFunctionInfoAt(size_t n) const 
	{
		return m_debugFunctionInfos.at(n);
	}

	/** Returns the number of elements in the vector container DebugFunctionInfo.
	@return The number of elements that conform the vector's content.
	*/
	size_t getDebugFunctionInfosSize() const 
	{
		return m_debugFunctionInfos.size();
	}

	/** Returns whether the vector container DebugFunctionInfo is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isDebugFunctionInfosEmpty() const 
	{
		return m_debugFunctionInfos.empty();
	}

	/** Adds a new element at the end of the vector DebugFunctionInfo, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addDebugFunctionInfo(shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
	{
		m_debugFunctionInfos.push_back(copy_ptr(o));
	}

	/** The vector DebugFunctionInfo is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	DebugFunctionInfoIterator insertDebugFunctionInfo(DebugFunctionInfoIterator pos, shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
	{
		return m_debugFunctionInfos.insert(pos, copy_ptr(o));
	}

	/** The vector DebugFunctionInfo is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertDebugFunctionInfo(DebugFunctionInfoIterator pos, DebugFunctionInfoIterator first, DebugFunctionInfoIterator last)  
	{
		std::transform(first, last, std::inserter(m_debugFunctionInfos, pos), static_cast< shared_ptr< _DebugFunctionInfo<EncodingT> >(*)(shared_ptr< _DebugFunctionInfo<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container DebugFunctionInfo a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	DebugFunctionInfoIterator eraseDebugFunctionInfo(DebugFunctionInfoIterator pos)  
	{
		return m_debugFunctionInfos.erase(pos);
	}

	/** Removes from the vector container DebugFunctionInfo a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	DebugFunctionInfoIterator eraseDebugFunctionInfo(DebugFunctionInfoIterator first, DebugFunctionInfoIterator last)  
	{
		return m_debugFunctionInfos.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container DebugFunctionInfo, leaving the container with a size of 0.
	*/
	void clearDebugFunctionInfos()  
	{
		m_debugFunctionInfos.clear();
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
		         << "signature : " << A(m_signature) << endl
		         << "startDecBlock : " << m_startDecBlock << endl
		         << "lengthDecBlock : " << m_lengthDecBlock << endl
		         << "decLineNumber : " << m_decLineNumber << endl
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
	class SignatureEquality;
	class SignatureInferior;
	class SignatureSuperior;
	class StartDecBlockEquality;
	class StartDecBlockInferior;
	class StartDecBlockSuperior;
	class LengthDecBlockEquality;
	class LengthDecBlockInferior;
	class LengthDecBlockSuperior;
	class DecLineNumberEquality;
	class DecLineNumberInferior;
	class DecLineNumberSuperior;
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
