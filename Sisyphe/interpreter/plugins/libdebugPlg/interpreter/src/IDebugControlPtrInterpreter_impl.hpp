/*
 * IDebugControlPtrInterpreter_impl.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
class DEBUG_STACK_FRAMEInterpreter;

template <class EncodingT>
class DEBUG_VALUEInterpreter;

template <class EncodingT>
class IDebugBreakpointPtrInterpreter;

template <class EncodingT>
IDebugControlPtrInterpreter<EncodingT>::IDebugControlPtrInterpreter()
{
}

template <class EncodingT>
void IDebugControlPtrInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
void IDebugControlPtrInterpreter<EncodingT>::initValue(const IDebugControlPtr& object)
{
	m_object = object;
}

template <class EncodingT>
IDebugControlPtr& IDebugControlPtrInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const IDebugControlPtr& IDebugControlPtrInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
IDebugControlPtrInterpreter<EncodingT>::IDebugControlPtrInterpreter(const IDebugControlPtr& object)
{
	initValue(object);
}

template <class EncodingT>
const IDebugControlPtr& IDebugControlPtrInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void IDebugControlPtrInterpreter<EncodingT>::value(IDebugControlPtr const& object)
{
	if (&object != &value()) {
		tidyValue();
		initValue(object);
	}
}

template <class EncodingT>
typename EncodingT::string_t IDebugControlPtrInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new IDebugControlPtrInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t IDebugControlPtrInterpreter<EncodingT>::getClassName() const
{
	return UCS("IDebugControlPtr");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, UCS("IDebugControlPtr"), method, args, ret) ||
			tryInvoke(this, UCS("Base"), method, args, ret))
		{
			find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
			for (size_t i = 0; i < params.size(); ++i)
			{
				find_parameter(ret, i, params[i]);
			}
		}
		else
		{
			Category* logger = &Category::getInstance(LOGNAME);
			logger->errorStream() << "Unexpected call in IDebugControlPtr, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Waits for an event that breaks into the debugger engine application. 
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::waitForEvent(const boost::shared_ptr< Base<EncodingT> >& flags, const boost::shared_ptr< Base<EncodingT> >& timeout)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeFlags;
		unsigned long nativeTimeout;
		if (check_numeric_i(flags, nativeFlags) && 
			check_numeric_i(timeout, nativeTimeout))
		{
			res->LLvalue(valuePtr->WaitForEvent(nativeFlags, nativeTimeout));
		}
	}
	return res;
}

// The SetTextMacro method sets the value of a fixed-name alias.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::setTextMacro(const boost::shared_ptr< Base<EncodingT> >& slot, const boost::shared_ptr< Base<EncodingT> >& macro)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeSlot;
		typename ansi::string_t nativeMacro;
		if (check_numeric_i(slot, nativeSlot) && 
			check_string<ansi>(macro, nativeMacro))
		{
			res->LLvalue(valuePtr->SetTextMacro(nativeSlot, nativeMacro.c_str()));
		}
	}
	return res;
}

// The Evaluate method evaluates an expression, returning the result.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::evaluate(const boost::shared_ptr< Base<EncodingT> >& expression, const boost::shared_ptr< Base<EncodingT> >& desiredType, boost::shared_ptr< Base<EncodingT> >& debugValue, boost::shared_ptr< Base<EncodingT> >& remainderIndex)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		typename ansi::string_t nativeExpression;
		unsigned long nativeDesiredType;
		DEBUG_VALUE nativeDebugValue;
		unsigned long nativeRemainderIndex;
		if (check_string<ansi>(expression, nativeExpression) && 
			check_numeric_i(desiredType, nativeDesiredType) && 
			check_DEBUG_VALUE(debugValue, nativeDebugValue) && 
			check_numeric_i(remainderIndex, nativeRemainderIndex))
		{
			res->LLvalue(valuePtr->Evaluate(nativeExpression.c_str(), nativeDesiredType, &nativeDebugValue, &nativeRemainderIndex));
			reset_DEBUG_VALUE(debugValue, nativeDebugValue);
			reset_numeric_i(remainderIndex, nativeRemainderIndex);
		}
	}
	return res;
}

// The Execute method executes the specified debugger commands.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::execute(const boost::shared_ptr< Base<EncodingT> >& outputControl, const boost::shared_ptr< Base<EncodingT> >& command, const boost::shared_ptr< Base<EncodingT> >& flags)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeOutputControl;
		typename ansi::string_t nativeCommand;
		unsigned long nativeFlags;
		if (check_numeric_i(outputControl, nativeOutputControl) && 
			check_string<ansi>(command, nativeCommand) && 
			check_numeric_i(flags, nativeFlags))
		{
			res->LLvalue(valuePtr->Execute(nativeOutputControl, nativeCommand.c_str(), nativeFlags));
		}
	}
	return res;
}

// The Assemble method assembles a single processor instruction. The assembled instruction is placed in the target's memory.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::assemble(const boost::shared_ptr< Base<EncodingT> >& offset, const boost::shared_ptr< Base<EncodingT> >& instr, boost::shared_ptr< Base<EncodingT> >& endOffset)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long long nativeOffset;
		typename ansi::string_t nativeInstr;
		unsigned long long nativeEndOffset;
		if (check_numeric_i(offset, nativeOffset) && 
			check_string<ansi>(instr, nativeInstr) && 
			check_numeric_i(endOffset, nativeEndOffset))
		{
			res->LLvalue(valuePtr->Assemble(nativeOffset, nativeInstr.c_str(), &nativeEndOffset));
			reset_numeric_i(endOffset, nativeEndOffset);
		}
	}
	return res;
}

// The GetExecutionStatus method returns information about the execution status of the debugger engine.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::getExecutionStatus(boost::shared_ptr< Base<EncodingT> >& status)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeStatus;
		if (check_numeric_i(status, nativeStatus))
		{
			res->LLvalue(valuePtr->GetExecutionStatus(&nativeStatus));
			reset_numeric_i(status, nativeStatus);
		}
	}
	return res;
}

// The GetActualProcessorType method returns the processor type of the physical processor of the computer that is running the target.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::getActualProcessorType(boost::shared_ptr< Base<EncodingT> >& type)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeType;
		if (check_numeric_i(type, nativeType))
		{
			res->LLvalue(valuePtr->GetActualProcessorType(&nativeType));
			reset_numeric_i(type, nativeType);
		}
	}
	return res;
}

// The SetEffectiveProcessorType method sets the effective processor type of the processor of the computer that is running the target.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::setEffectiveProcessorType(const boost::shared_ptr< Base<EncodingT> >& type)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeType;
		if (check_numeric_i(type, nativeType))
		{
			res->LLvalue(valuePtr->SetEffectiveProcessorType(nativeType));
		}
	}
	return res;
}

// Returns the standard prompt text that will be prepended to the formatted output specified in the OutputPrompt and OutputPromptVaList methods.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::getPromptText(boost::shared_ptr< Base<EncodingT> >& buffer)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDebugControlPtr valuePtr = value();
  if (valuePtr != NULL)
  {
    char nativeBuffer[2048];
    res.reset(new Numeric<EncodingT>(valuePtr->GetPromptText(nativeBuffer, 2048, NULL)));
    reset_string<ansi>(buffer, nativeBuffer);
  }
  return res;
}

// Opens a log file that will receive output from the client objects.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::openLogFile(const boost::shared_ptr< Base<EncodingT> >& file, const boost::shared_ptr< Base<EncodingT> >& append)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		typename ansi::string_t nativeFile;
		bool nativeAppend;
		if (check_string<ansi>(file, nativeFile) && 
			check_bool(append, nativeAppend))
		{
			res->LLvalue(valuePtr->OpenLogFile(nativeFile.c_str(), nativeAppend));
		}
	}
	return res;
}

// Closes the currently-open log file.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::closeLogFile()
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		res->LLvalue(valuePtr->CloseLogFile());
	}
	return res;
}

// Returns the return address for the current function.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::getReturnOffset(boost::shared_ptr< Base<EncodingT> >& offset)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long long nativeOffset;
		if (check_numeric_i(offset, nativeOffset))
		{
			res->LLvalue(valuePtr->GetReturnOffset(&nativeOffset));
			reset_numeric_i(offset, nativeOffset);
		}
	}
	return res;
}

// Creates a new breakpoint for the current target.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::addBreakpoint(const boost::shared_ptr< Base<EncodingT> >& type, const boost::shared_ptr< Base<EncodingT> >& desiredId, boost::shared_ptr< Base<EncodingT> >& bp)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeType;
		unsigned long nativeDesiredId;
		IDebugBreakpointPtr nativeBp;
		if (check_numeric_i(type, nativeType) && 
			check_numeric_i(desiredId, nativeDesiredId) && 
			check_IDebugBreakpointPtr(bp, nativeBp))
		{
			res->LLvalue(valuePtr->AddBreakpoint(nativeType, nativeDesiredId, &nativeBp));
			reset_IDebugBreakpointPtr(bp, nativeBp);
		}
	}
	return res;
}

// Removes a breakpoint.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::removeBreakpoint(const boost::shared_ptr< Base<EncodingT> >& bp)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		IDebugBreakpointPtr nativeBp;
		if (check_IDebugBreakpointPtr(bp, nativeBp))
		{
			res->LLvalue(valuePtr->RemoveBreakpoint(nativeBp));
		}
	}
	return res;
}

// The SetExpressionSyntax method sets the syntax that the engine will use to evaluate expressions.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::setExpressionSyntax(const boost::shared_ptr< Base<EncodingT> >& flags)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long nativeFlags;
		if (check_numeric_i(flags, nativeFlags))
		{
			res->LLvalue(valuePtr->SetExpressionSyntax(nativeFlags));
		}
	}
	return res;
}

// The IsPointer64Bit method determines if the effective processor uses 64-bit pointers.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::isPointer64Bit()
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		res->LLvalue(valuePtr->IsPointer64Bit());
	}
	return res;
}

// The GetStackTrace method returns the frames at the top of the specified call stack.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::getStackTrace(const boost::shared_ptr< Base<EncodingT> >& frameOffset, const boost::shared_ptr< Base<EncodingT> >& stackOffset, const boost::shared_ptr< Base<EncodingT> >& instructionOffset, boost::shared_ptr< Base<EncodingT> >& frames, const boost::shared_ptr< Base<EncodingT> >& frameSize, boost::shared_ptr< Base<EncodingT> >& framesFilled)
{
boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
  IDebugControlPtr valuePtr = value();
  if (valuePtr != NULL)
  {
    unsigned long long nativeFrameOffset;
    unsigned long long nativeStackOffset;
    unsigned long long nativeInstructionOffset;
    std::vector< DEBUG_STACK_FRAME > nativeFrames;
    unsigned long nativeFrameSize;
    unsigned long nativeFramesFilled;
    if (check_numeric_i(frameOffset, nativeFrameOffset) &&
      check_numeric_i(stackOffset, nativeStackOffset) &&
      check_numeric_i(instructionOffset, nativeInstructionOffset) &&
      check_array(frames, nativeFrames, check_DEBUG_STACK_FRAME<EncodingT>) &&
      check_numeric_i(frameSize, nativeFrameSize) &&
      check_numeric_i(framesFilled, nativeFramesFilled))
    {
      nativeFrames.resize(nativeFrameSize);
      res.reset(new Numeric<EncodingT>(valuePtr->GetStackTrace(nativeFrameOffset, nativeStackOffset, nativeInstructionOffset, nativeFrames.data(), nativeFrameSize, &nativeFramesFilled)));
      boost::shared_ptr< Array<EncodingT> > framesArray  = dynamic_pointer_cast< Array<EncodingT> >(frames);
      if (framesArray)
      {
          for (size_t i = 0; i < nativeFramesFilled; ++i)
          {
            boost::shared_ptr< Base<EncodingT> > item(new DEBUG_STACK_FRAMEInterpreter<EncodingT>(nativeFrames[i]));
            framesArray->addValue(item);
          }
      }
      reset_numeric_i(framesFilled, nativeFramesFilled);
    }
  }
  return res;
}

// The GetNearInstruction method returns the location of a processor instruction relative to a given location.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > IDebugControlPtrInterpreter<EncodingT>::getNearInstruction(const boost::shared_ptr< Base<EncodingT> >& offset, const boost::shared_ptr< Base<EncodingT> >& delta, boost::shared_ptr< Base<EncodingT> >& nearOffset)
{
	boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>());
	IDebugControlPtr valuePtr = refValue();
	if (valuePtr != NULL)
	{
		unsigned long long nativeOffset;
		unsigned long nativeDelta;
		unsigned long long nativeNearOffset;
		if (check_numeric_i(offset, nativeOffset) && 
			check_numeric_i(delta, nativeDelta) && 
			check_numeric_i(nearOffset, nativeNearOffset))
		{
			res->LLvalue(valuePtr->GetNearInstruction(nativeOffset, nativeDelta, &nativeNearOffset));
			reset_numeric_i(nearOffset, nativeNearOffset);
		}
	}
	return res;
}


template <class EncodingT>
bool check_IDebugControlPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDebugControlPtr& a)
{
	boost::shared_ptr< IDebugControlPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDebugControlPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDebugControlPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_IDebugControlPtr(boost::shared_ptr< Base<EncodingT> >& val, IDebugControlPtr const& a)
{
	boost::shared_ptr< IDebugControlPtrInterpreter<EncodingT> > value  = dynamic_pointer_cast< IDebugControlPtrInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "IDebugControlPtr expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C