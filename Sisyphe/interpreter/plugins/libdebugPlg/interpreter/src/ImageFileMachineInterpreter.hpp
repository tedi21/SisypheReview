/*
 * ImageFileMachineInterpreter.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _IMAGEFILEMACHINE_INTERPRETER_H_
#define _IMAGEFILEMACHINE_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"


#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	template <class EncodingT>
	class ImageFileMachineInterpreter
	: public Base<EncodingT>
	{
	private:

	public:
		ImageFileMachineInterpreter();

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_AM33() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_AMD64() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_ARM() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_ARMV7() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_EBC() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_I386() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_IA64() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_M32R() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_MIPS16() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_MIPSFPU() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_MIPSFPU16() const;

		boost::shared_ptr< Base<EncodingT> > getIMAGE_FILE_MACHINE_POWERPC() const;

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( ImageFileMachineInterpreter, UCS("ImageFileMachine") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_AM33, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_AM33") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_AMD64, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_AMD64") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_ARM, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_ARM") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_ARMV7, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_ARMV7") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_EBC, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_EBC") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_I386, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_I386") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_IA64, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_IA64") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_M32R, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_M32R") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_MIPS16, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_MIPS16") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_MIPSFPU, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_MIPSFPU") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_MIPSFPU16, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_MIPSFPU16") );
			METHOD_KEY_REGISTER ( ImageFileMachineInterpreter, boost::shared_ptr< Base<EncodingT> >, getIMAGE_FILE_MACHINE_POWERPC, const_t, UCS("ImageFileMachine::IMAGE_FILE_MACHINE_POWERPC") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( UCS("ImageFileMachine") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_AM33") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_AMD64") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_ARM") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_ARMV7") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_EBC") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_I386") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_IA64") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_M32R") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_MIPS16") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_MIPSFPU") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_MIPSFPU16") );
			METHOD_KEY_UNREGISTER ( UCS("ImageFileMachine::IMAGE_FILE_MACHINE_POWERPC") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "ImageFileMachineInterpreter_impl.hpp"

#endif