#ifndef GENERATOR_EXCEPTION_HPP
#define GENERATOR_EXCEPTION_HPP

#include <exception>
#include "generator_info.hpp"

namespace gen {

template <typename CharT>
class generator_exception : public std::exception {
private :
    typedef typename generator_string<CharT>::str_t        str_t;
    str_t m_buffer;
public:
    /// Constructeur
    generator_exception(str_t const& buffer) throw ()
    : m_buffer(buffer) 
    {}

    ~generator_exception() throw () {}

    str_t const& buffer() const
    {
        return m_buffer;
    }
    
    /// récupère la description de l'erreur
    virtual const char* what() const throw () {
        return "generator exception";
    }
};

}

#endif