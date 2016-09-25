# IDebugControlPtr
 Classe permettant d'accéder aux contrôles de débogage. 

# Référence
## Méthode WaitForEvent
*Paramètres*
* Numeric : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Waits for an event that breaks into the debugger engine application. 
```
WaitForEvent();
```

## Méthode SetTextMacro
*Paramètres*
* Numeric : 
* String : 

*Retour*
* Numeric : 

*Description*
*  The SetTextMacro method sets the value of a fixed-name alias.
```
SetTextMacro();
```

## Méthode Evaluate
*Paramètres*
* String : 
* Numeric : 
* DEBUG_VALUE : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The Evaluate method evaluates an expression, returning the result.
```
Evaluate();
```

## Méthode Execute
*Paramètres*
* Numeric : 
* String : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The Execute method executes the specified debugger commands.
```
Execute();
```

## Méthode Assemble
*Paramètres*
* Numeric : 
* String : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The Assemble method assembles a single processor instruction. The assembled instruction is placed in the target's memory.
```
Assemble();
```

## Méthode GetExecutionStatus
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The GetExecutionStatus method returns information about the execution status of the debugger engine.
```
GetExecutionStatus();
```

## Méthode GetActualProcessorType
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The GetActualProcessorType method returns the processor type of the physical processor of the computer that is running the target.
```
GetActualProcessorType();
```

## Méthode SetEffectiveProcessorType
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The SetEffectiveProcessorType method sets the effective processor type of the processor of the computer that is running the target.
```
SetEffectiveProcessorType();
```

## Méthode GetPromptText
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  Returns the standard prompt text that will be prepended to the formatted output specified in the OutputPrompt and OutputPromptVaList methods.
```
GetPromptText();
```

## Méthode OpenLogFile
*Paramètres*
* String : 
* Bool : 

*Retour*
* Numeric : 

*Description*
*  Opens a log file that will receive output from the client objects.
```
OpenLogFile();
```

## Méthode CloseLogFile
*Paramètres*
* None.

*Retour*
* Numeric : 

*Description*
*  Closes the currently-open log file.
```
CloseLogFile();
```

## Méthode GetReturnOffset
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Returns the return address for the current function.
```
GetReturnOffset();
```

## Méthode AddBreakpoint
*Paramètres*
* Numeric : 
* Numeric : 
* IDebugBreakpointPtr : 

*Retour*
* Numeric : 

*Description*
*  Creates a new breakpoint for the current target.
```
AddBreakpoint();
```

## Méthode RemoveBreakpoint
*Paramètres*
* IDebugBreakpointPtr : 

*Retour*
* Numeric : 

*Description*
*  Removes a breakpoint.
```
RemoveBreakpoint();
```

## Méthode SetExpressionSyntax
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The SetExpressionSyntax method sets the syntax that the engine will use to evaluate expressions.
```
SetExpressionSyntax();
```
