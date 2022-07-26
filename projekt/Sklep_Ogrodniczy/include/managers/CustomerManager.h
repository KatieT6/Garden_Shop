//
// Created by student on 09.06.2022.
//

#ifndef SKLEP_OGRODNICZY_CUSTOMERMANAGER_H
#define SKLEP_OGRODNICZY_CUSTOMERMANAGER_H


#include <vector>
#include "model/typedefs.h"
#include "repositories/Repository.h"
#include "model/typedefs.h"

class CustomerManager {
private:
    // Customer Repository object
    CustomerRepositoryPtr customerRepo;
public:
    CustomerManager(const CustomerRepositoryPtr &customerRepo);

    virtual ~CustomerManager();

    // Function to get Customer
    const CustomerPtr getCustomer(const std::string &Id) const;
    // Function for registering Customer
    CustomerPtr registerCustomer(const std::string &id, const AddressPtr &address, const std::string &phoneNumber,
                                       const std::string &password);

    // Function for unregistering Customer
    void unregisterCustomer(const CustomerPtr &customer);

    // Function for getting Customers
    std::vector<CustomerPtr> findCustomers(const CustomerPredicate predicate) const;

    // Function to get all Customers
    std::vector<CustomerPtr> findAllCustomers() const;

    // Function to get raport of Clients
    std::string getAllCustomersReport() const;

    void save(std::string nazwaPliku) const;
};


#endif //SKLEP_OGRODNICZY_CUSTOMERMANAGER_H
