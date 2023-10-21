cmake_minimum_required(VERSION 3.18)
project(AccountingManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# find_package(libpqxx REQUIRED)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)


file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*)


set(DEPS 
deps/sqlite3/sqlite3.c
)

set(HEADERS 
deps/sqlite3/sqlite3.h
)


add_subdirectory(deps/googletest)

add_executable(AccountingManager 
    main.cpp
    ${SRC}
    ${DEPS})

    add_executable(UnitTests 
    test/UnitTests.cpp
    ${SRC}
    ${DEPS})

target_include_directories(AccountingManager PUBLIC 
    src/Records/Database
    src/Records/Accounts
    deps/sqlite3)
    
target_include_directories(UnitTests PUBLIC 
    src/Records/Database
    src/Records/Accounts
    deps/sqlite3
    tests/)

target_link_libraries(UnitTests gtest_main)




enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(GoogleTest)
gtest_discover_tests(UnitTests)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
