#include "SimpleHPPWordGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHPPWordGenerator::SimpleHPPWordGenerator()
		{
			SourceHPP = 
				CreateFile;

			CreateFile =
                                CreateHeader(file_g(getFileNameHandler(KIND_ALIAS)) << ".h")
                << line_g(1) << CreateHPPDefine("_" << file_g(getFileNameHandler(KIND_ALIAS)) << "_h_")
				<< line_g(1) << CreateInclude
				<< line_g(1) << CreateNamespace(str_g("word"))
                << ListEnum
                   (
                       CommentWordEnum
                    << CreateWordEnum
                    << line_g(1)
                   )
                << ListClass
                   (   
                       DeclareWordClass
                    << line_g(1)
                    << CommentWordClass
                    << CreateWordClass
                    << line_g(1)
                   )       
				<< line_g(1) << CreateEndNamespace
				<< line_g(1) << CreateHPPEndDefine;            

			CreateInclude =
				   line_g(1) << STR_G(#include <windows.h>)
                << line_g(1) << STR_G(#include <string>)
                << ListClass
                   ( 
                       ListAttribute
                       (
                           WithClassType(line_g(1) << "#include \"" << ClassName << ".h\"")
                       )
                    << ListArray
                       (
                           GotoElementArray
                           (
                               WithClassType(line_g(1) << "#include \"" << ClassName << ".h\"")
                           )
                       )
                    << ListMethod
                       (
                           ListParameter
                           (
                               WithClassType(line_g(1) << "#include \"" << ClassName << ".h\"")
                           )
                        << GotoReturn
                           (
                               WithClassType(line_g(1) << "#include \"" << ClassName << ".h\"")
                           )
                           [Has_Return]
                       )
                   )[If_IsProject];

            CommentWordClass =
                   (line_g(1) << htab_g(1) << "/*" << ent_g(getEntityCommentHandler()) << "*/")
                   [ent_g(getHasEntityCommentHandler())];

			CreateWordClass =
                   line_g(1) << htab_g(1) << "class " << ClassName
                <<(line_g(1) << htab_g(1) << ": public " << BaseName)              [Has_Base]
                << line_g(1) << htab_g(1) << "{"
                <<(line_g(1) << htab_g(1) << "protected:"
                << line_g(1) << htab_g(2) << "IDispatch* m_pObject;") [!Has_Base]
                << line_g(2) << htab_g(1) << "public:"
                << line_g(1) << htab_g(2) << "// Constructor"
                << line_g(1) << htab_g(2) << ClassName << "();"
                << line_g(1) << htab_g(2) << "// Constructor"
                << line_g(1) << htab_g(2) << ClassName << "(IDispatch* p" << ClassName << ", bool pAddRef = false);"
                <<(line_g(1) << htab_g(2) << "// Copy Constructor"
                << line_g(1) << htab_g(2) << ClassName << "(const " << ClassName << "& copy);"
                << line_g(1) << htab_g(2) << "// Destructor"
                << line_g(1) << htab_g(2) << "~" << ClassName << "();"
                << line_g(1) << htab_g(2) << "// Assignment operator"
                << line_g(1) << htab_g(2) << "const " << ClassName << "& operator=(const " << ClassName << "& copy);"
                << line_g(1) << htab_g(2) << "// Cast operator"
                << line_g(1) << htab_g(2) << "operator IDispatch*() const;")       [!Has_Base]
                << line_g(1) << htab_g(2) << ListAttribute
                                             (
                                                  CommentWordAttribute 
                                               << CreateWordAttribute
                                             )
                << line_g(1) << htab_g(2) << ListArray
                                             (
                                                  CommentWordArray
                                               << CreateWordArray
                                             )
                << line_g(1) << htab_g(2) << ListMethod
                                             (
                                                  CommentWordMethod
                                               << CreateWordMethod
                                             )
                << line_g(1) << htab_g(2) << ListConstant
                                             (
                                                  CommentWordConstant
                                               << CreateWordConstant
                                             )
                << line_g(1) << htab_g(1) << "};";
            
            CommentWordAttribute =
                   (line_g(1) << htab_g(2) << "/*" << attr_g(getAttributeCommentHandler()) << "*/")
                   [attr_g(getHasAttributeCommentHandler())];

            CreateWordAttribute =
                   line_g(1) << htab_g(2) << AttributeType << " get" << AttributeName << "() const;"
                << (line_g(1) << htab_g(2) << "void set" << AttributeName << "(" << AttributeTypeParam << " " << AttributeParamName << ");")
                   [!If_IsReadOnly]; 

	        CommentWordMethod =
                   (line_g(1) << htab_g(2) << "/*" << ent_g(getEntityCommentHandler()) << "*/")
                   [ent_g(getHasEntityCommentHandler())];

            CreateWordMethod =
                   line_g(1) << htab_g(2) << ReturnType << " " << MethodName << "(" << CreateParameters << ");";

	        CommentWordArray =
                   (line_g(1) << htab_g(2) << "/*" << ent_g(getEntityCommentHandler()) << "*/")
                   [ent_g(getHasEntityCommentHandler())];

            CreateWordArray =
                   line_g(1) << htab_g(2) 
                << GotoElementArray
                   (
                       AttributeType << " get" << AttributeName << "(" 
                    << GotoIndexArray
                       (
                           ParameterType << " " << ParameterName
                       )
                    << ") const;"
                   )
                << GotoElementArray
                   (
                       (line_g(1) << htab_g(2) 
                    << "void set" << AttributeName << "("
                    << GotoIndexArray
                       (
                           ParameterType << " " << ParameterName
                       )
                    << ", "
                    << AttributeTypeParam << " " << AttributeParamName
                    << ");")[!If_IsReadOnly]
                   );

            CreateParameters =
                   ListParameter
                   (
                        ParameterType << " " << ParameterName << ~-str_g(", ")
                   );

            DeclareWordClass = 
                   (ListAttribute
                    (
                       WithClassType(line_g(1) << htab_g(1) << "class " << ClassName << ";")
                    )
                 << ListArray
                    (
                       GotoElementArray
                       (
                           WithClassType(line_g(1) << htab_g(1) << "class " << ClassName << ";")
                       )
                    )
                 << ListMethod
                    (
                       ListParameter
                       (
                           WithClassType(line_g(1) << htab_g(1) << "class " << ClassName << ";")
                       )
                    << GotoReturn
                       (
                           WithClassType(line_g(1) << htab_g(1) << "class " << ClassName << ";")
                       )
                       [Has_Return]
                    )
                   )[!If_IsProject];

            CommentWordEnum =
                   (line_g(1) << htab_g(1) << "/*" << ent_g(getEntityCommentHandler()) << "*/")
                   [ent_g(getHasEntityCommentHandler())];

            CreateWordEnum =
                   line_g(1) << htab_g(1) << "enum " << EnumName 
                << line_g(1) << htab_g(1) << "{" 
                << line_g(1) << htab_g(2) << ListEnumKey
                                             (
                                                 EnumKeyName << (str_g(" = ") << EnumValue)[Has_DefaultValue]
                                              << ~-( 
                                                     str_g(',') 
                                                  << line_g(1) << htab_g(2) 
                                                   )
                                             )
                << line_g(1) << htab_g(1) << "};";

            CommentWordConstant =
                   (line_g(1) << htab_g(2) << "/*" << attr_g(getAttributeCommentHandler()) << "*/")
                   [attr_g(getHasAttributeCommentHandler())];

            CreateWordConstant =
                   line_g(1) << htab_g(2) << "static const " << ConstantType << " " << ConstantName << ";"; 

		}
    }
}
