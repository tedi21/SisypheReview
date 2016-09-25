
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Structure<EncodingT>::Structure()
    {}

    template <class EncodingT>
    Structure<EncodingT>::~Structure()
    {}

    template <class EncodingT>
    typename EncodingT::string_t Structure<EncodingT>::toString() const
    {
        typename EncodingT::string_t str = C("[");
        if (!m_container.empty())
        {
            iterator_t last = --m_container.end();
            for (iterator_t i = m_container.begin(); i != m_container.end(); ++i)
            {
                str += i->first + C(":") + i->second->toString();
                if (i != last)
                {
                    str += C(";");
                }
            }
        }
        str += C("]");
        return str;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Structure<EncodingT>::clone() const
    {
        boost::shared_ptr< Structure<EncodingT> > obj(new Structure<EncodingT>());
		
        for (iterator_t i = m_container.begin(); i != m_container.end(); ++i)
        {
            obj->insertField(i->first, i->second->clone());
        }
        return obj;
    }

    template <class EncodingT>
    typename EncodingT::string_t Structure<EncodingT>::getClassName() const
    {
        return C("Structure");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Structure<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        if (method == C("Fields") && params.size() == 2)
        {
            typename EncodingT::string_t nativeName;
            if (check_string<EncodingT>(params[0], nativeName))
            {
                this->insertField(nativeName, params[1]);
            }
        }
        else if (method == C("removeFields") && params.size() == 1)
        {
            typename EncodingT::string_t nativeName;
            if (check_string<EncodingT>(params[0], nativeName))
            {
                this->removeField(nativeName);
            }
        }
        else if ((method == C("FieldsCount") || method == C("size")) && params.size() == 0)
        {
            obj.reset(new Numeric<EncodingT>(this->getFieldsCount()));
        }
        else if (method == C("FindField") && params.size() == 2)
        {
            typename EncodingT::string_t nativeName;
            if (check_string<EncodingT>(params[0], nativeName))
            {
                obj.reset(new Bool<EncodingT>(this->findField(nativeName, params[1])));
            }
        }
        else if (method == C("Fields") && params.size() == 1)
        {
            double value = 0;
            if (check_numeric(params[0], value))
            {
                size_t index = 0;
                if (check_index(value, m_container.size(), index))
                {
                    iterator_t i = this->getField(index);
                    boost::shared_ptr< Structure<EncodingT> > st(new Structure<EncodingT>());
                    st->insertField(C("Name"), boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(i->first)));
                    st->insertField(C("Value"), i->second);
                    obj = st;
                }
            }
        }
        else
        {
            typename EncodingT::string_t attribute = method;
            if (params.size() == 0)
            {
                bool removeAttribute = false;
                if (attribute.size() > 6 && attribute.substr(0, 6) == C("remove"))
                {
                    removeAttribute = true;
                    attribute.erase(0, 6);
                }
                itr_t i = m_container.find(attribute);
                if (i != m_container.end())
                {
                    if (removeAttribute)
                    {
                        m_container.erase(i);
                    }
                    else
                    {
                        obj = i->second;
                    }
                }
                else
                {
                    Category * logger = &Category::getInstance(LOGNAME);
                    logger->errorStream() << "Unexpected call in Structure, no attribute \"" << A(attribute) << "\" exists.";
                }
            }
            else if (params.size() == 1)
            {
                m_container[attribute] = params[0];
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Unexpected call in Structure, \"" << A(attribute) << "\" has too many parameters.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    void Structure<EncodingT>::removeField(typename EncodingT::string_t const& name)
    {
        itr_t i = m_container.find(name);
        if (i != m_container.end())
        {
            m_container.erase(i);
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Unexpected call in Structure, no attribute \"" << A(name) << "\" exists.";
        }
    }

    template <class EncodingT>
    void Structure<EncodingT>::insertField(typename EncodingT::string_t const& name, boost::shared_ptr< Base<EncodingT> > const& value)
    {
        m_container[name] = value;
    }

    template <class EncodingT>
    size_t Structure<EncodingT>::getFieldsCount() const
    {
        return m_container.size();
    }

    template <class EncodingT>
    bool Structure<EncodingT>::findField(typename EncodingT::string_t const& name, boost::shared_ptr< Base<EncodingT> >& value) const
    {
        bool found = false;
        iterator_t i = m_container.find(name);
        if (i != m_container.end())
        {
            value = i->second;
            found = true;
        }
        return found;
    }

    template <class EncodingT>
    typename Structure<EncodingT>::iterator_t Structure<EncodingT>::getField(size_t index) const
    {
        iterator_t i = m_container.begin();
        std::advance(i, index);
        return i;
    }

NAMESPACE_END

#undef C
#undef A
