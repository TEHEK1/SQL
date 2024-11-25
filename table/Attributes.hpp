#include <iostream>

enum class Attributes{
    UNIQUE,
    AUTOINCREMENT,  
    KEY
};

namespace std {
    template <>
    struct hash<Attributes> {
        size_t operator()(Attributes a) const {
            return static_cast<size_t>(a);
        }
    };
}