#ifndef _RELATION_GROUP_HPP_
#define _RELATION_GROUP_HPP_

#include "Workspace.hpp"
#include "FlatContainer.hpp"
#include "CoreExport.hpp"
#include "encoding.hpp"

namespace dsg {

    template <class EncodingT>
    class CORE_API RelationGroup
    : public FlatContainer<
                typename Workspace<EncodingT>::const_file_iterator,
                File<EncodingT>,
                typename File<EncodingT>::const_rel_iterator,
                Relation<EncodingT> const>
    {
    private:
        typedef FlatContainer<
                typename Workspace<EncodingT>::const_file_iterator,
                File<EncodingT>,
                typename File<EncodingT>::const_rel_iterator,
                Relation<EncodingT> const> FlatConstRelation;
    public:
        RelationGroup()
        {
            DataModel<EncodingT>* dataModel = DataModel<EncodingT>::getInstance();
            Workspace<EncodingT>* wrk = &(dataModel->getWorkspace());
            FlatConstRelation::define(wrk->beginFiles(), wrk->endFiles(), 
                                      &File<EncodingT>::beginRelations, 
                                      &File<EncodingT>::endRelations);
        }
    };

}

#endif    // _RELATION_GROUP_HPP_