#ifndef _SIMPLE_CPP_ACCESS_GENERATOR_HPP_
#define _SIMPLE_CPP_ACCESS_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "SimpleCPPCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleCPPAccessGenerator
		: public SimpleCPPCommonGenerator,
		  public report<SimpleCPPAccessGenerator> {

			format<gen_info>    SourceCPP_R2,
								CreateFile_R2, 
								CreateInclude_R2,
								CreateUsingNamespace_R2,
								CreateAccessClass_R2,
								CreateStaticAttribute_R2,
								CreateStaticMethod_R2,
								CreateAccessConstructor_R2, 
								CreateAccessDestructor_R2, 
								GetAllMeth_R2,
								AllMethodBody_R2,
								AllMethodDecl_R2,
								ConvertAttrLoop_R2,
								GetType_R2,
                                AttrDeclarationLoop_R2,
                                SetAttrLoop_R2,
                                EnumREFAttrLoop_R2,
                                EnumAttrLoop_R2,
                                SelEnumAttrLoop_R2,
								AttributeColumns_R2,
								InitializeAccessLoop_R2,
								InitializeAccess_R2,
								GetManyMeth_R2, 
								ManyMethodBody_R2,
								GetOneMeth_R2,
								ConvertCStringLoop_R2,
								OneMethodBody_R2,
                                VerifyPTR_R2,
								VerifyID_R2,
                                VerifyREF_R2,
                                VerifyRELATION_R2,
                                VerifyRELATION2_R2,
								SelectOneMeth_R2,
								SelOneMethodBody_R2,
								SelectManyMeth_R2,
								SelManyMethodBody_R2,
								CancelSelectMeth_R2,
								IsSelectMeth_R2,
								EntityEqualFunctor_R2,
                                RelationNEqualFunctor_R2,
								FillMeth1_R2,
								FillMeth1Body_R2,
								FillMeth2_R2, 
								FillMeth2Body_R2,
								FillMeth3_R2,
								FillMeth3Body_R2,
								FillMeth4_R2,
								FillMeth4Body_R2,
								DeleteMeth_R2,
								DeleteMethBody_R2,
								InitializeRelationAccess_R2,
								UpdateRelationOnDelete_R2,
								InsertMeth_R2,
								InsertMethBody_R2,
								InsertNULLAttribute_R2,
								UpdateMeth_R2,
								UpdateMethBody_R2,
								IsUpdateMeth_R2,
								IsUpdateMethBody_R2,
                                AddInsertSignalMeth_R2,
                                AddUpdateSignalMeth_R2,
                                AddDeleteSignalMeth_R2,
                                AddTransactionSignalMeth_R2,
                                RemoveInsertSignalMeth_R2,
                                RemoveUpdateSignalMeth_R2,
                                RemoveDeleteSignalMeth_R2,
                                RemoveTransactionSignalMeth_R2;

			SimpleCPPAccessGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleCPPAccessGenerator const& me)
				: EtatStart(me.SourceCPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_CPP_ACCESS_GENERATOR_HPP_
