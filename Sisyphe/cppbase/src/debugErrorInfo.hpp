/* 
 * debugErrorInfo.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGERRORINFO_HPP_
#define _DEBUGERRORINFO_HPP_

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
class _DebugErrorInfoAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

/// debugErrorInfo table represents error information for debug.
template <class EncodingT>
class  _DebugErrorInfo {
private :
	long long	m_identifier;
	typename EncodingT::string_t	m_callStack;
	Category*	m_logger;

protected :
	friend class data_access::_DebugErrorInfoAccess<EncodingT>;

	/** Creates a new element DebugErrorInfo.
	@param identifier 
	@param callStack 
	*/
	_DebugErrorInfo(long long identifier,
				const typename EncodingT::string_t& callStack)
	: m_identifier(identifier),
	  m_callStack(callStack)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugErrorInfo "
				<< m_identifier << ' '
				<< A(m_callStack) << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in DebugErrorInfo.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element DebugErrorInfo.
	*/
	_DebugErrorInfo()
	: m_identifier(-1),
	  m_callStack(EncodingT::EMPTY)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugErrorInfo ";
	}

	/** Creates a new element DebugErrorInfo.
	@param callStack 
	*/
	_DebugErrorInfo(const typename EncodingT::string_t& callStack)
	: m_identifier(-1),
	  m_callStack(callStack)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _DebugErrorInfo "
				<< m_identifier << ' '
				<< A(m_callStack) << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in DebugErrorInfo.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>callStack</i> in DebugErrorInfo.
	@return 
	*/
	const typename EncodingT::string_t& getCallStack() const 
	{
		return m_callStack;
	}

	/** Sets a value of the element <i>callStack</i> in DebugErrorInfo.
	@param callStack 
	*/
	void setCallStack(const typename EncodingT::string_t& callStack)  
	{
		m_callStack = callStack;
	}

	/** Prints DebugErrorInfo object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "DebugErrorInfo" << endl
		         << "identifier : " << m_identifier << endl
		         << "callStack : " << A(m_callStack);
	}

	/** Defines <i> operator<< </i> for DebugErrorInfo.
	@param o Reference of C++ stream object.
	@param elem Const reference of DebugErrorInfo object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _DebugErrorInfo<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class DebugErrorInfoIDEquality;
	class CallStackEquality;
	class CallStackInferior;
	class CallStackSuperior;
};

typedef _DebugErrorInfo<ucs> UniDebugErrorInfo;
typedef _DebugErrorInfo<ansi> DebugErrorInfo;

NAMESPACE_END

#undef C
#undef A

#include "debugErrorInfoPredicate.hpp"

#endif
