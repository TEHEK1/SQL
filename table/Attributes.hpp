#pragma once
#include <iostream>

enum class Attributes{
    UNIQUE,
    AUTOINCREMENT,  
    KEY
};
typedef std::unordered_set<Attributes> AttributesSet;

namespace std {
    template <>
    struct hash<Attributes> {
        size_t operator()(Attributes a) const {
            return static_cast<size_t>(a);
        }
    };
}