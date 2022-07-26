//
// Created by student on 09.06.2022.
//

#include "model/Plants.h"

Plants::Plants(float price, int stock, const std::string &name, const std::string &id) : Product(price,
                                                                                                         stock,
                                                                                                         name,
                                                                                                         id) {}

std::string Plants::getInfo() {
    return Product::getInfo();
}

nlohmann::json Plants::getJson() {
    return Product::getJson();
}

Plants::~Plants() = default;
