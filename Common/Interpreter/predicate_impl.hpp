#include "Bool.hpp"
#include "Array.hpp"
#include "Structure.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Predicate<EncodingT>::Predicate(Context<EncodingT> const& c, typename EncodingT::string_t const& functionName)
    {
        m_function = dynamic_pointer_cast< Function<EncodingT> >(c.getFunction(functionName));
        m_context = c;
        m_context.clear();
    }

    template <class EncodingT>
    Predicate<EncodingT>::~Predicate()
    {}

    template <class EncodingT>
    bool Predicate<EncodingT>::operator()(shared_ptr< Base<EncodingT> > const& value)
    {
        std::vector< shared_ptr< Base<EncodingT> > > params;
        params.push_back(value);
        return operate(params);
    }

    template <class EncodingT>
    bool Predicate<EncodingT>::operator()(shared_ptr< Base<EncodingT> > const& value1, shared_ptr< Base<EncodingT> > const& value2)
    {
        std::vector< shared_ptr< Base<EncodingT> > > params;
        params.push_back(value1);
        params.push_back(value2);
        return operate(params);
    }

    template <class EncodingT>
    bool Predicate<EncodingT>::operate(std::vector< shared_ptr< Base<EncodingT> > > const& params)
    {
        bool value = false;
        if (m_function)
        {
            std::vector<typename EncodingT::string_t> paramsName = m_function->getParams();
            for (size_t i = 0; i<params.size() && i<paramsName.size(); ++i)
            {
                m_context.add(paramsName[i], params[i]);
            }
            check_bool(m_function->interpret(m_context), value);

        }
        return value;
    }

    template <class EncodingT>
    typename EncodingT::string_t Predicate<EncodingT>::toString() const
    {
        return m_function->getName();
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Predicate<EncodingT>::clone() const
    {
        return shared_ptr< Base<EncodingT> >(new Predicate<EncodingT>(m_context, m_function->getName()));
    }

    template <class EncodingT>
    typename EncodingT::string_t Predicate<EncodingT>::getClassName() const
    {
        return C("Predicate");
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Predicate<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
    {
        shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("Predicate"), method, args, ret))
            {
                find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
                for (size_t i = 0; i < params.size(); ++i)
                {
                    find_parameter(ret, i, params[i]);
                }
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Unexpected call in Predicate, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Predicate<EncodingT>::call(shared_ptr< Base<EncodingT> > const& params)
    {
        shared_ptr< Base<EncodingT> > val(new Base<EncodingT>());
        if (m_function)
        {
            std::vector<typename EncodingT::string_t> paramsName = m_function->getParams();

            double n;
            shared_ptr< Array<EncodingT> > arr  = dynamic_pointer_cast< Array<EncodingT> >(params);
            if (arr)
            {
                if (check_numeric(arr->size(), n))
                {
                    size_t lg = (size_t)n;
                    for (size_t i = 0; i<lg && i<paramsName.size(); ++i)
                    {
                        m_context.add(paramsName[i],
                                      arr->getValue(shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(i))));
                    }
                    val = m_function->interpret(m_context);
                }
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Array expected, got " << A(val->getClassName());
            }
        }
        return val;
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Predicate<EncodingT>::getFunctionName() const
    {
        typename EncodingT::string_t name;
        if (m_function)
        {
            name = m_function->getName();
        }
        return shared_ptr< Base<EncodingT> >(new String<EncodingT>(name));
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Predicate<EncodingT>::getParameters() const
    {
        std::vector<typename EncodingT::string_t> paramsName;
        if (m_function)
        {
            paramsName = m_function->getParams();
        }
        return convert_string_array<EncodingT>(paramsName);
    }

    template <class EncodingT>
    void Predicate<EncodingT>::removeVariable(shared_ptr< Base<EncodingT> > const& name)
    {
        typename EncodingT::string_t nativeName;
        if (check_string<EncodingT>(name, nativeName))
        {
            m_context.remove(nativeName);
        }
    }

    template <class EncodingT>
    void Predicate<EncodingT>::insertVariable(shared_ptr< Base<EncodingT> > const& name, shared_ptr< Base<EncodingT> > const& variable)
    {
        typename EncodingT::string_t nativeName;
        if (check_string<EncodingT>(name, nativeName))
        {
            m_context.add(nativeName, variable);
        }
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Predicate<EncodingT>::getVariablesCount() const
    {
        return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_context.size()));
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Predicate<EncodingT>::findVariable(shared_ptr< Base<EncodingT> > const& name, shared_ptr< Base<EncodingT> >& variable) const
    {
        shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>(false));
        typename EncodingT::string_t nativeName;
        if (check_string<EncodingT>(name, nativeName))
        {
            typename Context<EncodingT>::iterator_t i = m_context.findObject(nativeName);
            if (i != m_context.end())
            {
                res.reset(new Bool<EncodingT>(true));
                variable = m_context.getObject(i);
            }
        }
        return res;
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Predicate<EncodingT>::getVariable(shared_ptr< Base<EncodingT> > const& i) const
    {
        shared_ptr< Base<EncodingT> > res(new Base<EncodingT>());
        double value = 0;
        if (check_numeric(i, value))
        {
            size_t index = 0;
            if (check_index(value, m_context.size(), index))
            {
                typename Context<EncodingT>::iterator_t i = m_context.begin();
                std::advance(i, index);
                shared_ptr< Structure<EncodingT> > st(new Structure<EncodingT>());
                st->insertField(C("Name"), shared_ptr< Base<EncodingT> >(new String<EncodingT>(m_context.getIdentifier(i))));
                st->insertField(C("Value"), m_context.getObject(i));
                res = st;
            }
        }
        return res;
    }

NAMESPACE_END

#undef C
#undef A
