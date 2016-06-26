#include "SimpleMDGenerator.hpp"

namespace dsg {

	namespace generator {

        SimpleMDGenerator::SimpleMDGenerator()
		{
            Source_R2 =
				CreateFile_R2;

			CreateFile_R2 =
                (CreateClassDescription
                << line_g(1) << CreateClassReference) [ent0, entN];

            CreateClassDescription =
                str_g("# ") << UEntity_R2
                << line_g(1) << ent_g(getEntityCommentHandler());


            CreateClassReference =
                line_g(1) << str_g("# Référence")
                << CreateDefaultConstructorReference_R2
                << CreateConstructorReference_R2
                << CreateAttributeGetterReference_R2
                << CreateAttributeRefGetterReference_R2
                << CreateAttributeSetterReference_R2
                << CreateAttributeIsNullReference_R2
                << CreateAttributeEraseReference_R2
                << CreateAttributeListEraseReference_R2
                << CreateAttributeListInsertReference_R2
                << CreateAttributeListAtReference_R2
                << CreateAttributeListClearReference_R2
                << CreateAttributeListEmptyReference_R2
                << CreateAttributeListSize_R2;

            CreateDefaultConstructorReference_R2 =
                line_g(1) << str_g("## Constructeur ") << UEntity_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* None."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Crée une instance de la classe " << UEntity_R2 << "."
                << line_g(1) << "```"
                << line_g(1) << "var = new " << UEntity_R2 << "();"
                << line_g(1) << "```"
                << line_g(1);

            CreateConstructorReference_R2 =
                line_g(1) << str_g("## Constructeur ") << UEntity_R2
                << line_g(1) << "*Paramètres*"
                << ListEntityParam_R2
                   (
                        line_g(1) << "* " << AttributeInterpreterTypeName_R2 << " : La valeur de la colonne " << LAttribute_R2 << "."
                   )
                << line_g(2) << "*Description*"
                << line_g(1) << "* Crée une instance de la classe " << UEntity_R2 << "."
                << line_g(1) << "```"
                << line_g(1) << "var = new " << UEntity_R2 << "("
                << ListEntityParam_R2
                   (
                        LAttribute_R2 << ~-(str_g(", "))
                   )
                << ");"
                << line_g(1) << "```"
                << line_g(1);

            CreateAttributeGetterReference_R2 =
                (line_g(1) << str_g("## Méthode ") << UAttribute_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* None."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* " << AttributeInterpreterTypeName_R2 << " : La colonne " << LAttribute_R2 << "."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Retourne la colonne " << UAttribute_R2 << "."
                << line_g(1) << "```"
                << line_g(1) << "val = var." << UAttribute_R2 << ";"
                << line_g(1) << "```"
                << line_g(1))
                [!If_IsREF_R2][attr0, attrN];

            CreateAttributeRefGetterReference_R2 =
                (line_g(1) << str_g("## Méthode ") << UAttribute_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* None."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* " << AttributeInterpreterTypeName_R2 << " : La colonne " << LAttribute_R2 << "."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Retourne la colonne " << UAttribute_R2 << "."
                << line_g(1) << "```"
                << line_g(1) << LAttribute_R2 << " = var." << UAttribute_R2 << ";"
                << line_g(1) << "```"
                << line_g(1))
                [If_IsREF_R2][attr0, attrN];

            CreateAttributeSetterReference_R2 =
                (line_g(1) << str_g("## Méthode ") << UAttribute_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* " << AttributeInterpreterTypeName_R2 << " : La valeur de la colonne " << LAttribute_R2 << "."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* None."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Définit la colonne " << LAttribute_R2 << "."
                << line_g(1) << "```"
                << line_g(1) << "var." << UAttribute_R2 << "(" << LAttribute_R2 << ");"
                << line_g(1) << "```"
                << line_g(1))
                [If_IsWriteAttribute_R2]
                [attr0, attrN];

            CreateAttributeIsNullReference_R2 =
                (line_g(1) << str_g("## Méthode Has") << UAttribute_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* None."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* Bool : Une valeur est définie pour la colonne " << LAttribute_R2 << "."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Indique si la colonne " << UAttribute_R2 << " a une valeur définie."
                << line_g(1) << "```"
                << line_g(1) << "val = var.Has" << UAttribute_R2 << ";"
                << line_g(1) << "```"
                << line_g(1))
                [If_IsREF_R2][attr0, attrN];

            CreateAttributeEraseReference_R2 =
                (line_g(1) << str_g("## Méthode remove") << UAttribute_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* None."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* None."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Supprime la valeur définie pour la colonne " << LAttribute_R2 << "."
                << line_g(1) << "```"
                << line_g(1) << "var." << UAttribute_R2 << " = null;"
                << line_g(1) << "```"
                << line_g(1))
                [If_IsREF_R2][attr0, attrN];

            CreateAttributeListEraseReference_R2 =
                ListRelationN_R2
                (
                    line_g(1) << str_g("## Méthode remove") << URelationNName_R2 << "s"
                    << line_g(1) << "*Paramètres*"
                    << line_g(1) << "* Numeric : La position de l'élément à supprimer dans la liste."
                    << line_g(2) << "*Retour*"
                    << line_g(1) << "* None."
                    << line_g(2) << "*Description*"
                    << line_g(1) << "* Supprime l'élément à la position *n* dans la liste de " << URelationNName_R2 << "s."
                    << line_g(1) << "```"
                    << line_g(1) << "var." << URelationNName_R2 << "s(0) = null;"
                    << line_g(1) << "```"
                    << line_g(1)
                );

            CreateAttributeListInsertReference_R2 =
                    ListRelationN_R2
                    (
                        line_g(1) << str_g("## Méthode ") << URelationNName_R2 << "s"
                        << line_g(1) << "*Paramètres*"
                        << line_g(1) << "* Numeric : La position de l'élément à insérer dans la liste."
                        << line_g(1) << "* " << URelationN_R2 << " : L'élément à insérer dans la liste."
                        << line_g(2) << "*Retour*"
                        << line_g(1) << "* None."
                        << line_g(2) << "*Description*"
                        << line_g(1) << "* Insère un élément à la position *n* dans la liste de " << URelationNName_R2 << "s."
                        << line_g(1) << "```"
                        << line_g(1) << "var." << URelationNName_R2 << "s(0) = " << LRelationNName_R2 << ";"
                        << line_g(1) << "```"
                        << line_g(1)
                    );


            CreateAttributeListAtReference_R2 =
                    ListRelationN_R2
                    (
                        line_g(1) << str_g("## Méthode ") << URelationNName_R2 << "s"
                        << line_g(1) << "*Paramètres*"
                        << line_g(1) << "* Numeric : La position de l'élément dans la liste."
                        << line_g(2) << "*Retour*"
                        << line_g(1) << "* " << URelationN_R2 << " : L'élément dans la liste."
                        << line_g(2) << "*Description*"
                        << line_g(1) << "* Retourne l'élément à la position *n* dans la liste de " << URelationNName_R2 << "s."
                        << line_g(1) << "```"
                        << line_g(1) << "val = var." << URelationNName_R2 << "s(0);"
                        << line_g(1) << "```"
                        << line_g(1)
                    );

            CreateAttributeListClearReference_R2 =
                    ListRelationN_R2
                    (
                        line_g(1) << str_g("## Méthode Clear") << URelationNName_R2 << "s"
                        << line_g(1) << "*Paramètres*"
                        << line_g(1) << "* None."
                        << line_g(2) << "*Retour*"
                        << line_g(1) << "* None."
                        << line_g(2) << "*Description*"
                        << line_g(1) << "* Supprime tous les éléments de liste."
                        << line_g(1) << "```"
                        << line_g(1) << "var.Clear" << URelationNName_R2 << "s();"
                        << line_g(1) << "```"
                        << line_g(1)
                    );

            CreateAttributeListEmptyReference_R2 =
                    ListRelationN_R2
                    (
                        line_g(1) << str_g("## Méthode Has") << URelationNName_R2 << "s"
                        << line_g(1) << "*Paramètres*"
                        << line_g(1) << "* None."
                        << line_g(2) << "*Retour*"
                        << line_g(1) << "* Bool : True si la liste n'est pas vide, False sinon."
                        << line_g(2) << "*Description*"
                        << line_g(1) << "* Indique si la liste n'est pas vide."
                        << line_g(1) << "```"
                        << line_g(1) << "val = var.Has" << URelationNName_R2 << "s();"
                        << line_g(1) << "```"
                        << line_g(1)
                    );

            CreateAttributeListSize_R2 =
                    ListRelationN_R2
                    (
                        line_g(1) << str_g("## Méthode ") << URelationNName_R2 << "sCount"
                        << line_g(1) << "*Paramètres*"
                        << line_g(1) << "* None."
                        << line_g(2) << "*Retour*"
                        << line_g(1) << "* Numeric : Le nombre d'éléments contenus dans la liste."
                        << line_g(2) << "*Description*"
                        << line_g(1) << "* Retourne le nombre d'élément contenus dans la liste."
                        << line_g(1) << "```"
                        << line_g(1) << "val = var." << URelationNName_R2 << "sCount();"
                        << line_g(1) << "```"
                        << line_g(1)
                    );
		}
    }
}


