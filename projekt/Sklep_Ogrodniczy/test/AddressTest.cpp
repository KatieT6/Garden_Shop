//
// Created by student on 12.06.2022.
//

#include <boost/test/unit_test.hpp>

#include "model/Address.h"
#include "exceptions/CustomerException.h"

BOOST_AUTO_TEST_SUITE(TestSuiteAddress)

    BOOST_AUTO_TEST_CASE(ContructorTest) {
        Address address("Piotrkowska", "Lodz", "11");
        BOOST_TEST(address.getCity() == "Lodz");
        BOOST_TEST(address.getStreet() == "Piotrkowska");
        BOOST_TEST(address.getNumber() == "11");
    }

    BOOST_AUTO_TEST_CASE(ParameterConstructorExceptionTest){
        BOOST_CHECK_NO_THROW(Address address("Lodz","Piotrkowska","11"));
        BOOST_REQUIRE_THROW(Address address("","Piotrkowska","11"), CustomerException);
        BOOST_CHECK_EXCEPTION(Address address("","Piotrkowska","11"), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "ADDRESS_EMPTY_EXCEPTION";});
        BOOST_REQUIRE_THROW(Address address("Lodz","","11"), CustomerException);
        BOOST_CHECK_EXCEPTION(Address address("Lodz","","11"), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "ADDRESS_EMPTY_EXCEPTION";});
        BOOST_REQUIRE_THROW(Address address("Lodz","Piotrkowska",""), CustomerException);
        BOOST_CHECK_EXCEPTION(Address address("Lodz","Piotrkowska",""), CustomerException, [](const CustomerException &e) -> bool {std::string s(e.what()); return s == "ADDRESS_EMPTY_EXCEPTION";});
    }

    BOOST_AUTO_TEST_CASE(SettersTest) {
        Address address("Piotrkowska", "Ldoz", "11");
        address.setCity("Poland");
        BOOST_TEST(address.getCity() == "Poland");
        address.setCity("");
        BOOST_TEST(address.getCity() == "Poland");

        address.setStreet("ul");
        BOOST_TEST(address.getStreet() == "ul");
        address.setStreet("");
        BOOST_TEST(address.getStreet() == "ul");

        address.setNumber("nr");
        BOOST_TEST(address.getNumber() == "nr");
        address.setNumber("");
        BOOST_TEST(address.getNumber() == "nr");
    }

    BOOST_AUTO_TEST_CASE(GetInfoTest) {
        Address address("Piotrkowska", "Lodz", "217");

        BOOST_TEST("ADDRESS city: Lodz, street: Piotrkowska, number: 217" == address.getInfo());
    }

BOOST_AUTO_TEST_SUITE_END()


