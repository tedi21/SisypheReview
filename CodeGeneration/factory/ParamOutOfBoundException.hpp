/**
 * @class            : ParamOutOfBoundException
 * @date            : 12/12/2006
 * @author            : Teddy DIDÉ
 * @version            : 1.0
 * @brief            : Classe pour une exception de type Param
 */

#ifndef PARAM_OUT_OF_BOUND_EXCEPTION_HPP
#define PARAM_OUT_OF_BOUND_EXCEPTION_HPP

#include <exception>
#include <string>

class ParamOutOfBoundException : public std::exception {
private :
    std::string sMsg;
public:
    /// Constructeur
    ParamOutOfBoundException(const char * msg) throw (){
        sMsg = "Out of bound : ";
        sMsg += msg;
    }
    ~ParamOutOfBoundException() throw () {}
    
    /// récupère la description de l'erreur
    virtual const char* what() const throw () {
        return sMsg.c_str();
    }
};

#endif
