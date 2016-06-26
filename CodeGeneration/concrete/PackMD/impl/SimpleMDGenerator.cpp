#include "SimpleMDGenerator.hpp"

namespace dsg {

	namespace generator {

        SimpleMDGenerator::SimpleMDGenerator()
		{
            Source =
                CreateFile[Has_Class];

			CreateFile =
                ListClass
                (
                                   (CreateClassDescription
                    << line_g(1) << CreateClassReference) [Has_Constant || Has_Method]
                );

            CreateClassDescription =
                   str_g("# ") << ClassName
                << line_g(1) << ent_g(getEntityCommentHandler());

            CreateClassReference =
                   line_g(1) << str_g("# Référence")
                << ListConstant
                   (
                       line_g(1) << str_g("## Constante `") << ConstantName << "`"
                    << line_g(1) << "*Description*"
                    << line_g(1) << "*" << attr_g(getAttributeCommentHandler())
                    << line_g(1) << "```"
                    << GetConstantExample
                       (
                            line_g(1) << cnt_g(getContentDataHandler())
                       )
                    << (line_g(1) << ConstantName << ";")[!Has_ConstantExample]
                    << line_g(1) << "```"
                    << line_g(1)
                   )
                 << ListMethod
                    (
                       line_g(1) << str_g("## Méthode ") << MethodName
                    << line_g(1) << "*Paramètres*"
                    << ListParameter
                       (
                            line_g(1) << "* " << ParameterType << " : "
                         << GetParameterDescription
                            (
                                 cnt_g(getContentDataHandler())
                            )
                       )
                    << (line_g(1) << "* None.")[!Has_Parameter]
                    << line_g(2) << "*Retour*"
                    << GetReturn
                       (
                            line_g(1) << "* " << ReturnType << " : "
                         << GetReturnDescription
                            (
                                 cnt_g(getContentDataHandler())
                            )
                       )
                    << (line_g(1) << "* None.")[!Has_Return]
                    << line_g(2) << "*Description*"
                    << line_g(1) << "* " << ent_g(getEntityCommentHandler())
                    << line_g(1) << "```"
                    << GetMethodExample
                       (
                            line_g(1) << cnt_g(getContentDataHandler())
                       )
                    << (line_g(1) << MethodName << "();")[!Has_MethodExample]
                    << line_g(1) << "```"
                    << line_g(1)
                    );

            ClassName =
                    ent_g(getEntityNameHandler(KIND_ALIAS));

            ListClass =
                   $(0)[If_IsClass][ent0, entN];

            ConstantName =
                    attr_g(getAttributeNameHandler(KIND_ALIAS))
                                            [attr_g(getHasAttributeAliasHandler())]
                 << upper_g( attr_g(getAttributeNameHandler(KIND_NAME)), 0, 1)
                                            [else_g()];

            ListConstant =
                   $(0)[If_IsConstant][attr0, attrN];

            MethodName =
                   ent_g(getEntityFunctionNameHandler(KIND_ALIAS))
                                            [ent_g(getHasEntityAliasHandler())]
                << upper_g( ent_g(getEntityFunctionNameHandler(KIND_NAME)), 0, 1)
                                            [else_g()];

            ListMethod =
                   $(0)[If_IsMethod]
                       [entitiesByRel(FILTER_TARGET|FILTER_CONTEXTUAL)]
                       [relationsByEnt(FILTER_SOURCE)];

            ParameterType =
                    (str_g("Bool")     [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                  << str_g("String")   [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                  << str_g("String")   [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                  << str_g("String")   [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                  << str_g("Numeric")  [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                  << str_g("String")   [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                  << str_g("String")   [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                  << str_g("String")   [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                  << str_g("String")   [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                  << str_g("")         [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                  << str_g("")         [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                  << str_g("")         [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                     [!If_IsREF]
                  << GetDependence
                     (
                         DependenceType
                     )
                     [If_IsREF];

            ListParameter =
                   $(0)[set_g((attr0,attrN), If_IsParameter)];

            DependenceType =
                   ClassName;

            GetDependence =
                   $(0)[entitiesByRel(FILTER_SOURCE)]
                       [relationsByAttr(FILTER_TARGET)];

            ReturnType =
                   ParameterType;

            GetReturn =
                   (+$(0))[If_IsAUTO][attr0,attrN];

            GetMethodExample =
                   $(0)[contentByEnt(L"Example")];

            GetParameterDescription =
                   $(0)[contentByAttr(L"ParameterDescription")];

            GetReturnDescription =
                   $(0)[contentByAttr(L"ReturnDescription")];

            GetConstantExample =
                   $(0)[contentByAttr(L"Example")];

            Has_Class =
                   has_g(0, set_g((ent0,entN), If_IsClass), gt_g());

            Has_Constant =
                   has_g(0, set_g((attr0,attrN), If_IsConstant), gt_g());

            Has_Method =
                   has_g(0, set_g((relationsByEnt(FILTER_SOURCE)*entitiesByRel(FILTER_TARGET|FILTER_CONTEXTUAL)), If_IsMethod), gt_g());

            Has_Contextual =
                   has_g(0, set_g((attr0,attrN), If_IsCONTEXTUAL), gt_g());

            Has_Parameter =
                   has_g(0, set_g((attr0,attrN), If_IsParameter), gt_g());

            Has_Return =
                   has_g(0, set_g((attr0,attrN), If_IsAUTO), gt_g());

            Has_MethodExample =
                   has_g(0, contentByEnt(L"Example"), gt_g());

            Has_ConstantExample =
                   has_g(0, contentByAttr(L"Example"), gt_g());

            If_IsClass =
                   ent_g(getIsEntityClassHandler(ENTITY_DATA)) && !Has_Contextual;


            If_IsConstant =
                    If_IsSTATIC && If_IsREADONLY;


            If_IsMethod =
                   ent_g(getIsEntityClassHandler(ENTITY_FUNCTION)) && Has_Contextual;

            If_IsParameter =
                   !If_IsAUTO && !If_IsID && !If_IsCONTEXTUAL && !If_IsBASE;

            If_IsID =
                   attr_g(getIsAttributeModifierHandler(ATTR_ID));

            If_IsREF =
                   attr_g(getIsAttributeModifierHandler(ATTR_REF));

            If_IsCONTEXTUAL =
                   attr_g(getIsAttributeModifierHandler(ATTR_CONTEXTUAL));

            If_IsAUTO =
                   attr_g(getIsAttributeModifierHandler(ATTR_AUTO));

            If_IsREADONLY =
                   attr_g(getIsAttributeModifierHandler(ATTR_CONST));

            If_IsBASE =
                   attr_g(getIsAttributeModifierHandler(ATTR_BASE));

            If_IsSTATIC =
                   attr_g(getIsAttributeModifierHandler(ATTR_STATIC));

            If_IsVIRTUAL =
                   attr_g(getIsAttributeModifierHandler(ATTR_VIRTUAL));

		}
    }
}
