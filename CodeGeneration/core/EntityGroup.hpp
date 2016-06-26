#ifndef _ENTITY_GROUP_HPP_
#define _ENTITY_GROUP_HPP_

#include "Workspace.hpp"
#include "FlatContainer.hpp"
#include "CoreExport.hpp"
#include "encoding.hpp"

namespace dsg {

    template <class EncodingT>
    class CORE_API EntityGroup
    : public FlatContainer<
                typename Workspace<EncodingT>::const_file_iterator,
                File<EncodingT>,
                typename File<EncodingT>::const_ent_iterator,
                Entity<EncodingT> const>
    {
    private:
        typedef FlatContainer<
                typename Workspace<EncodingT>::const_file_iterator,
                File<EncodingT>,
                typename File<EncodingT>::const_ent_iterator,
                Entity<EncodingT> const> FlatConstEntity;
    public:
        EntityGroup()
        {
            DataModel<EncodingT>* dataModel = DataModel<EncodingT>::getInstance();
            Workspace<EncodingT>* wrk = &(dataModel->getWorkspace());
            FlatConstEntity::define(wrk->beginFiles(), wrk->endFiles(), 
                                    &File<EncodingT>::beginEntities, 
                                    &File<EncodingT>::endEntities);
        }
    };

}

#endif    // _ENTITY_GROUP_HPP_