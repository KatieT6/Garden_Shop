//
// Created by student on 09.06.2022.
//

#ifndef SKLEP_OGRODNICZY_PRODUCT_H
#define SKLEP_OGRODNICZY_PRODUCT_H
#include <string>
#include "nlohmann/json.hpp"


class Product {
private:
    float price;
    int stock;
    std::string name;
    std::string Id;
    bool archived;

public:
    Product(float price, int stock, const std::string &name, const std::string &id);

    virtual ~Product();

    float getPrice() const;

    void setPrice(float price);

    int getStock() const;

    void setStock(int stock);

    virtual nlohmann::json getJson();

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getId() const;

    void setId(const std::string &id);

    bool isArchived() const;

    void setArchived(bool archived);

    virtual std::string getInfo();
};


#endif //SKLEP_OGRODNICZY_PRODUCT_H
