//
// Created by student on 11.06.2022.
//

#ifndef SKLEP_OGRODNICZY_TERMINALMENU_H
#define SKLEP_OGRODNICZY_TERMINALMENU_H
#include "model/typedefs.h"


class TerminalMenu {
private:
    CustomerManagerPtr customerManager;
    ProductManagerPtr productManager;
    ShoppingCartManagerPtr shoppingCartManager;
public:

    TerminalMenu(const CustomerManagerPtr &customerManager, const ProductManagerPtr &productManager,
                 const ShoppingCartManagerPtr &shoppingCartManager);

    virtual ~TerminalMenu();
    void start();
    void customer();
    void admin();
    void buy();
    void save();
};


#endif //SKLEP_OGRODNICZY_TERMINALMENU_H
