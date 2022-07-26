//
// Created by student on 09.06.2022.
//

#include "model/ShoppingCart.h"
#include "model/Product.h"
#include "model/Customer.h"
#include "exceptions/ShoppingCartException.h"

ShoppingCart::ShoppingCart(float currentPrice, const std::string &cartId) : currentPrice(currentPrice),
                                                                            cartId(cartId) {
if (currentPrice < 0){
throw(ShoppingCartException("PRICE_LOWER_THAN_ZERO_EXCEPTION"));
}

if (cartId.empty()) {
throw(ShoppingCartException("ID_EMPTY_EXCEPTION"));
}
}


ShoppingCart::~ShoppingCart() {

}

void ShoppingCart::addPoduct(const ProductPtr &product, int quantity) {
    productsList.push_back(product);
    setCurrentPrice(getCurrentPrice()+(product->getPrice()*float(quantity)));
}

float ShoppingCart::getCurrentPrice() const {
    return currentPrice;
}

const std::string &ShoppingCart::getCartId() const {
    return cartId;
}


void ShoppingCart::endShopping() {
   //metoda zmieniająca stan na zatwierdzony(?) i posumiwanie cen produktów
}

const std::string ShoppingCart::getInfo() const{
    std::string out = "ID koszyka: " + cartId + ", Przedmioty w koszyku: \n";
    for(auto & i : productsList){
     out += i->getInfo();
    }
    out += ", " + std::to_string(getCurrentPrice());
    return out;
}



void ShoppingCart::deletePoduct(const ProductPtr &product,int quantity) {
    int i=0;
    for(auto& p : productsList){
        if(p == product){
            productsList.erase(productsList.begin()+i);
            setCurrentPrice(getCurrentPrice()-(float(quantity)*product->getPrice()));
            break;
        }
        i++;
    }
}


void ShoppingCart::setCartId(const std::string &cartId) {
    if (cartId.empty()) {
    throw(ShoppingCartException("ID_EMPTY_EXCEPTION"));
    }else
    ShoppingCart::cartId = cartId;
}

//const std::string ShoppingCart :: getInfo() const{
//    std::string s = "ID koszyka: " + getCartId() + shoppingCartInfo() + ", Wartość łączna: " + std::to_string(getCurrentPrice());
//    return s;
//}

void ShoppingCart::setCurrentPrice(float currentPrice) {
    ShoppingCart::currentPrice = currentPrice;
}

nlohmann::json ShoppingCart::getJson() {
    return {{"currentPrice",currentPrice},{"cartId",cartId}};
}
