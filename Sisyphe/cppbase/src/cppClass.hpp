/* 
 * cppClass.hpp
 *
 *
 * @date 25-06-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPCLASS_HPP_
#define _CPPCLASS_HPP_

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
class _CppClassAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _CppInheritance;

template <class EncodingT>
class _CppFunction;

template <class EncodingT>
class _CppClass;

template <class EncodingT>
class _CppAttribute;

template <class EncodingT>
class _CppEnum;

template <class EncodingT>
class _CppClass;

template <class EncodingT>
class _CppFile;

/// cppClass table represents a class.
template <class EncodingT>
class  _CppClass {
private :
	boost::shared_ptr< _CppClass<EncodingT> >	m_encapsulationClass;
	long long	m_identifier;
	typename EncodingT::string_t	m_name;
	typename EncodingT::string_t	m_fullName;
	typename EncodingT::string_t	m_accessSpecifier;
	long long	m_isStruct;
	long long	m_isInterface;
	long long	m_isAbstract;
	long long	m_isTemplate;
	long long	m_linesCount;
	boost::shared_ptr< _CppFile<EncodingT> >	m_cppFile;
	long long	m_lineNumber;
	long long	m_startBlock;
	long long	m_lengthBlock;
	typedef std::vector< boost::shared_ptr< _CppInheritance<EncodingT> > >	vector_cppInheritance;
	vector_cppInheritance	m_cppInheritances;
	typedef std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >	vector_cppFunction;
	vector_cppFunction	m_cppFunctions;
	typedef std::vector< boost::shared_ptr< _CppClass<EncodingT> > >	vector_internClasse;
	vector_internClasse	m_internClasses;
	typedef std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > >	vector_cppAttribute;
	vector_cppAttribute	m_cppAttributes;
	typedef std::vector< boost::shared_ptr< _CppEnum<EncodingT> > >	vector_cppEnum;
	vector_cppEnum	m_cppEnums;
	Category*	m_logger;

protected :
	friend class data_access::_CppClassAccess<EncodingT>;

	/** Creates a new element CppClass.
	@param identifier 
	@param name 
	@param fullName 
	@param accessSpecifier 
	@param isStruct 
	@param isInterface 
	@param isAbstract 
	@param isTemplate 
	@param linesCount 
	@param lineNumber 
	@param startBlock 
	@param lengthBlock 
	*/
	_CppClass(long long identifier,
				const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& fullName,
				const typename EncodingT::string_t& accessSpecifier,
				long long isStruct,
				long long isInterface,
				long long isAbstract,
				long long isTemplate,
				long long linesCount,
				long long lineNumber,
				long long startBlock,
				long long lengthBlock)
	: m_identifier(identifier),
	  m_name(name),
	  m_fullName(fullName),
	  m_accessSpecifier(accessSpecifier),
	  m_isStruct(isStruct),
	  m_isInterface(isInterface),
	  m_isAbstract(isAbstract),
	  m_isTemplate(isTemplate),
	  m_linesCount(linesCount),
	  m_lineNumber(lineNumber),
	  m_startBlock(startBlock),
	  m_lengthBlock(lengthBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppClass "
				<< m_identifier << ' '
				<< A(m_name) << ' '
				<< A(m_fullName) << ' '
				<< A(m_accessSpecifier) << ' '
				<< m_isStruct << ' '
				<< m_isInterface << ' '
				<< m_isAbstract << ' '
				<< m_isTemplate << ' '
				<< m_linesCount << ' '
				<< m_lineNumber << ' '
				<< m_startBlock << ' '
				<< m_lengthBlock << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppClass.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element CppClass.
	*/
	_CppClass()
	: m_identifier(-1),
	  m_name(EncodingT::EMPTY),
	  m_fullName(EncodingT::EMPTY),
	  m_accessSpecifier(EncodingT::EMPTY),
	  m_isStruct(0),
	  m_isInterface(0),
	  m_isAbstract(0),
	  m_isTemplate(0),
	  m_linesCount(0),
	  m_lineNumber(0),
	  m_startBlock(0),
	  m_lengthBlock(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppClass ";
	}

	/** Creates a new element CppClass.
	@param name 
	@param fullName 
	@param accessSpecifier 
	@param isStruct 
	@param isInterface 
	@param isAbstract 
	@param isTemplate 
	@param linesCount 
	@param lineNumber 
	@param startBlock 
	@param lengthBlock 
	*/
	_CppClass(const typename EncodingT::string_t& name,
				const typename EncodingT::string_t& fullName,
				const typename EncodingT::string_t& accessSpecifier,
				long long isStruct,
				long long isInterface,
				long long isAbstract,
				long long isTemplate,
				long long linesCount,
				long long lineNumber,
				long long startBlock,
				long long lengthBlock)
	: m_identifier(-1),
	  m_name(name),
	  m_fullName(fullName),
	  m_accessSpecifier(accessSpecifier),
	  m_isStruct(isStruct),
	  m_isInterface(isInterface),
	  m_isAbstract(isAbstract),
	  m_isTemplate(isTemplate),
	  m_linesCount(linesCount),
	  m_lineNumber(lineNumber),
	  m_startBlock(startBlock),
	  m_lengthBlock(lengthBlock)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppClass "
				<< m_identifier << ' '
				<< A(m_name) << ' '
				<< A(m_fullName) << ' '
				<< A(m_accessSpecifier) << ' '
				<< m_isStruct << ' '
				<< m_isInterface << ' '
				<< m_isAbstract << ' '
				<< m_isTemplate << ' '
				<< m_linesCount << ' '
				<< m_lineNumber << ' '
				<< m_startBlock << ' '
				<< m_lengthBlock << ' ';
	}

	/** Returns a const reference to the element <i>encapsulationClass</i> in CppClass.
	@return 
	*/
	boost::shared_ptr< _CppClass<EncodingT> > getEncapsulationClass() const 
	{
		return m_encapsulationClass;
	}

	/** Sets a value of the element <i>encapsulationClass</i> in CppClass.
	@param encapsulationClass 
	*/
	void setEncapsulationClass(boost::shared_ptr< _CppClass<EncodingT> > encapsulationClass)  
	{
		m_encapsulationClass = encapsulationClass;
	}

	/** Returns whether the element <i>encapsulationClass</i> in CppClass is NULL.
	@return True if the element <i>encapsulationClass</i> is NULL, false otherwise.
	*/
	bool isNullEncapsulationClass() const 
	{
		return !m_encapsulationClass;
	}

	/** Removes from CppClass an element <i>encapsulationClass</i>.
	*/
	void eraseEncapsulationClass()  
	{
		m_encapsulationClass.reset();
	}

	/** Returns a const reference to the element <i>identifier</i> in CppClass.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>name</i> in CppClass.
	@return 
	*/
	const typename EncodingT::string_t& getName() const 
	{
		return m_name;
	}

	/** Sets a value of the element <i>name</i> in CppClass.
	@param name 
	*/
	void setName(const typename EncodingT::string_t& name)  
	{
		m_name = name;
	}

	/** Returns a const reference to the element <i>fullName</i> in CppClass.
	@return 
	*/
	const typename EncodingT::string_t& getFullName() const 
	{
		return m_fullName;
	}

	/** Sets a value of the element <i>fullName</i> in CppClass.
	@param fullName 
	*/
	void setFullName(const typename EncodingT::string_t& fullName)  
	{
		m_fullName = fullName;
	}

	/** Returns a const reference to the element <i>accessSpecifier</i> in CppClass.
	@return 
	*/
	const typename EncodingT::string_t& getAccessSpecifier() const 
	{
		return m_accessSpecifier;
	}

	/** Sets a value of the element <i>accessSpecifier</i> in CppClass.
	@param accessSpecifier 
	*/
	void setAccessSpecifier(const typename EncodingT::string_t& accessSpecifier)  
	{
		m_accessSpecifier = accessSpecifier;
	}

	/** Returns a const reference to the element <i>isStruct</i> in CppClass.
	@return 
	*/
	long long getIsStruct() const 
	{
		return m_isStruct;
	}

	/** Sets a value of the element <i>isStruct</i> in CppClass.
	@param isStruct 
	*/
	void setIsStruct(long long isStruct)  
	{
		m_isStruct = isStruct;
	}

	/** Returns a const reference to the element <i>isInterface</i> in CppClass.
	@return 
	*/
	long long getIsInterface() const 
	{
		return m_isInterface;
	}

	/** Sets a value of the element <i>isInterface</i> in CppClass.
	@param isInterface 
	*/
	void setIsInterface(long long isInterface)  
	{
		m_isInterface = isInterface;
	}

	/** Returns a const reference to the element <i>isAbstract</i> in CppClass.
	@return 
	*/
	long long getIsAbstract() const 
	{
		return m_isAbstract;
	}

	/** Sets a value of the element <i>isAbstract</i> in CppClass.
	@param isAbstract 
	*/
	void setIsAbstract(long long isAbstract)  
	{
		m_isAbstract = isAbstract;
	}

	/** Returns a const reference to the element <i>isTemplate</i> in CppClass.
	@return 
	*/
	long long getIsTemplate() const 
	{
		return m_isTemplate;
	}

	/** Sets a value of the element <i>isTemplate</i> in CppClass.
	@param isTemplate 
	*/
	void setIsTemplate(long long isTemplate)  
	{
		m_isTemplate = isTemplate;
	}

	/** Returns a const reference to the element <i>linesCount</i> in CppClass.
	@return 
	*/
	long long getLinesCount() const 
	{
		return m_linesCount;
	}

	/** Sets a value of the element <i>linesCount</i> in CppClass.
	@param linesCount 
	*/
	void setLinesCount(long long linesCount)  
	{
		m_linesCount = linesCount;
	}

	/** Returns a const reference to the element <i>cppFile</i> in CppClass.
	@return 
	*/
	boost::shared_ptr< _CppFile<EncodingT> > getCppFile() const 
	{
		return m_cppFile;
	}

	/** Sets a value of the element <i>cppFile</i> in CppClass.
	@param cppFile 
	*/
	void setCppFile(boost::shared_ptr< _CppFile<EncodingT> > cppFile)  
	{
		m_cppFile = cppFile;
	}

	/** Returns whether the element <i>cppFile</i> in CppClass is NULL.
	@return True if the element <i>cppFile</i> is NULL, false otherwise.
	*/
	bool isNullCppFile() const 
	{
		return !m_cppFile;
	}

	/** Removes from CppClass an element <i>cppFile</i>.
	*/
	void eraseCppFile()  
	{
		m_cppFile.reset();
	}

	/** Returns a const reference to the element <i>lineNumber</i> in CppClass.
	@return 
	*/
	long long getLineNumber() const 
	{
		return m_lineNumber;
	}

	/** Sets a value of the element <i>lineNumber</i> in CppClass.
	@param lineNumber 
	*/
	void setLineNumber(long long lineNumber)  
	{
		m_lineNumber = lineNumber;
	}

	/** Returns a const reference to the element <i>startBlock</i> in CppClass.
	@return 
	*/
	long long getStartBlock() const 
	{
		return m_startBlock;
	}

	/** Sets a value of the element <i>startBlock</i> in CppClass.
	@param startBlock 
	*/
	void setStartBlock(long long startBlock)  
	{
		m_startBlock = startBlock;
	}

	/** Returns a const reference to the element <i>lengthBlock</i> in CppClass.
	@return 
	*/
	long long getLengthBlock() const 
	{
		return m_lengthBlock;
	}

	/** Sets a value of the element <i>lengthBlock</i> in CppClass.
	@param lengthBlock 
	*/
	void setLengthBlock(long long lengthBlock)  
	{
		m_lengthBlock = lengthBlock;
	}

	/// Random access iterator types for CppInheritance vector.
	typedef typename vector_cppInheritance::iterator	CppInheritanceIterator;
	typedef typename vector_cppInheritance::const_iterator	CppInheritanceConstIterator;

	/// Random access iterator types for CppFunction vector.
	typedef typename vector_cppFunction::iterator	CppFunctionIterator;
	typedef typename vector_cppFunction::const_iterator	CppFunctionConstIterator;

	/// Random access iterator types for InternClasse vector.
	typedef typename vector_internClasse::iterator	InternClasseIterator;
	typedef typename vector_internClasse::const_iterator	InternClasseConstIterator;

	/// Random access iterator types for CppAttribute vector.
	typedef typename vector_cppAttribute::iterator	CppAttributeIterator;
	typedef typename vector_cppAttribute::const_iterator	CppAttributeConstIterator;

	/// Random access iterator types for CppEnum vector.
	typedef typename vector_cppEnum::iterator	CppEnumIterator;
	typedef typename vector_cppEnum::const_iterator	CppEnumConstIterator;

	/** Returns an iterator referring to the first element in the vector container CppInheritance.
	@return An iterator to the beginning of the sequence.
	*/
	CppInheritanceIterator getCppInheritancesBeginning()  
	{
		return m_cppInheritances.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container CppInheritance.
	@return An iterator to the element past the end of the sequence.
	*/
	CppInheritanceIterator getCppInheritancesEnd()  
	{
		return m_cppInheritances.end();
	}

	/** Returns a const iterator referring to the first element in the vector container CppInheritance.
	@return A const iterator to the beginning of the sequence.
	*/
	CppInheritanceConstIterator getCppInheritancesBeginning() const 
	{
		return m_cppInheritances.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container CppInheritance.
	@return A const iterator to the element past the end of the sequence.
	*/
	CppInheritanceConstIterator getCppInheritancesEnd() const 
	{
		return m_cppInheritances.end();
	}

	/** Returns a reference to the element at position n in the vector CppInheritance.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppInheritance<EncodingT> >& getCppInheritanceAt(size_t n)  
	{
		return m_cppInheritances.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppInheritance.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppInheritance<EncodingT> > getCppInheritanceAt(size_t n) const 
	{
		return m_cppInheritances.at(n);
	}

	/** Returns the number of elements in the vector container CppInheritance.
	@return The number of elements that conform the vector's content.
	*/
	size_t getCppInheritancesSize() const 
	{
		return m_cppInheritances.size();
	}

	/** Returns whether the vector container CppInheritance is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isCppInheritancesEmpty() const 
	{
		return m_cppInheritances.empty();
	}

	/** Adds a new element at the end of the vector CppInheritance, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addCppInheritance(boost::shared_ptr< _CppInheritance<EncodingT> > o)  
	{
		m_cppInheritances.push_back(copy_ptr(o));
	}

	/** The vector CppInheritance is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppInheritanceIterator insertCppInheritance(CppInheritanceIterator pos, boost::shared_ptr< _CppInheritance<EncodingT> > o)  
	{
		return m_cppInheritances.insert(pos, copy_ptr(o));
	}

	/** The vector CppInheritance is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertCppInheritance(CppInheritanceIterator pos, CppInheritanceIterator first, CppInheritanceIterator last)  
	{
		std::transform(first, last, std::inserter(m_cppInheritances, pos), static_cast< boost::shared_ptr< _CppInheritance<EncodingT> >(*)(boost::shared_ptr< _CppInheritance<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container CppInheritance a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	CppInheritanceIterator eraseCppInheritance(CppInheritanceIterator pos)  
	{
		return m_cppInheritances.erase(pos);
	}

	/** Removes from the vector container CppInheritance a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	CppInheritanceIterator eraseCppInheritance(CppInheritanceIterator first, CppInheritanceIterator last)  
	{
		return m_cppInheritances.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container CppInheritance, leaving the container with a size of 0.
	*/
	void clearCppInheritances()  
	{
		m_cppInheritances.clear();
	}

	/** Returns an iterator referring to the first element in the vector container CppFunction.
	@return An iterator to the beginning of the sequence.
	*/
	CppFunctionIterator getCppFunctionsBeginning()  
	{
		return m_cppFunctions.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container CppFunction.
	@return An iterator to the element past the end of the sequence.
	*/
	CppFunctionIterator getCppFunctionsEnd()  
	{
		return m_cppFunctions.end();
	}

	/** Returns a const iterator referring to the first element in the vector container CppFunction.
	@return A const iterator to the beginning of the sequence.
	*/
	CppFunctionConstIterator getCppFunctionsBeginning() const 
	{
		return m_cppFunctions.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container CppFunction.
	@return A const iterator to the element past the end of the sequence.
	*/
	CppFunctionConstIterator getCppFunctionsEnd() const 
	{
		return m_cppFunctions.end();
	}

	/** Returns a reference to the element at position n in the vector CppFunction.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppFunction<EncodingT> >& getCppFunctionAt(size_t n)  
	{
		return m_cppFunctions.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppFunction.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppFunction<EncodingT> > getCppFunctionAt(size_t n) const 
	{
		return m_cppFunctions.at(n);
	}

	/** Returns the number of elements in the vector container CppFunction.
	@return The number of elements that conform the vector's content.
	*/
	size_t getCppFunctionsSize() const 
	{
		return m_cppFunctions.size();
	}

	/** Returns whether the vector container CppFunction is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isCppFunctionsEmpty() const 
	{
		return m_cppFunctions.empty();
	}

	/** Adds a new element at the end of the vector CppFunction, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addCppFunction(boost::shared_ptr< _CppFunction<EncodingT> > o)  
	{
		m_cppFunctions.push_back(copy_ptr(o));
	}

	/** The vector CppFunction is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppFunctionIterator insertCppFunction(CppFunctionIterator pos, boost::shared_ptr< _CppFunction<EncodingT> > o)  
	{
		return m_cppFunctions.insert(pos, copy_ptr(o));
	}

	/** The vector CppFunction is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertCppFunction(CppFunctionIterator pos, CppFunctionIterator first, CppFunctionIterator last)  
	{
		std::transform(first, last, std::inserter(m_cppFunctions, pos), static_cast< boost::shared_ptr< _CppFunction<EncodingT> >(*)(boost::shared_ptr< _CppFunction<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container CppFunction a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	CppFunctionIterator eraseCppFunction(CppFunctionIterator pos)  
	{
		return m_cppFunctions.erase(pos);
	}

	/** Removes from the vector container CppFunction a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	CppFunctionIterator eraseCppFunction(CppFunctionIterator first, CppFunctionIterator last)  
	{
		return m_cppFunctions.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container CppFunction, leaving the container with a size of 0.
	*/
	void clearCppFunctions()  
	{
		m_cppFunctions.clear();
	}

	/** Returns an iterator referring to the first element in the vector container InternClasse.
	@return An iterator to the beginning of the sequence.
	*/
	InternClasseIterator getInternClassesBeginning()  
	{
		return m_internClasses.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container InternClasse.
	@return An iterator to the element past the end of the sequence.
	*/
	InternClasseIterator getInternClassesEnd()  
	{
		return m_internClasses.end();
	}

	/** Returns a const iterator referring to the first element in the vector container InternClasse.
	@return A const iterator to the beginning of the sequence.
	*/
	InternClasseConstIterator getInternClassesBeginning() const 
	{
		return m_internClasses.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container InternClasse.
	@return A const iterator to the element past the end of the sequence.
	*/
	InternClasseConstIterator getInternClassesEnd() const 
	{
		return m_internClasses.end();
	}

	/** Returns a reference to the element at position n in the vector InternClasse.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppClass<EncodingT> >& getInternClasseAt(size_t n)  
	{
		return m_internClasses.at(n);
	}

	/** Returns a const reference to the element at position n in the vector InternClasse.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppClass<EncodingT> > getInternClasseAt(size_t n) const 
	{
		return m_internClasses.at(n);
	}

	/** Returns the number of elements in the vector container InternClasse.
	@return The number of elements that conform the vector's content.
	*/
	size_t getInternClassesSize() const 
	{
		return m_internClasses.size();
	}

	/** Returns whether the vector container InternClasse is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isInternClassesEmpty() const 
	{
		return m_internClasses.empty();
	}

	/** Adds a new element at the end of the vector InternClasse, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addInternClasse(boost::shared_ptr< _CppClass<EncodingT> > o)  
	{
		m_internClasses.push_back(copy_ptr(o));
	}

	/** The vector InternClasse is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	InternClasseIterator insertInternClasse(InternClasseIterator pos, boost::shared_ptr< _CppClass<EncodingT> > o)  
	{
		return m_internClasses.insert(pos, copy_ptr(o));
	}

	/** The vector InternClasse is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertInternClasse(InternClasseIterator pos, InternClasseIterator first, InternClasseIterator last)  
	{
		std::transform(first, last, std::inserter(m_internClasses, pos), static_cast< boost::shared_ptr< _CppClass<EncodingT> >(*)(boost::shared_ptr< _CppClass<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container InternClasse a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	InternClasseIterator eraseInternClasse(InternClasseIterator pos)  
	{
		return m_internClasses.erase(pos);
	}

	/** Removes from the vector container InternClasse a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	InternClasseIterator eraseInternClasse(InternClasseIterator first, InternClasseIterator last)  
	{
		return m_internClasses.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container InternClasse, leaving the container with a size of 0.
	*/
	void clearInternClasses()  
	{
		m_internClasses.clear();
	}

	/** Returns an iterator referring to the first element in the vector container CppAttribute.
	@return An iterator to the beginning of the sequence.
	*/
	CppAttributeIterator getCppAttributesBeginning()  
	{
		return m_cppAttributes.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container CppAttribute.
	@return An iterator to the element past the end of the sequence.
	*/
	CppAttributeIterator getCppAttributesEnd()  
	{
		return m_cppAttributes.end();
	}

	/** Returns a const iterator referring to the first element in the vector container CppAttribute.
	@return A const iterator to the beginning of the sequence.
	*/
	CppAttributeConstIterator getCppAttributesBeginning() const 
	{
		return m_cppAttributes.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container CppAttribute.
	@return A const iterator to the element past the end of the sequence.
	*/
	CppAttributeConstIterator getCppAttributesEnd() const 
	{
		return m_cppAttributes.end();
	}

	/** Returns a reference to the element at position n in the vector CppAttribute.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppAttribute<EncodingT> >& getCppAttributeAt(size_t n)  
	{
		return m_cppAttributes.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppAttribute.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppAttribute<EncodingT> > getCppAttributeAt(size_t n) const 
	{
		return m_cppAttributes.at(n);
	}

	/** Returns the number of elements in the vector container CppAttribute.
	@return The number of elements that conform the vector's content.
	*/
	size_t getCppAttributesSize() const 
	{
		return m_cppAttributes.size();
	}

	/** Returns whether the vector container CppAttribute is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isCppAttributesEmpty() const 
	{
		return m_cppAttributes.empty();
	}

	/** Adds a new element at the end of the vector CppAttribute, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addCppAttribute(boost::shared_ptr< _CppAttribute<EncodingT> > o)  
	{
		m_cppAttributes.push_back(copy_ptr(o));
	}

	/** The vector CppAttribute is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppAttributeIterator insertCppAttribute(CppAttributeIterator pos, boost::shared_ptr< _CppAttribute<EncodingT> > o)  
	{
		return m_cppAttributes.insert(pos, copy_ptr(o));
	}

	/** The vector CppAttribute is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertCppAttribute(CppAttributeIterator pos, CppAttributeIterator first, CppAttributeIterator last)  
	{
		std::transform(first, last, std::inserter(m_cppAttributes, pos), static_cast< boost::shared_ptr< _CppAttribute<EncodingT> >(*)(boost::shared_ptr< _CppAttribute<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container CppAttribute a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	CppAttributeIterator eraseCppAttribute(CppAttributeIterator pos)  
	{
		return m_cppAttributes.erase(pos);
	}

	/** Removes from the vector container CppAttribute a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	CppAttributeIterator eraseCppAttribute(CppAttributeIterator first, CppAttributeIterator last)  
	{
		return m_cppAttributes.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container CppAttribute, leaving the container with a size of 0.
	*/
	void clearCppAttributes()  
	{
		m_cppAttributes.clear();
	}

	/** Returns an iterator referring to the first element in the vector container CppEnum.
	@return An iterator to the beginning of the sequence.
	*/
	CppEnumIterator getCppEnumsBeginning()  
	{
		return m_cppEnums.begin();
	}

	/** Returns an iterator referring to the past-the-end element in the vector container CppEnum.
	@return An iterator to the element past the end of the sequence.
	*/
	CppEnumIterator getCppEnumsEnd()  
	{
		return m_cppEnums.end();
	}

	/** Returns a const iterator referring to the first element in the vector container CppEnum.
	@return A const iterator to the beginning of the sequence.
	*/
	CppEnumConstIterator getCppEnumsBeginning() const 
	{
		return m_cppEnums.begin();
	}

	/** Returns a const iterator referring to the past-the-end element in the vector container CppEnum.
	@return A const iterator to the element past the end of the sequence.
	*/
	CppEnumConstIterator getCppEnumsEnd() const 
	{
		return m_cppEnums.end();
	}

	/** Returns a reference to the element at position n in the vector CppEnum.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppEnum<EncodingT> >& getCppEnumAt(size_t n)  
	{
		return m_cppEnums.at(n);
	}

	/** Returns a const reference to the element at position n in the vector CppEnum.
	@param n Position of an element in the vector.
	@return The element at the specified position in the vector.
	*/
	boost::shared_ptr< _CppEnum<EncodingT> > getCppEnumAt(size_t n) const 
	{
		return m_cppEnums.at(n);
	}

	/** Returns the number of elements in the vector container CppEnum.
	@return The number of elements that conform the vector's content.
	*/
	size_t getCppEnumsSize() const 
	{
		return m_cppEnums.size();
	}

	/** Returns whether the vector container CppEnum is empty, i.e. whether its size is 0.
	@return True if the vector size is 0, false otherwise.
	*/
	bool isCppEnumsEmpty() const 
	{
		return m_cppEnums.empty();
	}

	/** Adds a new element at the end of the vector CppEnum, after its current last element. The content of this new element is initialized to a copy of x.
	@param o Value to be copied to the new element.
	*/
	void addCppEnum(boost::shared_ptr< _CppEnum<EncodingT> > o)  
	{
		m_cppEnums.push_back(copy_ptr(o));
	}

	/** The vector CppEnum is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param o Value to be used to initialize the inserted elements.
	@return An iterator that points to the newly inserted element.
	*/
	CppEnumIterator insertCppEnum(CppEnumIterator pos, boost::shared_ptr< _CppEnum<EncodingT> > o)  
	{
		return m_cppEnums.insert(pos, copy_ptr(o));
	}

	/** The vector CppEnum is extended by inserting new elements before the element at position pos.
	@param pos Position in the vector where the new elements are inserted.
	@param first First iterator specifying a range of elements.
	@param last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.
	*/
	void insertCppEnum(CppEnumIterator pos, CppEnumIterator first, CppEnumIterator last)  
	{
		std::transform(first, last, std::inserter(m_cppEnums, pos), static_cast< boost::shared_ptr< _CppEnum<EncodingT> >(*)(boost::shared_ptr< _CppEnum<EncodingT> >) >(copy_ptr));
	}

	/** Removes from the vector container CppEnum a single element.
	@param pos Iterator pointing to a single element to be removed from the vector.
	*/
	CppEnumIterator eraseCppEnum(CppEnumIterator pos)  
	{
		return m_cppEnums.erase(pos);
	}

	/** Removes from the vector container CppEnum a range of elements ([first,last)).
	@param first First iterator specifying a range within the vector to be removed: [first,last).
	@param last Last iterator specifying a range within the vector to be removed: [first,last).
	*/
	CppEnumIterator eraseCppEnum(CppEnumIterator first, CppEnumIterator last)  
	{
		return m_cppEnums.erase(first, last);
	}

	/** All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container CppEnum, leaving the container with a size of 0.
	*/
	void clearCppEnums()  
	{
		m_cppEnums.clear();
	}

	/** Prints CppClass object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "CppClass" << endl
		         << "identifier : " << m_identifier << endl
		         << "name : " << A(m_name) << endl
		         << "fullName : " << A(m_fullName) << endl
		         << "accessSpecifier : " << A(m_accessSpecifier) << endl
		         << "isStruct : " << m_isStruct << endl
		         << "isInterface : " << m_isInterface << endl
		         << "isAbstract : " << m_isAbstract << endl
		         << "isTemplate : " << m_isTemplate << endl
		         << "linesCount : " << m_linesCount << endl
		         << "lineNumber : " << m_lineNumber << endl
		         << "startBlock : " << m_startBlock << endl
		         << "lengthBlock : " << m_lengthBlock;
	}

	/** Defines <i> operator<< </i> for CppClass.
	@param o Reference of C++ stream object.
	@param elem Const reference of CppClass object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _CppClass<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class CppClassIDEquality;
	class NameEquality;
	class NameInferior;
	class NameSuperior;
	class FullNameEquality;
	class FullNameInferior;
	class FullNameSuperior;
	class AccessSpecifierEquality;
	class AccessSpecifierInferior;
	class AccessSpecifierSuperior;
	class IsStructEquality;
	class IsStructInferior;
	class IsStructSuperior;
	class IsInterfaceEquality;
	class IsInterfaceInferior;
	class IsInterfaceSuperior;
	class IsAbstractEquality;
	class IsAbstractInferior;
	class IsAbstractSuperior;
	class IsTemplateEquality;
	class IsTemplateInferior;
	class IsTemplateSuperior;
	class LinesCountEquality;
	class LinesCountInferior;
	class LinesCountSuperior;
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

typedef _CppClass<ucs> UniCppClass;
typedef _CppClass<ansi> CppClass;

NAMESPACE_END

#undef C
#undef A

#include "cppClassPredicate.hpp"

#endif
