/**
 * @class            : UnRegisteredObjectException
 * @date            : 06/09/2006
 * @author            : Teddy DIDÉ
 * @version            : 1.0
 * @brief            : Classe pour une exception de type Object
 */

#ifndef UN_REGISTERED_OBJECT_EXCEPTION_HPP
#define UN_REGISTERED_OBJECT_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

namespace fctr {

class UnRegisteredObjectException : public std::exception {
private :
    std::string sMsg;
public:
    /// Constructeur
    UnRegisteredObjectException(const char * objectName) throw (){
        sMsg = "L'objet n'est pas enregistré dans le framework : ";
        sMsg += objectName;
    }
    ~UnRegisteredObjectException() throw () {}
    
    /// récupère la description de l'erreur
    virtual const char* what() const throw () {
        return sMsg.c_str();
    }
};

}

#endif
