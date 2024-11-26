cmake_minimum_required(VERSION 3.16)
project(InMemoryDB)

set(CMAKE_CXX_STANDARD 17)


file(GLOB PARSER ${CMAKE_SOURCE_DIR}/parser/*.*)
file(GLOB PARSER_CONDITIONS ${CMAKE_SOURCE_DIR}/parser/conditions/*.*)
file(GLOB PARSER_OPERATORS ${CMAKE_SOURCE_DIR}/parser/operators/*.*)
file(GLOB PARSER_QUERY ${CMAKE_SOURCE_DIR}/parser/query/*.*)
file(GLOB PARSE_FACTORY ${CMAKE_SOURCE_DIR}/parser/parse_factory/*.*)

file(GLOB TABLE ${CMAKE_SOURCE_DIR}/table/*.*)

add_executable(sql main.cpp ${PARSER_CONDITIONS} ${PARSER} ${PARSER_OPERATORS} ${PARSE_FACTORY} ${PARSER_QUERY} ${TABLE} )
target_include_directories(sql PUBLIC
        ${CMAKE_SOURCE_DIR}/parser
        ${CMAKE_SOURCE_DIR}/parser/conditions
        ${CMAKE_SOURCE_DIR}/parser/operators
        ${CMAKE_SOURCE_DIR}/parser/query
        ${CMAKE_SOURCE_DIR}/table)


file(GLOB TESTS ${CMAKE_SOURCE_DIR}/tests/*.* ${CMAKE_SOURCE_DIR}/tests/tableTest/*.*)


include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip)
FetchContent_MakeAvailable(googletest)

add_executable(unit_test ${TESTS} ${PARSER} ${PARSE_FACTORY} ${PARSER_CONDITIONS} ${PARSER_OPERATORS} ${PARSER_QUERY} ${TABLE})
target_link_libraries(unit_test gtest_main)
#target_compile_options(unit_test PUBLIC -fsanitize=address
#        -fsanitize=undefined)

target_include_directories(unit_test PRIVATE ${gtest_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/parser
        ${CMAKE_SOURCE_DIR}/parser/conditions
        ${CMAKE_SOURCE_DIR}/parser/operators
        ${CMAKE_SOURCE_DIR}/parser/query
        ${CMAKE_SOURCE_DIR}/table)
add_test(NAME unit_test COMMAND unit_test)
#set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)
#set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)