/* 
 * debugTypeInfo.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGTYPEINFO_HPP_
#define _DEBUGTYPEINFO_HPP_

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
class _DebugTypeInfoAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _DebugTypeInfo;

template <class EncodingT>
class _DebugFunctionInfo;

template <class EncodingT>
class _DebugVariableInfo;

template <class EncodingT>
class _DebugTypeInfo;

/// debugTypeInfo table represents type information for debug.
template <class EncodingT>
class  _DebugTypeInfo {
private :
	boost::shared_ptr< _DebugTypeInfo<EncodingT> >	m_primitiveType;
	long long	m_identifier;
	long long	m_isChar;
	long long	m_isString;
	long long	m_isBool;
	long long	m_isFloat;
	long long	m_isSigned;
	long long	m_isWide;
	long long	m_isPointer;
	long long	m_isReference;
	long long	m_isArray;
	long long	m_isConst;
	long long	m_isVolatile;
	long long	m_isStruct;
	long long	m_isClass;
	long long	m_isUnion;
	long long	m_isInterface;
	long long	m_isEnum;
	long long	m_isFunction;
	typename EncodingT::string_t	m_baseName;
	typename EncodingT::string_t	m_name;
	long long	m_sizeOf;
	long long	m_typeId;
	long long	m_arrayDim;
	typedef std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > >	vector_richType;
	vector_richType	m_richTypes;
	typedef std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > >	vector_debugFunctionInfo;
	vector_debugFunctionInfo	m_debugFunctionInfos;
	typedef std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >	vector_debugVariableInfo;
	vector_debugVariableInfo	m_debugVariableInfos;
	Category*	m_logger;

protected :
	friend class data_access::_DebugTypeInfoAccess<EncodingT>;

	/** Creates a new element DebugTypeInfo.
	@param identifier 
	@param isChar 
	@param isString 
	@param isBool 
	@param isFloat 
	@param isSigned 
	@param isWide 
	@param isPointer 
	@param isReference 
	@param isArray 
	@param isConst 
	@param isVolatile 
	@param isStruct 
	@param isClass 
	@param isUnion 
	@param isInterface 
	@param isEnum 
	@param isFunction 
	@param baseName 
	@param name 
	@param sizeOf 
	@param typeId 
	@param arrayDim 
	*/
	_DebugTypeInfo(long long identifier,
				long long isChar,
				long long isString,
				long long isBool,
				long long isFloat,
				long long isSigned,
				long long isWide,
				long long isPointer,
				long long isReference,
				long long isArray,
				long long isConst,
				long long isVolatile,
				long long isStruct,
				long long isClass,
				long long isUnion,
				long long isInterface,
				long long isEnum,
				long long isFunction,
				const typename EncodingT::string_t& baseName,
				const typename EncodingT::string_t& name,
				long long sizeOf,
				long long typeId,
				long long arrayDim)
	: m_identifier(identifier),
	  m_isChar(isChar),
	  m_isString(isString),
	  m_isBool(isBool),
	  m_isFloat(isFloat),
	  m_isSigned(isSigned),
	  m_isWide(isWide),
	  m_isPointer(isPointer),
	  m_isReference(isReference),
	  m_isArray(isArray),
	  m_isConst(isConst),
	  m_isVolatile(isVolatile),
	  m_isStruct(isStruct),
	  m_isClass(isClass),
	  m_isUnion(isUnion),
	  m_isInterface(isInterface),
	  m_isEnum(isEnum),
	  m_isFunction(isFunction),
	  m_baseName(baseName),
	  m_name(name),
	  m_sizeOf(sizeOf),
	  m_typeId(typeId),
	  m_arrayDim(arrayDim)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugTypeInfo "
				<< m_identifier << ' '
				<< m_isChar << ' '
				<< m_isString << ' '
				<< m_isBool << ' '
				<< m_isFloat << ' '
				<< m_isSigned << ' '
				<< m_isWide << ' '
				<< m_isPointer << ' '
				<< m_isReference << ' '
				<< m_isArray << ' '
				<< m_isConst << ' '
				<< m_isVolatile << ' '
				<< m_isStruct << ' '
				<< m_isClass << ' '
				<< m_isUnion << ' '
				<< m_isInterface << ' '
				<< m_isEnum << ' '
				<< m_isFunction << ' '
				<< A(m_baseName) << ' '
				<< A(m_name) << ' '
				<< m_sizeOf << ' '
				<< m_typeId << ' '
				<< m_arrayDim << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in DebugTypeInfo.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element DebugTypeInfo.
	*/
	_DebugTypeInfo()
	: m_identifier(-1),
	  m_isChar(0),
	  m_isString(0),
	  m_isBool(0),
	  m_isFloat(0),
	  m_isSigned(0),
	  m_isWide(0),
	  m_isPointer(0),
	  m_isReference(0),
	  m_isArray(0),
	  m_isConst(0),
	  m_isVolatile(0),
	  m_isStruct(0),
	  m_isClass(0),
	  m_isUnion(0),
	  m_isInterface(0),
	  m_isEnum(0),
	  m_isFunction(0),
	  m_baseName(EncodingT::EMPTY),
	  m_name(EncodingT::EMPTY),
	  m_sizeOf(0),
	  m_typeId(0),
	  m_arrayDim(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugTypeInfo ";
	}

	/** Creates a new element DebugTypeInfo.
	@param isChar 
	@param isString 
	@param isBool 
	@param isFloat 
	@param isSigned 
	@param isWide 
	@param isPointer 
	@param isReference 
	@param isArray 
	@param isConst 
	@param isVolatile 
	@param isStruct 
	@param isClass 
	@param isUnion 
	@param isInterface 
	@param isEnum 
	@param isFunction 
	@param baseName 
	@param name 
	@param sizeOf 
	@param typeId 
	@param arrayDim 
	*/
	_DebugTypeInfo(long long isChar,
				long long isString,
				long long isBool,
				long long isFloat,
				long long isSigned,
				long long isWide,
				long long isPointer,
				long long isReference,
				long long isArray,
				long long isConst,
				long long isVolatile,
				long long isStruct,
				long long isClass,
				long long isUnion,
				long long isInterface,
				long long isEnum,
				long long isFunction,
				const typename EncodingT::string_t& baseName,
				const typename EncodingT::string_t& name,
				long long sizeOf,
				long long typeId,
				long long arrayDim)
	: m_identifier(-1),
	  m_isChar(isChar),
	  m_isString(isString),
	  m_isBool(isBool),
	  m_isFloat(isFloat),
	  m_isSigned(isSigned),
	  m_isWide(isWide),
	  m_isPointer(isPointer),
	  m_isReference(isReference),
	  m_isArray(isArray),
	  m_isConst(isConst),
	  m_isVolatile(isVolatile),
	  m_isStruct(isStruct),
	  m_isClass(isClass),
	  m_isUnion(isUnion),
	  m_isInterface(isInterface),
	  m_isEnum(isEnum),
	  m_isFunction(isFunction),
	  m_baseName(baseName),
	  m_name(name),
	  m_sizeOf(sizeOf),
	  m_typeId(typeId),
	  m_arrayDim(arrayDim)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugTypeInfo "
				<< m_identifier << ' '
				<< m_isChar << ' '
				<< m_isString << ' '
				<< m_isBool << ' '
				<< m_isFloat << ' '
				<< m_isSigned << ' '
				<< m_isWide << ' '
				<< m_isPointer << ' '
				<< m_isReference << ' '
				<< m_isArray << ' '
				<< m_isConst << ' '
				<< m_isVolatile << ' '
				<< m_isStruct << ' '
				<< m_isClass << ' '
				<< m_isUnion << ' '
				<< m_isInterface << ' '
				<< m_isEnum << ' '
				<< m_isFunction << ' '
				<< A(m_baseName) << ' '
				<< A(m_name) << ' '
				<< m_sizeOf << ' '
				<< m_typeId << ' '
				<< m_arrayDim << ' ';
	}

	/** Returns a const reference to the element <i>primitiveType</i> in DebugTypeInfo.
	@return 
	*/
	boost::shared_ptr< _DebugTypeInfo<EncodingT> > getPrimitiveType() const 
	{
		return m_primitiveType;
	}

	/** Sets a value of the element <i>primitiveType</i> in DebugTypeInfo.
	@param primitiveType 
	*/
	void setPrimitiveType(boost::shared_ptr< _DebugTypeInfo<EncodingT> > primitiveType)  
	{
		m_primitiveType = primitiveType;
	}

	/** Returns whether the element <i>primitiveType</i> in DebugTypeInfo is NULL.
	@return True if the element <i>primitiveType</i> is NULL, false otherwise.
	*/
	bool isNullPrimitiveType() const 
	{
		return !m_primitiveType;
	}

	/** Removes from DebugTypeInfo an element <i>primitiveType</i>.
	*/
	void erasePrimitiveType()  
	{
		m_primitiveType.reset();
	}

	/** Returns a const reference to the element <i>identifier</i> in DebugTypeInfo.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>isChar</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsChar() const 
	{
		return m_isChar;
	}

	/** Sets a value of the element <i>isChar</i> in DebugTypeInfo.
	@param isChar 
	*/
	void setIsChar(long long isChar)  
	{
		m_isChar = isChar;
	}

	/** Returns a const reference to the element <i>isString</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsString() const 
	{
		return m_isString;
	}

	/** Sets a value of the element <i>isString</i> in DebugTypeInfo.
	@param isString 
	*/
	void setIsString(long long isString)  
	{
		m_isString = isString;
	}

	/** Returns a const reference to the element <i>isBool</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsBool() const 
	{
		return m_isBool;
	}

	/** Sets a value of the element <i>isBool</i> in DebugTypeInfo.
	@param isBool 
	*/
	void setIsBool(long long isBool)  
	{
		m_isBool = isBool;
	}

	/** Returns a const reference to the element <i>isFloat</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsFloat() const 
	{
		return m_isFloat;
	}

	/** Sets a value of the element <i>isFloat</i> in DebugTypeInfo.
	@param isFloat 
	*/
	void setIsFloat(long long isFloat)  
	{
		m_isFloat = isFloat;
	}

	/** Returns a const reference to the element <i>isSigned</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsSigned() const 
	{
		return m_isSigned;
	}

	/** Sets a value of the element <i>isSigned</i> in DebugTypeInfo.
	@param isSigned 
	*/
	void setIsSigned(long long isSigned)  
	{
		m_isSigned = isSigned;
	}

	/** Returns a const reference to the element <i>isWide</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsWide() const 
	{
		return m_isWide;
	}

	/** Sets a value of the element <i>isWide</i> in DebugTypeInfo.
	@param isWide 
	*/
	void setIsWide(long long isWide)  
	{
		m_isWide = isWide;
	}

	/** Returns a const reference to the element <i>isPointer</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsPointer() const 
	{
		return m_isPointer;
	}

	/** Sets a value of the element <i>isPointer</i> in DebugTypeInfo.
	@param isPointer 
	*/
	void setIsPointer(long long isPointer)  
	{
		m_isPointer = isPointer;
	}

	/** Returns a const reference to the element <i>isReference</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsReference() const 
	{
		return m_isReference;
	}

	/** Sets a value of the element <i>isReference</i> in DebugTypeInfo.
	@param isReference 
	*/
	void setIsReference(long long isReference)  
	{
		m_isReference = isReference;
	}

	/** Returns a const reference to the element <i>isArray</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsArray() const 
	{
		return m_isArray;
	}

	/** Sets a value of the element <i>isArray</i> in DebugTypeInfo.
	@param isArray 
	*/
	void setIsArray(long long isArray)  
	{
		m_isArray = isArray;
	}

	/** Returns a const reference to the element <i>isConst</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsConst() const 
	{
		return m_isConst;
	}

	/** Sets a value of the element <i>isConst</i> in DebugTypeInfo.
	@param isConst 
	*/
	void setIsConst(long long isConst)  
	{
		m_isConst = isConst;
	}

	/** Returns a const reference to the element <i>isVolatile</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsVolatile() const 
	{
		return m_isVolatile;
	}

	/** Sets a value of the element <i>isVolatile</i> in DebugTypeInfo.
	@param isVolatile 
	*/
	void setIsVolatile(long long isVolatile)  
	{
		m_isVolatile = isVolatile;
	}

	/** Returns a const reference to the element <i>isStruct</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsStruct() const 
	{
		return m_isStruct;
	}

	/** Sets a value of the element <i>isStruct</i> in DebugTypeInfo.
	@param isStruct 
	*/
	void setIsStruct(long long isStruct)  
	{
		m_isStruct = isStruct;
	}

	/** Returns a const reference to the element <i>isClass</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsClass() const 
	{
		return m_isClass;
	}

	/** Sets a value of the element <i>isClass</i> in DebugTypeInfo.
	@param isClass 
	*/
	void setIsClass(long long isClass)  
	{
		m_isClass = isClass;
	}

	/** Returns a const reference to the element <i>isUnion</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsUnion() const 
	{
		return m_isUnion;
	}

	/** Sets a value of the element <i>isUnion</i> in DebugTypeInfo.
	@param isUnion 
	*/
	void setIsUnion(long long isUnion)  
	{
		m_isUnion = isUnion;
	}

	/** Returns a const reference to the element <i>isInterface</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsInterface() const 
	{
		return m_isInterface;
	}

	/** Sets a value of the element <i>isInterface</i> in DebugTypeInfo.
	@param isInterface 
	*/
	void setIsInterface(long long isInterface)  
	{
		m_isInterface = isInterface;
	}

	/** Returns a const reference to the element <i>isEnum</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsEnum() const 
	{
		return m_isEnum;
	}

	/** Sets a value of the element <i>isEnum</i> in DebugTypeInfo.
	@param isEnum 
	*/
	void setIsEnum(long long isEnum)  
	{
		m_isEnum = isEnum;
	}

	/** Returns a const reference to the element <i>isFunction</i> in DebugTypeInfo.
	@return 
	*/
	long long getIsFunction() const 
	{
		return m_isFunction;
	}

	/** Sets a value of the element <i>isFunction</i> in DebugTypeInfo.
	@param isFunction 
	*/
	void setIsFunction(long long isFunction)  
	{
		m_isFunction = isFunction;
	}

	/** Returns a const reference to the element <i>baseName</i> in DebugTypeInfo.
	@return 
	*/
	const typename EncodingT::string_t& getBaseName() const 
	{
		return m_baseName;
	}

	/** Sets a value of the element <i>baseName</i> in DebugTypeInfo.
	@param baseName 
	*/
	void setBaseName(const typename EncodingT::string_t& baseName)  
	{
		m_baseName = baseName;
	}

	/** Returns a const reference to the element <i>name</i> in DebugTypeInfo.
	@return 
	*/
	const typename EncodingT::string_t& getName() const 
	{
		return m_name;
	}

	/** Sets a value of the element <i>name</i> in DebugTypeInfo.
	@param name 
	*/
	void setName(const typename EncodingT::string_t& name)  
	{
		m_name = name;
	}

	/** Returns a const reference to the element <i>sizeOf</i> in DebugTypeInfo.
	@return 
	*/
	long long getSizeOf() const 
	{
		return m_sizeOf;
	}

	/** Sets a value of the element <i>sizeOf</i> in DebugTypeInfo.
	@param sizeOf 
	*/
	void setSizeOf(long long sizeOf)  
	{
		m_sizeOf = sizeOf;
	}

	/** Returns a const reference to the element <i>typeId</i> in DebugTypeInfo.
	@return 
	*/
	long long getTypeId() const 
	{
		return m_typeId;
	}

	/** Sets a value of the element <i>typeId</i> in DebugTypeInfo.
	@param typeId 
	*/
	void setTypeId(long long typeId)  
	{
		m_typeId = typeId;
	}

	/** Returns a const reference to the element <i>arrayDim</i> in DebugTypeInfo.
	@return 
	*/
	long long getArrayDim() const 
	{
		return m_arrayDim;
	}

	/** Sets a value of the element <i>arrayDim</i> in DebugTypeInfo.
	@param arrayDim 
	*/
	void setArrayDim(long long arrayDim)  
	{
		m_arrayDim = arrayDim;
	}

	/// Random access iterator types for RichType vector.
	typedef typename vector_richType::iterator	RichTypeIterator;
	typedef typename vector_richType::const_iterator	RichTypeConstIterator;

	/// Random access iterator types for DebugFunctionInfo vector.
	typedef typename vector_debugFunctionInfo::iterator	DebugFunctionInfoIterator;
	typedef typename vector_debugFunctionInfo::const_iterator	DebugFunctionInfoConstIterator;

	/// Random access iterator types for DebugVariableInfo vector.
	typedef typename vector_debugVariableInfo::iterator	DebugVariableInfoIterator;
	typedef typename vector_debugVariableInfo::const_iterator	DebugVariableInfoConstIterator;

	/** Returns an iterator referring to the first element in the vector container RichType.
	@return An iterator to the beginning of the sequence.
	*/
	RichTypeIterator getRichTypesBeginning()  
	{
		return m_richTypes.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container RichType.
	@return An iterator to the element past the end of the sequence.
	*/
	RichTypeIterator getRichTypesEnd()  
	{
		return m_richTypes.end();
	}

	/** Returns a const iterator referring to the first element in the vector container RichType.
	@return A const iterator to the beginning of the sequence.
	*/
	RichTypeConstIterator getRichTypesBeginning() const 
	{
		return m_richTypes.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container RichType.
	@return A const iterator to the element past the end of the sequence.
	*/
	RichTypeConstIterator getRichTypesEnd() const 
	{
		return m_richTypes.end();
	}

	/** Returns a reference to the element at position n in the vector RichType.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _DebugTypeInfo<EncodingT> >& getRichTypeAt(size_t n)  
	{
		return m_richTypes.at(n);
	}

	/** Returns a const reference to the element at position n in the vector RichType.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _DebugTypeInfo<EncodingT> > getRichTypeAt(size_t n) const 
	{
		return m_richTypes.at(n);
	}

	/** Returns the number of elements in the vector container RichType.
	@return The number of elements that conform the vector's content.
	*/
	size_t getRichTypesSize() const 
	{
		return m_richTypes.size();
	}

	/** Returns whether the vector container RichType is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isRichTypesEmpty() const 
	{
		return m_richTypes.empty();
	}

	/** Adds a new element at the end of the vector RichType, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addRichType(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o)  
	{
		m_richTypes.push_back(copy_ptr(o));
	}

	/** The vector RichType is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	RichTypeIterator insertRichType(RichTypeIterator pos, boost::shared_ptr< _DebugTypeInfo<EncodingT> > o)  
	{
		return m_richTypes.insert(pos, copy_ptr(o));
	}

	/** The vector RichType is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertRichType(RichTypeIterator pos, RichTypeIterator first, RichTypeIterator last)  
	{
		std::transform(first, last, std::inserter(m_richTypes, pos), static_cast< boost::shared_ptr< _DebugTypeInfo<EncodingT> >(*)(boost::shared_ptr< _DebugTypeInfo<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container RichType a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	RichTypeIterator eraseRichType(RichTypeIterator pos)  
	{
		return m_richTypes.erase(pos);
	}

	/** Removes from the vector container RichType a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	RichTypeIterator eraseRichType(RichTypeIterator first, RichTypeIterator last)  
	{
		return m_richTypes.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container RichType, leaving the container with a size of 0.
	*/
	void clearRichTypes()  
	{
		m_richTypes.clear();
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
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> >& getDebugFunctionInfoAt(size_t n)  
	{
		return m_debugFunctionInfos.at(n);
	}

	/** Returns a const reference to the element at position n in the vector DebugFunctionInfo.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > getDebugFunctionInfoAt(size_t n) const 
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
	void addDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
	{
		m_debugFunctionInfos.push_back(copy_ptr(o));
	}

	/** The vector DebugFunctionInfo is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	DebugFunctionInfoIterator insertDebugFunctionInfo(DebugFunctionInfoIterator pos, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
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
		std::transform(first, last, std::inserter(m_debugFunctionInfos, pos), static_cast< boost::shared_ptr< _DebugFunctionInfo<EncodingT> >(*)(boost::shared_ptr< _DebugFunctionInfo<EncodingT> >) >(copy_ptr));
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

	/** Returns an iterator referring to the first element in the vector container DebugVariableInfo.
	@return An iterator to the beginning of the sequence.
	*/
	DebugVariableInfoIterator getDebugVariableInfosBeginning()  
	{
		return m_debugVariableInfos.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container DebugVariableInfo.
	@return An iterator to the element past the end of the sequence.
	*/
	DebugVariableInfoIterator getDebugVariableInfosEnd()  
	{
		return m_debugVariableInfos.end();
	}

	/** Returns a const iterator referring to the first element in the vector container DebugVariableInfo.
	@return A const iterator to the beginning of the sequence.
	*/
	DebugVariableInfoConstIterator getDebugVariableInfosBeginning() const 
	{
		return m_debugVariableInfos.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container DebugVariableInfo.
	@return A const iterator to the element past the end of the sequence.
	*/
	DebugVariableInfoConstIterator getDebugVariableInfosEnd() const 
	{
		return m_debugVariableInfos.end();
	}

	/** Returns a reference to the element at position n in the vector DebugVariableInfo.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _DebugVariableInfo<EncodingT> >& getDebugVariableInfoAt(size_t n)  
	{
		return m_debugVariableInfos.at(n);
	}

	/** Returns a const reference to the element at position n in the vector DebugVariableInfo.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _DebugVariableInfo<EncodingT> > getDebugVariableInfoAt(size_t n) const 
	{
		return m_debugVariableInfos.at(n);
	}

	/** Returns the number of elements in the vector container DebugVariableInfo.
	@return The number of elements that conform the vector's content.
	*/
	size_t getDebugVariableInfosSize() const 
	{
		return m_debugVariableInfos.size();
	}

	/** Returns whether the vector container DebugVariableInfo is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isDebugVariableInfosEmpty() const 
	{
		return m_debugVariableInfos.empty();
	}

	/** Adds a new element at the end of the vector DebugVariableInfo, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o)  
	{
		m_debugVariableInfos.push_back(copy_ptr(o));
	}

	/** The vector DebugVariableInfo is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	DebugVariableInfoIterator insertDebugVariableInfo(DebugVariableInfoIterator pos, boost::shared_ptr< _DebugVariableInfo<EncodingT> > o)  
	{
		return m_debugVariableInfos.insert(pos, copy_ptr(o));
	}

	/** The vector DebugVariableInfo is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertDebugVariableInfo(DebugVariableInfoIterator pos, DebugVariableInfoIterator first, DebugVariableInfoIterator last)  
	{
		std::transform(first, last, std::inserter(m_debugVariableInfos, pos), static_cast< boost::shared_ptr< _DebugVariableInfo<EncodingT> >(*)(boost::shared_ptr< _DebugVariableInfo<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container DebugVariableInfo a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	DebugVariableInfoIterator eraseDebugVariableInfo(DebugVariableInfoIterator pos)  
	{
		return m_debugVariableInfos.erase(pos);
	}

	/** Removes from the vector container DebugVariableInfo a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	DebugVariableInfoIterator eraseDebugVariableInfo(DebugVariableInfoIterator first, DebugVariableInfoIterator last)  
	{
		return m_debugVariableInfos.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container DebugVariableInfo, leaving the container with a size of 0.
	*/
	void clearDebugVariableInfos()  
	{
		m_debugVariableInfos.clear();
	}

	/** Prints DebugTypeInfo object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "DebugTypeInfo" << endl
		         << "identifier : " << m_identifier << endl
		         << "isChar : " << m_isChar << endl
		         << "isString : " << m_isString << endl
		         << "isBool : " << m_isBool << endl
		         << "isFloat : " << m_isFloat << endl
		         << "isSigned : " << m_isSigned << endl
		         << "isWide : " << m_isWide << endl
		         << "isPointer : " << m_isPointer << endl
		         << "isReference : " << m_isReference << endl
		         << "isArray : " << m_isArray << endl
		         << "isConst : " << m_isConst << endl
		         << "isVolatile : " << m_isVolatile << endl
		         << "isStruct : " << m_isStruct << endl
		         << "isClass : " << m_isClass << endl
		         << "isUnion : " << m_isUnion << endl
		         << "isInterface : " << m_isInterface << endl
		         << "isEnum : " << m_isEnum << endl
		         << "isFunction : " << m_isFunction << endl
		         << "baseName : " << A(m_baseName) << endl
		         << "name : " << A(m_name) << endl
		         << "sizeOf : " << m_sizeOf << endl
		         << "typeId : " << m_typeId << endl
		         << "arrayDim : " << m_arrayDim;
	}

	/** Defines <i> operator<< </i> for DebugTypeInfo.
	@param o Reference of C++ stream object.
	@param elem Const reference of DebugTypeInfo object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _DebugTypeInfo<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class DebugTypeInfoIDEquality;
	class DebugTypeInfoIDInferior;
	class IsCharEquality;
	class IsCharInferior;
	class IsCharSuperior;
	class IsStringEquality;
	class IsStringInferior;
	class IsStringSuperior;
	class IsBoolEquality;
	class IsBoolInferior;
	class IsBoolSuperior;
	class IsFloatEquality;
	class IsFloatInferior;
	class IsFloatSuperior;
	class IsSignedEquality;
	class IsSignedInferior;
	class IsSignedSuperior;
	class IsWideEquality;
	class IsWideInferior;
	class IsWideSuperior;
	class IsPointerEquality;
	class IsPointerInferior;
	class IsPointerSuperior;
	class IsReferenceEquality;
	class IsReferenceInferior;
	class IsReferenceSuperior;
	class IsArrayEquality;
	class IsArrayInferior;
	class IsArraySuperior;
	class IsConstEquality;
	class IsConstInferior;
	class IsConstSuperior;
	class IsVolatileEquality;
	class IsVolatileInferior;
	class IsVolatileSuperior;
	class IsStructEquality;
	class IsStructInferior;
	class IsStructSuperior;
	class IsClassEquality;
	class IsClassInferior;
	class IsClassSuperior;
	class IsUnionEquality;
	class IsUnionInferior;
	class IsUnionSuperior;
	class IsInterfaceEquality;
	class IsInterfaceInferior;
	class IsInterfaceSuperior;
	class IsEnumEquality;
	class IsEnumInferior;
	class IsEnumSuperior;
	class IsFunctionEquality;
	class IsFunctionInferior;
	class IsFunctionSuperior;
	class BaseNameEquality;
	class BaseNameInferior;
	class BaseNameSuperior;
	class NameEquality;
	class NameInferior;
	class NameSuperior;
	class SizeOfEquality;
	class SizeOfInferior;
	class SizeOfSuperior;
	class TypeIdEquality;
	class TypeIdInferior;
	class TypeIdSuperior;
	class ArrayDimEquality;
	class ArrayDimInferior;
	class ArrayDimSuperior;
};

typedef _DebugTypeInfo<ucs> UniDebugTypeInfo;
typedef _DebugTypeInfo<ansi> DebugTypeInfo;

NAMESPACE_END

#undef C
#undef A

#include "debugTypeInfoPredicate.hpp"

#endif
