# IDebugSymbolsPtr
 Classe permettant d'accéder aux informations de symboles de débogage.

# Référence
## Méthode AddSymbolOptions
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Turns on some of the engine's global symbol options. 
```
AddSymbolOptions();
```

## Méthode AppendImagePath
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  Appends directories to the executable image path.
```
AppendImagePath();
```

## Méthode AppendSourcePath
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  Appends directories to the source path.
```
AppendSourcePath();
```

## Méthode AppendSymbolPath
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  Appends directories to the symbol path.
```
AppendSymbolPath();
```

## Méthode GetSymbolModule
*Paramètres*
* String : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Returns the base address of module which contains the specified symbol.
```
GetSymbolModule();
```

## Méthode GetSymbolOptions
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Returns the engine's global symbol options.
```
GetSymbolOptions();
```

## Méthode GetSymbolPath
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  Returns the symbol path.
```
GetSymbolPath();
```

## Méthode GetLineByOffset
*Paramètres*
* Numeric : 
* Numeric : 
* String : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Returns the source filename and the line number within the source file of an instruction in the target.
```
GetLineByOffset();
```

## Méthode GetModuleByOffset
*Paramètres*
* Numeric : 
* Numeric : 
* Numeric : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Searches through the target's modules for one whose memory allocation includes the specified location.
```
GetModuleByOffset();
```

## Méthode GetNameByOffset
*Paramètres*
* Numeric : 
* String : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Returns the name of the symbol at the specified location in the target's virtual address space.
```
GetNameByOffset();
```

## Méthode GetNearNameByOffset
*Paramètres*
* Numeric : 
* Numeric : 
* String : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Returns the name of a symbol that is located near the specified location. 
```
GetNearNameByOffset();
```

## Méthode GetOffsetByLine
*Paramètres*
* Numeric : 
* String : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The GetOffsetByLine method returns the location of the instruction that corresponds to a specified line in the source code.
```
GetOffsetByLine();
```

## Méthode GetSourceFileLineOffsets
*Paramètres*
* String : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The GetSourceFileLineOffsets method maps each line in a source file to a location in the target's memory.
```
GetSourceFileLineOffsets();
```
