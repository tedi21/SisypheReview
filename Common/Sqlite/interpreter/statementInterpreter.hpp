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

        virtual shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

        // Execute Query
        shared_ptr< Base<EncodingT> >
        executeStep();

        shared_ptr< Base<EncodingT> >
        executeQuery();

        // Set Values
        FACTORY_PROTOTYPE2(setBlob,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        setBlob		(shared_ptr< Base<EncodingT> > const& index,
                     shared_ptr< Base<EncodingT> > const& value);

        FACTORY_PROTOTYPE2(setDouble,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        setDouble	(shared_ptr< Base<EncodingT> > const& index,
                     shared_ptr< Base<EncodingT> > const& value);

        FACTORY_PROTOTYPE2(setInt,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        setInt		(shared_ptr< Base<EncodingT> > const& index,
                     shared_ptr< Base<EncodingT> > const& value);

        FACTORY_PROTOTYPE2(setInt64,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        setInt64		(shared_ptr< Base<EncodingT> > const& index,
                     shared_ptr< Base<EncodingT> > const& value);
                     
        FACTORY_PROTOTYPE2(setText,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        setText		(shared_ptr< Base<EncodingT> > const& index,
                     shared_ptr< Base<EncodingT> > const& value);

        // Get Value
        FACTORY_PROTOTYPE2(getBlob,
                           In< shared_ptr< Base<EncodingT> > >,
                           InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        getBlob		(shared_ptr< Base<EncodingT> > const& column,
                     shared_ptr< Base<EncodingT> >& value);

        FACTORY_PROTOTYPE2(getDouble,
                           In< shared_ptr< Base<EncodingT> > >,
                           InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        getDouble	(shared_ptr< Base<EncodingT> > const& column,
                     shared_ptr< Base<EncodingT> >& value);

        FACTORY_PROTOTYPE2(getInt,
                           In< shared_ptr< Base<EncodingT> > >,
                           InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        getInt		(shared_ptr< Base<EncodingT> > const& column,
                     shared_ptr< Base<EncodingT> >& value);

        FACTORY_PROTOTYPE2(getInt64,
                           In< shared_ptr< Base<EncodingT> > >,
                           InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        getInt64		(shared_ptr< Base<EncodingT> > const& column,
                     shared_ptr< Base<EncodingT> >& value);
                     
        FACTORY_PROTOTYPE2(getText,
                           In< shared_ptr< Base<EncodingT> > >,
                           InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        getText		(shared_ptr< Base<EncodingT> > const& column,
                     shared_ptr< Base<EncodingT> >& value);

        void setError(const std::exception& e);

        void clearError();

        FACTORY_PROTOTYPE1(getError, InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > getError(shared_ptr< Base<EncodingT> >& text) const;

        FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( StatementInterpreter, C("Statement") );
            METHOD_KEY_REGISTER ( StatementInterpreter, shared_ptr< Base<EncodingT> >, executeStep, no_const_t, C("Statement::ExecuteStep") );
            METHOD_KEY_REGISTER ( StatementInterpreter, shared_ptr< Base<EncodingT> >, executeQuery, no_const_t, C("Statement::ExecuteQuery") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, setBlob, no_const_t, C("Statement::SetBlob") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, setDouble, no_const_t, C("Statement::SetDouble") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, setInt, no_const_t, C("Statement::SetInt") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, setInt64, no_const_t, C("Statement::SetInt64") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, setText, no_const_t, C("Statement::SetText") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, getBlob, no_const_t, C("Statement::GetBlob") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, getDouble, no_const_t, C("Statement::GetDouble") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, getInt, no_const_t, C("Statement::GetInt") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, getInt64, no_const_t, C("Statement::GetInt64") );
            METHOD_KEY_REGISTER2( StatementInterpreter, shared_ptr< Base<EncodingT> >, getText, no_const_t, C("Statement::GetText") );
            METHOD_KEY_REGISTER1( StatementInterpreter, shared_ptr< Base<EncodingT> >, getError, const_t, C("Statement::GetError") );
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
    bool check_statement_pointer(shared_ptr< Base<EncodingT> > const& val, _DataStatement<EncodingT>*& o);

NAMESPACE_END

#undef C
#undef A

#include "statementInterpreter_impl.hpp"

#endif
