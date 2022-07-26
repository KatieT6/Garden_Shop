//
// Created by student on 09.06.2022.
//

#ifndef SKLEP_OGRODNICZY_ADDRESS_H
#define SKLEP_OGRODNICZY_ADDRESS_H
#include "nlohmann/json.hpp"

#include <string>

class Address {
private:
    std::string street;
    std::string city;
    std::string number;
public:
    Address(const std::string &street, const std::string &city, const std::string &number);

    virtual ~Address();

    const std::string &getStreet() const;

    void setStreet(const std::string &street);

    const std::string &getCity() const;

    void setCity(const std::string &city);

    const std::string &getNumber() const;

    void setNumber(const std::string &number);

    std::string getInfo();

    nlohmann::json getJson();
};


#endif //SKLEP_OGRODNICZY_ADDRESS_H
