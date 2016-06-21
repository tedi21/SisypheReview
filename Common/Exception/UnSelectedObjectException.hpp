/**
 * @class            : UnSelectedObjectException
 * @date            : 20/04/2009
 * @author            : Teddy DIDÉ
 * @version            : 1.0
 * @brief            : Classe pour une exception de type SQL
 */

#ifndef UNSELECTED_OBJECT_EXCEPTION_HPP
#define UNSELECTED_OBJECT_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

namespace data_access {

class UnSelectedObjectException : public std::exception {
private :
    std::string sMsg;
public:
    /// Constructeur
    UnSelectedObjectException(const char * msg) throw (){
        sMsg = msg;
    }
    ~UnSelectedObjectException() throw () {}
    
    /// récupère la description de l'erreur
    virtual const char* what() const throw () {
        return sMsg.c_str();
    }
};

}

#endif
