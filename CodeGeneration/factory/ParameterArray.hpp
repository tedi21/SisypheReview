/**
 * @class            : ParameterArray
 * @date             : 12/02/2007
 * @author           : Teddy DIDÉ
 * @version          : 9.0
 * @brief            : Classes permettant d'encapsuler les paramètres pour les Factory
 */

#ifndef PARAMETER_ARRAY_H
#define PARAMETER_ARRAY_H

#include "Parameter.hpp"
#include <vector>
#include <boost/serialization/vector.hpp>
#include <boost/call_traits.hpp>

namespace fctr {

    class ParameterArray
    : public std::vector<Parameter>
    {
    private:
        // Archive
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version){
            ar & boost::serialization::make_nvp("ParameterArray", (std::vector<Parameter>&) *this);
        }

    public:
        // Constructor
        ParameterArray()
        {}
    };

    // Parameter policies
    // Indexed parameters class
    class IndexedParameterPolicy 
    {
    protected:
        template <class T>
        friend struct ReadParameter;
        template <class T>
        friend struct WriteParameter;

        template <class T>
        bool getParameter(const ParameterArray& parameters, size_t index, T& value) const
        {
            return find_parameter(parameters, index, value);
        }

        template <class T>
        void addParameter(ParameterArray& parameters, size_t index, const T& value) const
        {
            parameters.push_back(Parameter(index, value));
        }
    };

    // Named parameters class
    template <class KeyT>
    class NamedParameterPolicy 
    {
    private:
        std::vector<KeyT> m_orderedName;

    protected:
        template <class T>
        friend struct ReadParameter;
        template <class T>
        friend struct WriteParameter;

        template <class T>
        bool getParameter(const ParameterArray& parameters, size_t index, T& value) const
        {
            return index < m_orderedName.size() && 
                   find_parameter(parameters, m_orderedName[index], value);
        }

        template <class T>
        void addParameter(ParameterArray& parameters, size_t index, const T& value) const
        {
            parameters.push_back(Parameter(m_orderedName[index], value));
        }

    public:
        void insertParameterName(size_t index, typename boost::call_traits<KeyT>::param_type key)
        {
            m_orderedName.insert(m_orderedName.begin()+index, key);
        }

        template <class InputIterator>
        void assignParameterNames(InputIterator first, InputIterator last)
        {
            m_orderedName.assign(first, last);
        }
    };

    template <class KeyT, class T>
    bool find_parameter(const ParameterArray& parameters, KeyT key, T& value)
    {
        size_t i = 0;
        while (i < parameters.size() && !parameters[i].value(key, value))
        {
            ++i;
        }
        return i < parameters.size();
    }
}

#endif
