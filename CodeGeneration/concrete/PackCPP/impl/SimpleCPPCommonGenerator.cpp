#include "SimpleCPPCommonGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleCPPCommonGenerator::SimpleCPPCommonGenerator() {

			CreateHeader_R2 =
				str_g("/* \r\n")
				<< " * " << $(0) << "\r\n"
				   " *\r\n"
				   " *\r\n"
				   " * @date " << call_g(getDateHandler("dd-mm-yyyy")) << "\r\n"
				   " * @author " << call_g(getWorkspaceAuthorHandler()) << "\r\n"
				   " * @version " << call_g(getWorkspaceVersionHandler()) << "\r\n"
				   " * " << call_g(getWorkspaceBriefHandler()) << "\r\n"
				   " */\r\n\r\n";

			CreateHPPDefine_R2 = 
				str_g("#ifndef ") << upper_g($(0)) << "\r\n"
				   "#define " << upper_g($(0)) << "\r\n\r\n";

			CreateHPPEndDefine_R2 = 
				str_g("#endif\r\n");

			CreateNamespace_R2 =
				str_g("NAMESPACE_BEGIN(") << $(0) << ")\r\n\r\n";

			CreateEndNamespace_R2 =
				str_g("NAMESPACE_END\r\n\r\n");

			CreateMacro_R2 =
				str_g("#define A(str) encode<EncodingT,ansi>(str)"    "\r\n"
					  "#define C(str) encode<ansi,EncodingT>(str)"    "\r\n\r\n");

			CreateEndMacro_R2 = 
				str_g("#undef C"     "\r\n"
					  "#undef A"     "\r\n\r\n");

			ExportAPI_R2 =
				upper_g(call_g(getWorkspaceNameHandler())) << "_API ";

			CreateExportTClass_R2 =
				str_g("template <class EncodingT>\r\n"
				  "class ") << $(4) << " _" << $(0) << " {\r\n"
				  "private :\r\n"
				<< $(1)
				<< "\tCategory*\tm_logger;\r\n\r\n"
				   "protected :\r\n"
				<< $(2)
				<< "public :\r\n"
				<< $(3)
				<< "};\r\n\r\n"
				   "typedef _" << $(0) << "<ucs> Uni" << $(0) << ";\r\n"
				   "typedef _" << $(0) << "<ansi> " << $(0) << ";\r\n\r\n";

			CreateTClass_R2 =
				CreateExportTClass_R2($(0), $(1), $(2), $(3), str_g(""));

			CreateExportClass_R2 =
				str_g("class ") << $(3) << " " << $(0) << " {\r\n"
				  "private :\r\n"
				<< $(1)
				<< "\tCategory*\t\t\t\t\t\tm_logger;\r\n\r\n"
				   "public :\r\n"
				<< $(2)
				<< "};\r\n\r\n";

			CreateClass_R2 =
				CreateExportClass_R2($(0), $(1), $(2), str_g(""));

			CreateExportInternClass_R2 =
				str_g("template<class EncodingT>\r\n"
					  "class ") << $(4) << " " << $(0) << "::" << $(1) << " {\r\n"
				  "private :\r\n"
				<< $(2)
				<< "public :\r\n"
				<< $(3)
				<< "};\r\n\r\n";

			CreateInternClass_R2 =
				CreateExportInternClass_R2($(0), $(1), $(2), $(3), str_g(""));

			MemberName_R2 =
				str_g("m_") << $(0);

			Member_R2 =
				ch_g('\t') << $(0) << '\t' << $(1) << ";\r\n";

			CreateInlineMethod_R2 = 
				str_g("\t") << $(0) << " " << $(1) << "(" << $(2) << ") " << $(3) << " \r\n\t{"
				<< $(4)
				<< "\r\n\t}\r\n\r\n";

			CreateInlineGetMethod_R2 = 
				CreateInlineMethod_R2( $(0), str_g("get") << $(1), str_g(""), str_g("const"), $(2) );

			CreateInlineSetMethod_R2 = 
				CreateInlineMethod_R2( str_g("void"), str_g("set") << $(0), $(1), str_g(""), $(2) );

			IndentationInlineMethod_R2 = 
				line() << htab_g(2);

			CreateInlineConstructor_R2 =
				str_g("\t") << $(0) << "(" << $(1) << ")\r\n\t"
				<< $(2)
				<< "{\r\n"
				   "\t\tm_logger = &Category::getInstance(LOGNAME);\r\n"
				   "\t\tm_logger->debugStream() << \"constructor " << $(0) << " \""
				<< $(3)
				<< ";\r\n\t"
				   "}\r\n\r\n";

			CreateInlineTConstructor_R2 =
				CreateInlineConstructor_R2(ch_g('_') << $(0), $(1), $(2), $(3));

			CreateInternConstructor_R2 =
				str_g("\t") << $(0) << "(" << $(1) << ")\r\n\t"
				<< $(2)
				<< "{\r\n\t"
				   "}\r\n\r\n";

			CreateTConstructor_R2 =
				str_g("template<class EncodingT>\r\n_") 
				<< $(0) << "<EncodingT>::_" << $(0) << "(" << $(1) << ")\r\n"
				<< $(2)
				<< "{\r\n"
				   "\tm_logger = &Category::getInstance(LOGNAME);\r\n"
				   "\tm_logger->debugStream() << \"constructor " << $(0) << " \""
				<< $(3)
				<< ";\r\n"
				   "}\r\n\r\n";

			CreateTDestructor_R2 =
				str_g("template<class EncodingT>\r\n_") 
				<< $(0) << "<EncodingT>::~_" << $(0) << "()\r\n"
				   "{"
				<< $(1)
				<< "\r\n\tm_logger = NULL;\r\n"
				   "}\r\n\r\n";

			CreateInit_R2 =
				+ch_g(':') << ~+ch_g(' ') 
				<< ' ' << $(0) << '(' << $(1) << ')' << ~-str_g(",") << "\r\n\t";

			CreatePrint_R2 =
				str_g("\r\n\t\t\t\t<< ") 
				<< $(0)                         [If_IsNUMBER_R2]
				<< ConvertToAString_R2($(0))    [If_IsTEXT_R2]
				<< " << ' '";

			CreateTMethod_R2 = 
				str_g("template<class EncodingT>\r\n")
				<< $(0) << "\r\n" << $(1) << "::" << $(2) << "(" << $(3) << ") " << $(4) << " \r\n{"
				<< $(5)
				<< "\r\n}\r\n\r\n";

			CreateGetTMethod_R2 = 
				CreateTMethod_R2( $(0), $(1), str_g("get") << $(2), str_g(""), str_g("const"), $(3) );

			CreateSetTMethod_R2 = 
				CreateTMethod_R2( str_g("void"), $(0), str_g("set") << $(1), $(2), str_g(""), $(3) );

            CreateTypedef_R2 =
                str_g("\ttypedef ") << $(0) << "\t" << $(1) << ";\r\n";

			IndentationMethod_R2 = 
				line() << htab();

			CommaParam_R2 =
				str_g(",\r\n\t\t\t\t");

			SpaceParam_R2 =
				str_g(" ");

			InitializeConnection_R2 =
				str_g("\r\n\t"
					  "_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();\r\n\t"
					  "if (!connection) {"                                                 "\r\n\t\t"
					  "m_logger->errorStream() << \"DB connection is not initialized.\";    \r\n\t\t"
					  "throw NullPointerException(\"DB connection is not initialized.\");   \r\n\t"
					  "}");

			UEntity_R2 =
                upper_g(ent_g(getEntityNameHandler(KIND_ALIAS)),0,1);

			LEntity_R2 =
                lower_g(ent_g(getEntityNameHandler(KIND_ALIAS)),0,1);

			URelationN_R2 =
                upper_g(rel_g(getRelationTargetHandler(KIND_ALIAS)),0,1);

			LRelationN_R2 =
                lower_g(rel_g(getRelationTargetHandler(KIND_ALIAS)),0,1);

            URelationNName_R2 =
                upper_g(rel_g(getRelationNameHandler(KIND_ALIAS)),0,1) [If_HasRelationNName_R2]
                << URelationN_R2                                       [else_g()];

            LRelationNName_R2 =
                lower_g(rel_g(getRelationNameHandler(KIND_ALIAS)),0,1) [If_HasRelationNName_R2]
                << LRelationN_R2                                       [else_g()];

			URelation1_R2 =
                upper_g(rel_g(getRelationSourceHandler(KIND_ALIAS)),0,1);

			LRelation1_R2 =
                lower_g(rel_g(getRelationSourceHandler(KIND_ALIAS)),0,1);

            URelation1Name_R2 =
                upper_g(rel_g(getRelationTargetRefHandler(KIND_ALIAS)),0,1) [If_HasRelation1Name_R2]
                << URelation1_R2                                            [else_g()];

            LRelation1Name_R2 =
                lower_g(rel_g(getRelationTargetRefHandler(KIND_ALIAS)),0,1) [If_HasRelation1Name_R2]
                << LRelation1_R2                                            [else_g()];

			UAccess_R2 =
				UEntity_R2 << "Access";

			LAccess_R2 =
				LEntity_R2 << "Access";

			EncodingClass_R2 =
				ch_g('_') << $(0) << "<EncodingT>";

			EntityClass_R2 = 
				EncodingClass_R2(UEntity_R2);

			RelationNClass_R2 = 
				str_g("boost::shared_ptr< ") << EncodingClass_R2(URelationN_R2) << " >";

			Relation1Class_R2 = 
				EncodingClass_R2(URelation1_R2);

			AccessClass_R2 = 
				EncodingClass_R2(UAccess_R2);    

			EncodingClassDeclaration_R2 =
				str_g("template <class EncodingT>\r\n")
				<< "class _" << $(0) << ";\r\n\r\n";

			EntityClassDeclaration_R2 =
				EncodingClassDeclaration_R2(UEntity_R2);

			Relation1ClassDeclaration_R2 =
				EncodingClassDeclaration_R2(URelation1_R2);

			RelationNClassDeclaration_R2 =
				EncodingClassDeclaration_R2(URelationN_R2);

			AccessClassDeclaration_R2 =
				EncodingClassDeclaration_R2(UAccess_R2);

			EntityPointer_R2 =
				"boost::shared_ptr< " << EntityClass_R2 << " >";

			EntityReference_R2 =
				EntityClass_R2 << "&";

			EntityConstReference_R2 =
				str_g("const ") << EntityReference_R2;

			RelationNType_R2 = 
                str_g("vector_") << LRelationNName_R2;

			RelationNMemberName_R2 =
                MemberName_R2(LRelationNName_R2) << "s";

			RelationNMember_R2 =
				Member_R2(RelationNType_R2, RelationNMemberName_R2);    

			RelationNTypedef_R2 =
                CreateTypedef_R2("std::vector< " <<  RelationNClass_R2  << " >", RelationNType_R2);

			RelationNIterator_R2 =
                URelationNName_R2 << "Iterator";

			RelationNConstIterator_R2 =
                URelationNName_R2 << "ConstIterator";

			RelationNConstReference_R2 =
				str_g("const ") << RelationNReference_R2;

			RelationNReference_R2 =
				RelationNClass_R2 << "&";

			Relation1ConstReference_R2 =
				str_g("const ") << Relation1Reference_R2;

			Relation1Reference_R2 =
				Relation1Class_R2 << "&";

			If_IsNotNULL_R2 =
				rel_g(getIsRelationMultiplicityHandler(RELATION_ONE));

			// Attributes management
            URawAttribute_R2 =
                upper_g(attr_g(getAttributeNameHandler(KIND_NAME)),0,1)        [!If_IsREF_R2]
                << upper_g(rel_g(getRelationSourceRefHandler(KIND_NAME)),0,1)  [relationsByAttr(FILTER_TARGET)]
                                                                               [If_IsREF_R2];

            UAttribute_R2 =
                upper_g(attr_g(getAttributeNameHandler(KIND_ALIAS)),0,1)       [!If_IsREF_R2 || attr_g(getHasAttributeAliasHandler())]
                << URelation1_R2                                               [relationsByAttr(FILTER_TARGET)][else_g()];

            LAttribute_R2 =
                lower_g(attr_g(getAttributeNameHandler(KIND_ALIAS)),0,1)       [!If_IsREF_R2 || attr_g(getHasAttributeAliasHandler())]
                << LRelation1_R2                                               [relationsByAttr(FILTER_TARGET)][else_g()];

			AttributeValueType_R2 =
				(str_g("bool")                            [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))])
                << (str_g("unsigned char")                [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))])
                << (str_g("char")                         [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))])
                << (str_g("typename EncodingT::char_t")   [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))])
                << (str_g("typename ansi::char_t")        [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))])
                << (str_g("typename ucs::char_t")         [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_INT))])
                << (str_g("unsigned int")                 [attr_g(getIsAttributeTypeHandler(ATTR_UINT))])
                << (str_g("short")                        [attr_g(getIsAttributeTypeHandler(ATTR_INT16))])
                << (str_g("unsigned short")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))])
                << (str_g("long")                         [attr_g(getIsAttributeTypeHandler(ATTR_INT32))])
                << (str_g("unsigned long")                [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))])
                << (str_g("long long")                    [attr_g(getIsAttributeTypeHandler(ATTR_INT64))])
                << (str_g("unsigned long long")           [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))])
                << (str_g("float")                        [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))])
                << (str_g("double")                       [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))])
                << (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_STRING))])
                << (str_g("typename ansi::string_t")      [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))])
                << (str_g("typename ucs::string_t")       [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))])
				<< (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))])
                << (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_TIME))])
				<< (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_DATE))])
				<< (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                << (str_g("boost::container::vector<unsigned char>")    [attr_g(getIsAttributeTypeHandler(ATTR_BINARY))]);

            AttributeClassName_R2 =
                URelation1_R2                               [relationsByAttr(FILTER_TARGET)][If_IsREF_R2];

			AttributeType_R2 = 
                AttributeValueType_R2                       [!If_IsREF_R2]
                << (str_g("boost::shared_ptr< ") << EncodingClass_R2(AttributeClassName_R2) << " >")
                                                            [If_IsREF_R2];

			AttributeClass_R2 =
                EncodingClass_R2(AttributeClassName_R2)     [If_IsREF_R2];

			Reference_R2 =
				$(0)                [If_IsNUMBER_R2]
				<< ($(0) << "&")    [If_IsGROUP_R2];

			ConstReference_R2 =
				$(0)                                        [If_IsNUMBER_R2]
				<< (str_g("const ") << Reference_R2($(0)))  [If_IsGROUP_R2];

			AttributeConstReference_R2 =
                ConstReference_R2(AttributeType_R2)         [!If_IsREF_R2]
                << (AttributeType_R2)                       [If_IsREF_R2];

			AttributeReference_R2 =
                Reference_R2(AttributeType_R2)              [!If_IsREF_R2]
                << (AttributeType_R2 << "&")                [If_IsREF_R2];

			If_IsNUMBER_R2 =
				attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN)) ||
                attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))   ||
                attr_g(getIsAttributeTypeHandler(ATTR_BYTE))    ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT))     ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT))    ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT16))   ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT16))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT32))   ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT32))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT64))   ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT64))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE));

			If_IsTEXT_R2 =
                attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))   ||
                attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))   ||
                attr_g(getIsAttributeTypeHandler(ATTR_CHAR))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_STRING))     ||
                attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING)) ||
                attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING)) ||
                attr_g(getIsAttributeTypeHandler(ATTR_TEXT))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_TIME))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_DATE))       ||
				attr_g(getIsAttributeTypeHandler(ATTR_ANY));

            If_IsGROUP_R2 =
                If_IsTEXT_R2                                ||
                attr_g(getIsAttributeTypeHandler(ATTR_BINARY));

			If_IsID_R2 =
				attr_g(getIsAttributeModifierHandler(ATTR_ID));

			If_IsREF_R2 =
				attr_g(getIsAttributeModifierHandler(ATTR_REF));

			If_IsAUTO_R2 =
				attr_g(getIsAttributeModifierHandler(ATTR_AUTO)); 

			If_IsCONST_R2 =
				attr_g(getIsAttributeModifierHandler(ATTR_CONST));

			If_IsDATA_R2 =
				ent_g(getIsEntityClassHandler(ENTITY_DATA));

			If_IsFUNCTION_R2 =
				ent_g(getIsEntityClassHandler(ENTITY_FUNCTION));

            If_IsInitializable_R2 =
                attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))     ||
                attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_BYTE))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT))         ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT16))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT16))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT32))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT32))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT64))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT64))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_CHAR))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))    ||
                attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))    ||
                attr_g(getIsAttributeTypeHandler(ATTR_STRING))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_TEXT))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_TIME))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_DATE))        ||
				attr_g(getIsAttributeTypeHandler(ATTR_ANY));

            If_IsComparable_R2 =
                attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))     ||
                attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_BYTE))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT))         ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT16))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT16))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT32))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT32))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT64))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT64))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))    ||
                attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))    ||
                attr_g(getIsAttributeTypeHandler(ATTR_CHAR))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_STRING))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_TEXT))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_TIME))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_DATE))        ||
				attr_g(getIsAttributeTypeHandler(ATTR_ANY));

            If_IsPrintable_R2 =
                attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))     ||
                attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_BYTE))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT))         ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT16))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT16))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT32))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT32))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_INT64))       ||
                attr_g(getIsAttributeTypeHandler(ATTR_UINT64))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_CHAR))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))    ||
                attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))    ||
                attr_g(getIsAttributeTypeHandler(ATTR_STRING))      ||
                attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))  ||
                attr_g(getIsAttributeTypeHandler(ATTR_TEXT))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_TIME))        ||
                attr_g(getIsAttributeTypeHandler(ATTR_DATE))        ||
				attr_g(getIsAttributeTypeHandler(ATTR_ANY));

            If_HasRelationNName_R2 =
                rel_g(getHasRelationAliasHandler());

            If_HasRelation1Name_R2 =
                rel_g(getHasRelationTargetRefAliasHandler());

			AttributeMemberName_R2 =
				MemberName_R2(LAttribute_R2);

			AttributeMember_R2 =
				Member_R2(AttributeType_R2, AttributeMemberName_R2);

			AttributeInit_R2 =
                AttributeCopy_R2($(0));

			AttributeAccessor_R2 =
				$(0)                                                            [!If_IsREF_R2]
				<< ( $(0) << "->get" 
				<< UAttribute_R2                                                [If_IsID_R2]
                                                                                [attr0, attrN]
                                                                                [entitiesByRel(FILTER_SOURCE)]
                                                                                [relationsByAttr(FILTER_TARGET)]
				<< "()")                                                        [If_IsREF_R2];

            AttributeId_R2 =
                ($(0)                                                           [!If_IsREF_R2]
                << ( $(0)
                << (~+("->get" << URelation1Name_R2 << "()")
                << -("->get" << upper_g(rel_g(getRelationSourceRefHandler(KIND_NAME)),0,1) << "()"))
                                                                                [ReferencedRelations_R2])
                                                                                [If_IsREF_R2])
                                                                                [If_IsID_R2];

			AttributeValueMember_R2 =
				Member_R2(AttributeValueType_R2, AttributeMemberName_R2);

			AttributeVariable_R2 =
				$(0);

			AttributeAssignment_R2 =
				$(0) << str_g(" = ") << $(1);

            AttributeCopy_R2 =
				("copy_ptr(" << $(0) << ")")    
                        [If_IsREF_R2 && If_IsID_R2 && has_g(1, set_g((attr0, attrN), If_IsREF_R2 && If_IsID_R2), eq_g())]
                << $(0) [else_g()];

			AttributeIDParam_R2 =
				(AttributeConstReference_R2 << SpaceParam_R2 << LAttribute_R2 << ~-CommaParam_R2)    
															[If_IsID_R2][attr0, attrN];

			AttributeIDParamName_R2 =
				( LAttribute_R2 << ~-str_g(", ") )          [If_IsID_R2][attr0, attrN];

			ConvertToAString_R2 =
				( str_g("ToString::parse(")    << $(0) << ")" )    [If_IsNUMBER_R2]
				<< ( str_g("A(") << $(0) << ")" )                  [If_IsTEXT_R2];

			ConvertToType_R2 =
				( str_g("Convert< ") << AttributeValueType_R2
				<< " >::parse(A(" << $(0) << "))" )                [!If_IsTEXT_R2]
				<< $(0)                                            [If_IsTEXT_R2];

			ConvertToCString_R2 =
				( str_g("C(ToString::parse(") << $(0) << "))" )    [!If_IsTEXT_R2]
				<< $(0)                                            [If_IsTEXT_R2];

			Accessor_R2 =
				$(0) << "->get" << UAttribute_R2 << "()";

            RelationAccessor_R2 =
                $(0) << "->get" << URelation1Name_R2 << "()";

			IDParamName_R2 =
                ( $(0) << ~-str_g(", ") )                   [If_IsID_R2][attr0, attrN];

            AddDataParameter_R2 =
                ($(0) << ".addText( " << $(1) << " );")     [If_IsTEXT_R2]
                << ($(0) << ".addInt( " << $(1) << " );")
				                [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN)) ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))   ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_BYTE))    ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_INT))     ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_UINT))    ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_INT16))   ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_UINT16))  ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_INT32))   ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                 << ($(0) << ".addInt64( " << $(1) << " );")
                                 [attr_g(getIsAttributeTypeHandler(ATTR_INT64))   ||
                                  attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << ($(0) << ".addDouble( " << $(1) << " );")
                                [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))  ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << ($(0) << ".addBlob( " << $(1) << " );")
                                [attr_g(getIsAttributeTypeHandler(ATTR_BINARY))];

            GetDataStatement_R2 =
                ($(0) << ".getText( " << $(1) << ", "<< $(2) << " )")   [If_IsTEXT_R2]
                << ($(0) << ".getInt( " << $(1) << ", "<< $(2) << " )")
				                [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN)) ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))   ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_BYTE))    ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_INT))     ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_UINT))    ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_INT16))   ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_UINT16))  ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_INT32))   ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                 << ($(0) << ".getInt64( " << $(1) << ", "<< $(2) << " )")
                                 [attr_g(getIsAttributeTypeHandler(ATTR_INT64))   ||
                                  attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << ($(0) << ".getDouble( " << $(1) << ", "<< $(2) << " )")
                                [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))  ||
                                 attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << ($(0) << ".getBlob( " << $(1) << ", "<< $(2) << " )")
                                [attr_g(getIsAttributeTypeHandler(ATTR_BINARY))];

			DataStatementType_R2 =
				(str_g("int")                             [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_INT))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_UINT))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_INT16))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_INT32))])
                << (str_g("int")                          [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))])
                << (str_g("long long")                    [attr_g(getIsAttributeTypeHandler(ATTR_INT64))])
                << (str_g("long long")                    [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))])
                << (str_g("double")                       [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))])
                << (str_g("double")                       [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))])
                << (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_STRING))])
                << (str_g("typename ansi::string_t")      [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))])
                << (str_g("typename ucs::string_t")       [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))])
				<< (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))])
                << (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_TIME))])
				<< (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_DATE))])
				<< (str_g("typename EncodingT::string_t") [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                << (str_g("boost::container::vector<unsigned char>")    [attr_g(getIsAttributeTypeHandler(ATTR_BINARY))]);

            If_HasREF_ID_R2 =
                has_g(0, set_g((attr0,attrN), If_IsID_R2 && If_IsREF_R2), gt_g());

            If_HasUniqueID_R2 =
                has_g(1, set_g((attr0, attrN), If_IsID_R2), eq_g());

			ListRelationPA_R2 =
                $(0)                            [set_g(relationsByEnt(FILTER_SOURCE), 
                                                       has_g(0, set_g(entitiesByRel(FILTER_TARGET|FILTER_ERASE_REF)*(attr0,attrN),
                                                       callT_g<CONTEXT_PRODUCT(rel_context,attr_context)>(getIsAttributeModifierHandler(ATTR_ID))), eq_g()))];

			ListRelationPB_R2 =
                $(0)                            [If_IsREF_R2 && If_IsID_R2]
								                [attr0, attrN]
                                                [If_HasUniqueID_R2];

			ListRelationN_R2 =
                $(0)                            [set_g(relationsByEnt(FILTER_SOURCE), 
                                                       has_g(0, set_g(entitiesByRel(FILTER_TARGET|FILTER_ERASE_REF)*(attr0,attrN),
                                                       callT_g<CONTEXT_PRODUCT(rel_context,attr_context)>(getIsAttributeModifierHandler(ATTR_ID))), gt_g()))];

			ListRelation1_R2 =
				$(0)                            [relationsByAttr(FILTER_TARGET)]    
												[If_IsREF_R2]
												[attr0, attrN];

            ListAttribute_R2 =
                $(0)                            [attr0, attrN];

            GetReferencedAttribute_R2 =
                $(1)                                                            [!If_IsREF_R2]
                << ($(0) << GetReferencedAttribute_R2($(0),$(1),$(2))           [set_g((attr0, attrN), If_IsID_R2)]
                                                                                [entitiesByRel(FILTER_SOURCE)]
                                                                                [relationsByAttr(FILTER_TARGET)]
                << $(2))                                                        [If_IsREF_R2];

            RelationN = 
                set_g(relationsByEnt(FILTER_SOURCE), has_g(0, set_g(entitiesByRel(FILTER_TARGET|FILTER_ERASE_REF)*(attr0,attrN),
                                                     callT_g<CONTEXT_PRODUCT(rel_context,attr_context)>(getIsAttributeModifierHandler(ATTR_ID))), gt_g()));

            ReferencedEntity_R2 =
                relationsByAttr(FILTER_TARGET)*entitiesByRel(FILTER_SOURCE);

            ReferencedRelations_R2 =
                relationsByAttr(FILTER_TARGET) + (set_g(ReferencedEntity_R2,If_HasUniqueID_R2)*(set_g((attr0,attrN), If_IsID_R2&&If_IsREF_R2)*ReferencedRelations_R2));

		}
    }
}
