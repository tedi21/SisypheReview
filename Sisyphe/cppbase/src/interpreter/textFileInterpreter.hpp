/* 
 * textFileInterpreter.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _TEXTFILE_INTERPRETER_HPP_
#define _TEXTFILE_INTERPRETER_HPP_

#include "config.hpp"
#include "macros.hpp"
#include "Base.hpp"
#include "Array.hpp"

#include "cppBaseExport.hpp"
#include "cppBaseData.h"
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace entity;
using namespace boost;

template <class EncodingT>
class CppFileInterpreter;

template <class EncodingT>
class DebugFileInfoInterpreter;

template <class EncodingT>
class TextFileInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _TextFile<EncodingT> > m_value;

public:
	TextFileInterpreter();

	TextFileInterpreter(boost::shared_ptr< _TextFile<EncodingT> > const& value);

	FACTORY_PROTOTYPE1(TextFileInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >)
	TextFileInterpreter(boost::shared_ptr< Base<EncodingT> > const& content);

	boost::shared_ptr< _TextFile<EncodingT> > value() const;

	void value(boost::shared_ptr< _TextFile<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getRowid() const;

	boost::shared_ptr< Base<EncodingT> > getContent() const;

	FACTORY_PROTOTYPE1(setContent, In< boost::shared_ptr< Base<EncodingT> > >)
	void setContent(boost::shared_ptr< Base<EncodingT> > const& content);

	FACTORY_PROTOTYPE1(removeCppFile, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppFile(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeDebugFileInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE2(insertCppFile, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppFile(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppFile);

	FACTORY_PROTOTYPE2(insertDebugFileInfo, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugFileInfo);

	FACTORY_PROTOTYPE1(getCppFile, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppFile(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getDebugFileInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	void clearCppFiles();

	void clearDebugFileInfos();

	boost::shared_ptr< Base<EncodingT> > hasCppFiles() const;

	boost::shared_ptr< Base<EncodingT> > hasDebugFileInfos() const;

	boost::shared_ptr< Base<EncodingT> > cppFilesCount() const;

	boost::shared_ptr< Base<EncodingT> > debugFileInfosCount() const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( TextFileInterpreter, C("TextFile") );
		CLASS_KEY_REGISTER1( TextFileInterpreter, C("TextFile") );
		METHOD_KEY_REGISTER ( TextFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getRowid, const_t, C("TextFile::Rowid") );
		METHOD_KEY_REGISTER ( TextFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getContent, const_t, C("TextFile::Content") );
		METHOD_KEY_REGISTER1( TextFileInterpreter, void, setContent, no_const_t, C("TextFile::Content") );
		METHOD_KEY_REGISTER1( TextFileInterpreter, void, removeCppFile, no_const_t, C("TextFile::removeCppFiles") );
		METHOD_KEY_REGISTER2( TextFileInterpreter, void, insertCppFile, no_const_t, C("TextFile::CppFiles") );
		METHOD_KEY_REGISTER1( TextFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFile, no_const_t, C("TextFile::CppFiles") );
		METHOD_KEY_REGISTER ( TextFileInterpreter, void, clearCppFiles, no_const_t, C("TextFile::ClearCppFiles") );
		METHOD_KEY_REGISTER ( TextFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFiles, const_t, C("TextFile::HasCppFiles") );
		METHOD_KEY_REGISTER ( TextFileInterpreter, boost::shared_ptr< Base<EncodingT> >, cppFilesCount, const_t, C("TextFile::CppFilesCount") );
		METHOD_KEY_REGISTER1( TextFileInterpreter, void, removeDebugFileInfo, no_const_t, C("TextFile::removeDebugFileInfos") );
		METHOD_KEY_REGISTER2( TextFileInterpreter, void, insertDebugFileInfo, no_const_t, C("TextFile::DebugFileInfos") );
		METHOD_KEY_REGISTER1( TextFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugFileInfo, no_const_t, C("TextFile::DebugFileInfos") );
		METHOD_KEY_REGISTER ( TextFileInterpreter, void, clearDebugFileInfos, no_const_t, C("TextFile::ClearDebugFileInfos") );
		METHOD_KEY_REGISTER ( TextFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugFileInfos, const_t, C("TextFile::HasDebugFileInfos") );
		METHOD_KEY_REGISTER ( TextFileInterpreter, boost::shared_ptr< Base<EncodingT> >, debugFileInfosCount, const_t, C("TextFile::DebugFileInfosCount") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("TextFile") );
		CLASS_KEY_UNREGISTER1( C("TextFile") );
		METHOD_KEY_UNREGISTER ( C("TextFile::Rowid") );
		METHOD_KEY_UNREGISTER ( C("TextFile::Content") );
		METHOD_KEY_UNREGISTER1( C("TextFile::Content") );
		METHOD_KEY_UNREGISTER1( C("TextFile::removeCppFiles") );
		METHOD_KEY_UNREGISTER2( C("TextFile::CppFiles") );
		METHOD_KEY_UNREGISTER1( C("TextFile::CppFiles") );
		METHOD_KEY_UNREGISTER ( C("TextFile::ClearCppFiles") );
		METHOD_KEY_UNREGISTER ( C("TextFile::HasCppFiles") );
		METHOD_KEY_UNREGISTER ( C("TextFile::CppFilesCount") );
		METHOD_KEY_UNREGISTER1( C("TextFile::removeDebugFileInfos") );
		METHOD_KEY_UNREGISTER2( C("TextFile::DebugFileInfos") );
		METHOD_KEY_UNREGISTER1( C("TextFile::DebugFileInfos") );
		METHOD_KEY_UNREGISTER ( C("TextFile::ClearDebugFileInfos") );
		METHOD_KEY_UNREGISTER ( C("TextFile::HasDebugFileInfos") );
		METHOD_KEY_UNREGISTER ( C("TextFile::DebugFileInfosCount") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_textFile(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _TextFile<EncodingT> >& o);

template <class EncodingT>
bool reset_textFile(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _TextFile<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "textFileInterpreter_impl.hpp"

#endif
