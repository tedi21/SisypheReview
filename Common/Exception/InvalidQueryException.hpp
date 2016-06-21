/**
 * @class            : InvalidQueryException
 * @date            : 20/04/2009
 * @author            : Teddy DIDÉ
 * @version            : 1.0
 * @brief            : Classe pour une exception de type SQL
 */

#ifndef INVALID_QUERY_EXCEPTION_HPP
#define INVALID_QUERY_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

namespace data_access {

class InvalidQueryException : public std::exception {
private :
    std::string sMsg;
public:
    /// Constructeur
    InvalidQueryException(const char * msg) throw (){
        sMsg = msg;
    }
    ~InvalidQueryException() throw () {}
    
    /// récupère la description de l'erreur
    virtual const char* what() const throw () {
        return sMsg.c_str();
    }
};

}

#endif
