#ifndef _ATTRIBUTE_GROUP_HPP_
#define _ATTRIBUTE_GROUP_HPP_

#include "EntityGroup.hpp"
#include "FlatContainer.hpp"
#include "CoreExport.hpp"
#include "encoding.hpp"

namespace dsg {

    template <class EncodingT>
    class CORE_API AttributeGroup
    : public FlatContainer<
                typename EntityGroup<EncodingT>::const_iterator,
                Entity<EncodingT>,
                typename Entity<EncodingT>::const_attr_iterator,
                Attribute<EncodingT> const>
    {
    private:
        typedef FlatContainer<
                typename EntityGroup<EncodingT>::const_iterator,
                Entity<EncodingT>,
                typename Entity<EncodingT>::const_attr_iterator,
                Attribute<EncodingT> const> FlatConstAttribute;
    public:
        AttributeGroup()
        {
            EntityGroup<EncodingT> allEntities;
            FlatConstAttribute::define(allEntities.begin(), allEntities.end(), 
                                       &Entity<EncodingT>::beginAttributes, 
                                       &Entity<EncodingT>::endAttributes);
        }
    };

}

#endif    // _ATTRIBUTE_GROUP_HPP_