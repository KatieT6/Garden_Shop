//
// Created by student on 09.06.2022.
//

#include "model/Product.h"
#include "exceptions/ProductException.h"



float Product::getPrice() const {
    return price;
}

void Product::setPrice(float price) {
    if(price < 0)
        throw (ProductException("PRICE_LOWER_THAN_ZERO_EXCEPTION"));
    else
    Product::price = price;
}

int Product::getStock() const {
    return stock;
}

void Product::setStock(int stock) {
    if(stock < 0)
        throw (ProductException("STOCK_LOWER_THAN_ZERO_EXCEPTION"));
    else
    Product::stock = stock;
}

const std::string &Product::getName() const {
    return name;
}

void Product::setName(const std::string &name) {
    if(name.empty())
        throw (ProductException("NAME_EMPTY_EXCEPTION"));
    else
    Product::name = name;
}

bool Product::isArchived() const {
    return archived;
}

void Product::setArchived(bool archived) {
    Product::archived = archived;
}

std::string Product::getInfo() {
    return "Produkt: nazwa: " + getName() + ", ilosc sztuki produktu: " + std::to_string(getStock()) + ", cena za sztuke: " + std::to_string(getPrice()) + ", numer produktu: " + getId() + ", archiwizacja: " +
            std::to_string(isArchived());
}

Product::Product(float price, int stock, const std::string &name, const std::string &id) : price(price),
                                                                                                          stock(stock),
                                                                                                          name(name),
                                                                                                          Id(id){
    if (price < 0){
        throw(ProductException("PRICE_LOWER_THAN_ZERO_EXCEPTION"));
    }

    if (stock < 0) {
        throw(ProductException("STOCK_LOWER_THAN_ZERO_EXCEPTION"));
    }

    if (name == "") {
        throw(ProductException("NAME_EMPTY_EXCEPTION"));
    }

    if (id == ""){
        throw(ProductException("ID_EMPTY_EXCEPTION"));
    }
    setArchived(false);
}

const std::string &Product::getId() const {
    return Id;
}

void Product::setId(const std::string &id) {
    if(id.empty())
        throw (ProductException("ID_EMPTY_EXCEPTION"));
    else
    Id = id;
}

nlohmann::json Product::getJson() {
    return{{"price", price},{"stock", stock},{"name", name},{"Id", Id},{"archived", archived}};
}

Product::~Product() = default;
