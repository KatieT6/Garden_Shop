//
// Created by student on 09.06.2022.
//

#include "model/Customer.h"
#include "exceptions/CustomerException.h"


const std::string &Customer::getId() const {
    return id;
}

void Customer::setId(const std::string &id) {
    if(id.empty())
        throw (CustomerException("ID_EMPTY_EXCEPTION"));
    else
    Customer::id = id;
}



const std::string &Customer::getPhoneNumber() const {
    return phoneNumber;
}

void Customer::setPhoneNumber(const std::string &phoneNumber) {
    if(phoneNumber.empty())
        throw (CustomerException("PHONE_NUMBER_EMPTY_EXCEPTION"));
    else
    Customer::phoneNumber = phoneNumber;
}

bool Customer::isArchived() const {
    return archived;
}


void Customer::setArchived(bool archived) {
    Customer::archived = archived;

}

const std::string &Customer::getPassword() const {
    return password;
}

void Customer::setPassword(const std::string &password) {
    if(password.empty())
        throw (CustomerException("PASSWORD_EMPTY_EXCEPTION"));
    else
    Customer::password = password;
}

Customer::Customer(const std::string &id, const AddressPtr &address, const std::string &phoneNumber,
                   const std::string &password) : id(id), address(address), phoneNumber(phoneNumber),
                                                  password(password) {

    archived = false;
    if (id.empty()){
        throw(CustomerException("ID_EMPTY_EXCEPTION"));
    }

    if (address == nullptr) {
        throw(CustomerException("ADDRESS_NULLPTR_EXCEPTION"));
    }

    if (phoneNumber.empty()) {
        throw(CustomerException("PHONE_NUMBER_EMPTY_EXCEPTION"));
    }

    if (password.empty()){
        throw(CustomerException("PASSWORD_EMPTY_EXCEPTION"));
    }

};

const AddressPtr &Customer::getAddress() const {
    return address;
}

void Customer::setAddress(const AddressPtr &address) {
    if(address== nullptr)
        throw (CustomerException("ADDRESS_NULLPTR_EXCEPTION"));
    else
    Customer::address = address;
}

const std::string Customer::getInfo()  const{
    std::string s = "Klient: \n\tID: " + id + "\n\tAdres: " + address->getInfo() + "\n\tNumer telefonu: " + phoneNumber + "\n\tHasło: " + password;

    return s;
}

nlohmann::json Customer::getJson() {
    return {{"id", id},{"address", address->getJson()},{"PhoneNumber",phoneNumber},{"archived", archived},{"password",password}};
}


Customer::~Customer() = default;