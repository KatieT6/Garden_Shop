//
// Created by student on 12.06.2022.
//

#include <boost/test/unit_test.hpp>
#include "model/Product.h"
#include "model/Plants.h"
#include "model/GardenAccessories.h"
#include "model/typedefs.h"
#include "exceptions/ProductException.h"

using namespace boost::test_tools;

struct TestSuiteProductFixture{
    const std::string testName = "tuja";
    float testPrice = 50.99;
    int testStock = 5;
    std::string testProductId = "1";
    int testWarrantyTime = 12;

    TestSuiteProductFixture(){}

    ~TestSuiteProductFixture(){}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteProduct, TestSuiteProductFixture)

    BOOST_AUTO_TEST_CASE(ProductGetterTests) {
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        BOOST_CHECK_CLOSE(p->getPrice(),50.99,0.0001);
        BOOST_TEST(p->getStock() == 5);
        BOOST_TEST(p->getName() == "tuja");
        BOOST_TEST(p->getId() == "1");
    }

    BOOST_AUTO_TEST_CASE(ProductSetPriceTests) {
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        p->setPrice(40.0);
        BOOST_TEST(p->getPrice() == 40.0);
    }

    BOOST_AUTO_TEST_CASE(PrductSetStockTests) {
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        p->setStock(40);
        BOOST_TEST(p->getStock() == 40);
    }

    BOOST_AUTO_TEST_CASE(SetterNameTest){
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        BOOST_REQUIRE_NO_THROW(p->setName("dab"););
        p->setName("dab");
        BOOST_TEST(p->getName() == "dab");
    }

    BOOST_AUTO_TEST_CASE(ProductSetProductIdTests) {
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        p->setId("4");
        BOOST_TEST(p->getId() == "4");
    }
    BOOST_AUTO_TEST_CASE(SetterPriceLowerThanZeroTest){
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        BOOST_REQUIRE_THROW(p->setPrice(-1), ProductException);
        BOOST_CHECK_EXCEPTION(p->setPrice(-1), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "PRICE_LOWER_THAN_ZERO_EXCEPTION";});
        BOOST_CHECK_CLOSE(p->getPrice(),50.99,0.0001);
    }

    BOOST_AUTO_TEST_CASE(SetterStockLowerThanZeroTest){
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        BOOST_REQUIRE_THROW(p->setStock(-1), ProductException);
        BOOST_CHECK_EXCEPTION(p->setStock(-1), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "STOCK_LOWER_THAN_ZERO_EXCEPTION";});
        BOOST_TEST(p->getStock() == 5);
    }

    BOOST_AUTO_TEST_CASE(SetterNameEmptyTest){
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        BOOST_REQUIRE_THROW(p->setName(""), ProductException);
        BOOST_CHECK_EXCEPTION(p->setName(""), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "NAME_EMPTY_EXCEPTION";});
        BOOST_TEST(p->getName() == "tuja");
    }

    BOOST_AUTO_TEST_CASE(SetterProductIdEmptyTest){
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        BOOST_REQUIRE_THROW(p->setId(""), ProductException);
        BOOST_CHECK_EXCEPTION(p->setId(""), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "ID_EMPTY_EXCEPTION";});
        BOOST_TEST(p->getId() == "1");
    }

    BOOST_AUTO_TEST_CASE(ContructorTestExceptions) {
        BOOST_REQUIRE_NO_THROW(Product testProduct(testPrice, testStock, testName, testProductId));
        BOOST_REQUIRE_THROW(Product testProduct(-1, testStock, testName,  testProductId), ProductException);
        BOOST_CHECK_EXCEPTION(Product testProduct(-1, testStock, testName, testProductId), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "PRICE_LOWER_THAN_ZERO_EXCEPTION";});
        BOOST_REQUIRE_THROW(Product testProduct(testPrice, -1, testName,  testProductId), ProductException);
        BOOST_CHECK_EXCEPTION(Product testProduct(testPrice, -1, testName, testProductId), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "STOCK_LOWER_THAN_ZERO_EXCEPTION";});
        BOOST_REQUIRE_THROW(Product testProduct(testPrice, testStock, "", testProductId), ProductException);
        BOOST_CHECK_EXCEPTION(Product testProduct(testPrice, testStock, "", testProductId), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "NAME_EMPTY_EXCEPTION";});
        BOOST_REQUIRE_THROW(Product testProduct(testPrice, testStock, testName, ""), ProductException);
        BOOST_CHECK_EXCEPTION(Product testProduct(testPrice, testStock, testName, ""), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "ID_EMPTY_EXCEPTION";});
    }

    BOOST_AUTO_TEST_CASE(ArchivedTest) {
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);

        p->setArchived(true);

        BOOST_TEST(p->isArchived());
    }
    BOOST_AUTO_TEST_CASE(GetInfoPlantsTest) {
        ProductPtr p = std::make_shared<Plants>(testPrice, testStock, testName, testProductId);
        BOOST_TEST(p->getInfo() == "Produkt: nazwa: " + testName + ", ilosc sztuki produktu: " + std::to_string(testStock) + ", cena za sztuke: " + std::to_string(testPrice) + ", numer produktu: " + testProductId);
    }

    BOOST_AUTO_TEST_CASE(GetInfoGardenAccessoriesTest) {
        ProductPtr p = std::make_shared<GardenAccessories>(testPrice, testStock, testName, testProductId, testWarrantyTime);
        BOOST_TEST(p->getInfo() ==
                   "Produkt: nazwa: " + testName + ", ilosc sztuki produktu: " + std::to_string(testStock) + ", cena za sztuke: " +
                   std::to_string(testPrice) + ", numer produktu: " + testProductId + ", Czas gwarancji: " + std::to_string(testWarrantyTime));
    }

    BOOST_AUTO_TEST_CASE(ContructorTest) {
        BOOST_REQUIRE_NO_THROW(Product testProduct(testPrice, testStock, testName, testProductId));
        Product testProduct(testPrice, testStock, testName, testProductId);
        BOOST_TEST(testProduct.getInfo() == "Produkt: nazwa: " + testName + ", ilosc sztuki produktu: " + std::to_string(testStock) + ", cena za sztuke: " +
                std::to_string(testPrice)+ ", numer produktu: " + testProductId);
    }

    BOOST_AUTO_TEST_CASE(ContructorGardenAccessoriesTest) {
        BOOST_REQUIRE_NO_THROW(GardenAccessories testProduct(testPrice, testStock, testName, testProductId, testWarrantyTime));
        GardenAccessories testProduct(testPrice, testStock, testName, testProductId, testWarrantyTime);
        BOOST_TEST(testProduct.getInfo() == "Produkt: nazwa: " + testName + ", ilosc sztuki produktu: " + std::to_string(testStock) + ", cena za sztuke: " +
                                            std::to_string(testPrice) + ", numer produktu: " + testProductId + ", Czas gwarancji: " + std::to_string(testWarrantyTime) );
    }

    BOOST_AUTO_TEST_CASE(ContructorGATestExceptions) {
        BOOST_REQUIRE_NO_THROW(GardenAccessories testProduct(testPrice, testStock, testName, testProductId, testWarrantyTime));
        BOOST_REQUIRE_THROW(GardenAccessories testProduct(-1, testStock, testName,  testProductId, testWarrantyTime), ProductException);
        BOOST_CHECK_EXCEPTION(GardenAccessories testProduct(-1, testStock, testName, testProductId, testWarrantyTime), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "PRICE_LOWER_THAN_ZERO_EXCEPTION";});
        BOOST_REQUIRE_THROW(GardenAccessories testProduct(testPrice, -1, testName,  testProductId, testWarrantyTime), ProductException);
        BOOST_CHECK_EXCEPTION(GardenAccessories testProduct(testPrice, -1, testName, testProductId, testWarrantyTime), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "STOCK_LOWER_THAN_ZERO_EXCEPTION";});
        BOOST_REQUIRE_THROW(GardenAccessories testProduct(testPrice, testStock, "", testProductId, testWarrantyTime), ProductException);
        BOOST_CHECK_EXCEPTION(GardenAccessories testProduct(testPrice, testStock, "", testProductId, testWarrantyTime), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "NAME_EMPTY_EXCEPTION";});
        BOOST_REQUIRE_THROW(GardenAccessories testProduct(testPrice, testStock, testName, "", testWarrantyTime), ProductException);
        BOOST_CHECK_EXCEPTION(GardenAccessories testProduct(testPrice, testStock, testName, "", testWarrantyTime), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "ID_EMPTY_EXCEPTION";});
        BOOST_REQUIRE_THROW(GardenAccessories testProduct(testPrice, testStock, testName, testProductId, 5), ProductException);
        BOOST_CHECK_EXCEPTION(GardenAccessories testProduct(testPrice, testStock, testName, testProductId, 5), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "WARRANTY_DIFFERERNT_THAN_POSSIBLE_EXCEPTION";});
    }

    BOOST_AUTO_TEST_CASE(ProductSetWarrantyTimeTests) {
        GardenAccessories p(testPrice, testStock, testName, testProductId, testWarrantyTime);
        p.setWarrantyTime(12);
        BOOST_TEST(p.getWarrantyTime() == 12);
    }
    BOOST_AUTO_TEST_CASE(SetterSetWarrantyTimeOtherThanPossibleTest){
        GardenAccessories p(testPrice, testStock, testName, testProductId, testWarrantyTime);
        BOOST_REQUIRE_THROW(p.setWarrantyTime(5), ProductException);
        BOOST_CHECK_EXCEPTION(p.setWarrantyTime(5), ProductException, [](const ProductException &e) -> bool {std::string s(e.what()); return s == "WARRANTY_DIFFERERNT_THAN_POSSIBLE_EXCEPTION";});
        BOOST_TEST(p.getWarrantyTime() == 12);
    }

    BOOST_AUTO_TEST_SUITE_END()

