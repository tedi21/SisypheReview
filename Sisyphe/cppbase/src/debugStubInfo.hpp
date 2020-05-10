/* 
 * debugStubInfo.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGSTUBINFO_HPP_
#define _DEBUGSTUBINFO_HPP_

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
class _DebugStubInfoAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _DebugValueInfo;

template <class EncodingT>
class _DebugFileInfo;

/// debugStubInfo table represents stub information for debug.
template <class EncodingT>
class  _DebugStubInfo {
private :
	long long	m_identifier;
	long long	m_lineNumber;
	long long	m_isLineSkipped;
	boost::shared_ptr< _DebugFileInfo<EncodingT> >	m_debugFileInfo;
	typedef std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > >	vector_debugValueInfo;
	vector_debugValueInfo	m_debugValueInfos;
	Category*	m_logger;

protected :
	friend class data_access::_DebugStubInfoAccess<EncodingT>;

	/** Creates a new element DebugStubInfo.
	@param identifier 
	@param lineNumber 
	@param isLineSkipped 
	*/
	_DebugStubInfo(long long identifier,
				long long lineNumber,
				long long isLineSkipped)
	: m_identifier(identifier),
	  m_lineNumber(lineNumber),
	  m_isLineSkipped(isLineSkipped)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugStubInfo "
				<< m_identifier << ' '
				<< m_lineNumber << ' '
				<< m_isLineSkipped << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in DebugStubInfo.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element DebugStubInfo.
	*/
	_DebugStubInfo()
	: m_identifier(-1),
	  m_lineNumber(0),
	  m_isLineSkipped(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugStubInfo ";
	}

	/** Creates a new element DebugStubInfo.
	@param lineNumber 
	@param isLineSkipped 
	*/
	_DebugStubInfo(long long lineNumber,
				long long isLineSkipped)
	: m_identifier(-1),
	  m_lineNumber(lineNumber),
	  m_isLineSkipped(isLineSkipped)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugStubInfo "
				<< m_identifier << ' '
				<< m_lineNumber << ' '
				<< m_isLineSkipped << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in DebugStubInfo.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>lineNumber</i> in DebugStubInfo.
	@return 
	*/
	long long getLineNumber() const 
	{
		return m_lineNumber;
	}

	/** Sets a value of the element <i>lineNumber</i> in DebugStubInfo.
	@param lineNumber 
	*/
	void setLineNumber(long long lineNumber)  
	{
		m_lineNumber = lineNumber;
	}

	/** Returns a const reference to the element <i>isLineSkipped</i> in DebugStubInfo.
	@return 
	*/
	long long getIsLineSkipped() const 
	{
		return m_isLineSkipped;
	}

	/** Sets a value of the element <i>isLineSkipped</i> in DebugStubInfo.
	@param isLineSkipped 
	*/
	void setIsLineSkipped(long long isLineSkipped)  
	{
		m_isLineSkipped = isLineSkipped;
	}

	/** Returns a const reference to the element <i>debugFileInfo</i> in DebugStubInfo.
	@return 
	*/
	boost::shared_ptr< _DebugFileInfo<EncodingT> > getDebugFileInfo() const 
	{
		return m_debugFileInfo;
	}

	/** Sets a value of the element <i>debugFileInfo</i> in DebugStubInfo.
	@param debugFileInfo 
	*/
	void setDebugFileInfo(boost::shared_ptr< _DebugFileInfo<EncodingT> > debugFileInfo)  
	{
		m_debugFileInfo = debugFileInfo;
	}

	/** Returns whether the element <i>debugFileInfo</i> in DebugStubInfo is NULL.
	@return True if the element <i>debugFileInfo</i> is NULL, false otherwise.
	*/
	bool isNullDebugFileInfo() const 
	{
		return !m_debugFileInfo;
	}

	/** Removes from DebugStubInfo an element <i>debugFileInfo</i>.
	*/
	void eraseDebugFileInfo()  
	{
		m_debugFileInfo.reset();
	}

	/// Random access iterator types for DebugValueInfo vector.
	typedef typename vector_debugValueInfo::iterator	DebugValueInfoIterator;
	typedef typename vector_debugValueInfo::const_iterator	DebugValueInfoConstIterator;

	/** Returns an iterator referring to the first element in the vector container DebugValueInfo.
	@return An iterator to the beginning of the sequence.
	*/
	DebugValueInfoIterator getDebugValueInfosBeginning()  
	{
		return m_debugValueInfos.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container DebugValueInfo.
	@return An iterator to the element past the end of the sequence.
	*/
	DebugValueInfoIterator getDebugValueInfosEnd()  
	{
		return m_debugValueInfos.end();
	}

	/** Returns a const iterator referring to the first element in the vector container DebugValueInfo.
	@return A const iterator to the beginning of the sequence.
	*/
	DebugValueInfoConstIterator getDebugValueInfosBeginning() const 
	{
		return m_debugValueInfos.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container DebugValueInfo.
	@return A const iterator to the element past the end of the sequence.
	*/
	DebugValueInfoConstIterator getDebugValueInfosEnd() const 
	{
		return m_debugValueInfos.end();
	}

	/** Returns a reference to the element at position n in the vector DebugValueInfo.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _DebugValueInfo<EncodingT> >& getDebugValueInfoAt(size_t n)  
	{
		return m_debugValueInfos.at(n);
	}

	/** Returns a const reference to the element at position n in the vector DebugValueInfo.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _DebugValueInfo<EncodingT> > getDebugValueInfoAt(size_t n) const 
	{
		return m_debugValueInfos.at(n);
	}

	/** Returns the number of elements in the vector container DebugValueInfo.
	@return The number of elements that conform the vector's content.
	*/
	size_t getDebugValueInfosSize() const 
	{
		return m_debugValueInfos.size();
	}

	/** Returns whether the vector container DebugValueInfo is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isDebugValueInfosEmpty() const 
	{
		return m_debugValueInfos.empty();
	}

	/** Adds a new element at the end of the vector DebugValueInfo, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addDebugValueInfo(boost::shared_ptr< _DebugValueInfo<EncodingT> > o)  
	{
		m_debugValueInfos.push_back(copy_ptr(o));
	}

	/** The vector DebugValueInfo is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	DebugValueInfoIterator insertDebugValueInfo(DebugValueInfoIterator pos, boost::shared_ptr< _DebugValueInfo<EncodingT> > o)  
	{
		return m_debugValueInfos.insert(pos, copy_ptr(o));
	}

	/** The vector DebugValueInfo is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertDebugValueInfo(DebugValueInfoIterator pos, DebugValueInfoIterator first, DebugValueInfoIterator last)  
	{
		std::transform(first, last, std::inserter(m_debugValueInfos, pos), static_cast< boost::shared_ptr< _DebugValueInfo<EncodingT> >(*)(boost::shared_ptr< _DebugValueInfo<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container DebugValueInfo a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	DebugValueInfoIterator eraseDebugValueInfo(DebugValueInfoIterator pos)  
	{
		return m_debugValueInfos.erase(pos);
	}

	/** Removes from the vector container DebugValueInfo a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	DebugValueInfoIterator eraseDebugValueInfo(DebugValueInfoIterator first, DebugValueInfoIterator last)  
	{
		return m_debugValueInfos.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container DebugValueInfo, leaving the container with a size of 0.
	*/
	void clearDebugValueInfos()  
	{
		m_debugValueInfos.clear();
	}

	/** Prints DebugStubInfo object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "DebugStubInfo" << endl
		         << "identifier : " << m_identifier << endl
		         << "lineNumber : " << m_lineNumber << endl
		         << "isLineSkipped : " << m_isLineSkipped;
	}

	/** Defines <i> operator<< </i> for DebugStubInfo.
	@param o Reference of C++ stream object.
	@param elem Const reference of DebugStubInfo object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _DebugStubInfo<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class DebugStubInfoIDEquality;
	class LineNumberEquality;
	class LineNumberInferior;
	class LineNumberSuperior;
	class IsLineSkippedEquality;
	class IsLineSkippedInferior;
	class IsLineSkippedSuperior;
};

typedef _DebugStubInfo<ucs> UniDebugStubInfo;
typedef _DebugStubInfo<ansi> DebugStubInfo;

NAMESPACE_END

#undef C
#undef A

#include "debugStubInfoPredicate.hpp"

#endif
