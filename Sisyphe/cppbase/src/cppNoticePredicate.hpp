/* 
 * cppNoticePredicate.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPNOTICE_PREDICATE_HPP_
#define _CPPNOTICE_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _CppNotice<EncodingT>::CppNoticeIDEquality {
private :
	long long	m_identifier;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param identifier 
	*/
	CppNoticeIDEquality(long long identifier)
	: m_identifier(identifier)
	{
	}

	CppNoticeIDEquality(const _CppNotice<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>description</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::DescriptionEquality {
private :
	typename EncodingT::string_t	m_description;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param description 
	*/
	DescriptionEquality(const typename EncodingT::string_t& description)
	: m_description(description)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_description==other->getDescription());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>description</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::DescriptionInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDescription() < elem2->getDescription());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>description</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::DescriptionSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getDescription() > elem2->getDescription());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>category</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CategoryEquality {
private :
	typename EncodingT::string_t	m_category;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param category 
	*/
	CategoryEquality(const typename EncodingT::string_t& category)
	: m_category(category)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_category==other->getCategory());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>category</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CategoryInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCategory() < elem2->getCategory());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>category</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CategorySuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCategory() > elem2->getCategory());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>ruleNumber</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::RuleNumberEquality {
private :
	long long	m_ruleNumber;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param ruleNumber 
	*/
	RuleNumberEquality(long long ruleNumber)
	: m_ruleNumber(ruleNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_ruleNumber==other->getRuleNumber());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>ruleNumber</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::RuleNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getRuleNumber() < elem2->getRuleNumber());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>ruleNumber</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::RuleNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getRuleNumber() > elem2->getRuleNumber());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>lineNumber</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::LineNumberEquality {
private :
	long long	m_lineNumber;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param lineNumber 
	*/
	LineNumberEquality(long long lineNumber)
	: m_lineNumber(lineNumber)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_lineNumber==other->getLineNumber());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::LineNumberInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() < elem2->getLineNumber());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>lineNumber</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::LineNumberSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLineNumber() > elem2->getLineNumber());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>startBlock</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::StartBlockEquality {
private :
	long long	m_startBlock;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param startBlock 
	*/
	StartBlockEquality(long long startBlock)
	: m_startBlock(startBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_startBlock==other->getStartBlock());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>startBlock</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::StartBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartBlock() < elem2->getStartBlock());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>startBlock</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::StartBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getStartBlock() > elem2->getStartBlock());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>lengthBlock</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::LengthBlockEquality {
private :
	long long	m_lengthBlock;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param lengthBlock 
	*/
	LengthBlockEquality(long long lengthBlock)
	: m_lengthBlock(lengthBlock)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_lengthBlock==other->getLengthBlock());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>lengthBlock</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::LengthBlockInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthBlock() < elem2->getLengthBlock());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>lengthBlock</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::LengthBlockSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getLengthBlock() > elem2->getLengthBlock());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>isNew</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::IsNewEquality {
private :
	long long	m_isNew;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param isNew 
	*/
	IsNewEquality(long long isNew)
	: m_isNew(isNew)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_isNew==other->getIsNew());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>isNew</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::IsNewInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsNew() < elem2->getIsNew());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>isNew</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::IsNewSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getIsNew() > elem2->getIsNew());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>commitHash</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitHashEquality {
private :
	typename EncodingT::string_t	m_commitHash;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param commitHash 
	*/
	CommitHashEquality(const typename EncodingT::string_t& commitHash)
	: m_commitHash(commitHash)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_commitHash==other->getCommitHash());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>commitHash</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitHashInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCommitHash() < elem2->getCommitHash());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>commitHash</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitHashSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCommitHash() > elem2->getCommitHash());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>commitDate</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitDateEquality {
private :
	typename EncodingT::string_t	m_commitDate;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param commitDate 
	*/
	CommitDateEquality(const typename EncodingT::string_t& commitDate)
	: m_commitDate(commitDate)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_commitDate==other->getCommitDate());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>commitDate</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitDateInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCommitDate() < elem2->getCommitDate());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>commitDate</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitDateSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCommitDate() > elem2->getCommitDate());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>commitAuthor</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitAuthorEquality {
private :
	typename EncodingT::string_t	m_commitAuthor;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param commitAuthor 
	*/
	CommitAuthorEquality(const typename EncodingT::string_t& commitAuthor)
	: m_commitAuthor(commitAuthor)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_commitAuthor==other->getCommitAuthor());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>commitAuthor</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitAuthorInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCommitAuthor() < elem2->getCommitAuthor());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>commitAuthor</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitAuthorSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCommitAuthor() > elem2->getCommitAuthor());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to find an object with the same element <i>commitLine</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitLineEquality {
private :
	long long	m_commitLine;
public :
	/** Creates a new functor allowing to find CppNotice object.
	@param commitLine 
	*/
	CommitLineEquality(long long commitLine)
	: m_commitLine(commitLine)
	{
	}

	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > other) const 
	{
		return (other != NULL && m_commitLine==other->getCommitLine());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>commitLine</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitLineInferior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCommitLine() < elem2->getCommitLine());
	}

};

/// Represents a comparaison class for CppNotice object.
/// This class is used to sort objects by <i>commitLine</i>.
template<class EncodingT>
class  _CppNotice<EncodingT>::CommitLineSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _CppNotice<EncodingT> > elem1, boost::shared_ptr< _CppNotice<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCommitLine() > elem2->getCommitLine());
	}

};

NAMESPACE_END

#endif
