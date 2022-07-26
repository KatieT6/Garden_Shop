//
// Created by student on 09.06.2022.
//

#ifndef SKLEP_OGRODNICZY_PRODUCTMANAGER_H
#define SKLEP_OGRODNICZY_PRODUCTMANAGER_H

#include <vector>
#include "model/typedefs.h"
#include "model/GardenAccessories.h"
#include "model/Plants.h"
#include "repositories/Repository.h"


class ProductManager {
private:
    // Customer Repository object
    ProductRepositoryPtr productRepo;
public:

    ProductManager(const ProductRepositoryPtr &productRepo);

    virtual ~ProductManager();

    // Function to get Product with given Id
    const ProductPtr getProduct(const std::string &Id) const;
    //Function to register Plant
    const ProductPtr registerPlant(float price, int stock, const std::string &name, const std::string &Id);

    const ProductPtr
    registerGardenAccessories(float price, int stock, const std::string &name, const std::string &id, int warrantyTime);

    void unregisterProduct(const ProductPtr &product);

    const std::vector<ProductPtr> findProducts(const ProductPredicate predicate) const;

    const std::vector<ProductPtr> findAllProducts() const;

    const std::string getAllProductsReport() const;

    void save(std::string nazwaPliku) const;

};


#endif //SKLEP_OGRODNICZY_PRODUCTMANAGER_H
