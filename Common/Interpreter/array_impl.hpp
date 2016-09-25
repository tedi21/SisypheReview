#include "Predicate.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Array<EncodingT>::Array()
    {}

    template <class EncodingT>
    Array<EncodingT>::~Array()
    {}

    template <class EncodingT>
    typename EncodingT::string_t Array<EncodingT>::toString() const
    {
        typename EncodingT::string_t str = C("[");
        typename std::vector< boost::shared_ptr< Base<EncodingT> > >::const_iterator i;
        for (i = m_container.begin(); i != m_container.end(); ++i)
        {
            str += (*i)->toString();
            if (i != m_container.end()-1)
            {
                str += C(";");
            }
        }
        str += C("]");
        return str;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Array<EncodingT>::clone() const
    {
        boost::shared_ptr< Array<EncodingT> > obj(new Array<EncodingT>());
		
        typename std::vector< boost::shared_ptr< Base<EncodingT> > >::const_iterator i;
        for (i = m_container.begin(); i != m_container.end(); ++i)
        {
            obj->addValue((*i)->clone());
        }
        return obj;
    }

    template <class EncodingT>
    typename EncodingT::string_t Array<EncodingT>::getClassName() const
    {
        return C("Array");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Array<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("Array"), method, args, ret) ||
                tryInvoke(this, C("String"), method, args, ret))
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
                logger->errorStream() << "Unexpected call in Array, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    void Array<EncodingT>::addValue(boost::shared_ptr< Base<EncodingT> > const& val)
    {
        insertValue(size(), val);
    }

    template <class EncodingT>
    void Array<EncodingT>::insertValue(boost::shared_ptr< Base<EncodingT> > const& i, boost::shared_ptr< Base<EncodingT> > const& val)
    {
        double value = 0;     
        if (check_numeric(i, value))
        {
            size_t index = 0;
            if (check_index(value, m_container.size()+1, index))
            {
                m_container.insert(m_container.begin()+index, val);
            }
        }
    }

    template <class EncodingT>
    void Array<EncodingT>::removeValue(boost::shared_ptr< Base<EncodingT> > const& i)
    {
        double value = 0;     
        if (check_numeric(i, value))
        {
            size_t index = 0;
            if (check_index(value, m_container.size(), index))
            {
                m_container.erase(m_container.begin()+index);
            }
        }
    }
    
    template <class EncodingT>
    void Array<EncodingT>::clear()
    {
        m_container.clear();
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Array<EncodingT>::getValue(boost::shared_ptr< Base<EncodingT> > const& i) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Base<EncodingT>);
        double value = 0;     
        if (check_numeric(i, value))
        {
            size_t index = 0;
            if (check_index(value, m_container.size(), index))
            {
                res = m_container[index];
            }
        }
        return res;    
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Array<EncodingT>::size() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_container.size()));
    }

    template <class EncodingT>
    void Array<EncodingT>::sort(boost::shared_ptr< Base<EncodingT> > const& function)
    {
        boost::shared_ptr< Predicate<EncodingT> > value  = dynamic_pointer_cast< Predicate<EncodingT> >(function);
        if (value)
        {
            std::sort(m_container.begin(), m_container.end(), *value);
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Predicate expected, got " << A(function->getClassName());
        }
    }

    template <class EncodingT>
    void Array<EncodingT>::sort()
    {
        std::sort(m_container.begin(), m_container.end());
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Array<EncodingT>::find(boost::shared_ptr< Base<EncodingT> > const& function) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>(m_container.size()));
        boost::shared_ptr< Predicate<EncodingT> > value  = dynamic_pointer_cast< Predicate<EncodingT> >(function);
        if (value)
        {
            typename std::vector< boost::shared_ptr< Base<EncodingT> > >::const_iterator i =
                    std::find_if(m_container.begin(), m_container.end(), *value);
            res.reset(new Numeric<EncodingT>(i - m_container.begin()));
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Predicate expected, got " << A(function->getClassName());
        }
        return res;
    }

    inline bool check_index(double value, size_t size, size_t& index)
    {
        index = (size_t) value;
        bool inside = index < size;
        if (!inside)
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Index out of range : Index [" << index << "], Max [" << size-1 << "]";
        }
        return inside;
    }
	
    template <class EncodingT, class T>
    boost::shared_ptr< Base<EncodingT> > convert_numeric_array(const bc::vector<T>& value)
	{
                boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
		for (size_t i=0; i<value.size(); ++i)
		{
                        arr->addValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(value[i])));
		}
		return arr;
	}

    template <class EncodingT, class T>
    bool check_numeric_array(boost::shared_ptr< Base<EncodingT> > const& val, bc::vector<T>& v)
    {
      double n, numeric;
      boost::shared_ptr< Array<EncodingT> > value  = dynamic_pointer_cast< Array<EncodingT> >(val);
      if (value)
      {
        v.clear();
        if (check_numeric(value->size(), n))
        {
          size_t lg = (size_t)n;
          for (size_t i=0; i<lg; ++i)
          {
            if (check_numeric(
              value->getValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(i))),
              numeric))
            {
              v.push_back(numeric);
            }
          }
        }
      }
      else
      {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Array expected, got " << A(val->getClassName());
      }
      return (value != NULL);
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > convert_string_array(const std::vector<typename EncodingT::string_t>& value)
    {
        boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
        for (size_t i=0; i<value.size(); ++i)
        {
            arr->addValue(boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(value[i])));
        }
        return arr;
    }

    template <class EncodingT>
    bool check_string_array(boost::shared_ptr< Base<EncodingT> > const& val, std::vector<typename EncodingT::string_t>& v)
    {
      double n;
      typename EncodingT::string_t str;
      boost::shared_ptr< Array<EncodingT> > value  = dynamic_pointer_cast< Array<EncodingT> >(val);
      if (value)
      {
          v.clear();
          if (check_numeric(value->size(), n))
          {
              size_t lg = (size_t)n;
              for (size_t i=0; i<lg; ++i)
              {
                  if (check_string<EncodingT>(
                      value->getValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(i))),
                      str))
                  {
                      v.push_back(str);
                  }
              }
          }
      }
      else
      {
          Category * logger = &Category::getInstance(LOGNAME);
          logger->errorStream() << "Array expected, got " << A(val->getClassName());
      }
      return (value != NULL);
    }
    
    template <class EncodingT, class T, class Fct>
    bool check_array(boost::shared_ptr< Base<EncodingT> > const& val, std::vector<T>& v, Fct check_fct)
    {
      double n;
      T elem;
      boost::shared_ptr< Array<EncodingT> > value  = dynamic_pointer_cast< Array<EncodingT> >(val);
      if (value)
      {
          v.clear();
          if (check_numeric(value->size(), n))
          {
              size_t lg = (size_t)n;
              for (size_t i=0; i<lg; ++i)
              {
                  if (check_fct(
                      value->getValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(i))),
                      elem))
                  {
                      v.push_back(elem);
                  }
              }
          }
      }
      else
      {
          Category * logger = &Category::getInstance(LOGNAME);
          logger->errorStream() << "Array expected, got " << A(val->getClassName());
      }
      return (value != NULL);
    }
    
    template <class EncodingT, class T, class Fct>
    bool reset_array(boost::shared_ptr< Base<EncodingT> >& val, std::vector<T> const& v, Fct reset_fct)
    {
      boost::shared_ptr< Array<EncodingT> > value  = dynamic_pointer_cast< Array<EncodingT> >(val);
      if (value)
      {
        size_t lg;
        if (check_numeric(value->size(), lg))
        {
          for (size_t i = 0; i < v.size() && i < lg; ++i)
          {
            boost::shared_ptr< Base<EncodingT> > item = value->getValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(i)));
            reset_fct(item, v[i]);
          }
        }
      }
      else
      {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Array expected, got " << A(val->getClassName());
      }
      return (value != NULL);
    }

NAMESPACE_END

#undef C
#undef A
