//
// Created by student on 12.06.2022.
//

#ifndef SKLEP_OGRODNICZY_CUSTOMEREXCEPTION_H
#define SKLEP_OGRODNICZY_CUSTOMEREXCEPTION_H

#include <stdexcept>

class CustomerException : public std::logic_error{
public:
    explicit CustomerException(const std::string &str): std::logic_error(str){};

};


#endif //SKLEP_OGRODNICZY_CUSTOMEREXCEPTION_H
