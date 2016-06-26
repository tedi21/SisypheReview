/**
 * @class           : UnRegisteredClassException
 * @date            : 12/12/2006
 * @author          : Teddy DID�
 * @version         : 1.0
 * @brief           : Classe pour une exception de type Factory
 */

#ifndef UN_REGISTERED_CLASS_EXCEPTION_HPP
#define UN_REGISTERED_CLASS_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

namespace fctr {

class UnRegisteredClassException : public std::exception {
private :
    std::string sMsg;
public:
    /// Constructeur
    UnRegisteredClassException(const char * factoryName) throw (){
        sMsg = "La factory n'est pas enregistr�e dans le framework : ";
        sMsg += factoryName;
    }
    ~UnRegisteredClassException() throw () {}
    
    /// r�cup�re la description de l'erreur
    virtual const char* what() const throw () {
        return sMsg.c_str();
    }
};

}

#endif
