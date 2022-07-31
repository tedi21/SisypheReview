/* 
 * cppFileTypeInterpreterAccess.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPFILETYPE_INTERPRETER_ACCESS_HPP_
#define _CPPFILETYPE_INTERPRETER_ACCESS_HPP_

#include "config.hpp"
#include "Macros.hpp"
#include "String.hpp"

#include "cppBaseExport.hpp"
#include "cppBaseData.h"
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace data_access;
using namespace boost;

template <class EncodingT>
class CppFileTypeInterpreterAccess
: public Base<EncodingT>
{
private:
	_CppFileTypeAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	CppFileTypeInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllCppFileTypes();

	FACTORY_PROTOTYPE1(getManyCppFileTypes, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyCppFileTypes(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneCppFileType,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneCppFileType(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneCppFileType,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneCppFileType(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedCppFileType, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedCppFileType(const boost::shared_ptr< Base<EncodingT> >& cppFileType);

	FACTORY_PROTOTYPE2(fillAllCppFiles, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppFiles(boost::shared_ptr< Base<EncodingT> >& cppFileType, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppFile,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppFile(boost::shared_ptr< Base<EncodingT> >& refCppFileType,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppFiles, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppFiles(boost::shared_ptr< Base<EncodingT> >& cppFileType, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE1(isModifiedCppFileType, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedCppFileType(const boost::shared_ptr< Base<EncodingT> >& cppFileType);

	FACTORY_PROTOTYPE1(updateCppFileType, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateCppFileType(boost::shared_ptr< Base<EncodingT> >& cppFileType);

	FACTORY_PROTOTYPE1(insertCppFileType, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppFileType(boost::shared_ptr< Base<EncodingT> >& cppFileType);

	FACTORY_PROTOTYPE1(deleteCppFileType, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteCppFileType(boost::shared_ptr< Base<EncodingT> >& cppFileType);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppFileTypeInterpreterAccess, UCS("CppFileTypeAccess") );
		METHOD_KEY_REGISTER ( CppFileTypeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllCppFileTypes, no_const_t, UCS("CppFileTypeAccess::GetAllCppFileTypes") );
		METHOD_KEY_REGISTER1( CppFileTypeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyCppFileTypes, no_const_t, UCS("CppFileTypeAccess::GetManyCppFileTypes") );
		METHOD_KEY_REGISTER1( CppFileTypeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneCppFileType, no_const_t, UCS("CppFileTypeAccess::GetOneCppFileType") );
		METHOD_KEY_REGISTER2( CppFileTypeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneCppFileType, no_const_t, UCS("CppFileTypeAccess::SelectOneCppFileType") );
		METHOD_KEY_REGISTER ( CppFileTypeInterpreterAccess, void, cancelSelection, no_const_t, UCS("CppFileTypeAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( CppFileTypeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedCppFileType, no_const_t, UCS("CppFileTypeAccess::IsSelectedCppFileType") );
		METHOD_KEY_REGISTER2( CppFileTypeInterpreterAccess, void, fillAllCppFiles, no_const_t, UCS("CppFileTypeAccess::FillAllCppFiles") );
		METHOD_KEY_REGISTER3( CppFileTypeInterpreterAccess, void, fillOneCppFile, no_const_t, UCS("CppFileTypeAccess::FillOneCppFile") );
		METHOD_KEY_REGISTER3( CppFileTypeInterpreterAccess, void, fillManyCppFiles, no_const_t, UCS("CppFileTypeAccess::FillManyCppFiles") );
		METHOD_KEY_REGISTER1( CppFileTypeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedCppFileType, no_const_t, UCS("CppFileTypeAccess::IsModifiedCppFileType") );
		METHOD_KEY_REGISTER1( CppFileTypeInterpreterAccess, void, updateCppFileType, no_const_t, UCS("CppFileTypeAccess::UpdateCppFileType") );
		METHOD_KEY_REGISTER1( CppFileTypeInterpreterAccess, void, insertCppFileType, no_const_t, UCS("CppFileTypeAccess::InsertCppFileType") );
		METHOD_KEY_REGISTER1( CppFileTypeInterpreterAccess, void, deleteCppFileType, no_const_t, UCS("CppFileTypeAccess::DeleteCppFileType") );
		METHOD_KEY_REGISTER1( CppFileTypeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("CppFileTypeAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppFileTypeAccess") );
		METHOD_KEY_UNREGISTER ( UCS("CppFileTypeAccess::GetAllCppFileTypes") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileTypeAccess::GetManyCppFileTypes") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileTypeAccess::GetOneCppFileType") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileTypeAccess::SelectOneCppFileType") );
		METHOD_KEY_UNREGISTER ( UCS("CppFileTypeAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileTypeAccess::IsSelectedCppFileType") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileTypeAccess::FillAllCppFiles") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileTypeAccess::FillOneCppFile") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileTypeAccess::FillManyCppFiles") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileTypeAccess::IsModifiedCppFileType") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileTypeAccess::UpdateCppFileType") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileTypeAccess::InsertCppFileType") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileTypeAccess::DeleteCppFileType") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileTypeAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _CppFileType<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "cppFileTypeInterpreterAccess_impl.hpp"

#endif
