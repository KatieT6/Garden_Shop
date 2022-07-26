//
// Created by student on 12.06.2022.
//

#ifndef SKLEP_OGRODNICZY_PRODUCTEXCEPTION_H
#define SKLEP_OGRODNICZY_PRODUCTEXCEPTION_H

#include <stdexcept>

class ProductException : public std::logic_error{
public:
    virtual ~ProductException();

    ProductException(const char *string);

};


#endif //SKLEP_OGRODNICZY_PRODUCTEXCEPTION_H
