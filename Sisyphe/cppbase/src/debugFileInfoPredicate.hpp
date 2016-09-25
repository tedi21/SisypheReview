/* 
 * debugFileInfoPredicate.hpp
 *
 *
 * @date 28-08-2016
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGFILEINFO_PREDICATE_HPP_
#define _DEBUGFILEINFO_PREDICATE_HPP_

NAMESPACE_BEGIN(entity)

/// Represents a comparaison class for DebugFileInfo object.
/// This class is used to find an object with the same ID.
template<class EncodingT>
class  _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality {
private :
	int	m_identifier;
public :
	/** Creates a new functor allowing to find DebugFileInfo object.
	@param identifier 
	*/
	DebugFileInfoIDEquality(int identifier)
	: m_identifier(identifier)
	{
	}

	DebugFileInfoIDEquality(const _DebugFileInfo<EncodingT>& elem)
	: m_identifier(elem.getIdentifier())
	{
	}

	bool operator()(boost::shared_ptr< _DebugFileInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_identifier==other->getIdentifier());
	}

};

/// Represents a comparaison class for DebugFileInfo object.
/// This class is used to find an object with the same element <i>compilandPath</i>.
template<class EncodingT>
class  _DebugFileInfo<EncodingT>::CompilandPathEquality {
private :
	typename EncodingT::string_t	m_compilandPath;
public :
	/** Creates a new functor allowing to find DebugFileInfo object.
	@param compilandPath 
	*/
	CompilandPathEquality(const typename EncodingT::string_t& compilandPath)
	: m_compilandPath(compilandPath)
	{
	}

	bool operator()(boost::shared_ptr< _DebugFileInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_compilandPath==other->getCompilandPath());
	}

};

/// Represents a comparaison class for DebugFileInfo object.
/// This class is used to sort objects by <i>compilandPath</i>.
template<class EncodingT>
class  _DebugFileInfo<EncodingT>::CompilandPathInferior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFileInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFileInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCompilandPath() < elem2->getCompilandPath());
	}

};

/// Represents a comparaison class for DebugFileInfo object.
/// This class is used to sort objects by <i>compilandPath</i>.
template<class EncodingT>
class  _DebugFileInfo<EncodingT>::CompilandPathSuperior {
private :
public :
	bool operator()(boost::shared_ptr< _DebugFileInfo<EncodingT> > elem1, boost::shared_ptr< _DebugFileInfo<EncodingT> > elem2) const 
	{
		return (elem1 != NULL && elem2 != NULL && elem1->getCompilandPath() > elem2->getCompilandPath());
	}

};

/// Represents a comparaison class for DebugFileInfo object.
/// This class is used to find an object with the same element <i>checksum</i>.
template<class EncodingT>
class  _DebugFileInfo<EncodingT>::ChecksumEquality {
private :
	boost::container::vector<unsigned char>	m_checksum;
public :
	/** Creates a new functor allowing to find DebugFileInfo object.
	@param checksum 
	*/
	ChecksumEquality(const boost::container::vector<unsigned char>& checksum)
	: m_checksum(checksum)
	{
	}

	bool operator()(boost::shared_ptr< _DebugFileInfo<EncodingT> > other) const 
	{
		return (other != NULL && m_checksum==other->getChecksum());
	}

};

NAMESPACE_END

#endif
