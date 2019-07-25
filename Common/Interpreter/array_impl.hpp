#include "Predicate.hpp"
#include "Numeric.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Array<EncodingT>::Array()
    {}
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Array<EncodingT>::valueAt(size_t i) const
    {
      return m_container[i];
    }
    
    template <class EncodingT>
    size_t Array<EncodingT>::length() const
    {
      return m_container.size();
    }

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
                str += C(",");
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
            if (tryInvoke(this, C("Array"), method, args, ret)  ||
                tryInvoke(this, C("Base"), method, args, ret))
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
        m_container.push_back(val);
    }

    template <class EncodingT>
    void Array<EncodingT>::insertValue(boost::shared_ptr< Base<EncodingT> > const& i, boost::shared_ptr< Base<EncodingT> > const& val)
    {
        size_t index = 0;
        if (check_numeric_i(i, index))
        {
            if (check_index(index, m_container.size()+1))
            {
                m_container.insert(m_container.begin()+index, val);
            }
        }
    }
    
    template <class EncodingT>
    void Array<EncodingT>::insertList(boost::shared_ptr< Base<EncodingT> > const& i1, boost::shared_ptr< Base<EncodingT> > const& i2, boost::shared_ptr< Base<EncodingT> > const& val)
    {
        size_t index1 = 0, index2 = 0;
        boost::shared_ptr< Array<EncodingT> > value  = dynamic_pointer_cast< Array<EncodingT> >(val);
        if (value &&
            check_numeric_i(i1, index1) &&
            check_numeric_i(i2, index2))
        {
            if (value->m_container.size() > 0)
            {
                if (index2 == static_cast<size_t>(-1))
                {
                    index2 = value->m_container.size();
                }
                else
                {
                    index2 = (index2 - index1) + 1;
                }

                if (check_index(index1, m_container.size()+1) &&
                    check_index(index2, value->m_container.size()+1))
                {
                    m_container.insert(m_container.begin() + index1, value->m_container.begin(), value->m_container.begin() + index2);
                }
            }
        }
    }

    template <class EncodingT>
    void Array<EncodingT>::removeValue(boost::shared_ptr< Base<EncodingT> > const& i)
    {
        size_t index = 0;
        if (check_numeric_i(i, index))
        {
            if (check_index(index, m_container.size()))
            {
                m_container.erase(m_container.begin() + index);
            }
        }
    }
    
    template <class EncodingT>
    void Array<EncodingT>::removeList(boost::shared_ptr< Base<EncodingT> > const& i1, boost::shared_ptr< Base<EncodingT> > const& i2)
    {
        size_t index1 = 0, index2 = 0;
        if (check_numeric_i(i1, index1) &&
            check_numeric_i(i2, index2))
        {
            if (index2 == static_cast<size_t>(-1))
            {
                index2 = m_container.size();
            }
            else
            {
                index2 = index2 + 1;
            }

            if (check_index(index1, m_container.size()) &&
                check_index(index2, m_container.size()+1))
            {
                m_container.erase(m_container.begin() + index1, m_container.begin() + index2);
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
        size_t index = 0;
        if (check_numeric_i(i, index))
        {
            if (check_index(index, m_container.size()))
            {
                res = m_container[index];
            }
        }
        return res;    
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Array<EncodingT>::getList(boost::shared_ptr< Base<EncodingT> > const& i1, boost::shared_ptr< Base<EncodingT> > const& i2) const
    {
        boost::shared_ptr< Array<EncodingT> > res(new Array<EncodingT>);
        size_t index1 = 0, index2 = 0;
        if (check_numeric_i(i1, index1) &&
            check_numeric_i(i2, index2))
        {
            if (index2 == static_cast<size_t>(-1))
            {
                index2 = m_container.size();
            }
            else
            {
                index2 = index2 + 1;
            }

            if (check_index(index1, m_container.size()) &&
                check_index(index2, m_container.size()+1))
            {
                res->m_container.insert(res->m_container.begin(), m_container.begin() + index1, m_container.begin() + index2);
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
    void Array<EncodingT>::unique()
    {
        m_container.erase(std::unique(m_container.begin(), m_container.end()), m_container.end());
    }
    
    template <class EncodingT>
    void Array<EncodingT>::unique(boost::shared_ptr< Base<EncodingT> > const& function)
    {
        boost::shared_ptr< Predicate<EncodingT> > value  = dynamic_pointer_cast< Predicate<EncodingT> >(function);
        if (value)
        {
            m_container.erase(std::unique(m_container.begin(), m_container.end(), *value), m_container.end());
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Predicate expected, got " << A(function->getClassName());
        }
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

    template <class EncodingT>
    size_t Array<EncodingT>::dichotomy(std::vector< boost::shared_ptr< Base<EncodingT> > > const& container,
                                       size_t start,
                                       size_t end,
                                       boost::shared_ptr< Predicate<EncodingT> > const& pValid,
                                       boost::shared_ptr< Predicate<EncodingT> > const& pInf) const
    {
        size_t size = end - start;
        size_t index = end;
        if (size > 0)
        {
            size_t pivot = start + std::floor(size / 2);
            const boost::shared_ptr< Base<EncodingT> >& value = container[pivot];
            if ((*pValid)(value))
            {
                index = pivot;
            }
            else if ((*pInf)(value))
            {
                if (pivot > start)
                {
                    size_t indexInf = dichotomy(container, start, pivot, pValid, pInf);
                    if (indexInf != pivot)
                    {
                        index = indexInf;
                    }
                }
            }
            else
            {
                if ((pivot+1) < end)
                {
                    size_t indexSup = dichotomy(container, (pivot+1), end, pValid, pInf);
                    if (indexSup != end)
                    {
                        index = indexSup;
                    }
                }
            }
        }
        return index;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Array<EncodingT>::dichotomy(boost::shared_ptr< Base<EncodingT> > const& fnValid, boost::shared_ptr< Base<EncodingT> > const& fnInf) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>(m_container.size()));
        boost::shared_ptr< Predicate<EncodingT> > pValid  = dynamic_pointer_cast< Predicate<EncodingT> >(fnValid);
        boost::shared_ptr< Predicate<EncodingT> > pInf  = dynamic_pointer_cast< Predicate<EncodingT> >(fnInf);
        if (pValid && pInf)
        {
            size_t i = dichotomy(m_container, 0, m_container.size(), pValid, pInf);
            res.reset(new Numeric<EncodingT>(i));
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Predicate expected, got " << A(pValid->getClassName());
            logger->errorStream() << "Predicate expected, got " << A(pInf->getClassName());
        }
        return res;
    }

    inline bool check_index(size_t index, size_t size)
    {
        bool inside = index < size;
        if (!inside)
        {
            Category * logger = &Category::getInstance(LOGNAME);
            if (size > 0)
            {
                logger->errorStream() << "Index out of range : Index [" << index << "], Max [" << size-1 << "]";
            }
            else
            {
                logger->errorStream() << "Index out of range : Empty array";
            }
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

    template <class EncodingT, class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
    bool check_numeric_i_array(boost::shared_ptr< Base<EncodingT> > const& val, bc::vector<T>& v)
    {
      boost::shared_ptr< Array<EncodingT> > value  = dynamic_pointer_cast< Array<EncodingT> >(val);
      if (value)
      {
        v.clear();
        size_t lg = value->length();
        T numeric;
        for (size_t i=0; i<lg; ++i)
        {
          if (check_numeric_i(value->valueAt(i), numeric))
          {
            v.push_back(numeric);
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

    template <class EncodingT, class T, class = typename std::enable_if<std::is_floating_point<T>::value>::type>
    bool check_numeric_d_array(boost::shared_ptr< Base<EncodingT> > const& val, bc::vector<T>& v)
    {
      boost::shared_ptr< Array<EncodingT> > value  = dynamic_pointer_cast< Array<EncodingT> >(val);
      if (value)
      {
        v.clear();
        size_t lg = value->length();
        T numeric;
        for (size_t i=0; i<lg; ++i)
        {
          if (check_numeric_d(value->valueAt(i), numeric))
          {
            v.push_back(numeric);
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
      typename EncodingT::string_t str;
      boost::shared_ptr< Array<EncodingT> > value  = dynamic_pointer_cast< Array<EncodingT> >(val);
      if (value)
      {
          v.clear();
          size_t lg = value->length();
          for (size_t i=0; i<lg; ++i)
          {
              if (check_string<EncodingT>(value->valueAt(i), str))
              {
                  v.push_back(str);
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
    bool check_base(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< Base<EncodingT> >& value)
    {
        value = val;
        return true;
    }
    
    template <class EncodingT, class T, class Fct>
    bool check_array(boost::shared_ptr< Base<EncodingT> > const& val, std::vector<T>& v, Fct check_fct)
    {
      T elem;
      boost::shared_ptr< Indexable<EncodingT> > value  = dynamic_pointer_cast< Indexable<EncodingT> >(val);
      if (value)
      {
          v.clear();
          size_t lg = value->length();
          for (size_t i=0; i<lg; ++i)
          {
              if (check_fct(value->valueAt(i), elem))
              {
                  v.push_back(elem);
              }
          }
      }
      else
      {
          Category * logger = &Category::getInstance(LOGNAME);
          logger->errorStream() << "Indexable (Array, String) expected, got " << A(val->getClassName());
      }
      return (value != NULL);
    }
    
    template <class EncodingT, class T, class Fct>
    bool reset_array(boost::shared_ptr< Base<EncodingT> >& val, std::vector<T> const& v, Fct reset_fct)
    {
      boost::shared_ptr< Indexable<EncodingT> > value  = dynamic_pointer_cast< Indexable<EncodingT> >(val);
      if (value)
      {
        size_t lg = value->length();
        for (size_t i = 0; i < v.size() && i < lg; ++i)
        {
          boost::shared_ptr< Base<EncodingT> > item = value->valueAt(i);
          reset_fct(item, v[i]);
        }
      }
      else
      {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Indexable (Array, String) expected, got " << A(val->getClassName());
      }
      return (value != NULL);
    }

NAMESPACE_END

#undef C
#undef A
