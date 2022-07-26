//
// Created by student on 09.06.2022.
//

#ifndef SKLEP_OGRODNICZY_SHOPPINGCART_H
#define SKLEP_OGRODNICZY_SHOPPINGCART_H
#include <string>
#include <vector>
#include <memory>
#include "nlohmann/json.hpp"

class Product;

typedef std::shared_ptr<Product> ProductPtr;

class ShoppingCart {
private:
    float currentPrice = 0.0;
    std::string cartId;
    std::vector<ProductPtr> productsList;

public:
    ShoppingCart(float currentPrice, const std::string &cartId);

    virtual ~ShoppingCart();

    nlohmann::json getJson();

    float getCurrentPrice() const;

    void setCurrentPrice(float currentPrice);

    const std::string &getCartId() const;

    void deletePoduct(const ProductPtr &product,int quantity);

    void endShopping();

    void addPoduct(const ProductPtr &product, int quantity);

   // const std::string shoppingCartInfo() const;
    void setCartId(const std::string &cartId);


    const std::string getInfo() const;
};


#endif //SKLEP_OGRODNICZY_SHOPPINGCART_H
