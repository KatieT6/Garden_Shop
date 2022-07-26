//
// Created by student on 09.06.2022.
//

#include "model/Address.h"
#include "exceptions/CustomerException.h"

Address::Address(const std::string &street, const std::string &city, const std::string &number) : street(street),
                                                                                                  city(city),
                                                                                                  number(number) {
    //if (street == "" || city.empty() || number == "")throw CustomerException("ADDRESS_EMPTY_EXCEPTION");

    if (city.empty()) { throw CustomerException("ADDRESS_EMPTY_EXCEPTION"); }
    if (street.empty()) { throw CustomerException("ADDRESS_EMPTY_EXCEPTION"); }
    if (number.empty()) { throw CustomerException("ADDRESS_EMPTY_EXCEPTION"); }
}

const std::string &Address::getStreet() const {
    return street;
}

void Address::setStreet(const std::string &street) {
    if(street.empty())
        return;
    else
    Address::street = street;
}

const std::string &Address::getCity() const {
    return city;
}

void Address::setCity(const std::string &city) {
    if (city.empty())
        return;
    else
    Address::city = city;
}

const std::string &Address::getNumber() const {
    return number;
}

void Address::setNumber(const std::string &number) {
    if(number.empty())
        return;
    else
    Address::number = number;
}

std::string Address::getInfo() {
    return "ADDRESS city: " + getCity() + ", street: " + getStreet() + ", number: " + getNumber();
}

nlohmann::json Address::getJson() {
    return {{"city", city},{"street", street},{"number", number}};
}

Address::~Address() = default;
