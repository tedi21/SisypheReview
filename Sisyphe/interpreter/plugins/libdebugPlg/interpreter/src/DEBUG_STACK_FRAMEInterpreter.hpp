/*
 * DEBUG_STACK_FRAMEInterpreter.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _DEBUG_STACK_FRAME_INTERPRETER_H_
#define _DEBUG_STACK_FRAME_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"


#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// The DEBUG_STACK_FRAME structure describes a stack frame and the address of the current instruction for the stack frame.
	template <class EncodingT>
	class DEBUG_STACK_FRAMEInterpreter
	: public Base<EncodingT>
	{
	private:
		DEBUG_STACK_FRAME m_object;

		void initValue(const DEBUG_STACK_FRAME& object);

		DEBUG_STACK_FRAME& refValue();

		const DEBUG_STACK_FRAME& refValue() const;

		void tidyValue();

	public:
		DEBUG_STACK_FRAMEInterpreter();

		DEBUG_STACK_FRAMEInterpreter(const DEBUG_STACK_FRAME& object);

		const DEBUG_STACK_FRAME& value() const;

		void value(DEBUG_STACK_FRAME const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		boost::shared_ptr< Base<EncodingT> > getinstructionOffset() const;

		boost::shared_ptr< Base<EncodingT> > getreturnOffset() const;

		boost::shared_ptr< Base<EncodingT> > getframeOffset() const;

		boost::shared_ptr< Base<EncodingT> > getstackOffset() const;

		boost::shared_ptr< Base<EncodingT> > getfuncTableEntry() const;

		boost::shared_ptr< Base<EncodingT> > getvirtual() const;

		boost::shared_ptr< Base<EncodingT> > getframeNumber() const;

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( DEBUG_STACK_FRAMEInterpreter, UCS("DEBUG_STACK_FRAME") );
			METHOD_KEY_REGISTER ( DEBUG_STACK_FRAMEInterpreter, boost::shared_ptr< Base<EncodingT> >, getinstructionOffset, const_t, UCS("DEBUG_STACK_FRAME::InstructionOffset") );
			METHOD_KEY_REGISTER ( DEBUG_STACK_FRAMEInterpreter, boost::shared_ptr< Base<EncodingT> >, getreturnOffset, const_t, UCS("DEBUG_STACK_FRAME::ReturnOffset") );
			METHOD_KEY_REGISTER ( DEBUG_STACK_FRAMEInterpreter, boost::shared_ptr< Base<EncodingT> >, getframeOffset, const_t, UCS("DEBUG_STACK_FRAME::FrameOffset") );
			METHOD_KEY_REGISTER ( DEBUG_STACK_FRAMEInterpreter, boost::shared_ptr< Base<EncodingT> >, getstackOffset, const_t, UCS("DEBUG_STACK_FRAME::StackOffset") );
			METHOD_KEY_REGISTER ( DEBUG_STACK_FRAMEInterpreter, boost::shared_ptr< Base<EncodingT> >, getfuncTableEntry, const_t, UCS("DEBUG_STACK_FRAME::FuncTableEntry") );
			METHOD_KEY_REGISTER ( DEBUG_STACK_FRAMEInterpreter, boost::shared_ptr< Base<EncodingT> >, getvirtual, const_t, UCS("DEBUG_STACK_FRAME::Virtual") );
			METHOD_KEY_REGISTER ( DEBUG_STACK_FRAMEInterpreter, boost::shared_ptr< Base<EncodingT> >, getframeNumber, const_t, UCS("DEBUG_STACK_FRAME::FrameNumber") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( UCS("DEBUG_STACK_FRAME") );
			METHOD_KEY_UNREGISTER ( UCS("DEBUG_STACK_FRAME::InstructionOffset") );
			METHOD_KEY_UNREGISTER ( UCS("DEBUG_STACK_FRAME::ReturnOffset") );
			METHOD_KEY_UNREGISTER ( UCS("DEBUG_STACK_FRAME::FrameOffset") );
			METHOD_KEY_UNREGISTER ( UCS("DEBUG_STACK_FRAME::StackOffset") );
			METHOD_KEY_UNREGISTER ( UCS("DEBUG_STACK_FRAME::FuncTableEntry") );
			METHOD_KEY_UNREGISTER ( UCS("DEBUG_STACK_FRAME::Virtual") );
			METHOD_KEY_UNREGISTER ( UCS("DEBUG_STACK_FRAME::FrameNumber") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_DEBUG_STACK_FRAME(boost::shared_ptr< Base<EncodingT> > const& val, DEBUG_STACK_FRAME& a);

	template <class EncodingT>
	bool reset_DEBUG_STACK_FRAME(boost::shared_ptr< Base<EncodingT> >& val, DEBUG_STACK_FRAME const& a);

NAMESPACE_END

#undef A
#undef C
#include "DEBUG_STACK_FRAMEInterpreter_impl.hpp"

#endif