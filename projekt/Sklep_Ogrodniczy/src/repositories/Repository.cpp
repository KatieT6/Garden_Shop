//
// Created by student on 11.06.2022.
//

#include "repositories/Repository.h"

#include "model/ShoppingCart.h"
#include "model/Customer.h"
#include "model/Product.h"

#include "exceptions/CustomerException.h"
#include "exceptions/ProductException.h"
#include "exceptions/ShoppingCartException.h"
#include <string>

template<class T>
Repository<T>::Repository() = default;

template<class T>
Repository<T>::~Repository() {

}

template<class T>
const T & Repository<T>::get(const int i) const {
    if (i < size()) {
        return elements[i];
    }
    throw CustomerException("Wrong index!");
}

template<class T>
void Repository<T>::add(const T &element) {
    if (element == nullptr) {
        throw CustomerException("Cannot add nullptr!");
    }
    elements.push_back(element);

}

template<class T>
void Repository<T>::remove(const T &element) {
    for (int i = 0; i < size(); ++i) {
        if (element == get(i)) {
            elements.erase(elements.begin() + i);
        }
    }
}

template<class T>
std::string Repository<T>::report() {
    std::string out="INFO:";
    for (int i = 0; i < size(); i++) {
        out += (get(i)->getInfo() + " \n");
    }
    return out;
}

template<class T>
int Repository<T>::size() const {
    return elements.size();
}

template<class T>
T Repository<T>::findBy(const std::function<bool(T)> &predicate) const {
    T element = nullptr;
    for (int i = 0; i < size(); i++) {
        element = get(i);
        if (element != nullptr && predicate(element)) {
            return element;
        }
    }
    return nullptr;
}

template<class T>                                                                                                           
std::vector<T> Repository<T>::findAll(const std::function<bool(T)> &predicate) const {
    std::vector<T> result;
    for (int i = 0; i < size(); ++i) {
        T element = get(i);
        if (predicate(element)) {
            result.push_back(element);
        }
    }
    return result;
}

template<class T>
nlohmann::json Repository<T>::getJson() const {
    std::vector<nlohmann::json> jsonList;
    for(auto &object: elements){
        jsonList.push_back(object->getJson());
    }
    return jsonList;
}

template
class Repository<CustomerPtr>;

template
class Repository<ProductPtr>;

template
class Repository<ShoppingCartPtr>;