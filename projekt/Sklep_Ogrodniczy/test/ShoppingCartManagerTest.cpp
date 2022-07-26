//
// Created by student on 18.06.2022.
//

#include "managers/ShoppingCartManager.h"
#include "exceptions/ShoppingCartException.h"
#include "exceptions/CustomerException.h"
#include "exceptions/ProductException.h"
#include "model/ShoppingCart.h"
#include "model/ShoppingCart.h"
#include <boost/test/unit_test.hpp>
#include "repositories/Repository.h"
#include "model/Address.h"
#include "model/Product.h"
#include "model/Plants.h"
#include "model/Customer.h"
#include "model/typedefs.h"


struct TestSuiteShoppingCartManagerFixture{
    float testCurrentPrice = 0.0;
    const std::string testId = "3421";
    const std::string testId2 = "6381";
    const std::vector<ProductPtr> testProductList;
    ShoppingCartRepositoryPtr testShoppingCartRepository;
    ShoppingCartRepositoryPtr  testCurrentShoppingCarts = std::make_shared<Repository<ShoppingCartPtr>>();
    ShoppingCartRepositoryPtr testArchivedShoppingCarts = std::make_shared<Repository<ShoppingCartPtr>>();
    float testPrice = 31.99;
    int testStock = 13;
    const std::string testProductName = "tuja";
    const std::string testProductId = "3421";
    float testPrice2 = 16.00;
    int testStock2 = 9;
    const std::string testProductName2 = "kaktus";
    const std::string testProductId2 = "8645";
    const std::string tcId = "231";
    const std::string tcId2 = "521";
    const std::string tcPhoneNumber = "123456789";
    const std::string tcPassword = "mnbv";
    AddressPtr testAddress;
    ProductPtr testProduct;
    ProductPtr testProduct2;
    ProductPtr testProduct3;
    CustomerPtr testCustomer;
    CustomerPtr testCustomer2;
    CustomerPtr testCustomerArchived;

    TestSuiteShoppingCartManagerFixture(){
        testShoppingCartRepository = std::make_shared<Repository<ShoppingCartPtr>>();
        testAddress = std::make_shared<Address>("Padereckiego", "Kielce", "42");
        testProduct = std::make_shared<Plants>(testPrice, testStock, testProductName, testProductId);
        testProduct2 = std::make_shared<Plants>(testPrice2, testStock2, testProductName2, testProductId2);
        testCustomer = std::make_shared<Customer>(tcId, testAddress, tcPhoneNumber, tcPassword);
        testCustomerArchived = std::make_shared<Customer>(tcId2, testAddress, tcPhoneNumber, tcPassword);
        testCustomerArchived->setArchived(true);
    }
};

BOOST_FIXTURE_TEST_SUITE(ShoppingCartManagerTestSuite, TestSuiteShoppingCartManagerFixture)

    BOOST_AUTO_TEST_CASE(ContructorException) {
        BOOST_REQUIRE_THROW(ShoppingCartManager m=ShoppingCartManager(nullptr, nullptr), ShoppingCartException);
    }

    BOOST_AUTO_TEST_CASE(GetShoppingCartTest){
        ShoppingCartManager shoppingCartManager(testCurrentShoppingCarts, testArchivedShoppingCarts);
        shoppingCartManager.buyProduct(testCustomer, testProduct, 2);
        ShoppingCartPtr testShoppingCart = shoppingCartManager.getShoppingCartbyCustomer(testCustomer);
        BOOST_TEST_REQUIRE(testShoppingCart == shoppingCartManager.getShoppingCartbyCustomer(testCustomer));
    }

    BOOST_AUTO_TEST_CASE(BuyProductExceptionsTest){
        ShoppingCartManager shoppingCartManager(testCurrentShoppingCarts, testArchivedShoppingCarts);
        shoppingCartManager.buyProduct(testCustomer, testProduct, 2);
        ShoppingCartPtr testShoppingCart = shoppingCartManager.getShoppingCartbyCustomer(testCustomer);
        BOOST_REQUIRE_THROW(shoppingCartManager.buyProduct(testCustomer2, testProduct, 2), CustomerException);
        BOOST_CHECK_EXCEPTION(shoppingCartManager.buyProduct(testCustomer2, testProduct, 2), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "ShoppingCartManager::buyProduct() -> Customer can't be null";});
        BOOST_REQUIRE_THROW(shoppingCartManager.buyProduct(testCustomer, testProduct3, 2), ProductException);
        BOOST_CHECK_EXCEPTION(shoppingCartManager.buyProduct(testCustomer, testProduct3, 2), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "ShoppingCartManager::buyProduct() -> Product can't be null";});
        BOOST_REQUIRE_THROW(shoppingCartManager.buyProduct(testCustomer, testProduct, -5), ProductException);
        BOOST_CHECK_EXCEPTION(shoppingCartManager.buyProduct(testCustomer, testProduct, -5), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "ShoppingCartManager::buyProduct() -> Are you dumb?";});
        BOOST_REQUIRE_THROW(shoppingCartManager.buyProduct(testCustomer, testProduct, 432), ProductException);
        BOOST_CHECK_EXCEPTION(shoppingCartManager.buyProduct(testCustomer, testProduct, 432), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "ShoppingCartManager::buyProduct() -> Product is not available";});
        BOOST_REQUIRE_THROW(shoppingCartManager.buyProduct(testCustomerArchived, testProduct, 2), CustomerException);
        BOOST_CHECK_EXCEPTION(shoppingCartManager.buyProduct(testCustomerArchived, testProduct, 2), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "ShoppingCartManager::buyProduct() -> Customer is archived";});
        testProduct2->setArchived(true);
        BOOST_REQUIRE_THROW(shoppingCartManager.buyProduct(testCustomer, testProduct2, 2), ProductException);
        BOOST_CHECK_EXCEPTION(shoppingCartManager.buyProduct(testCustomer, testProduct2, 2), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "ShoppingCartManager::buyProduct() -> Product is archived";});
    }

    BOOST_AUTO_TEST_CASE(BuyProductTest){
        ShoppingCartManager shoppingCartManager(testCurrentShoppingCarts, testArchivedShoppingCarts);
        shoppingCartManager.buyProduct(testCustomer, testProduct, 2);
        shoppingCartManager.buyProduct(testCustomer, testProduct2, 3);
        float price = 111.98;
        BOOST_CHECK_CLOSE(shoppingCartManager.Receipt(testCustomer), price, 0.0001);
}

    BOOST_AUTO_TEST_CASE(FindShoppingCartsTest){
        ShoppingCartManager shoppingCartManager(testCurrentShoppingCarts, testArchivedShoppingCarts);
        shoppingCartManager.buyProduct(testCustomer, testProduct, 2);
        ShoppingCartPtr testShoppingCart = shoppingCartManager.getShoppingCartbyCustomer(testCustomer);
        CustomerPtr customer = testCustomer;
        BOOST_TEST_REQUIRE(testShoppingCart == shoppingCartManager.findShoppingCarts([&customer](const ShoppingCartPtr &ptr) -> bool {return ptr->getCartId() == customer->getId();})[0]);
    }

    BOOST_AUTO_TEST_CASE(FindAllCustomersTest){
        ShoppingCartManager shoppingCartManager(testCurrentShoppingCarts, testArchivedShoppingCarts);
        shoppingCartManager.buyProduct(testCustomer, testProduct, 2);
        testCustomer2 = std::make_shared<Customer>(tcId2, testAddress, tcPhoneNumber, tcPassword);
        shoppingCartManager.buyProduct(testCustomer2, testProduct, 2);
        ShoppingCartPtr testShoppingCart = shoppingCartManager.getShoppingCartbyCustomer(testCustomer);
        ShoppingCartPtr testShoppingCart2 = shoppingCartManager.getShoppingCartbyCustomer(testCustomer2);
        BOOST_TEST_REQUIRE(shoppingCartManager.findAllShoppingCarts().size() == 2);
    }

BOOST_AUTO_TEST_SUITE_END()