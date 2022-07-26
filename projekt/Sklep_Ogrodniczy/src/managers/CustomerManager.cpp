//
// Created by student on 09.06.2022.
//

#include "managers/CustomerManager.h"
#include "exceptions/CustomerException.h"
#include "model/Customer.h"
#include <fstream>


CustomerManager::CustomerManager(const CustomerRepositoryPtr &customerRepo) : customerRepo(customerRepo) {
    if (customerRepo == nullptr) { throw CustomerException("Cannot create customerManager without repository!"); }
}


CustomerManager::~CustomerManager() {

}

const CustomerPtr CustomerManager::getCustomer(const std::string &id) const {
    CustomerPredicate predicate = [id](const CustomerPtr ptr) {
        return ptr->getId() == id;
    };
    return customerRepo->findBy(predicate);
}

CustomerPtr CustomerManager::registerCustomer(const std::string &id, const AddressPtr &address, const std::string &phoneNumber, const std::string &password) {
    if (getCustomer(id) == nullptr)
    {
        CustomerPtr newCustomer = std::make_shared<Customer>(id, address, phoneNumber, password);
        customerRepo->add(newCustomer);
        return newCustomer; }
    else
    {
       throw CustomerException("CustomerRepository error: Such Customer already exists.");
    }

}

void CustomerManager::unregisterCustomer(const CustomerPtr &customer) {
    if (customer == nullptr)
        throw CustomerException("CustomerManager::unregisterCustomer() -> Can't unregister null customer");

    if (getCustomer(customer->getId()) != nullptr)
        getCustomer(customer->getId())->setArchived(true);

}

std::vector<CustomerPtr> CustomerManager::findCustomers(const CustomerPredicate predicate) const {
    if (predicate == nullptr)
        throw CustomerException("CustomerManager::findCustomers() -> Customer Predicate is needed and can't be none");

    return customerRepo->findAll([predicate](const CustomerPtr &ptr) -> bool { return predicate(ptr) && !ptr->isArchived(); });
}

std::vector<CustomerPtr> CustomerManager::findAllCustomers() const {
    return findCustomers([](const CustomerPtr &ptr) -> bool {return true;});
}

std::string CustomerManager::getAllCustomersReport() const {
    return customerRepo->report();}

void CustomerManager::save(std::string nazwaPliku) const {
    std::ofstream file(nazwaPliku);
    file<<std::setw(4)<<customerRepo->getJson();
    file.close();
}

