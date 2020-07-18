/* 
 * cppInclude.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPINCLUDE_HPP_
#define _CPPINCLUDE_HPP_

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
class _CppIncludeAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _CppFile;

/// cppInclude table represents an include in cpp file.
template <class EncodingT>
class  _CppInclude {
private :
	long long	m_identifier;
	typename EncodingT::string_t	m_fileName;
	boost::shared_ptr< _CppFile<EncodingT> >	m_cppFile;
	long long	m_lineNumber;
	Category*	m_logger;

protected :
	friend class data_access::_CppIncludeAccess<EncodingT>;

	/** Creates a new element CppInclude.
	@param identifier 
	@param fileName 
	@param lineNumber 
	*/
	_CppInclude(long long identifier,
				const typename EncodingT::string_t& fileName,
				long long lineNumber)
	: m_identifier(identifier),
	  m_fileName(fileName),
	  m_lineNumber(lineNumber)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppInclude "
				<< m_identifier << ' '
				<< A(m_fileName) << ' '
				<< m_lineNumber << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppInclude.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element CppInclude.
	*/
	_CppInclude()
	: m_identifier(-1),
	  m_fileName(EncodingT::EMPTY),
	  m_lineNumber(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppInclude ";
	}

	/** Creates a new element CppInclude.
	@param fileName 
	@param lineNumber 
	*/
	_CppInclude(const typename EncodingT::string_t& fileName,
				long long lineNumber)
	: m_identifier(-1),
	  m_fileName(fileName),
	  m_lineNumber(lineNumber)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppInclude "
				<< m_identifier << ' '
				<< A(m_fileName) << ' '
				<< m_lineNumber << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in CppInclude.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>fileName</i> in CppInclude.
	@return 
	*/
	const typename EncodingT::string_t& getFileName() const 
	{
		return m_fileName;
	}

	/** Sets a value of the element <i>fileName</i> in CppInclude.
	@param fileName 
	*/
	void setFileName(const typename EncodingT::string_t& fileName)  
	{
		m_fileName = fileName;
	}

	/** Returns a const reference to the element <i>cppFile</i> in CppInclude.
	@return 
	*/
	boost::shared_ptr< _CppFile<EncodingT> > getCppFile() const 
	{
		return m_cppFile;
	}

	/** Sets a value of the element <i>cppFile</i> in CppInclude.
	@param cppFile 
	*/
	void setCppFile(boost::shared_ptr< _CppFile<EncodingT> > cppFile)  
	{
		m_cppFile = cppFile;
	}

	/** Returns whether the element <i>cppFile</i> in CppInclude is NULL.
	@return True if the element <i>cppFile</i> is NULL, false otherwise.
	*/
	bool isNullCppFile() const 
	{
		return !m_cppFile;
	}

	/** Removes from CppInclude an element <i>cppFile</i>.
	*/
	void eraseCppFile()  
	{
		m_cppFile.reset();
	}

	/** Returns a const reference to the element <i>lineNumber</i> in CppInclude.
	@return 
	*/
	long long getLineNumber() const 
	{
		return m_lineNumber;
	}

	/** Sets a value of the element <i>lineNumber</i> in CppInclude.
	@param lineNumber 
	*/
	void setLineNumber(long long lineNumber)  
	{
		m_lineNumber = lineNumber;
	}

	/** Prints CppInclude object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "CppInclude" << endl
		         << "identifier : " << m_identifier << endl
		         << "fileName : " << A(m_fileName) << endl
		         << "lineNumber : " << m_lineNumber;
	}

	/** Defines <i> operator<< </i> for CppInclude.
	@param o Reference of C++ stream object.
	@param elem Const reference of CppInclude object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _CppInclude<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class CppIncludeIDEquality;
	class FileNameEquality;
	class FileNameInferior;
	class FileNameSuperior;
	class LineNumberEquality;
	class LineNumberInferior;
	class LineNumberSuperior;
};

typedef _CppInclude<ucs> UniCppInclude;
typedef _CppInclude<ansi> CppInclude;

NAMESPACE_END

#undef C
#undef A

#include "cppIncludePredicate.hpp"

#endif
