//
// Created by student on 11.06.2022.
//

#ifndef SKLEP_OGRODNICZY_TYPEDEFS_H
#define SKLEP_OGRODNICZY_TYPEDEFS_H

#include <memory>
#include <functional>

//class
class Address;
class Customer;
class GardenAccessories;
class Plants;
class Product;
class ShoppingCart;



template<class T>
class Repository;

class CustomerManager;
class ShoppingCartManager;
class ProductManager;

// Client
typedef std::shared_ptr<Customer> CustomerPtr;

// Address
typedef std::shared_ptr<Address> AddressPtr;

// Shopping Cart
typedef std::shared_ptr<ShoppingCart> ShoppingCartPtr;

// Products
typedef std::shared_ptr<Product> ProductPtr;
typedef std::shared_ptr<Plants> PlantsPtr;
typedef std::shared_ptr<GardenAccessories> GardenAccessoriesPtr;

// Repository
typedef std::shared_ptr<Repository<CustomerPtr>> CustomerRepositoryPtr;
typedef std::shared_ptr<Repository<ProductPtr>> ProductRepositoryPtr;
typedef std::shared_ptr<Repository<ShoppingCartPtr>> ShoppingCartRepositoryPtr;

// Manager
typedef std::shared_ptr<CustomerManager> CustomerManagerPtr;
typedef std::shared_ptr<ShoppingCartManager> ShoppingCartManagerPtr;
typedef std::shared_ptr<ProductManager> ProductManagerPtr;

// Predicates
typedef std::function<bool(CustomerPtr)> CustomerPredicate;
typedef std::function<bool(ProductPtr)> ProductPredicate;
typedef std::function<bool(ShoppingCartPtr)> ShoppingCartPredicate;


#endif //SKLEP_OGRODNICZY_TYPEDEFS_H
