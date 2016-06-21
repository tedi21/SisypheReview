#include "Array.hpp"
#include "Bool.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
StatementInterpreter<EncodingT>::StatementInterpreter()
{}

template <class EncodingT>
StatementInterpreter<EncodingT>::StatementInterpreter(_DataStatement<EncodingT>& stmt)
{
    m_object.swap(stmt);
}

template <class EncodingT>
StatementInterpreter<EncodingT>::~StatementInterpreter()
{}

template <class EncodingT>
_DataStatement<EncodingT>*
StatementInterpreter<EncodingT>::getPointer()
{
    return &m_object;
}

template <class EncodingT>
typename EncodingT::string_t StatementInterpreter<EncodingT>::toString() const
{
    return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > StatementInterpreter<EncodingT>::clone() const
{
    Category* logger = &Category::getInstance(LOGNAME);
    logger->warnStream() << "Cannot clone Statement object.";
    return shared_ptr< Base<EncodingT> >(new StatementInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t StatementInterpreter<EncodingT>::getClassName() const
{
    return C("Statement");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > StatementInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
    shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

    ParameterArray args, ret;
    if (check_parameters_array(params, args))
    {
        if (tryInvoke(this, C("Statement"), method, args, ret))
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
            logger->errorStream() << "Unexpected call in Statement, no method \"" << A(method) << "\" exists.";
        }
    }
    return obj;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
StatementInterpreter<EncodingT>::executeStep()
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        res.reset(new Bool<EncodingT>(m_object.executeStep()));
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
StatementInterpreter<EncodingT>::executeQuery()
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        res.reset(new Bool<EncodingT>(m_object.executeQuery()));
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> >
StatementInterpreter<EncodingT>::setBlob(shared_ptr< Base<EncodingT> > const& index,
                                         shared_ptr< Base<EncodingT> > const& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeIndex;
        boost::container::vector<unsigned char> nativeValue;
        if (check_numeric(index, nativeIndex) &&
            check_numeric_array(value, nativeValue))
        {
            res.reset(new Bool<EncodingT>(m_object.setBlob(nativeIndex, nativeValue)));
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
StatementInterpreter<EncodingT>::setDouble(shared_ptr< Base<EncodingT> > const& index,
                                           shared_ptr< Base<EncodingT> > const& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeIndex;
        double nativeValue;
        if (check_numeric(index, nativeIndex) &&
            check_numeric(value, nativeValue))
        {
            res.reset(new Bool<EncodingT>(m_object.setDouble(nativeIndex, nativeValue)));
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
StatementInterpreter<EncodingT>::setInt(shared_ptr< Base<EncodingT> > const& index,
                                        shared_ptr< Base<EncodingT> > const& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeIndex;
        double nativeValue;
        if (check_numeric(index, nativeIndex) &&
            check_numeric(value, nativeValue))
        {
            res.reset(new Bool<EncodingT>(m_object.setInt(nativeIndex, nativeValue)));
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
StatementInterpreter<EncodingT>::setInt64(shared_ptr< Base<EncodingT> > const& index,
                                        shared_ptr< Base<EncodingT> > const& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeIndex;
        double nativeValue;
        if (check_numeric(index, nativeIndex) &&
            check_numeric(value, nativeValue))
        {
            res.reset(new Bool<EncodingT>(m_object.setInt64(nativeIndex, nativeValue)));
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
StatementInterpreter<EncodingT>::setText(shared_ptr< Base<EncodingT> > const& index,
                                         shared_ptr< Base<EncodingT> > const& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeIndex;
        typename EncodingT::string_t nativeValue;
        if (check_numeric(index, nativeIndex) &&
            check_string<EncodingT>(value, nativeValue))
        {
            res.reset(new Bool<EncodingT>(m_object.setText(nativeIndex, nativeValue)));
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
StatementInterpreter<EncodingT>::getBlob(shared_ptr< Base<EncodingT> > const& column,
                                         shared_ptr< Base<EncodingT> >& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeColumn;
        boost::container::vector<unsigned char> nativeValue;
        if (check_numeric(column, nativeColumn))
        {
            res.reset(new Bool<EncodingT>(m_object.getBlob(nativeColumn, nativeValue)));
            value = convert_numeric_array<EncodingT>(nativeValue);
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
StatementInterpreter<EncodingT>::getDouble(shared_ptr< Base<EncodingT> > const& column,
                                           shared_ptr< Base<EncodingT> >& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeColumn;
        double nativeValue;
        if (check_numeric(column, nativeColumn))
        {
            res.reset(new Bool<EncodingT>(m_object.getDouble(nativeColumn, nativeValue)));
            value.reset(new Numeric<EncodingT>(nativeValue));
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
StatementInterpreter<EncodingT>::getInt(shared_ptr< Base<EncodingT> > const& column,
                                        shared_ptr< Base<EncodingT> >& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeColumn;
        int nativeValue;
        if (check_numeric(column, nativeColumn))
        {
            res.reset(new Bool<EncodingT>(m_object.getInt(nativeColumn, nativeValue)));
            value.reset(new Numeric<EncodingT>(nativeValue));
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
StatementInterpreter<EncodingT>::getInt64(shared_ptr< Base<EncodingT> > const& column,
                                        shared_ptr< Base<EncodingT> >& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeColumn;
        long long nativeValue;
        if (check_numeric(column, nativeColumn))
        {
            res.reset(new Bool<EncodingT>(m_object.getInt64(nativeColumn, nativeValue)));
            value.reset(new Numeric<EncodingT>(nativeValue));
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
StatementInterpreter<EncodingT>::getText(shared_ptr< Base<EncodingT> > const& column,
                                         shared_ptr< Base<EncodingT> >& value)
{
    shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
    clearError();
    try
    {
        double nativeColumn;
        typename EncodingT::string_t nativeValue;
        if (check_numeric(column, nativeColumn))
        {
            res.reset(new Bool<EncodingT>(m_object.getText(nativeColumn, nativeValue)));
            value.reset(new String<EncodingT>(nativeValue));
        }
    }
    catch (std::exception& e)
    {
        setError(e);
    }
    return res;
}

template <class EncodingT>
void StatementInterpreter<EncodingT>::setError(const std::exception& error)
{
    m_error = true;
    m_errorText = error.what();
}

template <class EncodingT>
void StatementInterpreter<EncodingT>::clearError()
{
    m_error = false;
    m_errorText.clear();
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > StatementInterpreter<EncodingT>::getError(shared_ptr< Base<EncodingT> >& text) const
{
    shared_ptr< String<EncodingT> > str  = dynamic_pointer_cast< String<EncodingT> >(text);
    if (str)
    {
        str->setValue(C(m_errorText));
    }
    return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_error));
}

template <class EncodingT>
bool check_statement_pointer(shared_ptr< Base<EncodingT> > const& val, _DataStatement<EncodingT>*& o)
{
    shared_ptr< StatementInterpreter<EncodingT> > value  = dynamic_pointer_cast< StatementInterpreter<EncodingT> >(val);
    if (value)
    {
        o = value->getPointer();
    }
    else
    {
        Category* logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Statement expected, got " << A(val->getClassName());
    }
    return value;
}

NAMESPACE_END

#undef C
#undef A

