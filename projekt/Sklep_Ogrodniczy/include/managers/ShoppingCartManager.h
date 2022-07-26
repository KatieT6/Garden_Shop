//
// Created by student on 09.06.2022.
//

#ifndef SKLEP_OGRODNICZY_SHOPPINGCARTMANAGER_H
#define SKLEP_OGRODNICZY_SHOPPINGCARTMANAGER_H

#include "model/typedefs.h"
#include <vector>
#include "model/ShoppingCart.h"


class ShoppingCartManager {
private:
    // current Cart Repository object
    ShoppingCartRepositoryPtr currentShoppingCarts;
    // archived Cart Repository object
    ShoppingCartRepositoryPtr archivedShoppingCarts;
public:
    ShoppingCartManager(const ShoppingCartRepositoryPtr &currentShoppingCarts,
                        const ShoppingCartRepositoryPtr &archivedShoppingCarts);

    virtual ~ShoppingCartManager();

    //const std::vector<ShoppingCartPtr> getAllCustomersShoppingCarts(const CustomerPtr &customer) const;

    const ShoppingCartPtr getShoppingCartbyCustomer(const CustomerPtr &customer) const;

    const std::vector<ShoppingCartPtr> findShoppingCarts(const ShoppingCartPredicate predicate) const;

    const std::vector<ShoppingCartPtr> findAllShoppingCarts() const;

    const float checkCustomerShoppingBalance(const CustomerPtr &customer) const;

    const float checkCurrentProfit(std::vector<CustomerPtr> customers);

    ShoppingCartPtr buyProduct(std::shared_ptr<Customer> customer, std::shared_ptr<Product> product, int quantity);

    float Receipt(const CustomerPtr &customer) const;

    const ShoppingCartRepositoryPtr &getCurrentShoppingCarts() const;

    const ShoppingCartRepositoryPtr &getArchivedShoppingCarts() const;

    void save(std::string nazwaPliku) const;


};


#endif //SKLEP_OGRODNICZY_SHOPPINGCARTMANAGER_H
