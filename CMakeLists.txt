cmake_minimum_required(VERSION 3.18)
project(AccountingManager VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AccountingManager main.cpp)
find_package(libpqxx REQUIRED)
target_link_libraries(AccountingManager libpqxx::pqxx)

if(TARGET libpqxx::pqxx)
    message("libpqxx defined!")
else() 
    message("not found")
endif()

add_subdirectory(deps/googletest)



# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
