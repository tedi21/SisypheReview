/**
 * @class            : NullPointerException
 * @date            : 20/04/2009
 * @author            : Teddy DID�
 * @version            : 1.0
 * @brief            : Classe pour une exception de type NULL pointer
 */

#ifndef NULL_POINTER_EXCEPTION_HPP
#define NULL_POINTER_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

namespace data_access {

class NullPointerException : public std::exception {
private :
    std::string sMsg;
public:
    /// Constructeur
    NullPointerException(const char * msg) throw (){
        sMsg = msg;
    }
    ~NullPointerException() throw () {}
    
    /// r�cup�re la description de l'erreur
    virtual const char* what() const throw () {
        return sMsg.c_str();
    }
};

}

#endif
