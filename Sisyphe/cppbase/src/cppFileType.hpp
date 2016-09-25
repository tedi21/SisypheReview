/* 
 * cppFileType.hpp
 *
 *
 * @date 28-08-2016
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPFILETYPE_HPP_
#define _CPPFILETYPE_HPP_

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
class _CppFileTypeAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _CppFile;

/// Creation Table________________cppFileType table represents a type of file : header or source.
template <class EncodingT>
class  _CppFileType {
private :
	int	m_identifier;
	typename EncodingT::string_t	m_string;
	typedef std::vector< boost::shared_ptr< _CppFile<EncodingT> > >	vector_cppFile;
	vector_cppFile	m_cppFiles;
	Category*	m_logger;

protected :
	friend class data_access::_CppFileTypeAccess<EncodingT>;

	/** Creates a new element CppFileType.
	@param identifier 
	@param string 
	*/
	_CppFileType(int identifier,
				const typename EncodingT::string_t& string)
	: m_identifier(identifier),
	  m_string(string)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppFileType "
				<< m_identifier << ' '
				<< A(m_string) << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppFileType.
	@param identifier 
	*/
	void setIdentifier(int identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element CppFileType.
	*/
	_CppFileType()
	: m_identifier(-1),
	  m_string(EncodingT::EMPTY)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppFileType ";
	}

	/** Creates a new element CppFileType.
	@param string 
	*/
	_CppFileType(const typename EncodingT::string_t& string)
	: m_identifier(-1),
	  m_string(string)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppFileType "
				<< m_identifier << ' '
				<< A(m_string) << ' ';
	}

	/** Creates a copy of elem as the content for the CppFileType object.
	@param elem A CppFileType object containing elements of the same type.
	*/
	_CppFileType(const _CppFileType<EncodingT>& elem)
	: m_identifier(elem.m_identifier),
	  m_string(elem.m_string),
	  m_cppFiles(copy_ptr(elem.m_cppFiles))
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppFileType " << ": copy";
	}

	/** Assigns a copy of elem as the new content for the CppFileType object.
	@param elem A CppFileType object containing elements of the same type.
	@return *this
	*/
	_CppFileType<EncodingT>& operator=(const _CppFileType<EncodingT>& elem)  
	{
		m_identifier = elem.m_identifier;
		m_string = elem.m_string;
		m_cppFiles = copy_ptr(elem.m_cppFiles);
		return *this;
	}

	/** Returns a const reference to the element <i>identifier</i> in CppFileType.
	@return 
	*/
	int getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>string</i> in CppFileType.
	@return 
	*/
	const typename EncodingT::string_t& getString() const 
	{
		return m_string;
	}

	/** Sets a value of the element <i>string</i> in CppFileType.
	@param string 
	*/
	void setString(const typename EncodingT::string_t& string)  
	{
		m_string = string;
	}

	/// Random access iterator types for CppFile vector.
	typedef typename vector_cppFile::iterator	CppFileIterator;
	typedef typename vector_cppFile::const_iterator	CppFileConstIterator;

	/** Returns an iterator referring to the first element in the vector container CppFile.
	@return An iterator to the beginning of the sequence.
	*/
	CppFileIterator getCppFilesBeginning()  
	{
		return m_cppFiles.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container CppFile.
	@return An iterator to the element past the end of the sequence.
	*/
	CppFileIterator getCppFilesEnd()  
	{
		return m_cppFiles.end();
	}

	/** Returns a const iterator referring to the first element in the vector container CppFile.
	@return A const iterator to the beginning of the sequence.
	*/
	CppFileConstIterator getCppFilesBeginning() const 
	{
		return m_cppFiles.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container CppFile.
	@return A const iterator to the element past the end of the sequence.
	*/
	CppFileConstIterator getCppFilesEnd() const 
	{
		return m_cppFiles.end();
	}

	/** Returns a reference to the element at position n in the vector CppFile.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppFile<EncodingT> >& getCppFileAt(size_t n)  
	{
		return m_cppFiles.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppFile.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppFile<EncodingT> > getCppFileAt(size_t n) const 
	{
		return m_cppFiles.at(n);
	}

	/** Returns the number of elements in the vector container CppFile.
	@return The number of elements that conform the vector's content.
	*/
	size_t getCppFilesSize() const 
	{
		return m_cppFiles.size();
	}

	/** Returns whether the vector container CppFile is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isCppFilesEmpty() const 
	{
		return m_cppFiles.empty();
	}

	/** Adds a new element at the end of the vector CppFile, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addCppFile(boost::shared_ptr< _CppFile<EncodingT> > o)  
	{
		m_cppFiles.push_back(copy_ptr(o));
	}

	/** The vector CppFile is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppFileIterator insertCppFile(CppFileIterator pos, boost::shared_ptr< _CppFile<EncodingT> > o)  
	{
		return m_cppFiles.insert(pos, copy_ptr(o));
	}

	/** The vector CppFile is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertCppFile(CppFileIterator pos, CppFileIterator first, CppFileIterator last)  
	{
		std::transform(first, last, std::inserter(m_cppFiles, pos), static_cast< boost::shared_ptr< _CppFile<EncodingT> >(*)(boost::shared_ptr< _CppFile<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container CppFile a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	CppFileIterator eraseCppFile(CppFileIterator pos)  
	{
		return m_cppFiles.erase(pos);
	}

	/** Removes from the vector container CppFile a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	CppFileIterator eraseCppFile(CppFileIterator first, CppFileIterator last)  
	{
		return m_cppFiles.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container CppFile, leaving the container with a size of 0.
	*/
	void clearCppFiles()  
	{
		m_cppFiles.clear();
	}

	/** Prints CppFileType object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "CppFileType" << endl
		         << "identifier : " << m_identifier << endl
		         << "string : " << A(m_string);
	}

	/** Defines <i> operator<< </i> for CppFileType.
	@param o Reference of C++ stream object.
	@param elem Const reference of CppFileType object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _CppFileType<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class CppFileTypeIDEquality;
	class StringEquality;
	class StringInferior;
	class StringSuperior;
};

typedef _CppFileType<ucs> UniCppFileType;
typedef _CppFileType<ansi> CppFileType;

NAMESPACE_END

#undef C
#undef A

#include "cppFileTypePredicate.hpp"

#endif
