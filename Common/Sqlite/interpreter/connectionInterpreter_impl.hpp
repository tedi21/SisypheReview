#include "statementInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
ConnectionInterpreter<EncodingT>::ConnectionInterpreter()
{
    m_object = _DataConnection<EncodingT>::getInstance();
}

template <class EncodingT>
ConnectionInterpreter<EncodingT>::~ConnectionInterpreter()
{}

template <class EncodingT>
typename EncodingT::string_t ConnectionInterpreter<EncodingT>::toString() const
{
    return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > ConnectionInterpreter<EncodingT>::clone() const
{
    return shared_ptr< Base<EncodingT> >(new ConnectionInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t ConnectionInterpreter<EncodingT>::getClassName() const
{
    return C("Connection");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > ConnectionInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
    shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

    ParameterArray args, ret;
    if (check_parameters_array(params, args))
    {
        if (tryInvoke(this, C("Connection"), method, args, ret))
        {
            find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
            for (size_t i = 0; i < params.size(); ++i)
            {
                find_parameter(ret, i, params[i]);
            }
        }
        else
        {
            Category* logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Unexpected call in Connection, no method \"" << A(method) << "\" exists.";
        }
    }
    return obj;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::select(shared_ptr< Base<EncodingT> > const& columns,
                                         shared_ptr< Base<EncodingT> > const& tables,
                                         shared_ptr< Base<EncodingT> > const& filter)
{
   shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
   clearError();
   try
   {
       std::vector<typename EncodingT::string_t> nativeColumns, nativeTables;
       typename EncodingT::string_t nativeFilter;
       if (check_string<EncodingT>(filter, nativeFilter) &&
           check_string_array(columns, nativeColumns) &&
           check_string_array(tables, nativeTables))
       {
           res.reset(new StatementInterpreter<EncodingT>(m_object->select(nativeColumns, nativeTables, nativeFilter)));
       }
   }
   catch (std::exception& e)
   {
       setError(e);
   }
   return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::selectForUpdate(shared_ptr< Base<EncodingT> > const& columns,
                                                  shared_ptr< Base<EncodingT> > const& tables,
                                                  shared_ptr< Base<EncodingT> > const& filter,
                                                  shared_ptr< Base<EncodingT> > const& nowait)
{
    shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
    clearError();
    try
    {
        bool nativeNoWait;
        std::vector<typename EncodingT::string_t> nativeColumns, nativeTables;
        typename EncodingT::string_t nativeFilter;
        if (check_string<EncodingT>(filter, nativeFilter) &&
            check_string_array(columns, nativeColumns) &&
            check_string_array(tables, nativeTables) &&
            check_bool(nowait, nativeNoWait))
        {
            res.reset(new StatementInterpreter<EncodingT>(m_object->selectForUpdate(nativeColumns, nativeTables, nativeFilter, nativeNoWait)));
        }
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::insert(shared_ptr< Base<EncodingT> > const& table,
                                         shared_ptr< Base<EncodingT> > const& columns)
{
    shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
    clearError();
    try
    {
        std::vector<typename EncodingT::string_t> nativeColumns;
        typename EncodingT::string_t nativeTable;
        if (check_string_array(columns, nativeColumns) &&
            check_string<EncodingT>(table, nativeTable))
        {
            res.reset(new StatementInterpreter<EncodingT>(m_object->insert(nativeTable, nativeColumns)));
        }
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::deleteFrom(shared_ptr< Base<EncodingT> > const& table,
                                             shared_ptr< Base<EncodingT> > const& filter)
{
    shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
    clearError();
    try
    {
        typename EncodingT::string_t nativeFilter;
        typename EncodingT::string_t nativeTable;
        if (check_string<EncodingT>(filter, nativeFilter) &&
            check_string<EncodingT>(table, nativeTable))
        {
            res.reset(new StatementInterpreter<EncodingT>(m_object->deleteFrom(nativeTable, nativeFilter)));
        }
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::update(shared_ptr< Base<EncodingT> > const& table,
                                         shared_ptr< Base<EncodingT> > const& columns,
                                         shared_ptr< Base<EncodingT> > const& filter)
{
    shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
    clearError();
    try
    {
        std::vector<typename EncodingT::string_t> nativeColumns;
        typename EncodingT::string_t nativeTable, nativeFilter;
        if (check_string<EncodingT>(filter, nativeFilter) &&
            check_string_array(columns, nativeColumns) &&
            check_string<EncodingT>(table, nativeTable))
        {
            res.reset(new StatementInterpreter<EncodingT>(m_object->update(nativeTable, nativeColumns, nativeFilter)));
        }
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::getLastInsertID()
{
    shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
    clearError();
    try
    {
        res.reset(new Numeric<EncodingT>(m_object->getLastInsertID()));
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::selectMaxID(shared_ptr< Base<EncodingT> > const& columnid,
                                              shared_ptr< Base<EncodingT> > const& table)
{
    shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
    clearError();
    try
    {
        typename EncodingT::string_t nativeColumnId, nativeTable;
        if (check_string<EncodingT>(columnid, nativeColumnId) &&
            check_string<EncodingT>(table, nativeTable))
        {
            res.reset(new Numeric<EncodingT>(m_object->selectMaxID(nativeColumnId, nativeTable)));
        }
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::commit()
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        res.reset(new Bool<EncodingT>(m_object->commit()));
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::rollback()
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        res.reset(new Bool<EncodingT>(m_object->rollback()));
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::startTransaction()
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        res.reset(new Bool<EncodingT>(m_object->startTransaction()));
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::isTransactionInProgress()
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        res.reset(new Bool<EncodingT>(m_object->isTransactionInProgress()));
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
void
ConnectionInterpreter<EncodingT>::setPragma(shared_ptr< Base<EncodingT> > const& pragma)
{
    clearError();
    try
    {
        typename EncodingT::string_t nativePragma;
        if (check_string<EncodingT>(pragma, nativePragma))
        {
            m_object->setPragma(nativePragma);
        }
    }
    catch (std::exception& e)
    {
        setError(e);
    }
}

template <class EncodingT>
void ConnectionInterpreter<EncodingT>::setError(const std::exception& error)
{
    m_error = true;
    m_errorText = error.what();
}

template <class EncodingT>
void ConnectionInterpreter<EncodingT>::clearError()
{
    m_error = false;
    m_errorText.clear();
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > ConnectionInterpreter<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
{
    shared_ptr< String<EncodingT> > str  = dynamic_pointer_cast< String<EncodingT> >(text);
    if (str)
    {
        str->setValue(C(m_errorText));
    }
    return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_error));
}

NAMESPACE_END

#undef C
#undef A

