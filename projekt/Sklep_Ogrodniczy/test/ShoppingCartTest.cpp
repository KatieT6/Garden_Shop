//
// Created by student on 12.06.2022.
//

#include <boost/test/unit_test.hpp>
#include "model/ShoppingCart.h"
#include "model/Customer.h"
#include "model/Address.h"
#include "model/Product.h"
#include "model/Plants.h"
#include "exceptions/ShoppingCartException.h"

namespace btt = boost::test_tools;

struct TestSuiteShoppingCartFixture {
    const float testCurrentPrice = 0;
    const std::string testCartId = "0123456789";
    const unsigned int testBasePrice = 100;
    std::vector<ProductPtr> productsList;
    ProductPtr testProduct1;
    ProductPtr testProduct2;
    float testProductPrice1 = 13.59;
    int testProductStock1 = 5;
    float testProductPrice2 = 20.30;
    int testProductStock2 = 8;

    TestSuiteShoppingCartFixture() {
        testProduct1 = std::make_shared<Plants>(testProductPrice1, testProductStock1, "tuja", "17");
        testProduct2 = std::make_shared<Plants>(testProductPrice2, testProductStock2, "kaktus", "23");
    }
};
BOOST_FIXTURE_TEST_SUITE(TestSuiteShoppingCart, TestSuiteShoppingCartFixture)

    BOOST_AUTO_TEST_CASE(ContructorTest) {
    BOOST_REQUIRE_NO_THROW(ShoppingCartPtr testShoppingCart = std::make_shared<ShoppingCart>(testCurrentPrice, testCartId));
    ShoppingCart shoppingCart(testCurrentPrice, testCartId);
    shoppingCart.addPoduct(testProduct1,1);
    BOOST_TEST(shoppingCart.getInfo() == "ID koszyka: " + testCartId + ", Przedmioty w koszyku: \n" + testProduct1->getInfo() + ", " + std::to_string(testCurrentPrice + testProduct1->getPrice()));
    }


    BOOST_AUTO_TEST_CASE(ContructorTestExceptions) {
    BOOST_REQUIRE_NO_THROW(ShoppingCart testShoppingCart(testCurrentPrice, testCartId));
    BOOST_REQUIRE_THROW(ShoppingCart testShoppingCart(-321, testCartId), ShoppingCartException);
    BOOST_CHECK_EXCEPTION(ShoppingCart testShoppingCart(-321, testCartId), ShoppingCartException, [](const ShoppingCartException &e) -> bool {std::string s(e.what()); return s == "PRICE_LOWER_THAN_ZERO_EXCEPTION";});
    BOOST_REQUIRE_THROW(ShoppingCart testShoppingCart(testCurrentPrice, ""), ShoppingCartException);
    BOOST_CHECK_EXCEPTION(ShoppingCart testShoppingCart(testCurrentPrice, ""), ShoppingCartException, [](const ShoppingCartException &e) -> bool {std::string s(e.what()); return s == "ID_EMPTY_EXCEPTION";});
}

    BOOST_AUTO_TEST_CASE(SetterIdTest){
    ShoppingCart SH(testCurrentPrice, testCartId);
        BOOST_REQUIRE_NO_THROW(SH.setCartId("214"));
        SH.setCartId("214");
        BOOST_TEST(SH.getCartId() == "214");
}

    BOOST_AUTO_TEST_CASE(SetterIdEmptyTest){
    ShoppingCart SH(testCurrentPrice, testCartId);
        BOOST_REQUIRE_THROW(SH.setCartId(""), ShoppingCartException);
        BOOST_CHECK_EXCEPTION(SH.setCartId(""), ShoppingCartException, [](const ShoppingCartException &e) -> bool {std::string s(e.what()); return s == "ID_EMPTY_EXCEPTION";});
        BOOST_TEST(SH.getCartId() == testCartId);
        }

    BOOST_AUTO_TEST_CASE(AddProductTest){
    ShoppingCart SH(testCurrentPrice, testCartId);
    SH.addPoduct(testProduct1,testProductStock1);
    BOOST_TEST(SH.getInfo() == "ID koszyka: " + testCartId + ", Przedmioty w koszyku: \n" + testProduct1->getInfo()
    + ", " + std::to_string(testCurrentPrice + testProductStock1*testProduct1->getPrice()));
}

    BOOST_AUTO_TEST_CASE(DeleteProductTest){
    ShoppingCart SH(testCurrentPrice, testCartId);
    SH.addPoduct(testProduct1,testProductStock1);
    SH.addPoduct(testProduct2,testProductStock2);
    SH.deletePoduct(testProduct1,testProductStock1);
    BOOST_TEST(SH.getInfo() == "ID koszyka: " + testCartId + ", Przedmioty w koszyku: \n" + testProduct2->getInfo()
    + ", " + std::to_string(testProductStock2*testProduct2->getPrice()));
}

BOOST_AUTO_TEST_SUITE_END()
