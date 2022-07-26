//
// Created by student on 09.06.2022.
//

#ifndef SKLEP_OGRODNICZY_CUSTOMER_H
#define SKLEP_OGRODNICZY_CUSTOMER_H

#include <string>
#include "Address.h"
#include "typedefs.h"
#include "nlohmann/json.hpp"


class Customer {
private:
    std::string id;
    AddressPtr address;
    std::string phoneNumber;
    bool archived;
    std::string password;
public:
    nlohmann::json getJson();

    Customer(const std::string &id, const AddressPtr &address, const std::string &phoneNumber,
             const std::string &password);

    virtual ~Customer();

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const std::string &getId() const;

    void setId(const std::string &id);

    const AddressPtr &getAddress() const;

    void setAddress(const AddressPtr &address);

    const std::string &getPhoneNumber() const;

    void setPhoneNumber(const std::string &phoneNumber);

    bool isArchived() const;

    void setArchived(bool archived);

    const std::string getInfo() const;
};


#endif //SKLEP_OGRODNICZY_CUSTOMER_H