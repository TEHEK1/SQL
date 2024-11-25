cmake_minimum_required(VERSION 3.16)
project(InMemoryDB)

set(CMAKE_CXX_STANDARD 17)


file(GLOB PARSER ${CMAKE_SOURCE_DIR}/parser/*.*)
file(GLOB PARSER_CONDITIONS ${CMAKE_SOURCE_DIR}/parser/conditions/*.*)
file(GLOB PARSER_OPERATORS ${CMAKE_SOURCE_DIR}/parser/operators/*.*)
file(GLOB PARSER_QUERY ${CMAKE_SOURCE_DIR}/parser/query/*.*)

file(GLOB TABLE ${CMAKE_SOURCE_DIR}/table/*.*)

add_executable(sql main.cpp ${PARSER} ${PARSER_CONDITIONS} ${PARSER_OPERATORS} ${PARSER_QUERY} ${TABLE} )
target_include_directories(sql PUBLIC
        ${CMAKE_SOURCE_DIR}/parser
        ${CMAKE_SOURCE_DIR}/parser/conditions
        ${CMAKE_SOURCE_DIR}/parser/operators
        ${CMAKE_SOURCE_DIR}/parser/query
        ${CMAKE_SOURCE_DIR}/table)



#include(GoogleTest)
#add_executable(FooTest FooUnitTest.cxx)
#gtest_add_tests(TARGET      FooTest
#        TEST_SUFFIX .noArgs
#        TEST_LIST   noArgsTests
#)
#gtest_add_tests(TARGET      FooTest
#        EXTRA_ARGS  --someArg someValue
#        TEST_SUFFIX .withArgs
#        TEST_LIST   withArgsTests
#)
#set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)
#set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)