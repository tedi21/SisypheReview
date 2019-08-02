/*
 * dataParametersInterpreter.hpp
 *
 *
 * @date 02-03-2014
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _DATA_PARAMETERS_INTERPRETER_HPP_
#define _DATA_PARAMETERS_INTERPRETER_HPP_

#include "config.hpp"
#include "Macros.hpp"
#include "String.hpp"
#include "dataparameters.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    using namespace boost;
    using namespace data_access;

    template <class EncodingT>
    class DataParametersInterpreter
    : public Base<EncodingT>
    {
    private:
        _DataParameters<EncodingT> m_object;

    public:
        DataParametersInterpreter();

        virtual typename EncodingT::string_t toString() const;

        virtual boost::shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        // Fill Statement
        FACTORY_PROTOTYPE1(fill,
                           InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> >
        fill(boost::shared_ptr< Base<EncodingT> >& statement) const;

        // Add Value
        FACTORY_PROTOTYPE1(addBlob,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        void
        addBlob		(const boost::shared_ptr< Base<EncodingT> >& value);

        FACTORY_PROTOTYPE1(addDouble,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        void
        addDouble	(const boost::shared_ptr< Base<EncodingT> >& value);

        FACTORY_PROTOTYPE1(addInt,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        void
        addInt		(const boost::shared_ptr< Base<EncodingT> >& value);
        
        FACTORY_PROTOTYPE1(addInt64,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        void
        addInt64	(const boost::shared_ptr< Base<EncodingT> >& value);

        FACTORY_PROTOTYPE1(addText,
                           In< boost::shared_ptr< Base<EncodingT> > >)
        void
        addText		(const boost::shared_ptr< Base<EncodingT> >& value);

        FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( DataParametersInterpreter, UCS("DataParameters") );
            METHOD_KEY_REGISTER1( DataParametersInterpreter, boost::shared_ptr< Base<EncodingT> >, fill, const_t, UCS("DataParameters::Fill") );
            METHOD_KEY_REGISTER1( DataParametersInterpreter, void, addBlob, no_const_t, UCS("DataParameters::AddBlob") );
            METHOD_KEY_REGISTER1( DataParametersInterpreter, void, addDouble, no_const_t, UCS("DataParameters::AddDouble") );
            METHOD_KEY_REGISTER1( DataParametersInterpreter, void, addInt, no_const_t, UCS("DataParameters::AddInt") );
            METHOD_KEY_REGISTER1( DataParametersInterpreter, void, addInt64, no_const_t, UCS("DataParameters::AddInt64") );
            METHOD_KEY_REGISTER1( DataParametersInterpreter, void, addText, no_const_t, UCS("DataParameters::AddText") );
        FACTORY_END_REGISTER

        FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( UCS("DataParameters") );
            METHOD_KEY_UNREGISTER1( UCS("DataParameters::Fill") );
            METHOD_KEY_UNREGISTER1( UCS("DataParameters::AddBlob") );
            METHOD_KEY_UNREGISTER1( UCS("DataParameters::AddDouble") );
            METHOD_KEY_UNREGISTER1( UCS("DataParameters::AddInt") );
            METHOD_KEY_UNREGISTER1( UCS("DataParameters::AddInt64") );
            METHOD_KEY_UNREGISTER1( UCS("DataParameters::AddText") );
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#undef C
#undef A

#include "dataParametersInterpreter_impl.hpp"

#endif
