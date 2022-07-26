//
// Created by student on 12.06.2022.
//

#include "exceptions/ProductException.h"

ProductException::~ProductException() {

}

ProductException::ProductException(const char *string) : logic_error(string) {

}
