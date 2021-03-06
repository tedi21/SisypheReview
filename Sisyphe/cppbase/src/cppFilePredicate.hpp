/* 
 * cppFilePredicate.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPFILE_PREDICATE_HPP_
#define _CPPFILE_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for CppFile object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _CppFile<EncodingT>::CppFileIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find CppFile object.
	@param identifier 
	*/
	CppFileIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	CppFileIDEquality(const _CppFile<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to find an object with the same element <i>path</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::PathEquality {
private :
	typename EncodingT::string_t	m_path;
public :
	/** Creates a new functor allowing to find CppFile object.
	@param path 
	*/
	PathEquality(const typename EncodingT::string_t& path)
	: m_path(path)
	{
	}

	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > other) const 
	{
		return (other != NULL && m_path==other->getPath());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>path</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::PathInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getPath() < elem2->getPath());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>path</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::PathSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getPath() > elem2->getPath());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to find an object with the same element <i>name</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::NameEquality {
private :
	typename EncodingT::string_t	m_name;
public :
	/** Creates a new functor allowing to find CppFile object.
	@param name 
	*/
	NameEquality(const typename EncodingT::string_t& name)
	: m_name(name)
	{
	}

	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > other) const 
	{
		return (other != NULL && m_name==other->getName());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::NameInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() < elem2->getName());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>name</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::NameSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getName() > elem2->getName());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to find an object with the same element <i>linesCount</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::LinesCountEquality {
private :
	long long	m_linesCount;
public :
	/** Creates a new functor allowing to find CppFile object.
	@param linesCount 
	*/
	LinesCountEquality(long long linesCount)
	: m_linesCount(linesCount)
	{
	}

	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > other) const 
	{
		return (other != NULL && m_linesCount==other->getLinesCount());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>linesCount</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::LinesCountInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLinesCount() < elem2->getLinesCount());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>linesCount</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::LinesCountSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLinesCount() > elem2->getLinesCount());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to find an object with the same element <i>hash</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::HashEquality {
private :
	long long	m_hash;
public :
	/** Creates a new functor allowing to find CppFile object.
	@param hash 
	*/
	HashEquality(long long hash)
	: m_hash(hash)
	{
	}

	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > other) const 
	{
		return (other != NULL && m_hash==other->getHash());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>hash</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::HashInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getHash() < elem2->getHash());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>hash</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::HashSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getHash() > elem2->getHash());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to find an object with the same element <i>analyzed</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::AnalyzedEquality {
private :
	long long	m_analyzed;
public :
	/** Creates a new functor allowing to find CppFile object.
	@param analyzed 
	*/
	AnalyzedEquality(long long analyzed)
	: m_analyzed(analyzed)
	{
	}

	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > other) const 
	{
		return (other != NULL && m_analyzed==other->getAnalyzed());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>analyzed</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::AnalyzedInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getAnalyzed() < elem2->getAnalyzed());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>analyzed</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::AnalyzedSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getAnalyzed() > elem2->getAnalyzed());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to find an object with the same element <i>isTracked</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::IsTrackedEquality {
private :
	long long	m_isTracked;
public :
	/** Creates a new functor allowing to find CppFile object.
	@param isTracked 
	*/
	IsTrackedEquality(long long isTracked)
	: m_isTracked(isTracked)
	{
	}

	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > other) const 
	{
		return (other != NULL && m_isTracked==other->getIsTracked());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>isTracked</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::IsTrackedInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsTracked() < elem2->getIsTracked());
	}

};

/// Represents a comparaison class for CppFile object.
/// This class is used to sort objects by <i>isTracked</i>.
template<class EncodingT>
class  _CppFile<EncodingT>::IsTrackedSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppFile<EncodingT> > elem1, boost::shared_ptr< _CppFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsTracked() > elem2->getIsTracked());
	}

};

NAMESPACE_END

#endif
