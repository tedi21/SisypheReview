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
DROP TABLE textNotice;
DROP TABLE debugFileInfo;
DROP TABLE debugFunctionInfo;
DROP TABLE debugVariableInfo;

-- Creation Virtual Table
--________________

-- Table using FTS4 describes data type for source generation. These information are not used by sqlite.

-- textFile table represents a text file

CREATE VIRTUAL TABLE textFile USING fts4 (
content     TEXT        NOT NULL);

CREATE VIRTUAL TABLE textNotice USING fts4 (
description     TEXT        NOT NULL,
category        TEXT,       
lineNumber      INT         NOT NULL,
idText          INT         NOT NULL,
startBlock      INT,
lengthBlock     INT,

CONSTRAINT FK_TEXTNOTICE_TEXTFILE FOREIGN KEY(idText) REFERENCES textFile(rowid));

-- Creation Table
--________________

-- cppFileType table represents a type of file : header or source.

CREATE TABLE cppFileType (
identifier      INT         NOT NULL,
string      VARCHAR(10)     NOT NULL,

CONSTRAINT PK_FILETYPE  PRIMARY KEY(identifier));

INSERT INTO cppFileType (identifier, string) VALUES (1, 'header');
INSERT INTO cppFileType (identifier, string) VALUES (2, 'source');

-- cppFile table represents a file.

CREATE TABLE cppFile (
idText        INT             NOT NULL,
path          VARCHAR(512)    NOT NULL,
name          VARCHAR(256)    NOT NULL,
idType        INT             NOT NULL,
linesCount    INT             NOT NULL,

CONSTRAINT PK_FILE          PRIMARY KEY(idText),
CONSTRAINT FK_FILE_FILETYPE FOREIGN KEY(idType) REFERENCES cppFileType(identifier),
CONSTRAINT FK_FILE_TEXTFILE FOREIGN KEY(idText) REFERENCES textFile(rowid));

-- cppInclude table represents an include in cpp file.

CREATE TABLE cppInclude (
identifier        INT             NOT NULL,
fileName          VARCHAR(256)    NOT NULL,
idFile            INT             NOT NULL,

CONSTRAINT PK_INCLUDE       PRIMARY KEY(identifier),
CONSTRAINT FK_INCLUDE_FILE  FOREIGN KEY(idFile) REFERENCES cppFile(idText));

-- cppClass table represents a class.

CREATE TABLE cppClass (
identifier        INT             NOT NULL,
name              VARCHAR(256)    NOT NULL,
isStruct          INT,
isInterface       INT,
isAbstract        INT,
linesCount        INT,
idFile            INT             NOT NULL,
lineNumber        INT             NOT NULL,
startBlock        INT,
lengthBlock       INT,

CONSTRAINT PK_CLASS       PRIMARY KEY(identifier),
CONSTRAINT FK_CLASS_FILE  FOREIGN KEY(idFile) REFERENCES cppFile(idText));

-- cppInheritance table represents an inheritance.

CREATE TABLE cppInheritance (
identifier        INT             NOT NULL,
idDerived         INT             NOT NULL,
baseClassName     VARCHAR(256)    NOT NULL,
baseAccess        VARCHAR(256),

CONSTRAINT PK_INHERITANCE           PRIMARY KEY(identifier),
CONSTRAINT FK_INHERITANCE_DERIVED   FOREIGN KEY(idDerived) REFERENCES cppClass(identifier));

-- cppFunction table represents a function.

CREATE TABLE cppFunction (
identifier        INT             NOT NULL,
name              VARCHAR(256)    NOT NULL,
idClass           INT,
accessSpecifier   VARCHAR(64),
returnType        VARCHAR(256),
isConst           INT,
isVirtual         INT,
isVirtualPure     INT,
isStatic          INT,
isOperator        INT,
isDestructor      INT,
isConstructor     INT,
isVariadic        INT,
signature         VARCHAR(256)    NOT NULL,
idDecFile         INT             NOT NULL,
startDecBlock     INT,
lengthDecBlock    INT,
decLineNumber     INT             NOT NULL,
linesCount        INT,
complexity        INT,
idDefFile         INT             NOT NULL,
defLineNumber     INT             NOT NULL,
startDefBlock     INT,
lengthDefBlock    INT,

CONSTRAINT PK_FUNCTION            PRIMARY KEY(identifier),
CONSTRAINT FK_FUNCTION_CLASS      FOREIGN KEY(idClass) REFERENCES cppClass(identifier),
CONSTRAINT FK_FUNCTION_DEC_FILE   FOREIGN KEY(idDecFile)  REFERENCES cppFile(idText),
CONSTRAINT FK_FUNCTION_DEF_FILE   FOREIGN KEY(idDefFile)  REFERENCES cppFile(idText));

-- cppParameter table represents a parameter.

CREATE TABLE cppParameter (
identifier        INT         NOT NULL,
paramOrder        INT         NOT NULL,
paramType         VARCHAR(256),
defaultValue      VARCHAR(256),
idFunction        INT         NOT NULL,
decName           VARCHAR(256),
startDecBlock     INT,
lengthDecBlock    INT,
defName           VARCHAR(256),
startDefBlock     INT,
lengthDefBlock    INT,

CONSTRAINT PK_PARAMETER           PRIMARY KEY(identifier),
CONSTRAINT FK_PARAMETER_FUNCTION  FOREIGN KEY(idFunction) REFERENCES cppFunction(identifier));

-- cppAttribute table represents an attribute.

CREATE TABLE cppAttribute (
identifier        INT             NOT NULL,
attrType          VARCHAR(256),
name              VARCHAR(256)    NOT NULL,
accessSpecifier   VARCHAR(64),
isStatic          INT,
isConst           INT,
constValue        VARCHAR(256),
idClass           INT             NOT NULL,
lineNumber        INT             NOT NULL,
startBlock        INT,
lengthBlock       INT,

CONSTRAINT PK_ATTRIBUTE         PRIMARY KEY(identifier),
CONSTRAINT FK_ATTRIBUTE_CLASS   FOREIGN KEY(idClass) REFERENCES cppClass(identifier));

-- cppVariable table represents a variable.

CREATE TABLE cppVariable (
identifier        INT             NOT NULL,
varType           VARCHAR(256),
name              VARCHAR(256)    NOT NULL,
isStatic          INT,
isConst           INT,
idFunction        INT             NOT NULL,
lineNumber        INT             NOT NULL,
startBlock        INT,
lengthBlock       INT,

CONSTRAINT PK_VARIABLE            PRIMARY KEY(identifier),
CONSTRAINT FK_VARIABLE_FUNCTION   FOREIGN KEY(idFunction) REFERENCES cppFunction(identifier));

-- cppEnum table represents an enumeration.

CREATE TABLE cppEnum (
identifier          INT           NOT NULL,
name                VARCHAR(256)  NOT NULL,
idFile              INT           NOT NULL,
lineNumber          INT           NOT NULL,
startBlock          INT,
lengthBlock         INT,

CONSTRAINT PK_ENUM        PRIMARY KEY(identifier),
CONSTRAINT FK_ENUM_FILE   FOREIGN KEY(idFile) REFERENCES cppFile(idText));

-- cppEnumConstant table represents a parameter.

CREATE TABLE cppEnumConstant (
identifier        INT       NOT NULL,
name              VARCHAR(256),
defaultValue      INT,
idEnum            INT       NOT NULL,
startBlock        INT,
lengthBlock       INT,

CONSTRAINT PK_ENUM_CONSTANT       PRIMARY KEY(identifier),
CONSTRAINT FK_ENUM_CONSTANT_ENUM  FOREIGN KEY(idEnum) REFERENCES cppEnum(identifier));

-- cMacro table represents a macro.

CREATE TABLE cMacro (
identifier        INT       NOT NULL,
name              VARCHAR(256),
isConst           INT,
constValue        VARCHAR(256),
idFile            INT       NOT NULL,
lineNumber        INT       NOT NULL,
startBlock        INT,
lengthBlock       INT,

CONSTRAINT PK_MACRO       PRIMARY KEY(identifier),
CONSTRAINT FK_MACRO_FILE  FOREIGN KEY(idFile) REFERENCES cppFile(idText));

-- debugFileInfo table represents file information for debug.

CREATE TABLE debugFileInfo (
identifier        INT             NOT NULL,
compilandPath     VARCHAR(512)    NOT NULL,
checksum	  BLOB,
idFile            INT             NOT NULL,

CONSTRAINT PK_DEBUGFILE       PRIMARY KEY(identifier),
CONSTRAINT FK_DEBUGFILE_FILE  FOREIGN KEY(idFile) REFERENCES cppFile(idText));

-- debugFunctionInfo table represents function information for debug.

CREATE TABLE debugFunctionInfo (
identifier        INT             NOT NULL,
lineNumber        INT             NOT NULL,
address           INT             NOT NULL,
debugStart        INT             NOT NULL,
debugEnd          INT             NOT NULL,
idFunction        INT             NOT NULL,

CONSTRAINT PK_DEBUGFUNCTION           PRIMARY KEY(identifier),
CONSTRAINT FK_DEBUGFUNCTION_FUNCTION  FOREIGN KEY(idFunction) REFERENCES cppFunction(identifier));

-- debugVariableInfo table represents variable information for debug.

CREATE TABLE debugVariableInfo (
identifier        INT             NOT NULL,
category          VARCHAR(256)    NOT NULL,
type              VARCHAR(256)    NOT NULL,
name              VARCHAR(256)    NOT NULL,
textValue         VARCHAR(256),
idDebugFunction   INT             NOT NULL,

CONSTRAINT PK_DEBUGVARIABLE           	   PRIMARY KEY(identifier),
CONSTRAINT FK_DEBUGVARIABLE_DEBUGFUNCTION  FOREIGN KEY(idDebugFunction) REFERENCES debugFunctionInfo(identifier));
