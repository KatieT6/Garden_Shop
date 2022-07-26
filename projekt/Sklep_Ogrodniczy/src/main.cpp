#include <iostream>

#include "menu/TerminalMenu.h"

#include "managers/CustomerManager.h"
#include "managers/ProductManager.h"
#include "managers/ShoppingCartManager.h"

#include "repositories/Repository.h"

using namespace std;

int main()
{

    cout<<"Hello!! :) luv\n "<<endl;

    CustomerRepositoryPtr customerRepo = std::make_shared<Repository<CustomerPtr>>();
    CustomerManagerPtr customerManager = std::make_shared<CustomerManager>(customerRepo);

    ProductRepositoryPtr productRepo= std::make_shared<Repository<ProductPtr>>();
    ProductManagerPtr productManager = std::make_shared<ProductManager>(productRepo);

    ShoppingCartRepositoryPtr currentShoppingCarts = std::make_shared<Repository<ShoppingCartPtr>>();
    ShoppingCartRepositoryPtr archiveRents = std::make_shared<Repository<ShoppingCartPtr>>();
    ShoppingCartManagerPtr shoppingCartManager = std::make_shared<ShoppingCartManager>(currentShoppingCarts,archiveRents);

    TerminalMenu menu(customerManager, productManager, shoppingCartManager);

    menu.start();
    customerManager->save("CustomerJson");
    productManager->save("ProductJson");
    shoppingCartManager->save("ShoppingCartJson");

    return 0;
}
