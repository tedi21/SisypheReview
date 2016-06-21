/**
 * @class            : BadSqlQueryException
 * @date            : 20/04/2009
 * @author            : Teddy DIDÉ
 * @version            : 1.0
 * @brief            : Classe pour une exception de type SQL
 */

#ifndef BAD_SQL_QUERY_EXCEPTION_HPP
#define BAD_SQL_QUERY_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

namespace data_access {

class BadSqlQueryException : public std::exception {
private :
    std::string sMsg;
public:
    /// Constructeur
    BadSqlQueryException(const char * msg) throw (){
        sMsg = msg;
    }
    ~BadSqlQueryException() throw () {}
    
    /// récupère la description de l'erreur
    virtual const char* what() const throw () {
        return sMsg.c_str();
    }
};

}

#endif
