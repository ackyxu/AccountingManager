cmake_minimum_required(VERSION 3.18)
project(AccountingManager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# find_package(libpqxx REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES 

src/Records/Database/Database.cpp
deps/sqlite3/sqlite3.c

)

set(HEADERS 
src/Records/Database/Database.h
deps/sqlite3/sqlite3.h
)



# if(TARGET libpqxx::pqxx)
#     message("libpqxx defined!")
# else() 
#     message("not found")
# endif()


add_subdirectory(deps/googletest)
add_executable(AccountingManager 
    main.cpp
    ${SOURCES})
add_executable(UnitTests 
    test/UnitTests.cpp
    ${SOURCES})

target_include_directories(AccountingManager PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Records/Database
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/sqlite3
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/)
    
target_include_directories(UnitTests PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Records/Database
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/sqlite3
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/)

target_link_libraries(UnitTests gtest_main)




enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(GoogleTest)
gtest_discover_tests(UnitTests)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
