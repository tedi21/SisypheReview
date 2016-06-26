#include "SimpleCPPCommentGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleCPPCommentGenerator::SimpleCPPCommentGenerator() {

			CommentEntityClass_R2 =
				str_g("/// ") << ent_g(getEntityCommentHandler()) << "\r\n";

			CommentPredicateEqualID_R2 =
				str_g("/// Represents a comparaison class for ") << UEntity_R2 << " object.\r\n"
				<< "/// This class is used to find an object with the same ID.\r\n";

			CommentPredicateEqualIDConstructor_R2 =
				CreateMethodComment_R2( str_g("Creates a new functor allowing to find ") << UEntity_R2 << " object.",
										( CommentAttribute_R2    [If_IsID_R2] ) [attr0, attrN],
										str_g("") );

			CommentPredicateEqual_R2 =
				str_g("/// Represents a comparaison class for ") << UEntity_R2 << " object.\r\n"
				<< "/// This class is used to find an object with the same element <i>" << LAttribute_R2 << "</i>.\r\n";

			CommentPredicateEqualConstructor_R2 =
				CreateMethodComment_R2( str_g("Creates a new functor allowing to find ") << UEntity_R2 << " object.",
										CommentAttribute_R2,
										str_g("") );

			CommentPredicateLessThan_R2 =
				str_g("/// Represents a comparaison class for ") << UEntity_R2 << " object.\r\n"
				<< "/// This class is used to sort objects by <i>" << LAttribute_R2 << "</i>.\r\n";

			CommentPredicateGreaterThan_R2 =
				str_g("/// Represents a comparaison class for ") << UEntity_R2 << " object.\r\n"
				<< "/// This class is used to sort objects by <i>" << LAttribute_R2 << "</i>.\r\n";

			CommentAccessClass_R2 =
				str_g("/// Represents an access class for ") << UEntity_R2 << " object.\r\n"
				<< "/// This class is used to manage " << UEntity_R2 << " entity in database.\r\n";

			CommentAccessConstructor_R2 =
				CreateMethodComment_R2( str_g("Creates a new element ") << UEntity_R2 << "Access.",
										str_g(""),
										str_g("") );

			CommentAccessDestructor_R2 =
				CreateMethodComment_R2( str_g("Releases the ") << UEntity_R2 << "Access object.",
										str_g(""),
										str_g("") );

			CommentAccessGetInstance_R2 =
				CreateMethodComment_R2( str_g("Returns ") << UEntity_R2 << "Access object.",
										str_g(""),
										CommentReturn_R2(str_g("Instance of ") << UEntity_R2 << "Access.") );

			CommentAccessGetAll_R2 =
				CreateMethodComment_R2( str_g("Returns all ") << UEntity_R2 << " objects from database.",
										str_g(""),
										CommentReturn_R2(str_g("List of ") << UEntity_R2 << " objects.") );

			CommentAccessGetMany_R2 =
				CreateMethodComment_R2( str_g("Returns ") << UEntity_R2 << " objects from database.",
										CommentParam_R2(str_g("filter Condition allowing to filter data.")),
										CommentReturn_R2(str_g("List of ") << UEntity_R2 << " objects.") );

			CommentAccessGetOne_R2 =
				CreateMethodComment_R2( str_g("Returns ") << UEntity_R2 << " object from database.",
										CommentAttribute_R2 [If_IsID_R2][attr0, attrN],
										CommentReturn_R2(str_g("The ") << UEntity_R2 << " object.") );

			CommentAccessSelectMany_R2 =
				CreateMethodComment_R2( str_g("Returns ") << UEntity_R2 << " objects from database. Data are locked for update.",
										CommentParam_R2(str_g("filter Condition allowing to filter data."))
										<< CommentParam_R2(str_g("nowait Asynchonous call.")),
										CommentReturn_R2(str_g("List of ") << UEntity_R2 << " objects.") );

			CommentAccessSelectOne_R2 =
				CreateMethodComment_R2( str_g("Returns ") << UEntity_R2 << " object from database. Data are locked for update.",
										CommentAttribute_R2 [If_IsID_R2][attr0, attrN]
										<< CommentParam_R2(str_g("nowait Asynchonous call.")),
										CommentReturn_R2(str_g("The ") << UEntity_R2 << " object.") );

			 CommentAccessCancel_R2 =
				CreateMethodComment_R2( str_g("Cancel the selection. The ") << UEntity_R2 << " object cannot be updated or deleted from database.",
										str_g(""),
										str_g("") );

			CommentAccessIsSelected_R2 =
				CreateMethodComment_R2( str_g("Returns whether the data <i>") << UEntity_R2 << "</i> are selected.",
										/*CommentAttribute_R2 [If_IsID_R2][attr0, attrN],*/
                                        CommentParam_R2(str_g("o The ") << UEntity_R2 << " object."),
										CommentReturn_R2(str_g("True if the data <i>") << UEntity_R2 << "</i> are selected.") );

			CommentAccessFill1_R2 =
				CreateMethodComment_R2( str_g("Fills ") << LAttribute_R2 << " data from database.",
										CommentParam_R2(str_g("o The ") << UEntity_R2 << " object."),
										str_g("") );

			CommentAccessFill2_R2 =
                CreateMethodComment_R2( str_g("Fills ") << LRelationNName_R2 << " data from database.",
										CommentParam_R2(str_g("o The ") << URelation1_R2 << " object.")
										<< CommentParam_R2(str_g("nowait Asynchronous call.")),
										str_g("") );

			CommentAccessFill3_R2 =
                CreateMethodComment_R2( str_g("Fills ") << LRelationNName_R2 << " data from database.",
										CommentParam_R2(str_g("o The ") << URelation1_R2 << " object.")
										<< (CommentAttribute_R2)    
																							[If_IsID_R2]
																							[attr0, attrN]
																							[entitiesByRel(FILTER_TARGET|FILTER_ERASE_REF)]
										<< CommentParam_R2(str_g("nowait Asynchronous call.")),
										str_g("") );

			CommentAccessFill4_R2 =
                CreateMethodComment_R2( str_g("Fills ") << LRelationNName_R2 << " data from database.",
										CommentParam_R2(str_g("o The ") << URelation1_R2 << " object.")
										<< CommentParam_R2(str_g("filter Condition allowing to filter data."))
										<< CommentParam_R2(str_g("nowait Asynchonous call.")),
										str_g("") );

			CommentAccessUpdate_R2 =
				CreateMethodComment_R2( str_g("Updates ") << UEntity_R2 << " data to database.",
										CommentParam_R2(str_g("o The ") << UEntity_R2 << " object."),
										str_g("") );

			CommentAccessAltered_R2 =
				CreateMethodComment_R2( str_g("Returns whether ") << UEntity_R2 << " data are altered from database.",
										CommentParam_R2(str_g("o The ") << UEntity_R2 << " object."),
										CommentReturn_R2(str_g("True if data ") << UEntity_R2 << " have been altered.") );

			CommentAccessInsert_R2 =
				CreateMethodComment_R2( str_g("Inserts ") << UEntity_R2 << " data to database.",
										CommentParam_R2(str_g("o The ") << UEntity_R2 << " object."),
										str_g("") );

			CommentAccessDelete_R2 =
				CreateMethodComment_R2( str_g("Deletes ") << UEntity_R2 << " data to database.",
										CommentParam_R2(str_g("o The ") << UEntity_R2 << " object."),
										str_g("") );

            CommentAccessAddInsertSignal_R2 =
				CreateMethodComment_R2( str_g("Add signal for ") << UEntity_R2 << " insertion.",
										CommentParam_R2(str_g("subscriber The observer")),
										CommentReturn_R2(str_g("The connection")) );

            CommentAccessAddUpdateSignal_R2 =
				CreateMethodComment_R2( str_g("Add signal for ") << UEntity_R2 << " update.",
										CommentParam_R2(str_g("subscriber The observer")),
										CommentReturn_R2(str_g("The connection")) );

            CommentAccessAddDeleteSignal_R2 =
				CreateMethodComment_R2( str_g("Add signal for ") << UEntity_R2 << " deletion.",
										CommentParam_R2(str_g("subscriber The observer")),
										CommentReturn_R2(str_g("The connection")) );

            CommentAccessAddTransactionSignal_R2 =
				CreateMethodComment_R2( str_g("Add signal for ") << UEntity_R2 << " transaction result.",
										CommentParam_R2(str_g("subscriber The observer")),
										CommentReturn_R2(str_g("The connection")) );

            CommentAccessRemoveInsertSignal_R2 =
				CreateMethodComment_R2( str_g("Remove signal for ") << UEntity_R2 << " insertion.",
										CommentParam_R2(str_g("connection The connection")),
										str_g("") );

            CommentAccessRemoveUpdateSignal_R2 =
				CreateMethodComment_R2( str_g("Remove signal for ") << UEntity_R2 << " update.",
										CommentParam_R2(str_g("connection The connection")),
										str_g("") );

            CommentAccessRemoveDeleteSignal_R2 =
				CreateMethodComment_R2( str_g("Remove signal for ") << UEntity_R2 << " deletion.",
										CommentParam_R2(str_g("connection The connection")),
										str_g("") );

            CommentAccessRemoveTransactionSignal_R2 =
				CreateMethodComment_R2( str_g("Remove signal for ") << UEntity_R2 << " transaction result.",
										CommentParam_R2(str_g("connection The connection")),
										str_g("") );

			CreateMethodComment_R2 =
				str_g("\t/** ")
				<< $(0)
				<< $(1)
				<< $(2)
				<< "\r\n\t*/\r\n";

			CommentParam_R2 =
				str_g("\r\n\t@param ") << $(0);

			CommentReturn_R2 =
				str_g("\r\n\t@return ") << $(0);

			CommentEntityConstructor_R2 =
				CreateMethodComment_R2( str_g("Creates a new element ") << UEntity_R2 << ".",
										str_g(""),
										str_g("") );

			CommentEntity_R2 = 
				CommentParam_R2(LEntity_R2 << " The " << UEntity_R2 << " object.");

			CommentRelation_R2 =
                CommentParam_R2(LRelationNName_R2 << " The " << URelationN_R2 << " object.");

			CommentReturnAttribute_R2 =
				CommentReturn_R2(attr_g(getAttributeCommentHandler()));

			CommentAttribute_R2 =
				CommentParam_R2(LAttribute_R2 << " " << attr_g(getAttributeCommentHandler()));

			CommentEntityConstructor2_R2 =
				CreateMethodComment_R2( str_g("Creates a new element ") << UEntity_R2 << ".",
										CommentAttribute_R2    [!If_IsREF_R2 && !If_IsID_R2]    [attr0, attrN],
										str_g("") );

			CommentEntityConstructor3_R2 =
				CreateMethodComment_R2( str_g("Creates a new element ") << UEntity_R2 << ".",
										CommentAttribute_R2    [!If_IsREF_R2 || If_IsID_R2]    [attr0, attrN],
										str_g("") );

            CommentEntityCopyConstructor_R2 =
				CreateMethodComment_R2( str_g("Creates a copy of elem as the content for the ") << UEntity_R2 << " object.",
										CommentParam_R2(str_g("elem A ") << UEntity_R2 << " object containing elements of the same type."),
										str_g("") );

            CommentEntityAssignOperator_R2 =
				CreateMethodComment_R2( str_g("Assigns a copy of elem as the new content for the ") << UEntity_R2 << " object.",
										CommentParam_R2(str_g("elem A ") << UEntity_R2 << " object containing elements of the same type."),
										CommentReturn_R2(str_g("*this")) );

			CommentSetAttribute_R2 = 
				CreateMethodComment_R2( str_g("Sets a value of the element <i>") <<  LAttribute_R2 << "</i> in " << UEntity_R2 << ".",
										CommentAttribute_R2,
										str_g("") );

			CommentGetAttribute_R2 =
				CreateMethodComment_R2( str_g("Returns a const reference to the element <i>") <<  LAttribute_R2 << "</i> in " << UEntity_R2 << ".",
										str_g(""),
										CommentReturnAttribute_R2 );

			CommentGetREF_R2 =
				CreateMethodComment_R2( str_g("Returns a reference to the element <i>") <<  LAttribute_R2 << "</i> in " << UEntity_R2 << ".",
										str_g(""),
										CommentReturnAttribute_R2 );

			CommentIsNullREF_R2 =
				CreateMethodComment_R2( str_g("Returns whether the element <i>") <<  LAttribute_R2 << "</i> in " << UEntity_R2 << " is NULL.",
										str_g(""),
										CommentReturn_R2(str_g("True if the element <i>") <<  LAttribute_R2 << "</i> is NULL, false otherwise.") );

			CommentEraseREF_R2 =
				CreateMethodComment_R2( str_g("Removes from ") << UEntity_R2 << " an element <i>" <<  LAttribute_R2 << "</i>.",
										str_g(""),
										str_g("") );

            CommentIterator_R2 =
                str_g("\t/// Random access iterator types for ") << URelationNName_R2 << " vector.\r\n";

			CommentMethodBegin_R2 =
                CreateMethodComment_R2( str_g("Returns an iterator referring to the first element in the vector container ") << URelationNName_R2 << ".",
										str_g(""),
										CommentReturn_R2(str_g("An iterator to the beginning of the sequence.")) );

			CommentMethodEnd_R2 =
                CreateMethodComment_R2( str_g("Returns an iterator referring to the past-the-end element in the vector container ") << URelationNName_R2 << ".",
										str_g(""),
										CommentReturn_R2(str_g("An iterator to the element past the end of the sequence.")) );

			CommentMethodConstBegin_R2 =
                CreateMethodComment_R2( str_g("Returns a const iterator referring to the first element in the vector container ") << URelationNName_R2 << ".",
										str_g(""),
										CommentReturn_R2(str_g("A const iterator to the beginning of the sequence.")) );

			CommentMethodConstEnd_R2 =
                CreateMethodComment_R2( str_g("Returns a const iterator referring to the past-the-end element in the vector container ") << URelationNName_R2 << ".",
										str_g(""),
										CommentReturn_R2(str_g("A const iterator to the element past the end of the sequence.")) );

			CommentMethodAt_R2 =
                CreateMethodComment_R2( str_g("Returns a reference to the element at position n in the vector ") << URelationNName_R2 << ".",
										CommentParam_R2(str_g("n Position of an element in the vector.")),
										CommentReturn_R2(str_g("The element at the specified position in the vector.")) );

			CommentMethodConstAt_R2 =
                CreateMethodComment_R2( str_g("Returns a const reference to the element at position n in the vector ") << URelationNName_R2 << ".",
										CommentParam_R2(str_g("n Position of an element in the vector.")),
										CommentReturn_R2(str_g("The element at the specified position in the vector.")) );

			CommentMethodSize_R2 =
                CreateMethodComment_R2( str_g("Returns the number of elements in the vector container ") << URelationNName_R2 << ".",
										str_g(""),
										CommentReturn_R2(str_g("The number of elements that conform the vector's content.")) );

			 CommentMethodEmpty_R2 = 
                CreateMethodComment_R2( str_g("Returns whether the vector container ") << URelationNName_R2 << " is empty, i.e. whether its size is 0.",
										str_g(""),
										CommentReturn_R2(str_g("True if the vector size is 0, false otherwise.")) );

			 CommentMethodPushBack_R2 =
                CreateMethodComment_R2( str_g("Adds a new element at the end of the vector ") << URelationNName_R2 << ", after its current last element. The content of this new element is initialized to a copy of x.",
										CommentParam_R2(str_g("o Value to be copied to the new element.")),
										str_g("") );

			 CommentMethodInsert0_R2 =
                CreateMethodComment_R2( str_g("The vector ") << URelationNName_R2 << " is extended by inserting new elements before the element at position pos.",
										CommentParam_R2(str_g("pos Position in the vector where the new elements are inserted."))
										<< CommentParam_R2(str_g("o Value to be used to initialize the inserted elements.")),
										CommentReturn_R2(str_g("An iterator that points to the newly inserted element.")) );

			 CommentMethodInsert1_R2 =
                CreateMethodComment_R2( str_g("The vector ") << URelationNName_R2 << " is extended by inserting new elements before the element at position pos.",
										CommentParam_R2(str_g("pos Position in the vector where the new elements are inserted."))
										<< CommentParam_R2(str_g("first First iterator specifying a range of elements."))
										<< CommentParam_R2(str_g("last Last iterator specifying a range of elements. Copies of the elements in the range [first,last) are inserted at position pos.")),
										str_g("") );

			  CommentMethodErase0_R2 =
                CreateMethodComment_R2( str_g("Removes from the vector container ") << URelationNName_R2 << " a single element.",
										CommentParam_R2(str_g("pos Iterator pointing to a single element to be removed from the vector.")),
										str_g("") );

			  CommentMethodErase1_R2 =
                CreateMethodComment_R2( str_g("Removes from the vector container ") << URelationNName_R2 << " a range of elements ([first,last)).",
										CommentParam_R2(str_g("first First iterator specifying a range within the vector to be removed: [first,last)."))
										<< CommentParam_R2(str_g("last Last iterator specifying a range within the vector to be removed: [first,last).")),
										str_g("") );

			   CommentMethodClear_R2 =
                CreateMethodComment_R2( str_g("All the elements of the vector are dropped: their destructors are called, and then they are removed from the vector container ") << URelationNName_R2 << ", leaving the container with a size of 0.",
										str_g(""),
										str_g("") );

			 CommentPrintConsole_R2 =
				CreateMethodComment_R2( str_g("Prints ") << UEntity_R2 << " object on a C++ stream.",
										CommentParam_R2(str_g("o Reference of C++ stream object.")),
										CommentReturn_R2(str_g("The reference of C++ stream object.")) );

			 CommentSerialization_R2 =
				CreateMethodComment_R2( str_g("Deconstructs/reconstructs of ") << UEntity_R2 << " object to a sequence of bytes.",
										CommentParam_R2(str_g("ar The input or output archive object."))
										<< CommentParam_R2(str_g("file_version The archive file version.")),
										str_g("") );

			 CommentFriendOperatorStream_R2 =
				 CreateMethodComment_R2( str_g("Defines <i> operator<< </i> for ") << UEntity_R2 << ".",
										CommentParam_R2(str_g("o Reference of C++ stream object."))
										<< CommentParam_R2(str_g("elem Const reference of ") << UEntity_R2 << " object."),
										CommentReturn_R2(str_g("The reference of C++ stream object.")) );
		}
	}
}
