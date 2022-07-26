//
// Created by student on 12.06.2022.
//

#include <boost/test/unit_test.hpp>

#include "model/Customer.h"
#include "model/Address.h"
#include "repositories/Repository.h"
#include "exceptions/CustomerException.h"
#include "model/typedefs.h"
#include <functional>

namespace btt = boost::test_tools;

struct TestSuiteCustomerFixture {
    const std::string testID = "0123456789";
    const std::string testID2 = "0123456789";
    const std::string testPhoneNumber = "111222333";
    const std::string testPhoneNumber2 = "111222333";
    const std::string testPassword = "abcd";
    const std::string testPassword2 = "efghij";
    const std::string testCity = "Lodz";
    const std::string testStreet = "Piotrkowska";
    const std::string testNumber = "11";
    bool testArchived = false;
    AddressPtr testAddress;
    AddressPtr testAddress2;

    TestSuiteCustomerFixture(){
        testAddress = std::make_shared<Address>(testCity, testStreet, testNumber);
        testAddress2 = std::make_shared<Address>("Gdynia", "Pomorska", "8");
    }

    ~TestSuiteCustomerFixture(){}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteCustomer, TestSuiteCustomerFixture)

    BOOST_AUTO_TEST_CASE(ContructorTest) {
        BOOST_REQUIRE_NO_THROW(CustomerPtr testCustomer = std::make_shared<Customer>(testID, testAddress, testPhoneNumber, testPassword)) ;
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_TEST(customer.getInfo() == "Klient: \n\tID: " + testID + "\n\tAdres: " + testAddress->getInfo() + "\n\tNumer telefonu: " + testPhoneNumber + "\n\tHasło: " + testPassword);
    }


    BOOST_AUTO_TEST_CASE(ContructorTestExceptions) {
        BOOST_REQUIRE_NO_THROW(Customer testCustomer(testID, testAddress, testPhoneNumber, testPassword));
        BOOST_REQUIRE_THROW(Customer testCustomer("", testAddress, testPhoneNumber,  testPassword), CustomerException);
        BOOST_CHECK_EXCEPTION(Customer testCustomer("", testAddress, testPhoneNumber, testPassword), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "ID_EMPTY_EXCEPTION";});
        BOOST_REQUIRE_THROW(Customer testCustomer(testID, nullptr, testPhoneNumber,  testPassword), CustomerException);
        BOOST_CHECK_EXCEPTION(Customer testCustomer(testID, nullptr, testPhoneNumber, testPassword), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "ADDRESS_NULLPTR_EXCEPTION";});
        BOOST_REQUIRE_THROW(Customer testCustomer(testID, testAddress, "", testPassword), CustomerException);
        BOOST_CHECK_EXCEPTION(Customer testCustomer(testID, testAddress, "", testPassword), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "PHONE_NUMBER_EMPTY_EXCEPTION";});
        BOOST_REQUIRE_THROW(Customer testCustomer(testID, testAddress, testPhoneNumber, ""), CustomerException);
        BOOST_CHECK_EXCEPTION(Customer testCustomer(testID, testAddress, testPhoneNumber, ""), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "PASSWORD_EMPTY_EXCEPTION";});
    }

    BOOST_AUTO_TEST_CASE(GetInfoTest) {
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_TEST(customer.getInfo() ==
                           "Klient: \n\tID: " + testID + "\n\tAdres: " + testAddress->getInfo() + "\n\tNumer telefonu: " + testPhoneNumber + "\n\tHasło: " + testPassword);
    }

    BOOST_AUTO_TEST_CASE(ArchivedTest) {
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);

        customer.setArchived(true);

        BOOST_TEST(customer.isArchived());
    }

    BOOST_AUTO_TEST_CASE(SetterIdTest){
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_REQUIRE_NO_THROW(customer.setId("Maja"));
        customer.setId("Maja");
        BOOST_TEST(customer.getId() == "Maja");
    }

    BOOST_AUTO_TEST_CASE(SetterPhoneNumberTest){
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_REQUIRE_NO_THROW(customer.setPhoneNumber("123456789"));
        customer.setPhoneNumber("123456789");
        BOOST_TEST(customer.getPhoneNumber() == "123456789");
    }

    BOOST_AUTO_TEST_CASE(SetterPasswordTest){
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_REQUIRE_NO_THROW(customer.setPassword("qwer"));
        customer.setPassword("qwer");
        BOOST_TEST(customer.getPassword() == "qwer");
    }

    BOOST_AUTO_TEST_CASE(SetterIdEmptyTest){
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_REQUIRE_THROW(customer.setId(""), CustomerException);
        BOOST_CHECK_EXCEPTION(customer.setId(""), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "ID_EMPTY_EXCEPTION";});
        BOOST_TEST(customer.getId() == testID);
    }

    BOOST_AUTO_TEST_CASE(SetterPhoneNumberEmptyTest){
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_REQUIRE_THROW(customer.setPhoneNumber(""), CustomerException);
        BOOST_CHECK_EXCEPTION(customer.setPhoneNumber(""), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "PHONE_NUMBER_EMPTY_EXCEPTION";});
        BOOST_TEST(customer.getPhoneNumber() == testPhoneNumber);
    }

    BOOST_AUTO_TEST_CASE(SetterPasswordEmptyTest){
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_REQUIRE_THROW(customer.setPassword(""), CustomerException);
        BOOST_CHECK_EXCEPTION(customer.setPassword(""), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "PASSWORD_EMPTY_EXCEPTION";});
        BOOST_TEST(customer.getPassword() == testPassword);
    }

    BOOST_AUTO_TEST_CASE(SetterArchivedTest){
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_REQUIRE_NO_THROW(customer.setArchived(true));
        customer.setArchived(true);
        BOOST_TEST(customer.isArchived() == true);
    }

    BOOST_AUTO_TEST_CASE(SetterAddressTest){
        Customer customer(testID, testAddress2, testPhoneNumber, testPassword);
        BOOST_REQUIRE_NO_THROW(customer.setAddress(testAddress2));
        customer.setAddress(testAddress2);
        BOOST_TEST(customer.getAddress() == testAddress2);
    }

    BOOST_AUTO_TEST_CASE(SetterAddressEmptyTest){
        Customer customer(testID, testAddress, testPhoneNumber, testPassword);
        BOOST_REQUIRE_THROW(customer.setAddress(nullptr), CustomerException);
        BOOST_CHECK_EXCEPTION(customer.setAddress(nullptr), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "ADDRESS_NULLPTR_EXCEPTION";});
        BOOST_TEST(customer.getAddress() == testAddress);
    }


BOOST_AUTO_TEST_SUITE_END()
