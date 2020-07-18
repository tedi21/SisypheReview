/* 
 * textFilePredicate.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _TEXTFILE_PREDICATE_HPP_
#define _TEXTFILE_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for TextFile object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _TextFile<EncodingT>::TextFileIDEquality {
private :
	long long	m_rowid;
public :
	/** Creates a new functor allowing to find TextFile object.
	@param rowid 
	*/
	TextFileIDEquality(long long rowid)
	: m_rowid(rowid)
	{
	}

	TextFileIDEquality(const _TextFile<EncodingT>& elem)
	: m_rowid(elem.getRowid())
	{
	}

	bool operator()(boost::shared_ptr< _TextFile<EncodingT> > other) const 
	{
		return (other != NULL && m_rowid==other->getRowid());
	}

};

/// Represents a comparaison class for TextFile object.
/// This class is used to find an object with the same element <i>content</i>.
template<class EncodingT>
class  _TextFile<EncodingT>::ContentEquality {
private :
	typename EncodingT::string_t	m_content;
public :
	/** Creates a new functor allowing to find TextFile object.
	@param content 
	*/
	ContentEquality(const typename EncodingT::string_t& content)
	: m_content(content)
	{
	}

	bool operator()(boost::shared_ptr< _TextFile<EncodingT> > other) const 
	{
		return (other != NULL && m_content==other->getContent());
	}

};

/// Represents a comparaison class for TextFile object.
/// This class is used to sort objects by <i>content</i>.
template<class EncodingT>
class  _TextFile<EncodingT>::ContentInferior {
private :
public :
	bool operator()(boost::shared_ptr< _TextFile<EncodingT> > elem1, boost::shared_ptr< _TextFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getContent() < elem2->getContent());
	}

};

/// Represents a comparaison class for TextFile object.
/// This class is used to sort objects by <i>content</i>.
template<class EncodingT>
class  _TextFile<EncodingT>::ContentSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _TextFile<EncodingT> > elem1, boost::shared_ptr< _TextFile<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getContent() > elem2->getContent());
	}

};

NAMESPACE_END

#endif
