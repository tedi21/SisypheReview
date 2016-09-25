/*
 * statementInterpreter.hpp
 *
 *
 * @date 02-03-2014
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _STATEMENT_INTERPRETER_HPP_
#define _STATEMENT_INTERPRETER_HPP_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "DataStatement.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    using namespace boost;
    using namespace data_access;

    template <class EncodingT>
    class StatementInterpreter
    : public Base<EncodingT>
    {
    private:
        _DataStatement<EncodingT> m_object;
        std::string m_errorText;
        bool m_error;

    public:
        StatementInterpreter();

        StatementInterpreter(_DataStatement<EncodingT>& stmt);

        ~StatementInterpreter();

        _DataStatement<EncodingT>* getPointer();

        virtual typename EncodingT::string_t toString() const;

        virtual boost::shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        // Execute Query
        boost::shared_ptr< Base<EncodingT> >
        executeStep();

        boost::shared_ptr< Base<EncodingT> >
        executeQuery();

        // Set Values
        FACTORY_PROTOTYPE2(setBlob,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        setBlob		(boost::shared_ptr< Base<EncodingT> > const& index,
                     boost::shared_ptr< Base<EncodingT> > const& value);

        FACTORY_PROTOTYPE2(setDouble,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        setDouble	(boost::shared_ptr< Base<EncodingT> > const& index,
                     boost::shared_ptr< Base<EncodingT> > const& value);

        FACTORY_PROTOTYPE2(setInt,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        setInt		(boost::shared_ptr< Base<EncodingT> > const& index,
                     boost::shared_ptr< Base<EncodingT> > const& value);

        FACTORY_PROTOTYPE2(setInt64,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        setInt64		(boost::shared_ptr< Base<EncodingT> > const& index,
                     boost::shared_ptr< Base<EncodingT> > const& value);
                     
        FACTORY_PROTOTYPE2(setText,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        setText		(boost::shared_ptr< Base<EncodingT> > const& index,
                     boost::shared_ptr< Base<EncodingT> > const& value);

        // Get Value
        FACTORY_PROTOTYPE2(getBlob,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        getBlob		(boost::shared_ptr< Base<EncodingT> > const& column,
                     boost::shared_ptr< Base<EncodingT> >& value);

        FACTORY_PROTOTYPE2(getDouble,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        getDouble	(boost::shared_ptr< Base<EncodingT> > const& column,
                     boost::shared_ptr< Base<EncodingT> >& value);

        FACTORY_PROTOTYPE2(getInt,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        getInt		(boost::shared_ptr< Base<EncodingT> > const& column,
                     boost::shared_ptr< Base<EncodingT> >& value);

        FACTORY_PROTOTYPE2(getInt64,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        getInt64		(boost::shared_ptr< Base<EncodingT> > const& column,
                     boost::shared_ptr< Base<EncodingT> >& value);
                     
        FACTORY_PROTOTYPE2(getText,
                           In< boost::shared_ptr< Base<EncodingT> > >,
                           InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        getText		(boost::shared_ptr< Base<EncodingT> > const& column,
                     boost::shared_ptr< Base<EncodingT> >& value);

        void setError(const std::exception& e);

        void clearError();

        FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

        FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( StatementInterpreter, C("Statement") );
            METHOD_KEY_REGISTER ( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, executeStep, no_const_t, C("Statement::ExecuteStep") );
            METHOD_KEY_REGISTER ( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, executeQuery, no_const_t, C("Statement::ExecuteQuery") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, setBlob, no_const_t, C("Statement::SetBlob") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, setDouble, no_const_t, C("Statement::SetDouble") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, setInt, no_const_t, C("Statement::SetInt") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, setInt64, no_const_t, C("Statement::SetInt64") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, setText, no_const_t, C("Statement::SetText") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, getBlob, no_const_t, C("Statement::GetBlob") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, getDouble, no_const_t, C("Statement::GetDouble") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, getInt, no_const_t, C("Statement::GetInt") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, getInt64, no_const_t, C("Statement::GetInt64") );
            METHOD_KEY_REGISTER2( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, getText, no_const_t, C("Statement::GetText") );
            METHOD_KEY_REGISTER1( StatementInterpreter, boost::shared_ptr< Base<EncodingT> >, getError, const_t, C("Statement::GetError") );
        FACTORY_END_REGISTER

        FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( C("Statement") );
            METHOD_KEY_UNREGISTER ( C("Statement::ExecuteStep") );
            METHOD_KEY_UNREGISTER ( C("Statement::ExecuteQuery") );
            METHOD_KEY_UNREGISTER2( C("Statement::SetBlob") );
            METHOD_KEY_UNREGISTER2( C("Statement::SetDouble") );
            METHOD_KEY_UNREGISTER2( C("Statement::SetInt") );
            METHOD_KEY_UNREGISTER2( C("Statement::SetInt64") );
            METHOD_KEY_UNREGISTER2( C("Statement::SetText") );
            METHOD_KEY_UNREGISTER2( C("Statement::GetBlob") );
            METHOD_KEY_UNREGISTER2( C("Statement::GetDouble") );
            METHOD_KEY_UNREGISTER2( C("Statement::GetInt") );
            METHOD_KEY_UNREGISTER2( C("Statement::GetInt64") );
            METHOD_KEY_UNREGISTER2( C("Statement::GetText") );
            METHOD_KEY_UNREGISTER1( C("Statement::GetError") );
        FACTORY_END_UNREGISTER
    };

    template <class EncodingT>
    bool check_statement_pointer(boost::shared_ptr< Base<EncodingT> > const& val, _DataStatement<EncodingT>*& o);

NAMESPACE_END

#undef C
#undef A

#include "statementInterpreter_impl.hpp"

#endif
