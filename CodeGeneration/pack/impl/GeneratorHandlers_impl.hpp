
namespace dsg {

    namespace generator {

    #define IMPL_MODEL_GEN_HANDLER(NameHandler, Element, Return)\
        NameHandler::NameHandler()                              \
        : m_logger(&Category::getInstance(LOGNAME))             \
        {}                                                      \
                                                                \
        Return NameHandler::operator()                          \
                (const_Uni##Element##Itr& i) const

    #define IMPL_MODEL_GEN_MEMBER_HANDLER(NameHandler, Element, Member, NameMember, Return)\
        NameHandler::NameHandler(Member NameMember)                              \
        : m_##NameMember(NameMember),                                            \
        m_logger(&Category::getInstance(LOGNAME))                                \
        {}                                                                       \
                                                                                 \
        Return NameHandler::operator()                                           \
                (const_Uni##Element##Itr& i) const

    #define IMPL_MODEL_GEN_ENUM_HANDLER(NameHandler, Element, Enum, NameEnum)    \
        IMPL_MODEL_GEN_MEMBER_HANDLER(NameHandler, Element, Enum, NameEnum, bool)

    #define IMPL_DEFAULT_GEN_HANDLER(NameHandler, Return)                        \
        NameHandler::NameHandler()                                               \
        : m_logger(&Category::getInstance(LOGNAME))                              \
        {}                                                                       \
                                                                                 \
        Return NameHandler::operator()                                           \
                () const
        
    #define IMPL_DEFAULT_GEN_ENUM_HANDLER(NameHandler, Enum, NameEnum)           \
        NameHandler::NameHandler(Enum NameEnum)                                  \
        : m_##NameEnum(NameEnum),                                                \
        m_logger(&Category::getInstance(LOGNAME))                                \
        {}                                                                       \
                                                                                 \
        bool NameHandler::operator()                                             \
                () const

    }
    
}
