//
// Created by student on 17.06.2022.
//

//#include "model/typedefs.h"
#include "managers/CustomerManager.h"
#include "exceptions/CustomerException.h"
#include "model/Customer.h"
#include "model/Address.h"
#include <boost/test/unit_test.hpp>
#include "repositories/Repository.h"

//tc= testCustomer

struct TestSuiteCustomerManagerFixture {
    CustomerManagerPtr testCustomerManager;
    const std::string tcId = "231";
    const std::string tcId2 = "521";
    const std::string tcPhoneNumber = "123456789";
    const std::string tcPassword = "mnbv";
    AddressPtr testAddress;
    AddressPtr testAddress2;
    CustomerRepositoryPtr testCustomerRepository;

    TestSuiteCustomerManagerFixture(){
        testCustomerRepository = std::make_shared<Repository<CustomerPtr>>();
      //  testCustomerManager = std::make_shared<CustomerManager>();
        testAddress = std::make_shared<Address>("Padereckiego", "Kielce", "42");
        testAddress2 = std::make_shared<Address>("piotrkowska", "Uc", "21");

    }

};

BOOST_FIXTURE_TEST_SUITE(CustomerManagerTestSuite, TestSuiteCustomerManagerFixture)

    BOOST_AUTO_TEST_CASE(ContructorException) {
        BOOST_REQUIRE_THROW(new CustomerManager(nullptr), CustomerException);
    }
    BOOST_AUTO_TEST_CASE(RegisterCustomerTest) {
        CustomerManager cManager(testCustomerRepository);
        CustomerPtr testCustomer = cManager.registerCustomer(tcId,testAddress,tcPhoneNumber,tcPassword);
        BOOST_TEST_REQUIRE(testCustomer == cManager.getCustomer(tcId));
    }

    BOOST_AUTO_TEST_CASE(RegisterCustomerTestTheSameID) {
        CustomerManager cManager(testCustomerRepository);
        // zeby nie bylo bledu tylko ID musza sie roznic!!
        CustomerPtr testCustomer1 = cManager.registerCustomer(tcId,testAddress,tcPhoneNumber,tcPassword);
        BOOST_TEST_REQUIRE(testCustomer1 == cManager.getCustomer(tcId));
        BOOST_REQUIRE_THROW(CustomerPtr testCustomer2 = cManager.registerCustomer(tcId,testAddress2,tcPhoneNumber,tcPassword),CustomerException);
}

    BOOST_AUTO_TEST_CASE(GetCustomerTest){
        CustomerManager cManager(testCustomerRepository);
        CustomerPtr testCustomer1 = cManager.registerCustomer(tcId,testAddress,tcPhoneNumber,tcPassword);
        BOOST_TEST_REQUIRE(testCustomer1 == cManager.getCustomer(tcId));
}

    BOOST_AUTO_TEST_CASE(GetCustomerFalseTest){
        CustomerManager cManager(testCustomerRepository);
        CustomerPtr testCustomer1 = cManager.registerCustomer(tcId,testAddress,tcPhoneNumber,tcPassword);
        BOOST_TEST_REQUIRE(testCustomer1 == cManager.getCustomer(tcId));
        BOOST_TEST(cManager.getCustomer(tcId2) == nullptr);
    }

    BOOST_AUTO_TEST_CASE(UnregisterCustomerTest) {
        CustomerManager cManager(testCustomerRepository);
        CustomerPtr customer = cManager.registerCustomer(tcId, testAddress, tcPhoneNumber, tcPassword);
        cManager.unregisterCustomer(customer);
        BOOST_TEST(cManager.getCustomer(tcId)->isArchived());
    }

    BOOST_AUTO_TEST_CASE(FindCustomersTest){
        CustomerManager cManager(testCustomerRepository);
        CustomerPtr customer = cManager.registerCustomer(tcId, testAddress, tcPhoneNumber, tcPassword);
        BOOST_TEST_REQUIRE(customer == cManager.findCustomers([&customer](const CustomerPtr &ptr) -> bool {return ptr->getId() == customer->getId();})[0]);
    }

    BOOST_AUTO_TEST_CASE(FindAllCustomersTest){
        CustomerManager cManager(testCustomerRepository);
        CustomerPtr customer = cManager.registerCustomer(tcId, testAddress, tcPhoneNumber, tcPassword);
        CustomerPtr customer2 = cManager.registerCustomer(tcId2, testAddress2, tcPhoneNumber, tcPassword);
        BOOST_TEST_REQUIRE(cManager.findAllCustomers().size() == 2);
    }

BOOST_AUTO_TEST_SUITE_END()