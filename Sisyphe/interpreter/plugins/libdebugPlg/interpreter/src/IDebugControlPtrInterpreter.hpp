/*
 * IDebugControlPtrInterpreter.hpp
 *
 *
 * @date 24-09-2016
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _IDEBUGCONTROLPTR_INTERPRETER_H_
#define _IDEBUGCONTROLPTR_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "DebugPtr.h"
typedef CDebugPtr<IDebugControl3> IDebugControlPtr;
#include "IDebugBreakpointPtrInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe permettant d'accéder aux contrôles de débogage. 
	template <class EncodingT>
	class IDebugControlPtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDebugControlPtr m_object;

		void initValue(const IDebugControlPtr& object);

		IDebugControlPtr& value();

		const IDebugControlPtr& value() const;

		void tidyValue();

	public:
		IDebugControlPtrInterpreter();

		~IDebugControlPtrInterpreter();

		IDebugControlPtrInterpreter(const IDebugControlPtr& object);

		IDebugControlPtrInterpreter(const IDebugControlPtrInterpreter<EncodingT>& rhs);

		IDebugControlPtrInterpreter<EncodingT>& operator=(const IDebugControlPtrInterpreter<EncodingT>& rhs);

		const IDebugControlPtr& getValue() const;

		void setValue(IDebugControlPtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		// Waits for an event that breaks into the debugger engine application. 
		FACTORY_PROTOTYPE2(waitForEvent, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > waitForEvent(const boost::shared_ptr< Base<EncodingT> >& flags, const boost::shared_ptr< Base<EncodingT> >& timeout);

		// The SetTextMacro method sets the value of a fixed-name alias.
		FACTORY_PROTOTYPE2(setTextMacro, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > setTextMacro(const boost::shared_ptr< Base<EncodingT> >& slot, const boost::shared_ptr< Base<EncodingT> >& macro);

		// The Evaluate method evaluates an expression, returning the result.
		FACTORY_PROTOTYPE4(evaluate, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > evaluate(const boost::shared_ptr< Base<EncodingT> >& expression, const boost::shared_ptr< Base<EncodingT> >& desiredType, boost::shared_ptr< Base<EncodingT> >& debugValue, boost::shared_ptr< Base<EncodingT> >& remainderIndex);

		// The Execute method executes the specified debugger commands.
		FACTORY_PROTOTYPE3(execute, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > execute(const boost::shared_ptr< Base<EncodingT> >& outputControl, const boost::shared_ptr< Base<EncodingT> >& command, const boost::shared_ptr< Base<EncodingT> >& flags);

		// The Assemble method assembles a single processor instruction. The assembled instruction is placed in the target's memory.
		FACTORY_PROTOTYPE3(assemble, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > assemble(const boost::shared_ptr< Base<EncodingT> >& offset, const boost::shared_ptr< Base<EncodingT> >& instr, boost::shared_ptr< Base<EncodingT> >& endOffset);

		// The GetExecutionStatus method returns information about the execution status of the debugger engine.
		FACTORY_PROTOTYPE1(getExecutionStatus, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getExecutionStatus(boost::shared_ptr< Base<EncodingT> >& status);

		// The GetActualProcessorType method returns the processor type of the physical processor of the computer that is running the target.
		FACTORY_PROTOTYPE1(getActualProcessorType, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getActualProcessorType(boost::shared_ptr< Base<EncodingT> >& type);

		// The SetEffectiveProcessorType method sets the effective processor type of the processor of the computer that is running the target.
		FACTORY_PROTOTYPE1(setEffectiveProcessorType, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > setEffectiveProcessorType(const boost::shared_ptr< Base<EncodingT> >& type);

		// Returns the standard prompt text that will be prepended to the formatted output specified in the OutputPrompt and OutputPromptVaList methods.
		FACTORY_PROTOTYPE1(getPromptText, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getPromptText(boost::shared_ptr< Base<EncodingT> >& buffer);

		// Opens a log file that will receive output from the client objects.
		FACTORY_PROTOTYPE2(openLogFile, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > openLogFile(const boost::shared_ptr< Base<EncodingT> >& file, const boost::shared_ptr< Base<EncodingT> >& append);

		// Closes the currently-open log file.
		boost::shared_ptr< Base<EncodingT> > closeLogFile();

		// Returns the return address for the current function.
		FACTORY_PROTOTYPE1(getReturnOffset, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getReturnOffset(boost::shared_ptr< Base<EncodingT> >& offset);

		// Creates a new breakpoint for the current target.
		FACTORY_PROTOTYPE3(addBreakpoint, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > addBreakpoint(const boost::shared_ptr< Base<EncodingT> >& type, const boost::shared_ptr< Base<EncodingT> >& desiredId, boost::shared_ptr< Base<EncodingT> >& bp);

		// Removes a breakpoint.
		FACTORY_PROTOTYPE1(removeBreakpoint, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > removeBreakpoint(const boost::shared_ptr< Base<EncodingT> >& bp);

		// The SetExpressionSyntax method sets the syntax that the engine will use to evaluate expressions.
		FACTORY_PROTOTYPE1(setExpressionSyntax, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > setExpressionSyntax(const boost::shared_ptr< Base<EncodingT> >& flags);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDebugControlPtrInterpreter, C("IDebugControlPtr") );
			METHOD_KEY_REGISTER2( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, waitForEvent, no_const_t, C("IDebugControlPtr::WaitForEvent") );
			METHOD_KEY_REGISTER2( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, setTextMacro, no_const_t, C("IDebugControlPtr::SetTextMacro") );
			METHOD_KEY_REGISTER4( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, evaluate, no_const_t, C("IDebugControlPtr::Evaluate") );
			METHOD_KEY_REGISTER3( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, execute, no_const_t, C("IDebugControlPtr::Execute") );
			METHOD_KEY_REGISTER3( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, assemble, no_const_t, C("IDebugControlPtr::Assemble") );
			METHOD_KEY_REGISTER1( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, getExecutionStatus, no_const_t, C("IDebugControlPtr::GetExecutionStatus") );
			METHOD_KEY_REGISTER1( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, getActualProcessorType, no_const_t, C("IDebugControlPtr::GetActualProcessorType") );
			METHOD_KEY_REGISTER1( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, setEffectiveProcessorType, no_const_t, C("IDebugControlPtr::SetEffectiveProcessorType") );
			METHOD_KEY_REGISTER1( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, getPromptText, no_const_t, C("IDebugControlPtr::GetPromptText") );
			METHOD_KEY_REGISTER2( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, openLogFile, no_const_t, C("IDebugControlPtr::OpenLogFile") );
			METHOD_KEY_REGISTER ( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, closeLogFile, no_const_t, C("IDebugControlPtr::CloseLogFile") );
			METHOD_KEY_REGISTER1( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, getReturnOffset, no_const_t, C("IDebugControlPtr::GetReturnOffset") );
			METHOD_KEY_REGISTER3( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, addBreakpoint, no_const_t, C("IDebugControlPtr::AddBreakpoint") );
			METHOD_KEY_REGISTER1( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, removeBreakpoint, no_const_t, C("IDebugControlPtr::RemoveBreakpoint") );
			METHOD_KEY_REGISTER1( IDebugControlPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, setExpressionSyntax, no_const_t, C("IDebugControlPtr::SetExpressionSyntax") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("IDebugControlPtr") );
			METHOD_KEY_UNREGISTER2( C("IDebugControlPtr::WaitForEvent") );
			METHOD_KEY_UNREGISTER2( C("IDebugControlPtr::SetTextMacro") );
			METHOD_KEY_UNREGISTER4( C("IDebugControlPtr::Evaluate") );
			METHOD_KEY_UNREGISTER3( C("IDebugControlPtr::Execute") );
			METHOD_KEY_UNREGISTER3( C("IDebugControlPtr::Assemble") );
			METHOD_KEY_UNREGISTER1( C("IDebugControlPtr::GetExecutionStatus") );
			METHOD_KEY_UNREGISTER1( C("IDebugControlPtr::GetActualProcessorType") );
			METHOD_KEY_UNREGISTER1( C("IDebugControlPtr::SetEffectiveProcessorType") );
			METHOD_KEY_UNREGISTER1( C("IDebugControlPtr::GetPromptText") );
			METHOD_KEY_UNREGISTER2( C("IDebugControlPtr::OpenLogFile") );
			METHOD_KEY_UNREGISTER ( C("IDebugControlPtr::CloseLogFile") );
			METHOD_KEY_UNREGISTER1( C("IDebugControlPtr::GetReturnOffset") );
			METHOD_KEY_UNREGISTER3( C("IDebugControlPtr::AddBreakpoint") );
			METHOD_KEY_UNREGISTER1( C("IDebugControlPtr::RemoveBreakpoint") );
			METHOD_KEY_UNREGISTER1( C("IDebugControlPtr::SetExpressionSyntax") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDebugControlPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDebugControlPtr& a);

	template <class EncodingT>
	bool reset_IDebugControlPtr(boost::shared_ptr< Base<EncodingT> >& val, IDebugControlPtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDebugControlPtrInterpreter_impl.hpp"

#endif