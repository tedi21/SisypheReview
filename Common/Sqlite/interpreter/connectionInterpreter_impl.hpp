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
ConnectionInterpreter<EncodingT>::ConnectionInterpreter(boost::shared_ptr< Base<EncodingT> > const& value)
{
    typename EncodingT::string_t str;
    if (check_string<EncodingT>(value, str))
    {
        m_object = _DataConnection<EncodingT>::getInstance(str);
    }
}

template <class EncodingT>
typename EncodingT::string_t ConnectionInterpreter<EncodingT>::toString() const
{
    return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > ConnectionInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new ConnectionInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t ConnectionInterpreter<EncodingT>::getClassName() const
{
    return C("Connection");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > ConnectionInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
    boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

    ParameterArray args, ret;
    if (check_parameters_array(params, args))
    {
        if (tryInvoke(this, C("Connection"), method, args, ret) ||
            tryInvoke(this, C("Base"), method, args, ret))
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
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::select(boost::shared_ptr< Base<EncodingT> > const& columns,
                                         boost::shared_ptr< Base<EncodingT> > const& tables,
                                         boost::shared_ptr< Base<EncodingT> > const& filter)
{
    boost::shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
    if (m_object)
    {
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
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::selectForUpdate(boost::shared_ptr< Base<EncodingT> > const& columns,
                                                  boost::shared_ptr< Base<EncodingT> > const& tables,
                                                  boost::shared_ptr< Base<EncodingT> > const& filter,
                                                  boost::shared_ptr< Base<EncodingT> > const& nowait)
{
    boost::shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
    if (m_object)
    {
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
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::insert(boost::shared_ptr< Base<EncodingT> > const& table,
                                         boost::shared_ptr< Base<EncodingT> > const& columns)
{
    boost::shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
    if (m_object)
    {
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
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::deleteFrom(boost::shared_ptr< Base<EncodingT> > const& table,
                                             boost::shared_ptr< Base<EncodingT> > const& filter)
{
    boost::shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
    if (m_object)
    {
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
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::update(boost::shared_ptr< Base<EncodingT> > const& table,
                                         boost::shared_ptr< Base<EncodingT> > const& columns,
                                         boost::shared_ptr< Base<EncodingT> > const& filter)
{
    boost::shared_ptr< Base<EncodingT> > res(new StatementInterpreter<EncodingT>());
    if (m_object)
    {
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
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::getLastInsertID()
{
    boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
    if (m_object)
    {
      clearError();
      try
      {
          res.reset(new Numeric<EncodingT>(m_object->getLastInsertID()));
      }
      catch (std::exception& e)
      {
          setError(e);
      }
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::selectMaxID(boost::shared_ptr< Base<EncodingT> > const& columnid,
                                              boost::shared_ptr< Base<EncodingT> > const& table)
{
    boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>());
    if (m_object)
    {
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
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::commit()
{
    boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    if (m_object)
    {
      clearError();
      try
      {
          res.reset(new Bool<EncodingT>(m_object->commit()));
      }
      catch (std::exception& e)
      {
          setError(e);
      }
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::rollback()
{
    boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    if (m_object)
    {
      clearError();
      try
      {
          res.reset(new Bool<EncodingT>(m_object->rollback()));
      }
      catch (std::exception& e)
      {
          setError(e);
      }
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::startTransaction()
{
    boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    if (m_object)
    {
      clearError();
      try
      {
          res.reset(new Bool<EncodingT>(m_object->startTransaction()));
      }
      catch (std::exception& e)
      {
          setError(e);
      }
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::isTransactionInProgress()
{
    boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    if (m_object)
    {
      clearError();
      try
      {
          res.reset(new Bool<EncodingT>(m_object->isTransactionInProgress()));
      }
      catch (std::exception& e)
      {
          setError(e);
      }
    }
    return res;
}

template <class EncodingT>
void
ConnectionInterpreter<EncodingT>::setPragma(boost::shared_ptr< Base<EncodingT> > const& pragma)
{
    if (m_object)
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
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
ConnectionInterpreter<EncodingT>::openConnection(boost::shared_ptr< Base<EncodingT> > const& db)
{
    boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    typename EncodingT::string_t str;
    if (check_string<EncodingT>(db, str))
    {
        res.reset(new Bool<EncodingT>(_DataConnection<EncodingT>::openConnection(EncodingT::EMPTY, 0, str, EncodingT::EMPTY, EncodingT::EMPTY)));
        m_object = _DataConnection<EncodingT>::getInstance(str);
    }
    return res;
}

template <class EncodingT>
void
ConnectionInterpreter<EncodingT>::closeConnection(boost::shared_ptr< Base<EncodingT> > const& db)
{
    typename EncodingT::string_t str;
    if (check_string<EncodingT>(db, str))
    {
        _DataConnection<EncodingT>::closeConnection(str);
        m_object = NULL;
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
boost::shared_ptr< Base<EncodingT> > ConnectionInterpreter<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const
{
    boost::shared_ptr< String<EncodingT> > str  = dynamic_pointer_cast< String<EncodingT> >(text);
    if (str)
    {
        str->value(C(m_errorText));
    }
    return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_error));
}

NAMESPACE_END

#undef C
#undef A

