# DebugTypeInfo
debugTypeInfo table represents type information for debug.

# Référence
## Constructeur DebugTypeInfo
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugTypeInfo.
```
var = new DebugTypeInfo();
```

## Constructeur DebugTypeInfo
*Paramètres*
* Numeric : La valeur de la colonne isChar.
* Numeric : La valeur de la colonne isString.
* Numeric : La valeur de la colonne isBool.
* Numeric : La valeur de la colonne isFloat.
* Numeric : La valeur de la colonne isSigned.
* Numeric : La valeur de la colonne isWide.
* Numeric : La valeur de la colonne isPointer.
* Numeric : La valeur de la colonne isReference.
* Numeric : La valeur de la colonne isArray.
* Numeric : La valeur de la colonne isConst.
* Numeric : La valeur de la colonne isVolatile.
* Numeric : La valeur de la colonne isStruct.
* Numeric : La valeur de la colonne isClass.
* Numeric : La valeur de la colonne isUnion.
* Numeric : La valeur de la colonne isInterface.
* Numeric : La valeur de la colonne isEnum.
* Numeric : La valeur de la colonne isFunction.
* String : La valeur de la colonne baseName.
* String : La valeur de la colonne name.
* Numeric : La valeur de la colonne sizeOf.
* Numeric : La valeur de la colonne typeId.
* Numeric : La valeur de la colonne arrayDim.

*Description*
* Crée une instance de la classe DebugTypeInfo.
```
var = new DebugTypeInfo(isChar, isString, isBool, isFloat, isSigned, isWide, isPointer, isReference, isArray, isConst, isVolatile, isStruct, isClass, isUnion, isInterface, isEnum, isFunction, baseName, name, sizeOf, typeId, arrayDim);
```

## Méthode Identifier
*Paramètres*
* None.

*Retour*
* Numeric : La colonne identifier.

*Description*
* Retourne la colonne Identifier.
```
val = var.Identifier;
```

## Méthode IsChar
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isChar.

*Description*
* Retourne la colonne IsChar.
```
val = var.IsChar;
```

## Méthode IsString
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isString.

*Description*
* Retourne la colonne IsString.
```
val = var.IsString;
```

## Méthode IsBool
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isBool.

*Description*
* Retourne la colonne IsBool.
```
val = var.IsBool;
```

## Méthode IsFloat
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isFloat.

*Description*
* Retourne la colonne IsFloat.
```
val = var.IsFloat;
```

## Méthode IsSigned
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isSigned.

*Description*
* Retourne la colonne IsSigned.
```
val = var.IsSigned;
```

## Méthode IsWide
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isWide.

*Description*
* Retourne la colonne IsWide.
```
val = var.IsWide;
```

## Méthode IsPointer
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isPointer.

*Description*
* Retourne la colonne IsPointer.
```
val = var.IsPointer;
```

## Méthode IsReference
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isReference.

*Description*
* Retourne la colonne IsReference.
```
val = var.IsReference;
```

## Méthode IsArray
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isArray.

*Description*
* Retourne la colonne IsArray.
```
val = var.IsArray;
```

## Méthode IsConst
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isConst.

*Description*
* Retourne la colonne IsConst.
```
val = var.IsConst;
```

## Méthode IsVolatile
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isVolatile.

*Description*
* Retourne la colonne IsVolatile.
```
val = var.IsVolatile;
```

## Méthode IsStruct
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isStruct.

*Description*
* Retourne la colonne IsStruct.
```
val = var.IsStruct;
```

## Méthode IsClass
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isClass.

*Description*
* Retourne la colonne IsClass.
```
val = var.IsClass;
```

## Méthode IsUnion
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isUnion.

*Description*
* Retourne la colonne IsUnion.
```
val = var.IsUnion;
```

## Méthode IsInterface
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isInterface.

*Description*
* Retourne la colonne IsInterface.
```
val = var.IsInterface;
```

## Méthode IsEnum
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isEnum.

*Description*
* Retourne la colonne IsEnum.
```
val = var.IsEnum;
```

## Méthode IsFunction
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isFunction.

*Description*
* Retourne la colonne IsFunction.
```
val = var.IsFunction;
```

## Méthode BaseName
*Paramètres*
* None.

*Retour*
* String : La colonne baseName.

*Description*
* Retourne la colonne BaseName.
```
val = var.BaseName;
```

## Méthode Name
*Paramètres*
* None.

*Retour*
* String : La colonne name.

*Description*
* Retourne la colonne Name.
```
val = var.Name;
```

## Méthode SizeOf
*Paramètres*
* None.

*Retour*
* Numeric : La colonne sizeOf.

*Description*
* Retourne la colonne SizeOf.
```
val = var.SizeOf;
```

## Méthode TypeId
*Paramètres*
* None.

*Retour*
* Numeric : La colonne typeId.

*Description*
* Retourne la colonne TypeId.
```
val = var.TypeId;
```

## Méthode ArrayDim
*Paramètres*
* None.

*Retour*
* Numeric : La colonne arrayDim.

*Description*
* Retourne la colonne ArrayDim.
```
val = var.ArrayDim;
```

## Méthode PrimitiveType
*Paramètres*
* None.

*Retour*
* DebugTypeInfo : La colonne primitiveType.

*Description*
* Retourne la colonne PrimitiveType.
```
primitiveType = var.PrimitiveType;
```

## Méthode PrimitiveType
*Paramètres*
* DebugTypeInfo : La valeur de la colonne primitiveType.

*Retour*
* None.

*Description*
* Définit la colonne primitiveType.
```
var.PrimitiveType(primitiveType);
```

## Méthode IsChar
*Paramètres*
* Numeric : La valeur de la colonne isChar.

*Retour*
* None.

*Description*
* Définit la colonne isChar.
```
var.IsChar(isChar);
```

## Méthode IsString
*Paramètres*
* Numeric : La valeur de la colonne isString.

*Retour*
* None.

*Description*
* Définit la colonne isString.
```
var.IsString(isString);
```

## Méthode IsBool
*Paramètres*
* Numeric : La valeur de la colonne isBool.

*Retour*
* None.

*Description*
* Définit la colonne isBool.
```
var.IsBool(isBool);
```

## Méthode IsFloat
*Paramètres*
* Numeric : La valeur de la colonne isFloat.

*Retour*
* None.

*Description*
* Définit la colonne isFloat.
```
var.IsFloat(isFloat);
```

## Méthode IsSigned
*Paramètres*
* Numeric : La valeur de la colonne isSigned.

*Retour*
* None.

*Description*
* Définit la colonne isSigned.
```
var.IsSigned(isSigned);
```

## Méthode IsWide
*Paramètres*
* Numeric : La valeur de la colonne isWide.

*Retour*
* None.

*Description*
* Définit la colonne isWide.
```
var.IsWide(isWide);
```

## Méthode IsPointer
*Paramètres*
* Numeric : La valeur de la colonne isPointer.

*Retour*
* None.

*Description*
* Définit la colonne isPointer.
```
var.IsPointer(isPointer);
```

## Méthode IsReference
*Paramètres*
* Numeric : La valeur de la colonne isReference.

*Retour*
* None.

*Description*
* Définit la colonne isReference.
```
var.IsReference(isReference);
```

## Méthode IsArray
*Paramètres*
* Numeric : La valeur de la colonne isArray.

*Retour*
* None.

*Description*
* Définit la colonne isArray.
```
var.IsArray(isArray);
```

## Méthode IsConst
*Paramètres*
* Numeric : La valeur de la colonne isConst.

*Retour*
* None.

*Description*
* Définit la colonne isConst.
```
var.IsConst(isConst);
```

## Méthode IsVolatile
*Paramètres*
* Numeric : La valeur de la colonne isVolatile.

*Retour*
* None.

*Description*
* Définit la colonne isVolatile.
```
var.IsVolatile(isVolatile);
```

## Méthode IsStruct
*Paramètres*
* Numeric : La valeur de la colonne isStruct.

*Retour*
* None.

*Description*
* Définit la colonne isStruct.
```
var.IsStruct(isStruct);
```

## Méthode IsClass
*Paramètres*
* Numeric : La valeur de la colonne isClass.

*Retour*
* None.

*Description*
* Définit la colonne isClass.
```
var.IsClass(isClass);
```

## Méthode IsUnion
*Paramètres*
* Numeric : La valeur de la colonne isUnion.

*Retour*
* None.

*Description*
* Définit la colonne isUnion.
```
var.IsUnion(isUnion);
```

## Méthode IsInterface
*Paramètres*
* Numeric : La valeur de la colonne isInterface.

*Retour*
* None.

*Description*
* Définit la colonne isInterface.
```
var.IsInterface(isInterface);
```

## Méthode IsEnum
*Paramètres*
* Numeric : La valeur de la colonne isEnum.

*Retour*
* None.

*Description*
* Définit la colonne isEnum.
```
var.IsEnum(isEnum);
```

## Méthode IsFunction
*Paramètres*
* Numeric : La valeur de la colonne isFunction.

*Retour*
* None.

*Description*
* Définit la colonne isFunction.
```
var.IsFunction(isFunction);
```

## Méthode BaseName
*Paramètres*
* String : La valeur de la colonne baseName.

*Retour*
* None.

*Description*
* Définit la colonne baseName.
```
var.BaseName(baseName);
```

## Méthode Name
*Paramètres*
* String : La valeur de la colonne name.

*Retour*
* None.

*Description*
* Définit la colonne name.
```
var.Name(name);
```

## Méthode SizeOf
*Paramètres*
* Numeric : La valeur de la colonne sizeOf.

*Retour*
* None.

*Description*
* Définit la colonne sizeOf.
```
var.SizeOf(sizeOf);
```

## Méthode TypeId
*Paramètres*
* Numeric : La valeur de la colonne typeId.

*Retour*
* None.

*Description*
* Définit la colonne typeId.
```
var.TypeId(typeId);
```

## Méthode ArrayDim
*Paramètres*
* Numeric : La valeur de la colonne arrayDim.

*Retour*
* None.

*Description*
* Définit la colonne arrayDim.
```
var.ArrayDim(arrayDim);
```

## Méthode HasPrimitiveType
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne primitiveType.

*Description*
* Indique si la colonne PrimitiveType a une valeur définie.
```
val = var.HasPrimitiveType;
```

## Méthode removePrimitiveType
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne primitiveType.
```
var.PrimitiveType = null;
```

## Méthode removeRichTypes
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de RichTypes.
```
var.RichTypes(0) = null;
```

## Méthode removeDebugFunctionInfos
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de DebugFunctionInfos.
```
var.DebugFunctionInfos(0) = null;
```

## Méthode removeDebugVariableInfos
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de DebugVariableInfos.
```
var.DebugVariableInfos(0) = null;
```

## Méthode RichTypes
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugTypeInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de RichTypes.
```
var.RichTypes(0) = richType;
```

## Méthode DebugFunctionInfos
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugFunctionInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de DebugFunctionInfos.
```
var.DebugFunctionInfos(0) = debugFunctionInfo;
```

## Méthode DebugVariableInfos
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugVariableInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de DebugVariableInfos.
```
var.DebugVariableInfos(0) = debugVariableInfo;
```

## Méthode RichTypes
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugTypeInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de RichTypes.
```
val = var.RichTypes(0);
```

## Méthode DebugFunctionInfos
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugFunctionInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de DebugFunctionInfos.
```
val = var.DebugFunctionInfos(0);
```

## Méthode DebugVariableInfos
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugVariableInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de DebugVariableInfos.
```
val = var.DebugVariableInfos(0);
```

## Méthode ClearRichTypes
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearRichTypes();
```

## Méthode ClearDebugFunctionInfos
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearDebugFunctionInfos();
```

## Méthode ClearDebugVariableInfos
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearDebugVariableInfos();
```

## Méthode HasRichTypes
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasRichTypes();
```

## Méthode HasDebugFunctionInfos
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasDebugFunctionInfos();
```

## Méthode HasDebugVariableInfos
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasDebugVariableInfos();
```

## Méthode RichTypesCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.RichTypesCount();
```

## Méthode DebugFunctionInfosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.DebugFunctionInfosCount();
```

## Méthode DebugVariableInfosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.DebugVariableInfosCount();
```
