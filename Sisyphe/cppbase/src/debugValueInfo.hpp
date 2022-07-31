/* 
 * debugValueInfo.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGVALUEINFO_HPP_
#define _DEBUGVALUEINFO_HPP_

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
class _DebugValueInfoAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _DebugVariableInfo;

template <class EncodingT>
class _DebugStubInfo;

/// debugValueInfo table represents value information for debug.
template <class EncodingT>
class  _DebugValueInfo {
private :
	long long	m_identifier;
	typename EncodingT::string_t	m_textValue;
	boost::shared_ptr< _DebugVariableInfo<EncodingT> >	m_debugVariableInfo;
	boost::shared_ptr< _DebugStubInfo<EncodingT> >	m_debugStubInfo;
	Category*	m_logger;

protected :
	friend class data_access::_DebugValueInfoAccess<EncodingT>;

	/** Creates a new element DebugValueInfo.
	@param identifier 
	@param textValue 
	*/
	_DebugValueInfo(long long identifier,
				const typename EncodingT::string_t& textValue)
	: m_identifier(identifier),
	  m_textValue(textValue)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugValueInfo "
				<< m_identifier << ' '
				<< A(m_textValue) << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in DebugValueInfo.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element DebugValueInfo.
	*/
	_DebugValueInfo()
	: m_identifier(-1),
	  m_textValue(EncodingT::EMPTY)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugValueInfo ";
	}

	/** Creates a new element DebugValueInfo.
	@param textValue 
	*/
	_DebugValueInfo(const typename EncodingT::string_t& textValue)
	: m_identifier(-1),
	  m_textValue(textValue)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugValueInfo "
				<< m_identifier << ' '
				<< A(m_textValue) << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in DebugValueInfo.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>textValue</i> in DebugValueInfo.
	@return 
	*/
	const typename EncodingT::string_t& getTextValue() const 
	{
		return m_textValue;
	}

	/** Sets a value of the element <i>textValue</i> in DebugValueInfo.
	@param textValue 
	*/
	void setTextValue(const typename EncodingT::string_t& textValue)  
	{
		m_textValue = textValue;
	}

	/** Returns a const reference to the element <i>debugVariableInfo</i> in DebugValueInfo.
	@return 
	*/
	boost::shared_ptr< _DebugVariableInfo<EncodingT> > getDebugVariableInfo() const 
	{
		return m_debugVariableInfo;
	}

	/** Sets a value of the element <i>debugVariableInfo</i> in DebugValueInfo.
	@param debugVariableInfo 
	*/
	void setDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > debugVariableInfo)  
	{
		m_debugVariableInfo = debugVariableInfo;
	}

	/** Returns whether the element <i>debugVariableInfo</i> in DebugValueInfo is NULL.
	@return True if the element <i>debugVariableInfo</i> is NULL, false otherwise.
	*/
	bool isNullDebugVariableInfo() const 
	{
		return !m_debugVariableInfo;
	}

	/** Removes from DebugValueInfo an element <i>debugVariableInfo</i>.
	*/
	void eraseDebugVariableInfo()  
	{
		m_debugVariableInfo.reset();
	}

	/** Returns a const reference to the element <i>debugStubInfo</i> in DebugValueInfo.
	@return 
	*/
	boost::shared_ptr< _DebugStubInfo<EncodingT> > getDebugStubInfo() const 
	{
		return m_debugStubInfo;
	}

	/** Sets a value of the element <i>debugStubInfo</i> in DebugValueInfo.
	@param debugStubInfo 
	*/
	void setDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > debugStubInfo)  
	{
		m_debugStubInfo = debugStubInfo;
	}

	/** Returns whether the element <i>debugStubInfo</i> in DebugValueInfo is NULL.
	@return True if the element <i>debugStubInfo</i> is NULL, false otherwise.
	*/
	bool isNullDebugStubInfo() const 
	{
		return !m_debugStubInfo;
	}

	/** Removes from DebugValueInfo an element <i>debugStubInfo</i>.
	*/
	void eraseDebugStubInfo()  
	{
		m_debugStubInfo.reset();
	}

	/** Prints DebugValueInfo object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "DebugValueInfo" << endl
		         << "identifier : " << m_identifier << endl
		         << "textValue : " << A(m_textValue);
	}

	/** Defines <i> operator<< </i> for DebugValueInfo.
	@param o Reference of C++ stream object.
	@param elem Const reference of DebugValueInfo object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _DebugValueInfo<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class DebugValueInfoIDEquality;
	class DebugValueInfoIDInferior;
	class TextValueEquality;
	class TextValueInferior;
	class TextValueSuperior;
};

typedef _DebugValueInfo<ucs> UniDebugValueInfo;
typedef _DebugValueInfo<ansi> DebugValueInfo;

NAMESPACE_END

#undef C
#undef A

#include "debugValueInfoPredicate.hpp"

#endif
