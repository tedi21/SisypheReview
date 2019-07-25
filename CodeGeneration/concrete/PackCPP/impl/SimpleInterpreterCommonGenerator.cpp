#include "SimpleInterpreterCommonGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleInterpreterCommonGenerator::SimpleInterpreterCommonGenerator() {

			ListEntityIDParam_R2 =
				$(0)    [If_IsID_R2]
						[attr0, attrN];

			ListRelationIDParam_R2 =
				$(0)    [If_IsID_R2]
						[attr0, attrN]
						[entitiesByRel(FILTER_TARGET|FILTER_ERASE_REF)];	

			ListEntityParam_R2 =
				($(0)    [!If_IsREF_R2 && !If_IsID_R2]
						 [attr0, attrN])
						 [If_HasAttribute_R2]
				<< ($(0) [!If_IsREF_R2 || If_IsID_R2]
						 [attr0, attrN])
						 [If_HasReferenceID_R2];						
						
			EntityIDParamSize_R2 =
				size_g(set_g((attr0,attrN), If_IsID_R2));

			FillRelationParamSize_R2 =
				(math_g(cast_g<int>(size_g(set_g((attr0,attrN), If_IsID_R2))) + 2))
                         [entitiesByRel(FILTER_TARGET|FILTER_ERASE_REF)];

			SelectOneParamSize_R2 =
				math_g(cast_g<int>(size_g(set_g((attr0,attrN), If_IsID_R2))) + 1);

			CreateIDParam_R2 =
				ListEntityIDParam_R2(str_g("boost::shared_ptr< Base<EncodingT> > const& ") << LAttribute_R2 << ~-CommaParam_R2);		

			CreateConstructorParam_R2 =
				ListEntityParam_R2(str_g("boost::shared_ptr< Base<EncodingT> > const& ") << LAttribute_R2 << ~-CommaParam_R2);
				
			EntityParamSize_R2 = 
				(size_g(set_g((attr0,attrN), !If_IsREF_R2 && !If_IsID_R2)))    [If_HasAttribute_R2]
				<< (size_g(set_g((attr0,attrN), !If_IsREF_R2 || If_IsID_R2)))  [If_HasReferenceID_R2];	

            AttributeInterpreterTypeName_R2 =
                ((str_g("Bool")                    [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_INT))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_INT16))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_INT32))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_INT64))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))])
                << (str_g("Numeric")               [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_STRING))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_TIME))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_DATE))])
                << (str_g("String")                [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                << (str_g("Array[Numeric]")        [attr_g(getIsAttributeTypeHandler(ATTR_BINARY))]))
                                                   [!If_IsREF_R2]
                << (AttributeClassName_R2)         [If_IsREF_R2];

			AttributeInterpreterType_R2 =
                (str_g("boost::shared_ptr< Base<EncodingT> >( new ")
                    << (AttributeInterpreterTypeName_R2)        [!If_IsREF_R2]
                    << (AttributeClassName_R2 << "Interpreter") [If_IsREF_R2]
				<< "<EncodingT>(" << $(0) << ") )")[If_IsREF_R2 || !attr_g(getIsAttributeTypeHandler(ATTR_BINARY))]
                << (str_g("convert_numeric_array<EncodingT>(") << $(0) << ")")
                                                   [!If_IsREF_R2 && attr_g(getIsAttributeTypeHandler(ATTR_BINARY))];

			AttributeCheck_R2 =
				((str_g("check_bool(")                      [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))])
                << (str_g("check_char<EncodingT>(")         [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))])
                << (str_g("check_char<ansi>(")              [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))])
                << (str_g("check_char<ucs>(")               [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_INT))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_INT16))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_INT32))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_INT64))])
                << (str_g("check_numeric_i(")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))])
                << (str_g("check_numeric_d(")               [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))])
                << (str_g("check_numeric_d(")               [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))])
                << (str_g("check_string<EncodingT>(")       [attr_g(getIsAttributeTypeHandler(ATTR_STRING))])
                << (str_g("check_string<ansi>(")            [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))])
                << (str_g("check_string<ucs>(")             [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))])
                << (str_g("check_string<EncodingT>(")       [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))])
                << (str_g("check_string<EncodingT>(")       [attr_g(getIsAttributeTypeHandler(ATTR_TIME))])
                << (str_g("check_string<EncodingT>(")       [attr_g(getIsAttributeTypeHandler(ATTR_DATE))])
                << (str_g("check_string<EncodingT>(")       [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                << (str_g("check_numeric_i_array(")         [attr_g(getIsAttributeTypeHandler(ATTR_BINARY))]))
															[!If_IsREF_R2]
                << (str_g("check_") << LRelation1_R2 << "(")[relationsByAttr(FILTER_TARGET)][If_IsREF_R2]
				<< $(0) << ", " << $(1) << ")";

			AttributeNativeType_R2 =
				((str_g("bool")                           [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))])
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
                << (str_g("boost::container::vector<unsigned char>")    [attr_g(getIsAttributeTypeHandler(ATTR_BINARY))]))
														  [!If_IsREF_R2]
				<< (AttributeType_R2)                     [If_IsREF_R2];


			If_HasReferenceID_R2 = 
				has_g(0, set_g((attr0,attrN), If_IsID_R2 && If_IsREF_R2), gt_g());

			If_HasAttribute_R2 =
				has_g(0, set_g((attr0,attrN), If_IsID_R2 && If_IsREF_R2), eq_g()) &&
				has_g(0, set_g((attr0,attrN), !If_IsID_R2), gt_g());

			If_IsWriteAttribute_R2 =
				!If_IsID_R2 || has_g(0, set_g((attr0,attrN), If_IsID_R2 && If_IsREF_R2), gt_g());

		}
    }
}
