//
// Created by student on 11.06.2022.
//

#include "menu/TerminalMenu.h"
#include <iostream>

#include "exceptions/CustomerException.h"
#include "exceptions/ProductException.h"
#include "exceptions/ShoppingCartException.h"

#include "managers/CustomerManager.h"
#include "managers/ProductManager.h"
#include "managers/ShoppingCartManager.h"

#include "model/Address.h"
#include "model/Customer.h"
#include "model/Product.h"
#include "model/ShoppingCart.h"
#include "model/typedefs.h"




TerminalMenu::TerminalMenu(const CustomerManagerPtr &customerManager, const ProductManagerPtr &productManager,
                           const ShoppingCartManagerPtr &shoppingCartManager) : customerManager(customerManager),
                                                                                productManager(productManager),
                                                                                shoppingCartManager(
                                                                                        shoppingCartManager) {}

TerminalMenu::~TerminalMenu() {

}

void TerminalMenu::start() {
     std::cout<< "Witaj w naszym Sklepie Ogrodniczym!" << std::endl;

    bool exit = false;
    while (!exit) {
        std::cout<< "==================================" << std::endl
                    << "1. Zloz zamowienie."<<std::endl
                    << "2. Zarzadzaj  sklepem [admin]."<< std::endl
                    << "3. EXIT"<< std::endl
                    << "==================================" << std::endl;

        char pick;
        std::cin >> pick;

        switch (pick) {
            // 1. Zloz zamowienie.
            case '1':
                customer();
                break;
            //2. Zarzadzaj  sklepem [admin].
            case '2':
                admin();
                break;
            // 3. EXIT
            case '3':
                exit= true;
                break;

            default:
                std::cout<< "Bledny wybor!" << std::endl;
                break;
        }
    }

}

// 1. Zloz zamowienie.
void TerminalMenu::customer() {
    bool exit = false;
    std::cout<< "==================================" << std::endl
             << "Aby kupic produkt musisz byc zalogowany. Jesli nie posiadasz konta, zarejestruj sie!" << std::endl
             << "1. Zarejestruj sie."<<std::endl
             << "2. Zaloguj sie jesli posiadasz konto."<< std::endl
             << "3. EXIT"<< std::endl
             << "==================================" << std::endl;

    char pick;
    std::cin >> pick;

    switch (pick) {
        // 1. Zarejestruj sie.
        case '1':{
            //login traktujemy jako id
            std::string loginId, phoneNumber, pwr;
            std::cout << "Podaj login:" << std::endl;
            std::cin>>loginId;

            std::cout << "Podaj numer telefonu:" << std::endl;
            std::cin>>phoneNumber;

            std::cout << "Podaj haslo:" << std::endl;
            std::cin>>pwr;;

            //pobieranie adresu
            std::string city, street, number;
            std::cout << "Potrzebujemy twojego adresu dostawy.\n Podaj miasto:" << std::endl;
            std::cin>>city;

            std::cout << "Podaj ulice:" << std::endl;
            std::cin>>street;

            std::cout << "Podaj numer:" << std::endl;
            std::cin>>number;

            try {
                customerManager->registerCustomer(loginId, std::make_shared<Address>(street, city, number), "phoneNumber",pwr);
            } catch (CustomerException &e) {
                std::cerr << "Parameter error: " << e.what() << std::endl;
            }
            break;
    }

        //2. Zaloguj sie jesli posiadasz konto
        case '2': {
            std::string loginId, pwr;
            std::cout << "Podaj login:" << std::endl;
            std::cin.ignore();
            getline(std::cin, loginId);

            std::cout << "Podaj haslo:" << std::endl;
            std::cin.ignore();
            getline(std::cin, pwr);

            if(customerManager->getCustomer(loginId) == nullptr){
                std::cout<<"Login nie istanieje"<<std::endl;
                break;
            }

            if(customerManager->getCustomer(loginId)->getPassword() == pwr) {

                int quantity;
                std::string name;
                std::string productId;
                bool exit2= false;
                while (!exit2) {
                    std::cout<< "==================================" << std::endl
                     << "1. Wysietl i kup produkt." <<std::endl
                     << "2. Zatwierdz i zaplac." << std::endl;
                    std::cout << "==================================" << std::endl;
                    std::cin>>pick;
                    switch (pick) {
                        case '1':
                        {
                            std::cout << "Wyswietl dostepne produkty:" << std::endl;
                            productManager->getAllProductsReport();
                            std::cout<< "Wpisz nazwe produktu, numer produktu oraz jego ilość:\n" << std::endl;
                            std::cout<< "Nazwa: " << std::endl;
                            std::cin>>name;
                            std::cout<< "Numer produktu: " << std::endl;
                            std::cin>>productId;
                            std::cout<< ", Ilosc: " << std::endl;
                            std::cin>>quantity;
                            try {
                                shoppingCartManager->buyProduct(customerManager->getCustomer(loginId),
                                                                productManager->getProduct(productId), quantity);
                            } catch( ShoppingCartException &e) {
                                std::cerr << "Parameter error: " << e.what() << std::endl;
                            }
                            break;
                        }
                        case '2':
                        {
                            shoppingCartManager->Receipt(customerManager->getCustomer(loginId));
                            std::cout<< "ZATWIERDZONO" << std::endl;
                            exit2 = true;
                            break;
                        }
                    }

                }
            } else
            {
                std::cout << "Nieprawidlowe haslo!" << std::endl;
                break;
            }
            break;
        }
        case '3':
            exit= true;
            break;

        default:
            std::cout<< "Bledny wybor!" << std::endl;
            break;
    }
}


void TerminalMenu::admin() {

    bool exit = false;
    while (!exit) {
        std::cout<< "==================================" << std::endl
                 << "1. Dodaj nowe produkty."<<std::endl
                 << "2. Usun produkt z oferty."<< std::endl
                 << "3. Wyswietl informacje o produktach"<< std::endl
                 << "4. Wyswietl informacje o klientach"<< std::endl
                 << "5. Wyrejestruj klienta"<< std::endl
                 << "6. Podsumuj dochody"<< std::endl
                 << "7. Powrót."<< std::endl
                 << "==================================" << std::endl;

        char pick;
        std::cin >> pick;

        switch (pick) {
            // 1. Dodaj nowe produkty.
            case '1': {
                float price;
                int stock;
                int type;
                std::string name;
                std::string Id;
                std::cout << "Jaka to kategoria produktu? \n 1. Akcesoria Ogrodnicze? \n 2. Rosliny? ";
                    std::cin >> type;
                    if (type == 1 || type == 2) {
                    std::cout << "Podaj nazwe produktu: ";
                    std::cin >> name;
                    std::cout << "Podaj cene za sztuke: ";
                    std::cin >> price;
                    std::cout << "Podaj ilosc sztuk produktu:: ";
                    std::cin >> stock;
                    std::cout << "Podaj ID produktu, które pozwoli szybko wyszukac przedmiot :) : ";
                    std::cin >> Id;
                    if (type == 1) {
                        try {
                            productManager->registerGardenAccessories(price, stock, name, Id,
                                                                      12); //domyslnie mamy 12 ms gwarancji, za przedluzenia beda naliczane oplaty  dodatkowe
                        } catch (ProductException &e) {
                            std::cerr << "Parameter error: " << e.what() << std::endl;
                        }
                    }
                    if (type == 2) {
                        try {
                            productManager->registerPlant(price, stock, name, Id);
                        } catch (ProductException &e) {
                            std::cerr << "Parameter error: " << e.what() << std::endl;
                        }
                    }
                } else std::cout<<"Bledny wybor!" <<std::endl;

                break;
            }

            //2. Usun produkt z oferty.
            case '2':{
                std::string id;
               // productManager->getAllProductsReport();
                std::cout<< "Podaj id produktu, który chcesz usunac: ";
                std::cin >> id;
                try {
                productManager->unregisterProduct(productManager->getProduct(id));
                } catch (ProductException &e) {
                    std::cerr << "Parameter error: " << e.what() << std::endl;}
                break;
            }

            // 3. Wyswietl informacje o produktach
            case '3': {
                std::cout<<productManager->getAllProductsReport()<<std::endl;
                break;
            }
            //4. Wyswietl informacje o klientach
            case '4': {
                std::cout<<customerManager->getAllCustomersReport()<<std::endl;
                break;
            }
            //5. Wyrejestruj klienta
            case '5': {
                std::string personalId;
                std::cout<< "Podaj id Klienta, którego chcesz wyrejestrowac: ";
                std::cin>>personalId;
                try {
                    CustomerPtr customer = customerManager->getCustomer(personalId);
                    if (customer == nullptr) {
                        std::cout << "Klient o podanym peselu nie istnieje!" << std::endl;
                        break;
                    }
                customerManager->unregisterCustomer(customer);
                } catch (CustomerException &e) {
                    std::cerr << "Parameter error: " << e.what() << std::endl;
                }
                break;
            }
            //6. Podsumuj dochody
            case '6': {
                std::cout << "Aktualnie zarobiono: " << shoppingCartManager->checkCurrentProfit(customerManager->findAllCustomers()) << " zl :o" << std::endl;
                break;
            }
            //7. Powrót.
            case '7':
                exit= true;
                break;

            default:
                std::cout<< "Bledny wybor!" << std::endl;
                break;
        }
    }

}

//zapisz