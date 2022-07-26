//
// Created by student on 09.06.2022.
//

#ifndef SKLEP_OGRODNICZY_GARDENACCESSORIES_H
#define SKLEP_OGRODNICZY_GARDENACCESSORIES_H


#include "Product.h"
#include "nlohmann/json.hpp"

class GardenAccessories: public Product{
private:
    int warrantyTime;
public:
    GardenAccessories(float price, int stock, const std::string &name, const std::string &id,
                      int warrantyTime);

    virtual ~GardenAccessories();
    int getWarrantyTime() const;

    void setWarrantyTime(int warrantyTime);

    std::string getInfo() override;

    void warrantyExtension(int extension);

    nlohmann::json getJson() override;
};


#endif //SKLEP_OGRODNICZY_GARDENACCESSORIES_H
