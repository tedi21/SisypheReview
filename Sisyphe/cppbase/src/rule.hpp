/* 
 * rule.hpp
 *
 *
 * @date 25-06-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _RULE_HPP_
#define _RULE_HPP_

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
class _RuleAccess;

NAMESPACE_END

NAMESPACE_BEGIN(entity)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace boost;

/// Creation Table________________rule table represents a static analysis rule.
template <class EncodingT>
class  _Rule {
private :
	long long	m_identifier;
	long long	m_number;
	typename EncodingT::string_t	m_description;
	long long	m_enabled;
	Category*	m_logger;

protected :
	friend class data_access::_RuleAccess<EncodingT>;

	/** Creates a new element Rule.
	@param identifier 
	@param number 
	@param description 
	@param enabled 
	*/
	_Rule(long long identifier,
				long long number,
				const typename EncodingT::string_t& description,
				long long enabled)
	: m_identifier(identifier),
	  m_number(number),
	  m_description(description),
	  m_enabled(enabled)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _Rule "
				<< m_identifier << ' '
				<< m_number << ' '
				<< A(m_description) << ' '
				<< m_enabled << ' ';
	}

	/** Sets a value of the element <i>identifier</i> in Rule.
	@param identifier 
	*/
	void setIdentifier(long long identifier)  
	{
		m_identifier = identifier;
	}

public :
	/** Creates a new element Rule.
	*/
	_Rule()
	: m_identifier(-1),
	  m_number(0),
	  m_description(EncodingT::EMPTY),
	  m_enabled(0)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _Rule ";
	}

	/** Creates a new element Rule.
	@param number 
	@param description 
	@param enabled 
	*/
	_Rule(long long number,
				const typename EncodingT::string_t& description,
				long long enabled)
	: m_identifier(-1),
	  m_number(number),
	  m_description(description),
	  m_enabled(enabled)
	{
		m_logger = &Category::getInstance(LOGNAME);
		m_logger->debugStream() << "constructor _Rule "
				<< m_identifier << ' '
				<< m_number << ' '
				<< A(m_description) << ' '
				<< m_enabled << ' ';
	}

	/** Returns a const reference to the element <i>identifier</i> in Rule.
	@return 
	*/
	long long getIdentifier() const 
	{
		return m_identifier;
	}

	/** Returns a const reference to the element <i>number</i> in Rule.
	@return 
	*/
	long long getNumber() const 
	{
		return m_number;
	}

	/** Sets a value of the element <i>number</i> in Rule.
	@param number 
	*/
	void setNumber(long long number)  
	{
		m_number = number;
	}

	/** Returns a const reference to the element <i>description</i> in Rule.
	@return 
	*/
	const typename EncodingT::string_t& getDescription() const 
	{
		return m_description;
	}

	/** Sets a value of the element <i>description</i> in Rule.
	@param description 
	*/
	void setDescription(const typename EncodingT::string_t& description)  
	{
		m_description = description;
	}

	/** Returns a const reference to the element <i>enabled</i> in Rule.
	@return 
	*/
	long long getEnabled() const 
	{
		return m_enabled;
	}

	/** Sets a value of the element <i>enabled</i> in Rule.
	@param enabled 
	*/
	void setEnabled(long long enabled)  
	{
		m_enabled = enabled;
	}

	/** Prints Rule object on a C++ stream.
	@param o Reference of C++ stream object.
	@return The reference of C++ stream object.
	*/
	ostream& printConsole(ostream& o) const 
	{
		return o << "Rule" << endl
		         << "identifier : " << m_identifier << endl
		         << "number : " << m_number << endl
		         << "description : " << A(m_description) << endl
		         << "enabled : " << m_enabled;
	}

	/** Defines <i> operator<< </i> for Rule.
	@param o Reference of C++ stream object.
	@param elem Const reference of Rule object.
	@return The reference of C++ stream object.
	*/
	friend ostream& operator<<(ostream& o, const _Rule<EncodingT>& elem)  
	{
		return elem.printConsole(o<<"[ ")<<" ]";
	}

	class RuleIDEquality;
	class NumberEquality;
	class NumberInferior;
	class NumberSuperior;
	class DescriptionEquality;
	class DescriptionInferior;
	class DescriptionSuperior;
	class EnabledEquality;
	class EnabledInferior;
	class EnabledSuperior;
};

typedef _Rule<ucs> UniRule;
typedef _Rule<ansi> Rule;

NAMESPACE_END

#undef C
#undef A

#include "rulePredicate.hpp"

#endif
