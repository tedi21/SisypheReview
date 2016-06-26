#include "SimpleSQLParser.hpp"
#include "Equality.hpp"

namespace dsg {

    namespace parser {

        // Handles SQL Extensions
        IMPL_MODEL_PARSER_HANDLER(SqlExtensionHandler)
        {
            CHECK_MODEL(IS_VALID_ENTITY && 
                        NULL != m_attributePosition, 
                        "SqlExtensionHandler : Cannot create rowid, entities aren't initialized.")
            {
                // In FTS3 or FTS4 extension, ids are managed automatically with the column 'rowid'
                if (equalNoCase(L"FTS", UniString(szStart, szEnd-1).c_str()))
                {
                    // Add the implicit column 'rowid' in entity
                    (*m_attributePosition) = (*m_entityPosition)
                        ->addNewAttribute(L"rowid", L"", ATTR_INT64, (ATTR_ID|ATTR_AUTO));
                }
            }
        }
    
    }

}
