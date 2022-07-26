//
// Created by student on 12.06.2022.
//

#include "exceptions/ShoppingCartException.h"

ShoppingCartException::~ShoppingCartException() {

}

ShoppingCartException::ShoppingCartException(const char *string) : logic_error(string) {

}
