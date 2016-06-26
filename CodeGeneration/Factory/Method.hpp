/**
 * @class           : Method
 * @date            : 03/02/2007
 * @author          : Teddy DIDÉ
 * @version         : 9.0 
 * @brief           : La classe permet d'invoquer des méthodes
 */
 
#ifndef METHOD_H
#define METHOD_H

#include "MethodBase.hpp"
#include "Prototype.hpp"

namespace fctr {

    struct const_t{};
    struct no_const_t{};

}

#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, FCTR_MAX_SIZE)
#define BOOST_PP_FILENAME_1       "MethodSpec.hpp"
#include BOOST_PP_ITERATE()

#endif
