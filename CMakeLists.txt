cmake_minimum_required(VERSION 3.16)
project(InMemoryDB)

set(CMAKE_CXX_STANDARD 17)


file(GLOB PARSER ${CMAKE_SOURCE_DIR}/parser/*.*)

add_executable(sql main.cpp ${PARSER}
        main.cpp)
target_include_directories(sql PUBLIC
        ${CMAKE_SOURCE_DIR}/parser)