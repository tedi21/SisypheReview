/** 
 * SqliteDataInt64Parameter.hpp
 *
 *
 * @date: 19-07-2012
 * @author: Teddy DID�
 * @version: 2.00
 * @brief: Project generated by gensources
 */

#ifndef _SQLITE_DATA_INT64PARAMETER_HPP_
#define _SQLITE_DATA_INT64PARAMETER_HPP_

#include "databaseparameter.hpp"

NAMESPACE_BEGIN(data_access)

using namespace log4cpp;
using namespace enc;

template <class EncodingT>
class _DataInt64Parameter
: public _DataBaseParameter<EncodingT>
{ 
private:
	long long m_value;
	Category* m_logger;
	
public:
	_DataInt64Parameter(long long value);
	
	// Complete Statement
	virtual bool 
	complete(_DataStatement<EncodingT>& statement, int index) const;
};

typedef _DataInt64Parameter<ucs>        UniDataInt64Parameter;
typedef _DataInt64Parameter<ansi>       DataInt64Parameter;

NAMESPACE_END

#include "DataInt64Parameter_impl.hpp"
#endif
