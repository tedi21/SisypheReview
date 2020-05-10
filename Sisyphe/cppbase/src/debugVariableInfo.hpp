/* 
 * debugVariableInfo.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGVARIABLEINFO_HPP_
#define _DEBUGVARIABLEINFO_HPP_

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
class _DebugVariableInfoAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _DebugValueInfo;

template <class EncodingT>
class _DebugTypeInfo;

template <class EncodingT>
class _DebugFunctionInfo;

/// debugVariableInfo table represents variable information for debug.
template <class EncodingT>
class  _DebugVariableInfo {
private :
	long long	m_identifier;
	typename EncodingT::string_t	m_category;
	typename EncodingT::string_t	m_name;
	boost::shared_ptr< _DebugTypeInfo<EncodingT> >	m_debugTypeInfo;
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> >	m_debugFunctionInfo;
	typedef std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > >	vector_debugValueInfo;
	vector_debugValueInfo	m_debugValueInfos;
	Category*	m_logger;

protected :
	friend class data_access::_DebugVariableInfoAccess<EncodingT>;

	/** Creates a new element DebugVariableInfo.
	@param identifier 
	@param category 
	@param name 
	*/
	_DebugVariableInfo(long long identifier,
				const typename EncodingT::string_t& category,
				const typename EncodingT::string_t& name)
	: m_identifier(identifier),
	  m_category(category),
	  m_name(name)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugVariableInfo "
				<< m_identifier << ' '
				<< A(m_category) << ' '
				<< A(m_name) << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in DebugVariableInfo.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element DebugVariableInfo.
	*/
	_DebugVariableInfo()
	: m_identifier(-1),
	  m_category(EncodingT::EMPTY),
	  m_name(EncodingT::EMPTY)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugVariableInfo ";
	}

	/** Creates a new element DebugVariableInfo.
	@param category 
	@param name 
	*/
	_DebugVariableInfo(const typename EncodingT::string_t& category,
				const typename EncodingT::string_t& name)
	: m_identifier(-1),
	  m_category(category),
	  m_name(name)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugVariableInfo "
				<< m_identifier << ' '
				<< A(m_category) << ' '
				<< A(m_name) << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in DebugVariableInfo.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>category</i> in DebugVariableInfo.
	@return 
	*/
	const typename EncodingT::string_t& getCategory() const 
	{
		return m_category;
	}

	/** Sets a value of the element <i>category</i> in DebugVariableInfo.
	@param category 
	*/
	void setCategory(const typename EncodingT::string_t& category)  
	{
		m_category = category;
	}

	/** Returns a const reference to the element <i>name</i> in DebugVariableInfo.
	@return 
	*/
	const typename EncodingT::string_t& getName() const 
	{
		return m_name;
	}

	/** Sets a value of the element <i>name</i> in DebugVariableInfo.
	@param name 
	*/
	void setName(const typename EncodingT::string_t& name)  
	{
		m_name = name;
	}

	/** Returns a const reference to the element <i>debugTypeInfo</i> in DebugVariableInfo.
	@return 
	*/
	boost::shared_ptr< _DebugTypeInfo<EncodingT> > getDebugTypeInfo() const 
	{
		return m_debugTypeInfo;
	}

	/** Sets a value of the element <i>debugTypeInfo</i> in DebugVariableInfo.
	@param debugTypeInfo 
	*/
	void setDebugTypeInfo(boost::shared_ptr< _DebugTypeInfo<EncodingT> > debugTypeInfo)  
	{
		m_debugTypeInfo = debugTypeInfo;
	}

	/** Returns whether the element <i>debugTypeInfo</i> in DebugVariableInfo is NULL.
	@return True if the element <i>debugTypeInfo</i> is NULL, false otherwise.
	*/
	bool isNullDebugTypeInfo() const 
	{
		return !m_debugTypeInfo;
	}

	/** Removes from DebugVariableInfo an element <i>debugTypeInfo</i>.
	*/
	void eraseDebugTypeInfo()  
	{
		m_debugTypeInfo.reset();
	}

	/** Returns a const reference to the element <i>debugFunctionInfo</i> in DebugVariableInfo.
	@return 
	*/
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > getDebugFunctionInfo() const 
	{
		return m_debugFunctionInfo;
	}

	/** Sets a value of the element <i>debugFunctionInfo</i> in DebugVariableInfo.
	@param debugFunctionInfo 
	*/
	void setDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > debugFunctionInfo)  
	{
		m_debugFunctionInfo = debugFunctionInfo;
	}

	/** Returns whether the element <i>debugFunctionInfo</i> in DebugVariableInfo is NULL.
	@return True if the element <i>debugFunctionInfo</i> is NULL, false otherwise.
	*/
	bool isNullDebugFunctionInfo() const 
	{
		return !m_debugFunctionInfo;
	}

	/** Removes from DebugVariableInfo an element <i>debugFunctionInfo</i>.
	*/
	void eraseDebugFunctionInfo()  
	{
		m_debugFunctionInfo.reset();
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

	/** Prints DebugVariableInfo object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "DebugVariableInfo" << endl
		         << "identifier : " << m_identifier << endl
		         << "category : " << A(m_category) << endl
		         << "name : " << A(m_name);
	}

	/** Defines <i> operator<< </i> for DebugVariableInfo.
	@param o Reference of C++ stream object.
	@param elem Const reference of DebugVariableInfo object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _DebugVariableInfo<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class DebugVariableInfoIDEquality;
	class CategoryEquality;
	class CategoryInferior;
	class CategorySuperior;
	class NameEquality;
	class NameInferior;
	class NameSuperior;
};

typedef _DebugVariableInfo<ucs> UniDebugVariableInfo;
typedef _DebugVariableInfo<ansi> DebugVariableInfo;

NAMESPACE_END

#undef C
#undef A

#include "debugVariableInfoPredicate.hpp"

#endif
