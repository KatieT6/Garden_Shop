//
// Created by student on 09.06.2022.
//

#include "managers/ShoppingCartManager.h"
#include "repositories/Repository.h"
#include "exceptions/ShoppingCartException.h"
#include "exceptions/CustomerException.h"
#include "exceptions/ProductException.h"
#include "model/Customer.h"
#include "model/Plants.h"
#include "model/Product.h"
#include "model/GardenAccessories.h"
#include <fstream>

ShoppingCartManager::ShoppingCartManager(const ShoppingCartRepositoryPtr &currentShoppingCarts,
                                         const ShoppingCartRepositoryPtr &archivedShoppingCarts) : currentShoppingCarts(
        currentShoppingCarts), archivedShoppingCarts(archivedShoppingCarts) {
    if (currentShoppingCarts == nullptr) {
        throw ShoppingCartException("Cannot create productRepo without repository!");}
    if (archivedShoppingCarts == nullptr) {
            throw ShoppingCartException("Cannot create productRepo without repository!");}

}


ShoppingCartManager::~ShoppingCartManager(){

}


const ShoppingCartPtr ShoppingCartManager::getShoppingCartbyCustomer(const CustomerPtr &customer) const {
    if (customer == nullptr)
        throw ShoppingCartException("ShoppingCartManager::getShoppingCartbyCustomer() -> shopping cart can't be null");

    std::vector<ShoppingCartPtr> founds = currentShoppingCarts->findAll([&customer](const ShoppingCartPtr &ptr) -> bool {return ptr->getCartId() == customer->getId();});
    if (founds.size() == 0)
        return nullptr;

    return founds[0];
}

const std::vector<ShoppingCartPtr> ShoppingCartManager::findShoppingCarts(const ShoppingCartPredicate predicate) const {
    if (predicate == nullptr)
        throw ShoppingCartException("ShoppingCartManager::findShoppingCarts() -> predicate can't be null");

    return currentShoppingCarts->findAll(predicate);
}

const std::vector<ShoppingCartPtr> ShoppingCartManager::findAllShoppingCarts() const {
    return findShoppingCarts([](const ShoppingCartPtr &ptr) -> bool {return true;});
}

/*
const float ShoppingCartManager::checkCustomerShoppingBalance(const CustomerPtr &customer) const {
    if (customer == nullptr)
        throw ShoppingCartException("ShoppingCartManager::checkCustomerShoppingBalance() -> customer can't be null");

    std::vector<ShoppingCartPtr> founds = archivedShoppingCarts->findAll([&customer](const ShoppingCartPtr &ptr) -> bool {return ptr->getCartId() == customer->getId();});
    double cost = 0;
    for (ShoppingCartPtr buy : founds){
        cost += buy->getCurrentPrice();
    }
    return cost;
}
*/


float ShoppingCartManager::Receipt(const CustomerPtr &customer) const {
    if (customer == nullptr)
        throw CustomerException("ShoppingCartManager::buyProduct() -> Customer can't be null");
    else{
        float price = getShoppingCartbyCustomer(customer)->getCurrentPrice();
        archivedShoppingCarts->add(getShoppingCartbyCustomer(customer));
        currentShoppingCarts->remove(getShoppingCartbyCustomer(customer));
    return price; }
}

ShoppingCartPtr ShoppingCartManager::buyProduct(std::shared_ptr<Customer> customer, std::shared_ptr<Product> product, int quantity) {
    if (customer == nullptr)
        throw CustomerException("ShoppingCartManager::buyProduct() -> Customer can't be null");
    if (product == nullptr)
        throw ProductException("ShoppingCartManager::buyProduct() -> Product can't be null");
    if (customer -> isArchived())
        throw CustomerException("ShoppingCartManager::buyProduct() -> Customer is archived");
    if (product -> isArchived())
        throw ProductException("ShoppingCartManager::buyProduct() -> Product is archived");
    if(product->getStock() < quantity)
        throw ProductException("ShoppingCartManager::buyProduct() -> Product is not available");
    if(quantity < 0)
        throw ProductException("ShoppingCartManager::buyProduct() -> Are you dumb?");

    if(getShoppingCartbyCustomer(customer) != nullptr){
        getShoppingCartbyCustomer(customer)->addPoduct(product,quantity);
        return  getShoppingCartbyCustomer(customer);
    }

    if(getShoppingCartbyCustomer(customer) == nullptr){
        ShoppingCartPtr newShoppingCart = std::make_shared<ShoppingCart>( 0,  customer->getId());
        currentShoppingCarts->add(newShoppingCart);
        getShoppingCartbyCustomer(customer)->addPoduct(product,quantity);
        return newShoppingCart;
    }

    return nullptr;
}

const ShoppingCartRepositoryPtr &ShoppingCartManager::getCurrentShoppingCarts() const {
    return currentShoppingCarts;
}

const ShoppingCartRepositoryPtr &ShoppingCartManager::getArchivedShoppingCarts() const {
    return archivedShoppingCarts;
}

/*
const float ShoppingCartManager::checkCurrentProfit(std::vector<CustomerPtr> customers) {

    float cost = 0;
    for(int i = 0; i < archivedShoppingCarts->size(); i ++){

        cost += checkCustomerShoppingBalance(customers[i]);
    }
    return cost;
}
*/


const float ShoppingCartManager::checkCurrentProfit(std::vector<CustomerPtr> customers) {

    float cost = 0;
    std::vector<ShoppingCartPtr> founds = archivedShoppingCarts->findAll([&customers](const ShoppingCartPtr &ptr) -> bool {return true;});
    for(int i = 0; i < archivedShoppingCarts->size(); i ++){

        cost += founds[i]->getCurrentPrice();
    }
    return cost;
}

void ShoppingCartManager::save(std::string nazwaPliku) const {
    std::ofstream file(nazwaPliku);
    nlohmann::json carts;
    carts["currentCarts"]= currentShoppingCarts->getJson();
    carts["archivedCarts"]= archivedShoppingCarts->getJson();
    file<<std::setw(4)<<carts;
    file.close();
}


