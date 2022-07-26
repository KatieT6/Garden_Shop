cmake_minimum_required(VERSION 3.10)

#Configuration parameters of cmake
set(CMAKE_CXX_COMPILER g++)#requires g++ to be available on PATH
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(SOURCE_LIBRARY_FILES
        src/model/Product.cpp include/model/Product.h
        src/model/Plants.cpp include/model/Plants.h
        src/model/GardenAccessories.cpp include/model/GardenAccessories.h
        src/managers/ProductManager.cpp include/managers/ProductManager.h
        src/managers/ShoppingCartManager.cpp include/managers/ShoppingCartManager.h
        src/managers/CustomerManager.cpp include/managers/CustomerManager.h
        src/model/Customer.cpp include/model/Customer.h
        src/model/ShoppingCart.cpp include/model/ShoppingCart.h
        src/model/Address.cpp include/model/Address.h
        src/menu/TerminalMenu.cpp include/menu/TerminalMenu.h
        src/repositories/Repository.cpp include/repositories/Repository.h
        include/model/typedefs.h
        src/exceptions/CustomerException.cpp include/exceptions/CustomerException.h src/exceptions/ProductException.cpp include/exceptions/ProductException.h src/exceptions/ShoppingCartException.cpp include/exceptions/ShoppingCartException.h)

add_library(Library  ${SOURCE_LIBRARY_FILES})

target_include_directories(Library PUBLIC include)

#Source files here
set(SOURCE_FILES
        src/main.cpp)

add_executable(Project ${SOURCE_FILES})

target_include_directories(Project PUBLIC include)

target_link_libraries(Project Library)


#TESTs
enable_testing()
find_package(Boost 1.60.0 COMPONENTS unit_test_framework REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)



#Test source files here
set(SOURCE_TEST_FILES
        test/master.cpp
        test/AddressTest.cpp
        test/CustomerTest.cpp
        test/ProductTest.cpp
        test/ShoppingCartTest.cpp test/CustomerManagerTest.cpp test/ProductManagerTest.cpp test/ShoppingCartManagerTest.cpp test/RepositoryTest.cpp)

add_executable(TestProject ${SOURCE_TEST_FILES})

target_link_libraries(TestProject
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        Library)



add_test(TestProject1 TestProject
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_GetProperties(json)

if (NOT json_POPULATED)
    message("Clonning json")
    FetchContent_Populate(json)
    add_subdirectory(
            ${json_SOURCE_DIR}
            ${json_BINARY_DIR}
    )
endif()

set(nlohmann_json_DIR "${json_BINARY_DIR}")

find_package(nlohmann_json 3.10.5 REQUIRED)

target_link_libraries(Library nlohmann_json::nlohmann_json)
