//
// Created by student on 20.06.2022.
//
#include <boost/test/unit_test.hpp>

#include "repositories/Repository.h"
#include "model/typedefs.h"
#include "model/Customer.h"
#include "model/Address.h"

struct TestSuiteRepositoryFixture {
    const std::string testId = "5436";
    const std::string testPassword = "adfsa";
    const std::string testPhoneNumber = "0123456789";
    AddressPtr testAddress;

    TestSuiteRepositoryFixture() {
        testAddress = std::make_shared<Address>("Mickiewicza", "Opole", "56");
    }
};

// Testy tworzone dla jednego, bo reszta zachowuje się tak samo

BOOST_FIXTURE_TEST_SUITE(TestSuiteRepository, TestSuiteRepositoryFixture)

    BOOST_AUTO_TEST_CASE(GetTest) {
        Repository<CustomerPtr> cRepo;
        int size = 5;
        CustomerPtr customers[size];

        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            customers[i] = std::make_shared<Customer>(testId, testAddress, testPhoneNumber, testPassword);
            cRepo.add(customers[i]);
        }

        for (int i = 0; i < size; i++) {
            BOOST_TEST(cRepo.get(i) == customers[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(GetTestException) {
        Repository<CustomerPtr> cRepo;
        BOOST_REQUIRE_THROW(cRepo.get(1), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(AddTest) {
        Repository<CustomerPtr> cRepo;
        int size = 5;
        CustomerPtr customers[size];

        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Customer>(testId, testAddress, testPhoneNumber, testPassword));
        }

        BOOST_TEST(cRepo.size() == size);
    }

    BOOST_AUTO_TEST_CASE(AddTestException) {
        Repository<CustomerPtr> cRepo;
        BOOST_REQUIRE_THROW(cRepo.add(nullptr), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(FindTest) {
        Repository<CustomerPtr> cRepo;
        std::string findPersonalID = "looking_id";
        CustomerPtr findCustomer = std::make_shared<Customer>(findPersonalID, testAddress, testPhoneNumber, testPassword);
        cRepo.add(findCustomer);

        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Customer>(testId, testAddress, testPhoneNumber, testPassword));
        }

        CustomerPredicate predicate = [findPersonalID](const CustomerPtr &ptr) {
            return ptr->getId() == findPersonalID;
        };
        BOOST_TEST(cRepo.findBy(predicate) == findCustomer);
    }

    BOOST_AUTO_TEST_CASE(SizeTest) {
        Repository<CustomerPtr> cRepo;
        int size = 5;
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            cRepo.add(std::make_shared<Customer>(testId, testAddress, testPhoneNumber, testPassword));
        }

        BOOST_TEST(cRepo.size() == size);
    }

    BOOST_AUTO_TEST_CASE(RemoveTest) {
        Repository<CustomerPtr> cRepo;
        int size = 5;
        CustomerPtr customers[size];
        for (int i = 0; i < size; i++) {
            std::ostringstream sout;
            sout << "012345678" << i;
            customers[i] = std::make_shared<Customer>(testId, testAddress, testPhoneNumber, testPassword);
            cRepo.add(customers[i]);
        }

        cRepo.remove(customers[2]);
        cRepo.remove(customers[3]);

        BOOST_TEST(cRepo.size() == size - 2);
    }


BOOST_AUTO_TEST_SUITE_END()
