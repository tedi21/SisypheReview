/**
 * @class            : NoSqlRowException
 * @date            : 20/04/2009
 * @author            : Teddy DIDÉ
 * @version            : 1.0
 * @brief            : Classe pour une exception de type SQL
 */

#ifndef NO_SQL_ROW_EXCEPTION_HPP
#define NO_SQL_ROW_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

namespace data_access {

class NoSqlRowException : public std::exception {
private :
    std::string sMsg;
public:
    /// Constructeur
    NoSqlRowException(const char * msg) throw (){
        sMsg = msg;
    }
    ~NoSqlRowException() throw () {}
    
    /// récupère la description de l'erreur
    virtual const char* what() const throw () {
        return sMsg.c_str();
    }
};

}

#endif
