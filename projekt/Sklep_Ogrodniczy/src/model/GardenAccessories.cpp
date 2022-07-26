//
// Created by student on 09.06.2022.
//

#include "model/GardenAccessories.h"
#include "exceptions/ProductException.h"

GardenAccessories::GardenAccessories(float price, int stock, const std::string &name, const std::string &id, int warrantyTime) : Product(price, stock, name, id),
                                                                        warrantyTime(warrantyTime) {
    if (warrantyTime != 12 && warrantyTime != 24 && warrantyTime != 36 && warrantyTime != 48){
        throw(ProductException("WARRANTY_DIFFERERNT_THAN_POSSIBLE_EXCEPTION"));
    }
}

GardenAccessories::~GardenAccessories() = default;


int GardenAccessories::getWarrantyTime() const {
    return warrantyTime;
}

void GardenAccessories::setWarrantyTime(int warrantyTime) {
    if (warrantyTime != 12 && warrantyTime != 24 && warrantyTime != 36 && warrantyTime != 48){
        throw(ProductException("WARRANTY_DIFFERERNT_THAN_POSSIBLE_EXCEPTION"));
    } else
    GardenAccessories::warrantyTime = warrantyTime;
}

std::string GardenAccessories::getInfo() {
    return Product::getInfo() + ", Czas gwarancji: " + std::to_string(warrantyTime);
}

void GardenAccessories::warrantyExtension(int extension) {
    if(extension == 12){
        setPrice(float (getPrice()*1.2));
    }
    if(extension == 24){
        setPrice(float(getPrice()*1.3));
    }
    if(extension == 36){
        setPrice(float(getPrice()*1.4));
    }
    if(extension == 48){
        setPrice(float(getPrice()*1.5));
    }
}

nlohmann::json GardenAccessories::getJson() {
    nlohmann::json object = Product::getJson();
    object["warrantyTime"] = warrantyTime;
    return object;
}

