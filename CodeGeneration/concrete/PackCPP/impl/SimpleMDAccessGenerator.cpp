#include "SimpleMDAccessGenerator.hpp"

namespace dsg {

	namespace generator {

        SimpleMDAccessGenerator::SimpleMDAccessGenerator()
		{
            Source_R2 =
				CreateFile_R2;

            CreateFile_R2 =
                (CreateClassDescription
                << line_g(1) << CreateClassReference) [ent0, entN];

            CreateClassDescription =
                str_g("# ") <<  UEntity_R2 << "Access"
                << line_g(1) << "Réprésente une classe d'accès pour les objets " << UEntity_R2
                << ". Cette classe est utilisée pour gérer l'entité " << UEntity_R2 << " dans la base de données.";

            CreateClassReference =
                line_g(1) << str_g("# Référence")
                << CreateConstructorReference_R2
                << CreateGetAllReference_R2
                << CreateGetManyReference_R2
                << CreateGetOneReference_R2
                << CreateSelectOneReference_R2
                << CreateSelectManyReference_R2
                << CreateCancelSelectedReference_R2
                << CreateIsSelectedReference_R2
                << CreateFillReference_R2
                << CreateFillAllReference_R2
                << CreateFillOneReference_R2
                << CreateFillManyReference_R2
                << CreateIsModifiedReference_R2
                << CreateUpdateReference_R2
                << CreateInsertReference_R2
                << CreateDeleteReference_R2
                << CreateGetErrorReference_R2;

            CreateConstructorReference_R2 =
                line_g(1) << str_g("## Constructeur ") << UEntity_R2 << "Access"
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* None."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Crée une instance de la classe " << UEntity_R2 << "Access."
                << line_g(1) << "```"
                << line_g(1) << "access = new " << UEntity_R2 << "Access();"
                << line_g(1) << "```"
                << line_g(1);


            CreateGetAllReference_R2 =
                line_g(1) << str_g("## Méthode GetAll") << UEntity_R2 << "s"
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* None."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* Array[" << UEntity_R2 << "] : Tous les objets " << UEntity_R2 << " de la base de données."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Retourne toutes les objets " << UEntity_R2 << " de la base de données."
                << line_g(1) << "```"
                << line_g(1) << "objects = access.GetAll" << UEntity_R2 << "s();"
                << line_g(1) << "```"
                << line_g(1);

            CreateGetManyReference_R2 =
                line_g(1) << str_g("## Méthode GetMany") << UEntity_R2 << "s"
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* String : clause WHERE de la recherche SQL."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* Array[" << UEntity_R2 << "] : Les objets " << UEntity_R2 << " de la base de données correspondant à la requête SQL."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Retourne les objets " << UEntity_R2 << " de la base de données correspondant à la requête SQL."
                << line_g(1) << "```"
                << line_g(1) << "objects = access.GetMany" << UEntity_R2 << "s(\""
                << ListEntityParam_R2(+(LAttribute_R2 << " = \" & value")) << ");"
                << line_g(1) << "```"
                << line_g(1);

            CreateGetOneReference_R2 =
                line_g(1) << str_g("## Méthode GetOne") << UEntity_R2
                << line_g(1) << "*Paramètres*"
                << ListEntityIDParam_R2
                   (
                        line_g(1) << "* " << AttributeInterpreterTypeName_R2 << " : L'identifiant " << LAttribute_R2 << " de la table " << LEntity_R2 << "."
                   )
                << line_g(2) << "*Retour*"
                << line_g(1) << "* " << UEntity_R2 << " : L'objet " << UEntity_R2 << " de la base de données correspondant à l'identifiant."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Retourne l'objet " << UEntity_R2 << " de la base de données correspondant à l'identifiant."
                << line_g(1) << "```"
                << line_g(1) << "object = access.GetOne" << UEntity_R2 << "("
                << ListEntityIDParam_R2
                   (
                        LAttribute_R2 << ~-str_g(", ")
                   )
                << ");"
                << line_g(1) << "```"
                << line_g(1);

            CreateSelectOneReference_R2 =
                line_g(1) << str_g("## Méthode SelectOne") << UEntity_R2
                << line_g(1) << "*Paramètres*"
                << ListEntityIDParam_R2
                   (
                        line_g(1) << "* " << AttributeInterpreterTypeName_R2 << " : L'identifiant " << LAttribute_R2 << " de la table " << LEntity_R2 << "."
                   )
                << line_g(1) << "* Bool : non utilisé."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* " << UEntity_R2 << " : L'objet " << UEntity_R2 << " de la base de données correspondant à l'identifiant, verrouillé pour modification."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Verrouille l'objet " << UEntity_R2 << " de la base de données correspondant à l'identifiant."
                << line_g(1) << "```"
                << line_g(1) << "object = access.SelectOne" << UEntity_R2 << "("
                << ListEntityIDParam_R2
                   (
                        LAttribute_R2 << str_g(", ")
                   )
                << "false);"
                << line_g(1) << "```"
                << line_g(1);

            CreateSelectManyReference_R2 =
                (line_g(1) << str_g("## Méthode SelectMany") << UEntity_R2 << "s"
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* String : clause WHERE de la recherche SQL."
                << line_g(1) << "* Bool : non utilisé."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* Array[" << UEntity_R2 << "] : Les objets " << UEntity_R2 << " de la base de données correspondant à la requête SQL, verrouillés pour modification."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Verrouille les objets " << UEntity_R2 << " de la base de données correspondant à la requête SQL."
                << line_g(1) << "```"
                << line_g(1) << "objects = access.SelectMany" << UEntity_R2 << "s(\""
                << ListEntityParam_R2(+(LAttribute_R2 << " = \" & value")) << ", false);"
                << line_g(1) << "```"
                << line_g(1))
                [has_g(0, set_g((attr0,attrN), If_IsREF_R2), gt_g())];

            CreateCancelSelectedReference_R2 =
                line_g(1) << str_g("## Méthode CancelSelection")
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* None."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* None."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Déverrouille les objets et annule les modifications."
                << line_g(1) << "```"
                << line_g(1) << "access.CancelSelection();"
                << line_g(1) << "```"
                << line_g(1);

            CreateIsSelectedReference_R2 =
                line_g(1) << str_g("## Méthode IsSelected") << UEntity_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* " << UEntity_R2 << " : L'objet à tester."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* Bool : True, si l'objet est verrouillé, False sinon."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Retourne True, si l'objet est verrouillé, False sinon."
                << line_g(1) << "```"
                << line_g(1) << "var = access.IsSelected" << UEntity_R2 << "(" << LEntity_R2 << ");"
                << line_g(1) << "```"
                << line_g(1);

            CreateFillReference_R2 =
                (line_g(1) << str_g("## Méthode Fill") << UAttribute_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* " << UEntity_R2 << " : L'objet à remplir."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* None."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Recupère la donnée " << LAttribute_R2 << " dans la base de données."
                << line_g(1) << "```"
                << line_g(1) << "access.Fill" << UAttribute_R2 << "(" << LEntity_R2 << ");"
                << line_g(1) << "```"
                << line_g(1))
                [If_IsREF_R2 && !If_IsID_R2]
                [attr0, attrN];

            CreateFillAllReference_R2 =
                ListRelationN_R2
                (
                    line_g(1) << str_g("## Méthode FillAll") << URelationNName_R2 << "s"
                    << line_g(1) << "*Paramètres*"
                    << line_g(1) << "* " << URelation1_R2 << " : L'objet à remplir."
                    << line_g(1) << "* Bool : non utilisé."
                    << line_g(2) << "*Retour*"
                    << line_g(1) << "* None."
                    << line_g(2) << "*Description*"
                    << line_g(1) << "* Recupère les données " << URelationNName_R2 << " dans la base de données."
                    << line_g(1) << "```"
                    << line_g(1) << "access.FillAll" << URelationNName_R2 << "s(" << LRelation1_R2 << ", false);"
                    << line_g(1) << "```"
                    << line_g(1)
                );

            CreateFillOneReference_R2 =
                ListRelationN_R2
                (
                    line_g(1) << str_g("## Méthode FillOne") << URelationNName_R2
                    << line_g(1) << "*Paramètres*"
                    << line_g(1) << "* " << URelation1_R2 << " : L'objet à remplir."
                    << ListRelationIDParam_R2
                       (
                            line_g(1) << "* " << AttributeInterpreterTypeName_R2 << " : L'identifiant " << LAttribute_R2 << " de la table " << LEntity_R2 << "."
                       )
                    << line_g(1) << "* Bool : non utilisé."
                    << line_g(2) << "*Retour*"
                    << line_g(1) << "* None."
                    << line_g(2) << "*Description*"
                    << line_g(1) << "* Recupère la donnée " << URelationNName_R2 << " dans la base de données."
                    << line_g(1) << "```"
                    << line_g(1) << "access.FillOne" << URelationNName_R2 << "(" << LRelation1_R2
                    << ListRelationIDParam_R2
                    (
                         ", " << LAttribute_R2
                    )
                    << ", false);"
                    << line_g(1) << "```"
                    << line_g(1)
                );

            CreateFillManyReference_R2 =
                ListRelationN_R2
                (
                    line_g(1) << str_g("## Méthode FillMany") << URelationNName_R2 << "s"
                    << line_g(1) << "*Paramètres*"
                    << line_g(1) << "* " << URelation1_R2 << " : L'objet à remplir."
                    << line_g(1) << "* String : clause WHERE de la recherche SQL."
                    << line_g(1) << "* Bool : non utilisé."
                    << line_g(2) << "*Retour*"
                    << line_g(1) << "* None."
                    << line_g(2) << "*Description*"
                    << line_g(1) << "* Recupère les données " << URelationNName_R2 << " dans la base de données."
                    << line_g(1) << "```"
                    << line_g(1) << "access.FillMany" << URelationNName_R2 << "s(" << LRelation1_R2 << ", \""
                    << ListRelationIDParam_R2(+(LAttribute_R2 << " = \" & value")) << ", false);"
                    << line_g(1) << "```"
                    << line_g(1)
                );

            CreateIsModifiedReference_R2 =
                line_g(1) << str_g("## Méthode IsModified") << UEntity_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* " << UEntity_R2 << " : L'objet à tester."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* Bool : True si l'objet est modifié, False sinon."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Retourne True si l'objet est modifié, False sinon."
                << line_g(1) << "```"
                << line_g(1) << "var = access.IsModified" << UEntity_R2 << "(" << LEntity_R2 << ");"
                << line_g(1) << "```"
                << line_g(1);

            CreateUpdateReference_R2 =
                line_g(1) << str_g("## Méthode Update") << UEntity_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* " << UEntity_R2 << " : L'objet à mettre à jour dans la base de données."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* None."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification."
                << line_g(1) << "```"
                << line_g(1) << "var = access.Update" << UEntity_R2 << "(" << LEntity_R2 << ");"
                << line_g(1) << "```"
                << line_g(1);

            CreateInsertReference_R2 =
                line_g(1) << str_g("## Méthode Insert") << UEntity_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* " << UEntity_R2 << " : L'objet à ajouter dans la base de données."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* None."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Ajoute une donnée dans la base de données."
                << line_g(1) << "```"
                << line_g(1) << "var = access.Insert" << UEntity_R2 << "(" << LEntity_R2 << ");"
                << line_g(1) << "```"
                << line_g(1);

            CreateDeleteReference_R2 =
                line_g(1) << str_g("## Méthode Delete") << UEntity_R2
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* " << UEntity_R2 << " : L'objet à supprimer dans la base de données."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* None."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification."
                << line_g(1) << "```"
                << line_g(1) << "var = access.Delete" << UEntity_R2 << "(" << LEntity_R2 << ");"
                << line_g(1) << "```"
                << line_g(1);

            CreateGetErrorReference_R2 =
                line_g(1) << str_g("## Méthode GetError")
                << line_g(1) << "*Paramètres*"
                << line_g(1) << "* String : Le texte de l'erreur."
                << line_g(2) << "*Retour*"
                << line_g(1) << "* Bool : True si une erreur est survenue, False sinon."
                << line_g(2) << "*Description*"
                << line_g(1) << "* Retourne l'erreur remontée par la base de données."
                << line_g(1) << "```"
                << line_g(1) << "var = access.GetError(textError);"
                << line_g(1) << "```"
                << line_g(1);

		}
    }
}
