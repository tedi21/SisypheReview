DROP TABLE cppFile;
DROP TABLE cppFileType;
DROP TABLE cppInclude;
DROP TABLE textFile;
DROP TABLE cppClass;
DROP TABLE cppInheritance;
DROP TABLE cppAttribute;
DROP TABLE cppFunction;
DROP TABLE cppParameter;
DROP TABLE cppVariable;
DROP TABLE cppEnum;
DROP TABLE cppEnumConstant;
DROP TABLE cMacro;
DROP TABLE cppNotice;
DROP TABLE debugFileInfo;
DROP TABLE debugFunctionInfo;
DROP TABLE debugVariableInfo;
DROP TABLE debugValueInfo;
DROP TABLE debugTypeInfo;
DROP TABLE debugErrorInfo;
DROP TABLE debugStubInfo;

-- Creation Virtual Table
--________________

-- Table using FTS4 describes data type for source generation. These information are not used by sqlite.

-- textFile table represents a text file

CREATE VIRTUAL TABLE textFile USING fts4 (
content         TEXT              NOT NULL);

-- Creation Table
--________________

-- cppFileType table represents a type of file : header or source.

CREATE TABLE cppFileType (
identifier    INTEGER             NOT NULL,
string        VARCHAR(10)         NOT NULL,

CONSTRAINT PK_FILETYPE  PRIMARY KEY(identifier));

INSERT INTO cppFileType (identifier, string) VALUES (1, 'header');
INSERT INTO cppFileType (identifier, string) VALUES (2, 'source');

-- cppFile table represents a file.

CREATE TABLE cppFile (
identifier    INTEGER             NOT NULL,
idText        INTEGER             NOT NULL,
path          VARCHAR(512)        NOT NULL,
name          VARCHAR(256)        NOT NULL,
idType        INTEGER             NOT NULL,
linesCount    INTEGER             NOT NULL,
hash          INTEGER             NOT NULL,
analyzed      INTEGER             NOT NULL,

CONSTRAINT PK_FILE          PRIMARY KEY(identifier),
CONSTRAINT FK_FILE_FILETYPE FOREIGN KEY(idType) REFERENCES cppFileType(identifier),
CONSTRAINT FK_FILE_TEXTFILE FOREIGN KEY(idText) REFERENCES textFile(rowid));

-- cppInclude table represents an include in cpp file.

CREATE TABLE cppInclude (
identifier        INTEGER         NOT NULL,
fileName          VARCHAR(256)    NOT NULL,
idFile            INTEGER         NOT NULL,
lineNumber        INTEGER         NOT NULL,

CONSTRAINT PK_INCLUDE       PRIMARY KEY(identifier),
CONSTRAINT FK_INCLUDE_FILE  FOREIGN KEY(idFile) REFERENCES cppFile(identifier));

-- cppClass table represents a class.

CREATE TABLE cppClass (
identifier           INTEGER         NOT NULL,
name                 VARCHAR(256)    NOT NULL,
fullName             VARCHAR(256)    NOT NULL,
accessSpecifier      VARCHAR(64),
isStruct             INTEGER,
isInterface          INTEGER,
isAbstract           INTEGER,
isTemplate           INTEGER,
linesCount           INTEGER,
idEncapsulationClass INTEGER,
idFile               INTEGER         NOT NULL,
lineNumber           INTEGER         NOT NULL,
startBlock           INTEGER,
lengthBlock          INTEGER,

CONSTRAINT PK_CLASS       PRIMARY KEY(identifier),
CONSTRAINT FK_CLASS_CLASS FOREIGN KEY(idEncapsulationClass) REFERENCES cppClass(identifier),
CONSTRAINT FK_CLASS_FILE  FOREIGN KEY(idFile) REFERENCES cppFile(identifier));

-- cppInheritance table represents an inheritance.

CREATE TABLE cppInheritance (
identifier        INTEGER         NOT NULL,
idDerived         INTEGER         NOT NULL,
baseClassName     VARCHAR(256)    NOT NULL,
baseAccess        VARCHAR(256),

CONSTRAINT PK_INHERITANCE           PRIMARY KEY(identifier),
CONSTRAINT FK_INHERITANCE_DERIVED   FOREIGN KEY(idDerived) REFERENCES cppClass(identifier));

-- cppFunction table represents a function.

CREATE TABLE cppFunction (
identifier        INTEGER         NOT NULL,
name              VARCHAR(256)    NOT NULL,
idClass           INTEGER,
accessSpecifier   VARCHAR(64),
returnType        VARCHAR(256),
isConst           INTEGER,
isVirtual         INTEGER,
isVirtualPure     INTEGER,
isStatic          INTEGER,
isOperator        INTEGER,
isDestructor      INTEGER,
isConstructor     INTEGER,
isVariadic        INTEGER,
isTemplate        INTEGER,
isInline          INTEGER,
isConstexpr       INTEGER,
isOverride        INTEGER,
isFinal           INTEGER,
isNoexcept        INTEGER,
signature         VARCHAR(256)    NOT NULL,
idDecFile         INTEGER,
decLineNumber     INTEGER,
startDecBlock     INTEGER,
lengthDecBlock    INTEGER,
linesCount        INTEGER,
complexity        INTEGER,
idDefFile         INTEGER,
defLineNumber     INTEGER,
startDefBlock     INTEGER,
lengthDefBlock    INTEGER,

CONSTRAINT PK_FUNCTION            PRIMARY KEY(identifier),
CONSTRAINT FK_FUNCTION_CLASS      FOREIGN KEY(idClass) REFERENCES cppClass(identifier),
CONSTRAINT FK_FUNCTION_DEC_FILE   FOREIGN KEY(idDecFile)  REFERENCES cppFile(identifier),
CONSTRAINT FK_FUNCTION_DEF_FILE   FOREIGN KEY(idDefFile)  REFERENCES cppFile(identifier));

-- cppParameter table represents a parameter.

CREATE TABLE cppParameter (
identifier        INTEGER         NOT NULL,
paramOrder        INTEGER         NOT NULL,
paramType         VARCHAR(256),
isConst           INTEGER,
defaultValue      VARCHAR(256),
idFunction        INTEGER         NOT NULL,
decName           VARCHAR(256),
decLineNumber     INTEGER,
startDecBlock     INTEGER,
lengthDecBlock    INTEGER,
defName           VARCHAR(256),
defLineNumber     INTEGER,
startDefBlock     INTEGER,
lengthDefBlock    INTEGER,

CONSTRAINT PK_PARAMETER           PRIMARY KEY(identifier),
CONSTRAINT FK_PARAMETER_FUNCTION  FOREIGN KEY(idFunction) REFERENCES cppFunction(identifier));

-- cppAttribute table represents an attribute.

CREATE TABLE cppAttribute (
identifier        INTEGER         NOT NULL,
attrType          VARCHAR(256),
name              VARCHAR(256)    NOT NULL,
accessSpecifier   VARCHAR(64),
isStatic          INTEGER,
isConst           INTEGER,
isConstexpr       INTEGER,
constValue        VARCHAR(256),
idClass           INTEGER         NOT NULL,
lineNumber        INTEGER         NOT NULL,
startBlock        INTEGER,
lengthBlock       INTEGER,

CONSTRAINT PK_ATTRIBUTE         PRIMARY KEY(identifier),
CONSTRAINT FK_ATTRIBUTE_CLASS   FOREIGN KEY(idClass) REFERENCES cppClass(identifier));

-- cppVariable table represents a variable.

CREATE TABLE cppVariable (
identifier        INTEGER         NOT NULL,
varType           VARCHAR(256),
name              VARCHAR(256)    NOT NULL,
isStatic          INTEGER,
isConst           INTEGER,
isConstexpr       INTEGER,
idFunction        INTEGER,
lineNumber        INTEGER         NOT NULL,
startBlock        INTEGER,
lengthBlock       INTEGER,
idFile            INTEGER         NOT NULL,

CONSTRAINT PK_VARIABLE            PRIMARY KEY(identifier),
CONSTRAINT FK_VARIABLE_FUNCTION   FOREIGN KEY(idFunction) REFERENCES cppFunction(identifier),
CONSTRAINT FK_VARIABLE_FILE       FOREIGN KEY(idFile) REFERENCES cppFile(identifier));

-- cppEnum table represents an enumeration.

CREATE TABLE cppEnum (
identifier          INTEGER       NOT NULL,
name                VARCHAR(256)  NOT NULL,
idFile              INTEGER       NOT NULL,
idClass             INTEGER,
accessSpecifier     VARCHAR(64),
lineNumber          INTEGER       NOT NULL,
startBlock          INTEGER,
lengthBlock         INTEGER,

CONSTRAINT PK_ENUM        PRIMARY KEY(identifier),
CONSTRAINT FK_ENUM_FILE   FOREIGN KEY(idFile) REFERENCES cppFile(identifier),
CONSTRAINT FK_ENUM_CLASS  FOREIGN KEY(idClass) REFERENCES cppClass(identifier));

-- cppEnumConstant table represents a parameter.

CREATE TABLE cppEnumConstant (
identifier        INTEGER         NOT NULL,
name              VARCHAR(256),
defaultValue      INTEGER,
idEnum            INTEGER         NOT NULL,
lineNumber        INTEGER         NOT NULL,
startBlock        INTEGER,
lengthBlock       INTEGER,

CONSTRAINT PK_ENUM_CONSTANT       PRIMARY KEY(identifier),
CONSTRAINT FK_ENUM_CONSTANT_ENUM  FOREIGN KEY(idEnum) REFERENCES cppEnum(identifier));

-- cMacro table represents a macro.

CREATE TABLE cMacro (
identifier        INTEGER         NOT NULL,
name              VARCHAR(256),
isConst           INTEGER,
constValue        VARCHAR(256),
idFile            INTEGER         NOT NULL,
lineNumber        INTEGER         NOT NULL,
startBlock        INTEGER,
lengthBlock       INTEGER,

CONSTRAINT PK_MACRO       PRIMARY KEY(identifier),
CONSTRAINT FK_MACRO_FILE  FOREIGN KEY(idFile) REFERENCES cppFile(identifier));

-- cppNotice table represents an error.

CREATE TABLE cppNotice (
identifier      INTEGER           NOT NULL,
description     TEXT              NOT NULL,
category        TEXT,
ruleNumber      INTEGER           NOT NULL,
idFile          INTEGER           NOT NULL,
lineNumber      INTEGER           NOT NULL,
startBlock      INTEGER,
lengthBlock     INTEGER,

CONSTRAINT PK_NOTICE       PRIMARY KEY(identifier),
CONSTRAINT FK_NOTICE_FILE  FOREIGN KEY(idFile) REFERENCES cppFile(identifier));

-- debugTypeInfo table represents type information for debug.

CREATE TABLE debugTypeInfo (
identifier        INTEGER         NOT NULL,
isChar            INTEGER         NOT NULL,
isString          INTEGER         NOT NULL,
isBool            INTEGER         NOT NULL,
isFloat           INTEGER         NOT NULL,
isSigned          INTEGER         NOT NULL,
isWide            INTEGER         NOT NULL,
isPointer         INTEGER         NOT NULL,
isReference       INTEGER         NOT NULL,
isArray           INTEGER         NOT NULL,
isConst           INTEGER         NOT NULL,
isVolatile        INTEGER         NOT NULL,
isStruct          INTEGER         NOT NULL,
isClass           INTEGER         NOT NULL,
isUnion           INTEGER         NOT NULL,
isInterface       INTEGER         NOT NULL,
isEnum            INTEGER         NOT NULL,
isFunction        INTEGER         NOT NULL,
baseName          VARCHAR(256)    NOT NULL,
name              VARCHAR(256)    NOT NULL,
sizeOf            INTEGER         NOT NULL,
typeId            INTEGER         NOT NULL,
arrayDim          INTEGER         NOT NULL,

idPrimitiveType   INTEGER,

CONSTRAINT PK_DEBUGTYPE                        PRIMARY KEY(identifier),
CONSTRAINT FK_DEBUGTYPE_DEBUGTYPE              FOREIGN KEY(idPrimitiveType) REFERENCES debugTypeInfo(identifier));

-- debugFileInfo table represents file information for debug.

CREATE TABLE debugFileInfo (
identifier        INTEGER         NOT NULL,
idText            INTEGER         NOT NULL,
name              VARCHAR(256)    NOT NULL,
compilandPath     VARCHAR(512)    NOT NULL,
checksum          BLOB,

CONSTRAINT PK_DEBUGFILE           PRIMARY KEY(identifier),
CONSTRAINT FK_DEBUGFILE_TEXTFILE  FOREIGN KEY(idText) REFERENCES textFile(rowid));

-- debugFunctionInfo table represents function information for debug.

CREATE TABLE debugFunctionInfo (
identifier        INTEGER         NOT NULL,
name              VARCHAR(256)    NOT NULL,
firstLineNumber   INTEGER         NOT NULL,
lastLineNumber    INTEGER         NOT NULL,
address           INTEGER         NOT NULL,
idReturnType      INTEGER         NOT NULL,
idDebugFile       INTEGER         NOT NULL,

CONSTRAINT PK_DEBUGFUNCTION           PRIMARY KEY(identifier),
CONSTRAINT FK_DEBUGFUNCTION_DEBUGTYPE FOREIGN KEY(idReturnType) REFERENCES debugTypeInfo(identifier),
CONSTRAINT FK_DEBUGFUNCTION_DEBUGFILE FOREIGN KEY(idDebugFile) REFERENCES debugFileInfo(identifier));

-- debugVariableInfo table represents variable information for debug.

CREATE TABLE debugVariableInfo (
identifier        INTEGER         NOT NULL,
category          VARCHAR(256)    NOT NULL,
name              VARCHAR(256)    NOT NULL,
idDebugType       INTEGER         NOT NULL,
idDebugFunction   INTEGER,

CONSTRAINT PK_DEBUGVARIABLE           	   PRIMARY KEY(identifier),
CONSTRAINT FK_DEBUGVARIABLE_DEBUGTYPE      FOREIGN KEY(idDebugType) REFERENCES debugTypeInfo(identifier),
CONSTRAINT FK_DEBUGVARIABLE_DEBUGFUNCTION  FOREIGN KEY(idDebugFunction) REFERENCES debugFunctionInfo(identifier));

-- debugErrorInfo table represents error information for debug.

CREATE TABLE debugErrorInfo (
identifier        INTEGER         NOT NULL,
callStack         VARCHAR(1024),

CONSTRAINT PK_DEBUGERROR          PRIMARY KEY(identifier));

-- debugStubInfo table represents stub information for debug.

CREATE TABLE debugStubInfo (
identifier        INTEGER         NOT NULL,
lineNumber        INTEGER         NOT NULL,
isLineSkipped     INTEGER         NOT NULL,
idDebugFile       INTEGER         NOT NULL,

CONSTRAINT PK_DEBUGSTUB           PRIMARY KEY(identifier),
CONSTRAINT FK_DEBUGSTUB_DEBUGFILE FOREIGN KEY(idDebugFile) REFERENCES debugFileInfo(identifier));

-- debugValueInfo table represents value information for debug.

CREATE TABLE debugValueInfo (
identifier        INTEGER         NOT NULL,
textValue         VARCHAR(1024),
idDebugVariable   INTEGER         NOT NULL, 
idDebugStub       INTEGER,

CONSTRAINT PK_DEBUGVALUE           	PRIMARY KEY(identifier),
CONSTRAINT FK_DEBUGVALUE_DEBUGVARIABLE  FOREIGN KEY(idDebugVariable) REFERENCES debugVariableInfo(identifier),
CONSTRAINT FK_DEBUGVALUE_DEBUGSTUB      FOREIGN KEY(idDebugStub) REFERENCES debugStubInfo(identifier));

