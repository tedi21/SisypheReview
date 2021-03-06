/** 
 * SqliteDataBaseParameter.hpp
 *
 *
 * @date: 19-07-2012
 * @author: Teddy DID�
 * @version: 2.00
 * @brief: Project generated by gensources
 */

#ifndef _SQLITE_DATA_BASEPARAMETER_HPP_
#define _SQLITE_DATA_BASEPARAMETER_HPP_

NAMESPACE_BEGIN(data_access)

using namespace log4cpp;
using namespace enc;

template <class EncodingT>
class _DataBaseParameter
{ 
public:
    virtual ~_DataBaseParameter()
    {}
	// Complete Statement
	virtual bool 
	complete(_DataStatement<EncodingT>& statement, int index) const = 0;
};

typedef _DataBaseParameter<ucs>        UniDataBaseParameter;
typedef _DataBaseParameter<ansi>       DataBaseParameter;

NAMESPACE_END

#endif
