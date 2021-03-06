#ifndef _PREDICATE_HPP_
#define _PREDICATE_HPP_

#include <boost/shared_ptr.hpp>
#include "config.hpp"
#include "Macros.hpp"
#include "Interpreter.hpp"
#include "Base.hpp"

using namespace boost;
using namespace log4cpp;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    class Function;

    template <class EncodingT>
    class Predicate
    : public Base<EncodingT>
    {
    private:
        Context<EncodingT> m_context;
        boost::shared_ptr< Function<EncodingT> > m_function;
		
    public:
        // Constructor
        Predicate(Context<EncodingT> const& c, typename EncodingT::string_t const& functionName);

        // Functors
        bool operator()(boost::shared_ptr< Base<EncodingT> > const& value);
        bool operator()(boost::shared_ptr< Base<EncodingT> > const& value1, boost::shared_ptr< Base<EncodingT> > const& value2);
        bool operate(std::vector< boost::shared_ptr< Base<EncodingT> > > const& params);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual boost::shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        // Dynamic methods
        FACTORY_PROTOTYPE1(call, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > call(boost::shared_ptr< Base<EncodingT> > const& params);

        boost::shared_ptr< Base<EncodingT> > getFunctionName() const;

        boost::shared_ptr< Base<EncodingT> > getParameters() const;

        FACTORY_PROTOTYPE1(removeVariable, In< boost::shared_ptr< Base<EncodingT> > >)
        void removeVariable(boost::shared_ptr< Base<EncodingT> > const& name);

        FACTORY_PROTOTYPE2(insertVariable, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void insertVariable(boost::shared_ptr< Base<EncodingT> > const& name, boost::shared_ptr< Base<EncodingT> > const& variable);

        boost::shared_ptr< Base<EncodingT> > getVariablesCount() const;

        FACTORY_PROTOTYPE2(findVariable, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > findVariable(boost::shared_ptr< Base<EncodingT> > const& name, boost::shared_ptr< Base<EncodingT> >& variable) const;

        FACTORY_PROTOTYPE1(getVariable, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > getVariable(boost::shared_ptr< Base<EncodingT> > const& index) const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            METHOD_KEY_REGISTER1(Predicate, boost::shared_ptr< Base<EncodingT> >, call, no_const_t, UCS("Predicate::Call") )
            METHOD_KEY_REGISTER (Predicate, boost::shared_ptr< Base<EncodingT> >, getParameters, const_t, UCS("Predicate::Parameters") )
            METHOD_KEY_REGISTER (Predicate, boost::shared_ptr< Base<EncodingT> >, getFunctionName, const_t, UCS("Predicate::FunctionName") )
            METHOD_KEY_REGISTER1(Predicate, void, removeVariable, no_const_t, UCS("Predicate::removeVariables") )
            METHOD_KEY_REGISTER2(Predicate, void, insertVariable, no_const_t, UCS("Predicate::Variables") )
            METHOD_KEY_REGISTER (Predicate, boost::shared_ptr< Base<EncodingT> >, getVariablesCount, const_t, UCS("Predicate::VariablesCount") )
            METHOD_KEY_REGISTER2(Predicate, boost::shared_ptr< Base<EncodingT> >, findVariable, const_t, UCS("Predicate::FindVariable") )
            METHOD_KEY_REGISTER1(Predicate, boost::shared_ptr< Base<EncodingT> >, getVariable, const_t, UCS("Predicate::Variables") )
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            METHOD_KEY_UNREGISTER1(UCS("Predicate::Call"))
            METHOD_KEY_UNREGISTER (UCS("Predicate::Parameters"))
            METHOD_KEY_UNREGISTER (UCS("Predicate::FunctionName"))
            METHOD_KEY_UNREGISTER1(UCS("Predicate::removeVariables"))
            METHOD_KEY_UNREGISTER2(UCS("Predicate::Variables"))
            METHOD_KEY_UNREGISTER (UCS("Predicate::VariablesCount") )
            METHOD_KEY_UNREGISTER2(UCS("Predicate::FindVariable") )
            METHOD_KEY_UNREGISTER1(UCS("Predicate::Variables") )
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#include "Predicate_impl.hpp"

#endif
