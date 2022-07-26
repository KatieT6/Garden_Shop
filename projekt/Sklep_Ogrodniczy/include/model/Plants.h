//
// Created by student on 09.06.2022.
//

#ifndef SKLEP_OGRODNICZY_PLANTS_H
#define SKLEP_OGRODNICZY_PLANTS_H


#include "Product.h"
#include "nlohmann/json.hpp"

class Plants: public Product{
public:
    Plants(float price, int stock, const std::string &name, const std::string &id);

    virtual ~Plants();
    std::string getInfo() override;

    nlohmann::json getJson() override;
};


#endif //SKLEP_OGRODNICZY_PLANTS_H
