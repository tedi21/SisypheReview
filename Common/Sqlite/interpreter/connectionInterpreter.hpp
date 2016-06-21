/*
 * connectionInterpreter.hpp
 *
 *
 * @date 02-03-2014
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _CONNECTION_INTERPRETER_HPP_
#define _CONNECTION_INTERPRETER_HPP_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "DataConnection.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    using namespace boost;
    using namespace data_access;

    template <class EncodingT>
    class ConnectionInterpreter
    : public Base<EncodingT>
    {
    private:
        _DataConnection<EncodingT>* m_object;
        std::string m_errorText;
        bool m_error;

    public:
        ConnectionInterpreter();

        ~ConnectionInterpreter();

        virtual typename EncodingT::string_t toString() const;

        virtual shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

        // Get prepared statement
        FACTORY_PROTOTYPE3(select,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        select(shared_ptr< Base<EncodingT> > const& columns,
               shared_ptr< Base<EncodingT> > const& tables,
               shared_ptr< Base<EncodingT> > const& filter);

        FACTORY_PROTOTYPE4(selectForUpdate,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        selectForUpdate(shared_ptr< Base<EncodingT> > const& columns,
                        shared_ptr< Base<EncodingT> > const& tables,
                        shared_ptr< Base<EncodingT> > const& filter,
                        shared_ptr< Base<EncodingT> > const& nowait);

        FACTORY_PROTOTYPE2(insert,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        insert(shared_ptr< Base<EncodingT> > const& table,
               shared_ptr< Base<EncodingT> > const& columns);

        FACTORY_PROTOTYPE2(deleteFrom,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        deleteFrom(shared_ptr< Base<EncodingT> > const& table,
                   shared_ptr< Base<EncodingT> > const& filter);

        FACTORY_PROTOTYPE3(update,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        update(shared_ptr< Base<EncodingT> > const& table,
               shared_ptr< Base<EncodingT> > const& columns,
               shared_ptr< Base<EncodingT> > const& filter);

        // Unary query
        shared_ptr< Base<EncodingT> >
        getLastInsertID();

        FACTORY_PROTOTYPE2(selectMaxID,
                           In< shared_ptr< Base<EncodingT> > >,
                           In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> >
        selectMaxID(shared_ptr< Base<EncodingT> > const& columnid,
                    shared_ptr< Base<EncodingT> > const& table);

        shared_ptr< Base<EncodingT> >
        commit();

        shared_ptr< Base<EncodingT> >
        rollback();

        shared_ptr< Base<EncodingT> >
        startTransaction();

        shared_ptr< Base<EncodingT> >
        isTransactionInProgress();

        FACTORY_PROTOTYPE1(setPragma,
                           In< shared_ptr< Base<EncodingT> > >)
        void
        setPragma(shared_ptr< Base<EncodingT> > const& pragma);

        void setError(const std::exception& e);

        void clearError();

        FACTORY_PROTOTYPE1(getError, InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > getError(shared_ptr< Base<EncodingT> >& text) const;

        FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( ConnectionInterpreter, C("Connection") );
            METHOD_KEY_REGISTER3( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, select, no_const_t, C("Connection::Select") );
            METHOD_KEY_REGISTER4( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, selectForUpdate, no_const_t, C("Connection::SelectForUpdate") );
            METHOD_KEY_REGISTER2( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, insert, no_const_t, C("Connection::Insert") );
            METHOD_KEY_REGISTER2( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, deleteFrom, no_const_t, C("Connection::DeleteFrom") );
            METHOD_KEY_REGISTER3( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, update, no_const_t, C("Connection::Update") );
            METHOD_KEY_REGISTER ( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, getLastInsertID, no_const_t, C("Connection::LastInsertID") );
            METHOD_KEY_REGISTER2( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, selectMaxID, no_const_t, C("Connection::SelectMaxID") );
            METHOD_KEY_REGISTER ( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, commit, no_const_t, C("Connection::Commit") );
            METHOD_KEY_REGISTER ( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, rollback, no_const_t, C("Connection::Rollback") );
            METHOD_KEY_REGISTER ( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, startTransaction, no_const_t, C("Connection::StartTransaction") );
            METHOD_KEY_REGISTER1( ConnectionInterpreter, void, setPragma, no_const_t, C("Connection::SetPragma") );
            METHOD_KEY_REGISTER ( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, isTransactionInProgress, no_const_t, C("Connection::IsTransactionInProgress") );
            METHOD_KEY_REGISTER1( ConnectionInterpreter, shared_ptr< Base<EncodingT> >, getError, const_t, C("Connection::GetError") );
        FACTORY_END_REGISTER

        FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( C("Connection") );
            METHOD_KEY_UNREGISTER3( C("Connection::Select") );
            METHOD_KEY_UNREGISTER4( C("Connection::SelectForUpdate") );
            METHOD_KEY_UNREGISTER2( C("Connection::Insert") );
            METHOD_KEY_UNREGISTER2( C("Connection::DeleteFrom") );
            METHOD_KEY_UNREGISTER3( C("Connection::Update") );
            METHOD_KEY_UNREGISTER ( C("Connection::LastInsertID") );
            METHOD_KEY_UNREGISTER2( C("Connection::SelectMaxID") );
            METHOD_KEY_UNREGISTER ( C("Connection::Commit") );
            METHOD_KEY_UNREGISTER ( C("Connection::Rollback") );
            METHOD_KEY_UNREGISTER ( C("Connection::StartTransaction") );
            METHOD_KEY_UNREGISTER ( C("Connection::IsTransactionInProgress") );
            METHOD_KEY_UNREGISTER1( C("Connection::SetPragma") );
            METHOD_KEY_UNREGISTER1( C("Connection::GetError") );
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#undef C
#undef A

#include "connectionInterpreter_impl.hpp"

#endif
