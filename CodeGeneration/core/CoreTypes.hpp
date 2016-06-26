#ifndef _CORE_TYPES_HPP_
#define _CORE_TYPES_HPP_

#include "DataModel.hpp"
#include "EntityGroup.hpp"
#include "AttributeGroup.hpp"
#include "RelationGroup.hpp"
#include "encoding.hpp"
#include "CoreExport.hpp"
#include <vector>
#include <string>

using namespace std;
using namespace enc;

namespace dsg {

    // Unicode typedef
    typedef ucs::string_t                                       UniString;          // same as wstring
    typedef ucs::char_t                                         UniChar;            // same as wchar_t
    typedef dsg::Workspace<ucs>::const_file_iterator            const_UniFileItr;
    typedef dsg::File<ucs>::const_ent_iterator                  const_UniEntityItr;
    typedef dsg::File<ucs>::const_rel_iterator                  const_UniRelationItr;
    typedef dsg::File<ucs>::const_cnt_iterator                  const_UniContentItr;
    typedef dsg::Entity<ucs>::const_attr_iterator               const_UniAttributeItr;
    typedef dsg::Workspace<ucs>::const_reverse_file_iterator    const_reverse_UniFileItr;
    typedef dsg::File<ucs>::const_reverse_ent_iterator          const_reverse_UniEntityItr;
    typedef dsg::File<ucs>::const_reverse_rel_iterator          const_reverse_UniRelationItr;
    typedef dsg::File<ucs>::const_reverse_cnt_iterator          const_reverse_UniContentItr;
    typedef dsg::Entity<ucs>::const_reverse_attr_iterator       const_reverse_UniAttributeItr;
    typedef dsg::Workspace<ucs>::file_iterator                  UniFileItr;
    typedef dsg::File<ucs>::ent_iterator                        UniEntityItr;
    typedef dsg::File<ucs>::rel_iterator                        UniRelationItr;
    typedef dsg::File<ucs>::cnt_iterator                        UniContentItr;
    typedef dsg::Entity<ucs>::attr_iterator                     UniAttributeItr;
    typedef dsg::Workspace<ucs>::reverse_file_iterator          reverse_UniFileItr;
    typedef dsg::File<ucs>::reverse_ent_iterator                reverse_UniEntityItr;
    typedef dsg::File<ucs>::reverse_rel_iterator                reverse_UniRelationItr;
    typedef dsg::File<ucs>::reverse_cnt_iterator                reverse_UniContentItr;
    typedef dsg::Entity<ucs>::reverse_attr_iterator             reverse_UniAttributeItr;
    typedef dsg::DataModel<ucs>                                 UniDataModel;
    typedef WorkspaceArray(ucs)                                 UniWorkspaceArray;
    typedef dsg::Workspace<ucs>                                 UniWorkspace;
    typedef dsg::File<ucs>                                      UniFile;
    typedef FileArray(ucs)                                      UniFileArray;
    typedef dsg::FileNameEquality<ucs>                          UniFileNameEquality;
    typedef dsg::Entity<ucs>                                    UniEntity;
    typedef EntityArray(ucs)                                    UniEntityArray;
    typedef dsg::EntityGroup<ucs>                               UniEntityGroup;
    typedef dsg::EntityNameEquality<ucs>                        UniEntityNameEquality;
    typedef dsg::Relation<ucs>                                  UniRelation;
    typedef RelationArray(ucs)                                  UniRelationArray;
    typedef dsg::RelationGroup<ucs>                             UniRelationGroup;
    typedef dsg::RelationNameEquality<ucs>                      UniRelationNameEquality;
    typedef dsg::Attribute<ucs>                                 UniAttribute;
    typedef AttributeArray(ucs)                                 UniAttributeArray;
    typedef dsg::AttributeGroup<ucs>                            UniAttributeGroup;
    typedef dsg::AttributeNameEquality<ucs>                     UniAttributeNameEquality;  
    typedef dsg::Content<ucs>                                   UniContent;
    typedef ContentArray(ucs)                                   UniContentArray;
}

#endif // _CORE_TYPES_H_
