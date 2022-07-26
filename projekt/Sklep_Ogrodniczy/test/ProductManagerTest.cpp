//
// Created by student on 18.06.2022.
//
#include "managers/ProductManager.h"
#include "exceptions/ProductException.h"
#include "model/Product.h"
#include <boost/test/unit_test.hpp>
#include "repositories/Repository.h"

struct TestSuiteProductManagerFixture{
    ProductManagerPtr testProductManager;
    float testPrice = 31.99;
    int testStock = 13;
    const std::string testName = "tuja";
    const std::string testId = "3421";
    const std::string testId2 = "6381";
    int testWarrantyTime = 12;
    ProductRepositoryPtr testProductRepository;

    TestSuiteProductManagerFixture(){
        testProductRepository = std::make_shared<Repository<ProductPtr>>();
    }
};

BOOST_FIXTURE_TEST_SUITE(ProductManagerTestSuite, TestSuiteProductManagerFixture)

    BOOST_AUTO_TEST_CASE(ContructorException) {
        BOOST_REQUIRE_THROW(new ProductManager(nullptr), ProductException);
}
    BOOST_AUTO_TEST_CASE(RegisterPlantTest) {
        ProductManager productManager(testProductRepository);
        ProductPtr testProduct = productManager.registerPlant(testPrice, testStock, testName, testId);
        BOOST_TEST_REQUIRE(testProduct == productManager.getProduct(testId));
    }

    BOOST_AUTO_TEST_CASE(RegisterGardenAccessoriesTest) {
        ProductManager productManager(testProductRepository);
        ProductPtr testProduct = productManager.registerGardenAccessories(testPrice, testStock, testName, testId, testWarrantyTime);
        BOOST_TEST_REQUIRE(testProduct == productManager.getProduct(testId));
    }

    BOOST_AUTO_TEST_CASE(GetProductFalseTest){
        ProductManager productManager(testProductRepository);
        ProductPtr testProduct = productManager.registerPlant(testPrice, testStock, testName, testId);
        BOOST_TEST_REQUIRE(testProduct == productManager.getProduct(testId));
        BOOST_TEST(productManager.getProduct(testId2) == nullptr);
    }

    BOOST_AUTO_TEST_CASE(UnregisterProductTest) {
        ProductManager productManager(testProductRepository);
        ProductPtr testProduct = productManager.registerGardenAccessories(testPrice, testStock, testName, testId, testWarrantyTime);
        productManager.unregisterProduct(testProduct);
        BOOST_TEST(productManager.getProduct(testId)->isArchived());
    }
BOOST_AUTO_TEST_SUITE_END()