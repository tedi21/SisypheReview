#include "Array.hpp"
#include "Bool.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DataParametersInterpreter<EncodingT>::DataParametersInterpreter()
{}

template <class EncodingT>
DataParametersInterpreter<EncodingT>::~DataParametersInterpreter()
{}

template <class EncodingT>
typename EncodingT::string_t DataParametersInterpreter<EncodingT>::toString() const
{
    return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataParametersInterpreter<EncodingT>::clone() const
{
    Category* logger = &Category::getInstance(LOGNAME);
    logger->warnStream() << "Cannot clone DataParameters object.";
    return boost::shared_ptr< Base<EncodingT> >(new DataParametersInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DataParametersInterpreter<EncodingT>::getClassName() const
{
    return C("DataParameters");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DataParametersInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
    boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

    ParameterArray args, ret;
    if (check_parameters_array(params, args))
    {
        if (tryInvoke(this, C("DataParameters"), method, args, ret))
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
            logger->errorStream() << "Unexpected call in DataParameters, no method \"" << A(method) << "\" exists.";
        }
    }
    return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> >
DataParametersInterpreter<EncodingT>::fill(boost::shared_ptr< Base<EncodingT> >& statement) const
{
    boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());

    _DataStatement<EncodingT>* nativeStatement;
    if (check_statement_pointer(statement, nativeStatement))
    {
        res.reset(new Bool<EncodingT>(m_object.fill(*nativeStatement)));
    }
    return res;
}

template <class EncodingT>
void
DataParametersInterpreter<EncodingT>::addBlob(const boost::shared_ptr< Base<EncodingT> >& value)
{
    boost::container::vector<unsigned char> nativeValue;
    if (check_numeric_array(value, nativeValue))
    {
        m_object.addBlob(nativeValue);
    }
}

template <class EncodingT>
void
DataParametersInterpreter<EncodingT>::addDouble(const boost::shared_ptr< Base<EncodingT> >& value)
{
    double nativeValue;
    if (check_numeric(value, nativeValue))
    {
        m_object.addDouble(nativeValue);
    }
}

template <class EncodingT>
void
DataParametersInterpreter<EncodingT>::addInt(const boost::shared_ptr< Base<EncodingT> >& value)
{
    double nativeValue;
    if (check_numeric(value, nativeValue))
    {
        m_object.addInt(nativeValue);
    }
}

template <class EncodingT>
void
DataParametersInterpreter<EncodingT>::addInt64(const boost::shared_ptr< Base<EncodingT> >& value)
{
    double nativeValue;
    if (check_numeric(value, nativeValue))
    {
        m_object.addInt64(nativeValue);
    }
}

template <class EncodingT>
void
DataParametersInterpreter<EncodingT>::addText(const boost::shared_ptr< Base<EncodingT> >& value)
{
    typename EncodingT::string_t nativeValue;
    if (check_string<EncodingT>(value, nativeValue))
    {
        m_object.addText(nativeValue);
    }
}

NAMESPACE_END

#undef C
#undef A

