#ifndef _PREDICATE_HPP_
#define _PREDICATE_HPP_

#include <boost/shared_ptr.hpp>
#include "config.hpp"
#include "macros.hpp"
#include "base.hpp"
#include "interpreter.hpp"

#define C(str) encode<ansi,EncodingT>(str)

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
        shared_ptr< Function<EncodingT> > m_function;
		
    public:
        // Constructor
        Predicate(Context<EncodingT> const& c, typename EncodingT::string_t const& functionName);

        // Destructor
        virtual ~Predicate();

        // Functors
        bool operator()(shared_ptr< Base<EncodingT> > const& value);
        bool operator()(shared_ptr< Base<EncodingT> > const& value1, shared_ptr< Base<EncodingT> > const& value2);
        bool operate(std::vector< shared_ptr< Base<EncodingT> > > const& params);

        // Virtual methods
        virtual typename EncodingT::string_t toString() const;
        virtual shared_ptr< Base<EncodingT> > clone() const;
        virtual typename EncodingT::string_t getClassName() const;
        virtual shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params);

        // Dynamic methods
        FACTORY_PROTOTYPE1(call, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > call(shared_ptr< Base<EncodingT> > const& params);

        shared_ptr< Base<EncodingT> > getFunctionName() const;

        shared_ptr< Base<EncodingT> > getParameters() const;

        FACTORY_PROTOTYPE1(removeVariable, In< shared_ptr< Base<EncodingT> > >)
        void removeVariable(shared_ptr< Base<EncodingT> > const& name);

        FACTORY_PROTOTYPE2(insertVariable, In< shared_ptr< Base<EncodingT> > >, In< shared_ptr< Base<EncodingT> > >)
        void insertVariable(shared_ptr< Base<EncodingT> > const& name, shared_ptr< Base<EncodingT> > const& variable);

        shared_ptr< Base<EncodingT> > getVariablesCount() const;

        FACTORY_PROTOTYPE2(findVariable, In< shared_ptr< Base<EncodingT> > >, InOut< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > findVariable(shared_ptr< Base<EncodingT> > const& name, shared_ptr< Base<EncodingT> >& variable) const;

        FACTORY_PROTOTYPE1(getVariable, In< shared_ptr< Base<EncodingT> > >)
        shared_ptr< Base<EncodingT> > getVariable(shared_ptr< Base<EncodingT> > const& index) const;

        // Methods registration
        FACTORY_BEGIN_REGISTER
            METHOD_KEY_REGISTER1(Predicate, shared_ptr< Base<EncodingT> >, call, no_const_t, C("Predicate::Call") )
            METHOD_KEY_REGISTER (Predicate, shared_ptr< Base<EncodingT> >, getParameters, const_t, C("Predicate::Parameters") )
            METHOD_KEY_REGISTER (Predicate, shared_ptr< Base<EncodingT> >, getFunctionName, const_t, C("Predicate::FunctionName") )
            METHOD_KEY_REGISTER1(Predicate, void, removeVariable, no_const_t, C("Predicate::removeVariables") )
            METHOD_KEY_REGISTER2(Predicate, void, insertVariable, no_const_t, C("Predicate::Variables") )
            METHOD_KEY_REGISTER (Predicate, shared_ptr< Base<EncodingT> >, getVariablesCount, const_t, C("Predicate::VariablesCount") )
            METHOD_KEY_REGISTER2(Predicate, shared_ptr< Base<EncodingT> >, findVariable, const_t, C("Predicate::FindVariable") )
            METHOD_KEY_REGISTER1(Predicate, shared_ptr< Base<EncodingT> >, getVariable, const_t, C("Predicate::Variables") )
        FACTORY_END_REGISTER

        // Methods unregistration
        FACTORY_BEGIN_UNREGISTER
            METHOD_KEY_UNREGISTER1(C("Predicate::Call"))
            METHOD_KEY_UNREGISTER (C("Predicate::Parameters"))
            METHOD_KEY_UNREGISTER (C("Predicate::FunctionName"))
            METHOD_KEY_UNREGISTER1(C("Predicate::removeVariables"))
            METHOD_KEY_UNREGISTER2(C("Predicate::Variables"))
            METHOD_KEY_UNREGISTER (C("Predicate::VariablesCount") )
            METHOD_KEY_UNREGISTER2(C("Predicate::FindVariable") )
            METHOD_KEY_UNREGISTER1(C("Predicate::Variables") )
        FACTORY_END_UNREGISTER
    };

NAMESPACE_END

#undef C

#include "predicate_impl.hpp"

#endif
