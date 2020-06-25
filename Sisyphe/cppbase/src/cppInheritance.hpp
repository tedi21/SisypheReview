/* 
 * cppInheritance.hpp
 *
 *
 * @date 25-06-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPINHERITANCE_HPP_
#define _CPPINHERITANCE_HPP_

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
class _CppInheritanceAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

template <class EncodingT>
class _CppClass;

/// cppInheritance table represents an inheritance.
template <class EncodingT>
class  _CppInheritance {
private :
	boost::shared_ptr< _CppClass<EncodingT> >	m_derived;
	long long	m_identifier;
	typename EncodingT::string_t	m_baseClassName;
	typename EncodingT::string_t	m_baseAccess;
	Category*	m_logger;

protected :
	friend class data_access::_CppInheritanceAccess<EncodingT>;

	/** Creates a new element CppInheritance.
	@param identifier 
	@param baseClassName 
	@param baseAccess 
	*/
	_CppInheritance(long long identifier,
				const typename EncodingT::string_t& baseClassName,
				const typename EncodingT::string_t& baseAccess)
	: m_identifier(identifier),
	  m_baseClassName(baseClassName),
	  m_baseAccess(baseAccess)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppInheritance "
				<< m_identifier << ' '
				<< A(m_baseClassName) << ' '
				<< A(m_baseAccess) << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in CppInheritance.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element CppInheritance.
	*/
	_CppInheritance()
	: m_identifier(-1),
	  m_baseClassName(EncodingT::EMPTY),
	  m_baseAccess(EncodingT::EMPTY)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppInheritance ";
	}

	/** Creates a new element CppInheritance.
	@param baseClassName 
	@param baseAccess 
	*/
	_CppInheritance(const typename EncodingT::string_t& baseClassName,
				const typename EncodingT::string_t& baseAccess)
	: m_identifier(-1),
	  m_baseClassName(baseClassName),
	  m_baseAccess(baseAccess)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _CppInheritance "
				<< m_identifier << ' '
				<< A(m_baseClassName) << ' '
				<< A(m_baseAccess) << ' ';
	}

	/** Returns a const reference to the element <i>derived</i> in CppInheritance.
	@return 
	*/
	boost::shared_ptr< _CppClass<EncodingT> > getDerived() const 
	{
		return m_derived;
	}

	/** Sets a value of the element <i>derived</i> in CppInheritance.
	@param derived 
	*/
	void setDerived(boost::shared_ptr< _CppClass<EncodingT> > derived)  
	{
		m_derived = derived;
	}

	/** Returns whether the element <i>derived</i> in CppInheritance is NULL.
	@return True if the element <i>derived</i> is NULL, false otherwise.
	*/
	bool isNullDerived() const 
	{
		return !m_derived;
	}

	/** Removes from CppInheritance an element <i>derived</i>.
	*/
	void eraseDerived()  
	{
		m_derived.reset();
	}

	/** Returns a const reference to the element <i>identifier</i> in CppInheritance.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>baseClassName</i> in CppInheritance.
	@return 
	*/
	const typename EncodingT::string_t& getBaseClassName() const 
	{
		return m_baseClassName;
	}

	/** Sets a value of the element <i>baseClassName</i> in CppInheritance.
	@param baseClassName 
	*/
	void setBaseClassName(const typename EncodingT::string_t& baseClassName)  
	{
		m_baseClassName = baseClassName;
	}

	/** Returns a const reference to the element <i>baseAccess</i> in CppInheritance.
	@return 
	*/
	const typename EncodingT::string_t& getBaseAccess() const 
	{
		return m_baseAccess;
	}

	/** Sets a value of the element <i>baseAccess</i> in CppInheritance.
	@param baseAccess 
	*/
	void setBaseAccess(const typename EncodingT::string_t& baseAccess)  
	{
		m_baseAccess = baseAccess;
	}

	/** Prints CppInheritance object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "CppInheritance" << endl
		         << "identifier : " << m_identifier << endl
		         << "baseClassName : " << A(m_baseClassName) << endl
		         << "baseAccess : " << A(m_baseAccess);
	}

	/** Defines <i> operator<< </i> for CppInheritance.
	@param o Reference of C++ stream object.
	@param elem Const reference of CppInheritance object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _CppInheritance<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class CppInheritanceIDEquality;
	class BaseClassNameEquality;
	class BaseClassNameInferior;
	class BaseClassNameSuperior;
	class BaseAccessEquality;
	class BaseAccessInferior;
	class BaseAccessSuperior;
};

typedef _CppInheritance<ucs> UniCppInheritance;
typedef _CppInheritance<ansi> CppInheritance;

NAMESPACE_END

#undef C
#undef A

#include "cppInheritancePredicate.hpp"

#endif
