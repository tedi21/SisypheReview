/**
 * @class            : BadXmlFormatException
 * @date            : 12/12/2006
 * @author            : Teddy DIDÉ
 * @version            : 1.0
 * @brief            : Classe pour une exception de type XmlFormat
 */

#ifndef BAD_XML_FORMAT_EXCEPTION_HPP
#define BAD_XML_FORMAT_EXCEPTION_HPP

#include <exception>
#include <string>

using namespace std;

class BadXmlFormatException : public exception {
private :
    std::string sMsg;
public:
    /// Constructeur
    BadXmlFormatException(const char * msg) throw (){
        sMsg = "Bad Xml Format : ";
        sMsg += msg;
    }
    ~BadXmlFormatException() throw () {}
    
    /// récupère la description de l'erreur
    virtual const char* what() const throw () {
        return sMsg.c_str();
    }
};

#endif
