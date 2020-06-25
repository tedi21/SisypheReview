/* 
 * cppEnum.hpp
 *
 *
 * @date 25-06-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPENUM_HPP_
#define _CPPENUM_HPP_

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
class _CppEnumAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _CppEnumConstant;

template <class EncodingT>
class _CppFile;

template <class EncodingT>
class _CppClass;

/// cppEnum table represents an enumeration.
template <class EncodingT>
class  _CppEnum {
private :
	long long	m_identifier;
	typename EncodingT::string_t	m_name;
	boost::shared_ptr< _CppFile<EncodingT> >	m_cppFile;
	boost::shared_ptr< _CppClass<EncodingT> >	m_cppClass;
	typename EncodingT::string_t	m_accessSpecifier;
	long long	m_lineNumber;
	long long	m_startBlock;
	long long	m_lengthBlock;
	typedef std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > >	vector_cppEnumConstant;
	vector_cppEnumConstant	m_cppEnumConstants;
	Category*	m_logger;

protected :
	friend class data_access::_CppEnumAccess<EncodingT>;

	/** Creates a new element CppEnum.
	@param identifier 
	@param name 
	@param accessSpecifier 
	@param lineNumber 
	@param startBlock 
	@param lengthBlock 
	*/
	_CppEnum(long long identifier,
				const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& accessSpecifier,
				long long lineNumber,
				long long startBlock,
				long long lengthBlock)
	: m_identifier(identifier),
	  m_name(name),
	  m_accessSpecifier(accessSpecifier),
	  m_lineNumber(lineNumber),
	  m_startBlock(startBlock),
	  m_lengthBlock(lengthBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppEnum "
				<< m_identifier << ' '
				<< A(m_name) << ' '
				<< A(m_accessSpecifier) << ' '
				<< m_lineNumber << ' '
				<< m_startBlock << ' '
				<< m_lengthBlock << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppEnum.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element CppEnum.
	*/
	_CppEnum()
	: m_identifier(-1),
	  m_name(EncodingT::EMPTY),
	  m_accessSpecifier(EncodingT::EMPTY),
	  m_lineNumber(0),
	  m_startBlock(0),
	  m_lengthBlock(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppEnum ";
	}

	/** Creates a new element CppEnum.
	@param name 
	@param accessSpecifier 
	@param lineNumber 
	@param startBlock 
	@param lengthBlock 
	*/
	_CppEnum(const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& accessSpecifier,
				long long lineNumber,
				long long startBlock,
				long long lengthBlock)
	: m_identifier(-1),
	  m_name(name),
	  m_accessSpecifier(accessSpecifier),
	  m_lineNumber(lineNumber),
	  m_startBlock(startBlock),
	  m_lengthBlock(lengthBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppEnum "
				<< m_identifier << ' '
				<< A(m_name) << ' '
				<< A(m_accessSpecifier) << ' '
				<< m_lineNumber << ' '
				<< m_startBlock << ' '
				<< m_lengthBlock << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in CppEnum.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>name</i> in CppEnum.
	@return 
	*/
	const typename EncodingT::string_t& getName() const 
	{
		return m_name;
	}

	/** Sets a value of the element <i>name</i> in CppEnum.
	@param name 
	*/
	void setName(const typename EncodingT::string_t& name)  
	{
		m_name = name;
	}

	/** Returns a const reference to the element <i>cppFile</i> in CppEnum.
	@return 
	*/
	boost::shared_ptr< _CppFile<EncodingT> > getCppFile() const 
	{
		return m_cppFile;
	}

	/** Sets a value of the element <i>cppFile</i> in CppEnum.
	@param cppFile 
	*/
	void setCppFile(boost::shared_ptr< _CppFile<EncodingT> > cppFile)  
	{
		m_cppFile = cppFile;
	}

	/** Returns whether the element <i>cppFile</i> in CppEnum is NULL.
	@return True if the element <i>cppFile</i> is NULL, false otherwise.
	*/
	bool isNullCppFile() const 
	{
		return !m_cppFile;
	}

	/** Removes from CppEnum an element <i>cppFile</i>.
	*/
	void eraseCppFile()  
	{
		m_cppFile.reset();
	}

	/** Returns a const reference to the element <i>cppClass</i> in CppEnum.
	@return 
	*/
	boost::shared_ptr< _CppClass<EncodingT> > getCppClass() const 
	{
		return m_cppClass;
	}

	/** Sets a value of the element <i>cppClass</i> in CppEnum.
	@param cppClass 
	*/
	void setCppClass(boost::shared_ptr< _CppClass<EncodingT> > cppClass)  
	{
		m_cppClass = cppClass;
	}

	/** Returns whether the element <i>cppClass</i> in CppEnum is NULL.
	@return True if the element <i>cppClass</i> is NULL, false otherwise.
	*/
	bool isNullCppClass() const 
	{
		return !m_cppClass;
	}

	/** Removes from CppEnum an element <i>cppClass</i>.
	*/
	void eraseCppClass()  
	{
		m_cppClass.reset();
	}

	/** Returns a const reference to the element <i>accessSpecifier</i> in CppEnum.
	@return 
	*/
	const typename EncodingT::string_t& getAccessSpecifier() const 
	{
		return m_accessSpecifier;
	}

	/** Sets a value of the element <i>accessSpecifier</i> in CppEnum.
	@param accessSpecifier 
	*/
	void setAccessSpecifier(const typename EncodingT::string_t& accessSpecifier)  
	{
		m_accessSpecifier = accessSpecifier;
	}

	/** Returns a const reference to the element <i>lineNumber</i> in CppEnum.
	@return 
	*/
	long long getLineNumber() const 
	{
		return m_lineNumber;
	}

	/** Sets a value of the element <i>lineNumber</i> in CppEnum.
	@param lineNumber 
	*/
	void setLineNumber(long long lineNumber)  
	{
		m_lineNumber = lineNumber;
	}

	/** Returns a const reference to the element <i>startBlock</i> in CppEnum.
	@return 
	*/
	long long getStartBlock() const 
	{
		return m_startBlock;
	}

	/** Sets a value of the element <i>startBlock</i> in CppEnum.
	@param startBlock 
	*/
	void setStartBlock(long long startBlock)  
	{
		m_startBlock = startBlock;
	}

	/** Returns a const reference to the element <i>lengthBlock</i> in CppEnum.
	@return 
	*/
	long long getLengthBlock() const 
	{
		return m_lengthBlock;
	}

	/** Sets a value of the element <i>lengthBlock</i> in CppEnum.
	@param lengthBlock 
	*/
	void setLengthBlock(long long lengthBlock)  
	{
		m_lengthBlock = lengthBlock;
	}

	/// Random access iterator types for CppEnumConstant vector.
	typedef typename vector_cppEnumConstant::iterator	CppEnumConstantIterator;
	typedef typename vector_cppEnumConstant::const_iterator	CppEnumConstantConstIterator;

	/** Returns an iterator referring to the first element in the vector container CppEnumConstant.
	@return An iterator to the beginning of the sequence.
	*/
	CppEnumConstantIterator getCppEnumConstantsBeginning()  
	{
		return m_cppEnumConstants.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container CppEnumConstant.
	@return An iterator to the element past the end of the sequence.
	*/
	CppEnumConstantIterator getCppEnumConstantsEnd()  
	{
		return m_cppEnumConstants.end();
	}

	/** Returns a const iterator referring to the first element in the vector container CppEnumConstant.
	@return A const iterator to the beginning of the sequence.
	*/
	CppEnumConstantConstIterator getCppEnumConstantsBeginning() const 
	{
		return m_cppEnumConstants.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container CppEnumConstant.
	@return A const iterator to the element past the end of the sequence.
	*/
	CppEnumConstantConstIterator getCppEnumConstantsEnd() const 
	{
		return m_cppEnumConstants.end();
	}

	/** Returns a reference to the element at position n in the vector CppEnumConstant.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppEnumConstant<EncodingT> >& getCppEnumConstantAt(size_t n)  
	{
		return m_cppEnumConstants.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppEnumConstant.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppEnumConstant<EncodingT> > getCppEnumConstantAt(size_t n) const 
	{
		return m_cppEnumConstants.at(n);
	}

	/** Returns the number of elements in the vector container CppEnumConstant.
	@return The number of elements that conform the vector's content.
	*/
	size_t getCppEnumConstantsSize() const 
	{
		return m_cppEnumConstants.size();
	}

	/** Returns whether the vector container CppEnumConstant is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isCppEnumConstantsEmpty() const 
	{
		return m_cppEnumConstants.empty();
	}

	/** Adds a new element at the end of the vector CppEnumConstant, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o)  
	{
		m_cppEnumConstants.push_back(copy_ptr(o));
	}

	/** The vector CppEnumConstant is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppEnumConstantIterator insertCppEnumConstant(CppEnumConstantIterator pos, boost::shared_ptr< _CppEnumConstant<EncodingT> > o)  
	{
		return m_cppEnumConstants.insert(pos, copy_ptr(o));
	}

	/** The vector CppEnumConstant is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertCppEnumConstant(CppEnumConstantIterator pos, CppEnumConstantIterator first, CppEnumConstantIterator last)  
	{
		std::transform(first, last, std::inserter(m_cppEnumConstants, pos), static_cast< boost::shared_ptr< _CppEnumConstant<EncodingT> >(*)(boost::shared_ptr< _CppEnumConstant<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container CppEnumConstant a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	CppEnumConstantIterator eraseCppEnumConstant(CppEnumConstantIterator pos)  
	{
		return m_cppEnumConstants.erase(pos);
	}

	/** Removes from the vector container CppEnumConstant a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	CppEnumConstantIterator eraseCppEnumConstant(CppEnumConstantIterator first, CppEnumConstantIterator last)  
	{
		return m_cppEnumConstants.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container CppEnumConstant, leaving the container with a size of 0.
	*/
	void clearCppEnumConstants()  
	{
		m_cppEnumConstants.clear();
	}

	/** Prints CppEnum object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "CppEnum" << endl
		         << "identifier : " << m_identifier << endl
		         << "name : " << A(m_name) << endl
		         << "accessSpecifier : " << A(m_accessSpecifier) << endl
		         << "lineNumber : " << m_lineNumber << endl
		         << "startBlock : " << m_startBlock << endl
		         << "lengthBlock : " << m_lengthBlock;
	}

	/** Defines <i> operator<< </i> for CppEnum.
	@param o Reference of C++ stream object.
	@param elem Const reference of CppEnum object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _CppEnum<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class CppEnumIDEquality;
	class NameEquality;
	class NameInferior;
	class NameSuperior;
	class AccessSpecifierEquality;
	class AccessSpecifierInferior;
	class AccessSpecifierSuperior;
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

typedef _CppEnum<ucs> UniCppEnum;
typedef _CppEnum<ansi> CppEnum;

NAMESPACE_END

#undef C
#undef A

#include "cppEnumPredicate.hpp"

#endif
