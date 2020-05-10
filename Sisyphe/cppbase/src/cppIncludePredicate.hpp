/* 
 * cppIncludePredicate.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPINCLUDE_PREDICATE_HPP_
#define _CPPINCLUDE_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for CppInclude object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _CppInclude<EncodingT>::CppIncludeIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find CppInclude object.
	@param identifier 
	*/
	CppIncludeIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	CppIncludeIDEquality(const _CppInclude<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _CppInclude<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for CppInclude object.
/// This class is used to find an object with the same element <i>fileName</i>.
template<class EncodingT>
class  _CppInclude<EncodingT>::FileNameEquality {
private :
	typename EncodingT::string_t	m_fileName;
public :
	/** Creates a new functor allowing to find CppInclude object.
	@param fileName 
	*/
	FileNameEquality(const typename EncodingT::string_t& fileName)
	: m_fileName(fileName)
	{
	}

	bool operator()(boost::shared_ptr< _CppInclude<EncodingT> > other) const 
	{
		return (other != NULL && m_fileName==other->getFileName());
	}

};

/// Represents a comparaison class for CppInclude object.
/// This class is used to sort objects by <i>fileName</i>.
template<class EncodingT>
class  _CppInclude<EncodingT>::FileNameInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppInclude<EncodingT> > elem1, boost::shared_ptr< _CppInclude<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getFileName() < elem2->getFileName());
	}

};

/// Represents a comparaison class for CppInclude object.
/// This class is used to sort objects by <i>fileName</i>.
template<class EncodingT>
class  _CppInclude<EncodingT>::FileNameSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppInclude<EncodingT> > elem1, boost::shared_ptr< _CppInclude<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getFileName() > elem2->getFileName());
	}

};

/// Represents a comparaison class for CppInclude object.
/// This class is used to find an object with the same element <i>lineNumber</i>.
template<class EncodingT>
class  _CppInclude<EncodingT>::LineNumberEquality {
private :
	long long	m_lineNumber;
public :
	/** Creates a new functor allowing to find CppInclude object.
	@param lineNumber 
	*/
	LineNumberEquality(long long lineNumber)
	: m_lineNumber(lineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CppInclude<EncodingT> > other) const 
	{
		return (other != NULL && m_lineNumber==other->getLineNumber());
	}

};

/// Represents a comparaison class for CppInclude object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CppInclude<EncodingT>::LineNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppInclude<EncodingT> > elem1, boost::shared_ptr< _CppInclude<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() < elem2->getLineNumber());
	}

};

/// Represents a comparaison class for CppInclude object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CppInclude<EncodingT>::LineNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppInclude<EncodingT> > elem1, boost::shared_ptr< _CppInclude<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() > elem2->getLineNumber());
	}

};

NAMESPACE_END

#endif
