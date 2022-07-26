//
// Created by student on 12.06.2022.
//

#ifndef SKLEP_OGRODNICZY_SHOPPINGCARTEXCEPTION_H
#define SKLEP_OGRODNICZY_SHOPPINGCARTEXCEPTION_H

#include <stdexcept>

class ShoppingCartException: public std::logic_error {
public:
    virtual ~ShoppingCartException();

    ShoppingCartException(const char *string);

};


#endif //SKLEP_OGRODNICZY_SHOPPINGCARTEXCEPTION_H
