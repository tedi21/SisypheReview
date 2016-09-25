
namespace dsg {

    namespace parser {

        // MemoHandler Constructor
        template <class IndexorT>
        MemoHandler<IndexorT>::MemoHandler(const dictionnary_ptr_t& table, 
                                           const IndexorT& indexor,
                                           short key)
        : m_table(table),
          m_indexor(indexor),
          m_key(key),
          m_logger(&Category::getInstance(LOGNAME))
        {}

        // MemoHandler Operator
        template <class IndexorT>
        void MemoHandler<IndexorT>::operator()
            (UniChar const* szStart, UniChar const* szEnd) const
        {
            // Memorizes parsed value 
            //m_logger->debugStream() << "MemoHandler " << m_key;
            (*m_table)[m_indexor.getIndex(m_key)] = UniString(szStart, szEnd);
        }

        // MemoAppendHandler Constructor
        template <class IndexorT>
        MemoAppendHandler<IndexorT>::MemoAppendHandler(const dictionnary_ptr_t& table, 
                                                       const IndexorT& indexor,
                                                       short key)
        : m_table(table),
          m_indexor(indexor),
          m_key(key),
          m_logger(&Category::getInstance(LOGNAME))
        {}

        // MemoAppendHandler Operator
        template <class IndexorT>
        void MemoAppendHandler<IndexorT>::operator()
            (UniChar const* szStart, UniChar const* szEnd) const
        {
            // Append parsed value 
            (*m_table)[m_indexor.getIndex(m_key)] += UniString(szStart, szEnd);
        }

        // MemoExecutionHandler Constructor 
        template <class IndexorT, class F1>
        MemoExecutionHandler<IndexorT,F1>::MemoExecutionHandler(const dictionnary_ptr_t& table,
                                                                const IndexorT& indexor, 
                                                                short key,
                                                                const F1& handlerA)
        : m_table(table),
          m_indexor(indexor),
          m_key(key),
          m_handlerA(handlerA),
          m_logger(&Category::getInstance(LOGNAME))
        {}

        // MemoExecutionHandler Operator
        template <class IndexorT, class F1>
        void MemoExecutionHandler<IndexorT,F1>::operator()
            (UniChar const*, UniChar const*) const
        {
            // Searches key 
            dictionnary_t::const_iterator i = m_table->find(m_indexor.getIndex(m_key));
            if (i != m_table->end())
            {
                // Key found
                UniString str = i->second;
                UniChar const* sz = str.c_str();
                // Executes handler with memorized value
                m_handlerA(sz, sz+str.length());
            }
        }

        // MemoExecutionHandler2 Constructor 
        template <class IndexorT, class F1, class F2>
        MemoExecutionHandler2<IndexorT,F1,F2>::MemoExecutionHandler2(const dictionnary_ptr_t& table,
                             const IndexorT& indexor, 
                             short key,
                             const F1& handlerA,
                             const F2& handlerB)
        : m_table(table),
          m_indexor(indexor),
          m_key(key),
          m_handlerA(handlerA),
          m_handlerB(handlerB),
          m_logger(&Category::getInstance(LOGNAME))
        {}

        // MemoExecutionHandler2 Operator 
        template <class IndexorT, class F1, class F2>
        void MemoExecutionHandler2<IndexorT,F1,F2>::operator()
            (UniChar const* szStart, UniChar const* szEnd) const
        {
            // Searches key 
            dictionnary_t::const_iterator i = m_table->find(m_indexor.getIndex(m_key));
            if (i != m_table->end())
            {
                // Key found
                UniString str = i->second;
                UniChar const* sz = str.c_str();
                // Executes first handler with memorized value
                m_handlerA(sz, sz+str.length());
            }
            else
            {
                // Key not found
                // Executes second handler with parsed value
                m_handlerB(szStart, szEnd);
            }
        }

        // MemoExecutionAndRemoveHandler Constructor 
        template <class IndexorT,class F1>
        MemoExecutionAndRemoveHandler<IndexorT,F1>::MemoExecutionAndRemoveHandler
                            (const dictionnary_ptr_t& table,
                             const IndexorT& indexor,
                             short key,
                             const F1& handlerA)
        : m_table(table),
          m_indexor(indexor),
          m_key(key),
          m_handlerA(handlerA),
          m_logger(&Category::getInstance(LOGNAME))
        {}

        // MemoExecutionAndRemoveHandler Operator
        template <class IndexorT, class F1>
        void MemoExecutionAndRemoveHandler<IndexorT,F1>::operator()
            (UniChar const*, UniChar const*) const
        {
            // Searches key 
            dictionnary_t::iterator i = m_table->find(m_indexor.getIndex(m_key));
            if (i != m_table->end())
            {
                // Key found
                UniString str = i->second;
                UniChar const* sz = str.c_str();
                // Executes handler with memorized value
                m_handlerA(sz, sz+str.length());
                // Remove flag
                m_table->erase(i);
            }
        }

    #define IS_VALID_FILE                   \
        NULL != UniDataModel::getInstance() \
        && NULL != m_filePosition           \
        && *m_filePosition != UniDataModel::getInstance()->getWorkspace().endFiles()

    #define IS_VALID_ENTITY                 \
        IS_VALID_FILE                       \
        && NULL != m_entityPosition         \
        && *m_entityPosition != (*m_filePosition)->endEntities()

    #define IS_VALID_RELATION               \
        IS_VALID_FILE                       \
        && NULL != m_relationPosition       \
        && *m_relationPosition != (*m_filePosition)->endRelations()

    #define IS_VALID_ATTRIBUTE              \
        IS_VALID_ENTITY                     \
        && NULL != m_attributePosition      \
        && *m_attributePosition != (*m_entityPosition)->endAttributes()

    #define CHECK_MODEL(Cond, Message)      \
        if (!(Cond))                        \
        {                                   \
            m_logger->errorStream() << Message;\
        }                                   \
        else

    #define IMPL_MODEL_PARSER_HANDLER(NameHandler)                               \
        NameHandler::NameHandler(const boost::shared_ptr<UniFileItr>& filePosition,     \
                        const boost::shared_ptr<UniEntityItr>& entityPosition,          \
                        const boost::shared_ptr<UniRelationItr>& relationPosition,      \
                        const boost::shared_ptr<UniAttributeItr>& attributePosition)    \
        : m_filePosition(filePosition),                                          \
        m_entityPosition(entityPosition),                                        \
        m_relationPosition(relationPosition),                                    \
        m_attributePosition(attributePosition),                                  \
        m_logger(&Category::getInstance(LOGNAME))                                \
        {}                                                                       \
                                                                                 \
        void NameHandler::operator()                                             \
                (UniChar const* szStart, UniChar const* szEnd) const
        
    #define IMPL_MODEL_PARSER_ENUM_HANDLER(NameHandler, Enum, NameEnum)          \
        NameHandler::NameHandler(const boost::shared_ptr<UniFileItr>& filePosition,     \
                        const boost::shared_ptr<UniEntityItr>& entityPosition,          \
                        const boost::shared_ptr<UniRelationItr>& relationPosition,      \
                        const boost::shared_ptr<UniAttributeItr>& attributePosition,    \
                        Enum NameEnum)                                           \
        : m_filePosition(filePosition),                                          \
        m_entityPosition(entityPosition),                                        \
        m_relationPosition(relationPosition),                                    \
        m_attributePosition(attributePosition),                                  \
        m_##NameEnum(NameEnum),                                                  \
        m_logger(&Category::getInstance(LOGNAME))                                \
        {}                                                                       \
                                                                                 \
        void NameHandler::operator()                                             \
                (UniChar const* szStart, UniChar const* szEnd) const

    #define IMPL_DEFAULT_PARSER_HANDLER(NameHandler)                             \
        NameHandler::NameHandler()                                               \
        : m_logger(&Category::getInstance(LOGNAME))                              \
        {}                                                                       \
                                                                                 \
        void NameHandler::operator()                                             \
                (UniChar const* szStart, UniChar const* szEnd) const
        
    #define IMPL_DEFAULT_PARSER_ENUM_HANDLER(NameHandler, Enum, NameEnum)        \
        NameHandler::NameHandler(Enum NameEnum)                                  \
        : m_##NameEnum(NameEnum),                                                \
        m_logger(&Category::getInstance(LOGNAME))                                \
        {}                                                                       \
                                                                                 \
        void NameHandler::operator()                                             \
                (UniChar const* szStart, UniChar const* szEnd) const
            
    }
    
}
