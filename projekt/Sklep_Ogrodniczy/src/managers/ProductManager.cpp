//
// Created by student on 09.06.2022.
//

#include "managers/ProductManager.h""
#include "model/GardenAccessories.h"
#include "model/Plants.h"
#include "exceptions/ProductException.h"
#include <fstream>



ProductManager::ProductManager(const ProductRepositoryPtr &productRepo) : productRepo(productRepo) {
    if (productRepo == nullptr) { throw ProductException("Cannot create productRepo without repository!"); }
}

ProductManager::~ProductManager() {
}



const ProductPtr ProductManager::getProduct(const std::string &id) const {
    ProductPredicate predicate = [id](const ProductPtr ptr) {
        return ptr->getId() == id;
    };
    return productRepo->findBy(predicate);
}

//const ProductPtr ProductManager::getProductByName(const std::string &name) const {
//    ProductPredicate predicate = [name](const ProductPtr ptr) {
//        return ptr->getName() == name;
//    };
//    return productRepo->findBy(predicate);
//}

const ProductPtr ProductManager::registerPlant(float price, int stock, const std::string &name, const std::string &id) {
    if (getProduct(id) != nullptr)
        return getProduct(id);

    ProductPtr newProduct = std::make_shared<Plants>(price, stock, name, id);
    productRepo->add(newProduct);
    return newProduct;}

const ProductPtr ProductManager::registerGardenAccessories(float price, int stock, const std::string &name, const std::string &id, int warrantyTime) {
    if (getProduct(id) != nullptr)
        return getProduct(id);

    ProductPtr newProduct = std::make_shared<GardenAccessories>(price, stock, name, id, warrantyTime);
    productRepo->add(newProduct);
    return newProduct;}

void ProductManager::unregisterProduct(const ProductPtr &product) {
    if (product == nullptr)
        throw ProductException("ProductManager::unregisterProduct() -> product can't be null");

    if (getProduct(product->getId()) != nullptr)
        getProduct(product->getId())->setArchived(true);
}

const std::vector<ProductPtr> ProductManager::findProducts(const ProductPredicate predicate) const {
    if (predicate == nullptr)
        throw ProductException("ProductManager::findProducts() -> predicate can't be null");

    return productRepo->findAll([predicate](const ProductPtr &ptr) -> bool { return predicate(ptr) && !ptr->isArchived(); });
}

const std::vector<ProductPtr> ProductManager::findAllProducts() const {
    return findProducts([](const ProductPtr &ptr) -> bool {return true;});}

const std::string ProductManager::getAllProductsReport() const {
    return productRepo->report();
}

void ProductManager::save(std::string nazwaPliku) const {
    std::ofstream file(nazwaPliku);
    file<<std::setw(4)<<productRepo->getJson();
    file.close();
}

