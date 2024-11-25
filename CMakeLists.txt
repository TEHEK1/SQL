cmake_minimum_required(VERSION 3.16)
project(InMemoryDB)

set(CMAKE_CXX_STANDARD 17)


file(GLOB PARSER ${CMAKE_SOURCE_DIR}/parser/*.*)
file(GLOB TABLE ${CMAKE_SOURCE_DIR}/table/*.*)

add_executable(sql main.cpp ${PARSER}
        parser/RelationTable.hpp)
target_include_directories(sql PUBLIC
        ${CMAKE_SOURCE_DIR}/parser
        ${CMAKE_SOURCE_DIR}/parser/conditions
        ${CMAKE_SOURCE_DIR}/parser/operators
        ${CMAKE_SOURCE_DIR}/table)